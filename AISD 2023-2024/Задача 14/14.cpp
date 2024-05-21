#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <fstream>
#include <algorithm>
#include <stack>
#include <climits>
#include <set>



using namespace std;
using ll = long long;

const int MIN_ANHTIHEIGHT = -INT_MIN;
ll pudge;

ifstream fin("tst.in");
ofstream fout("tst.out");

struct TreeNode {
    ll val;
    ll height;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    bool naPuti;
    ll kts;

    int howmuchmore, howmuchless;
    
    TreeNode(ll x) {
        this->val = x;
        this->left = nullptr;
        this->right = nullptr;
        this->height = 0;
        this->parent = nullptr;
        this->naPuti = false;
        this->howmuchless = 0;
        this->howmuchmore = 0;
        this->kts = 0;
    }

    TreeNode(ll x, ll z) {
        this->val = x;
        this->left = nullptr;
        this->right = nullptr;
        this->height = z;
        this->parent = nullptr;
        this->naPuti = false;
        this->howmuchless = 0;
        this->howmuchmore = 0;
        this->kts = 0;
    }

    ll getHeight() {
        return height;
    }

    TreeNode* getLeft() {
        return left;
    }

    TreeNode* getRight() {
        return right;
    }

    bool isLeaf(TreeNode* b) {
        return b->left == nullptr && b->right == nullptr;
    }
};

class BT {
public:
    TreeNode* root;
    vector<TreeNode*> leafs;

    set<ll> toRemove;
    ll depth = MIN_ANHTIHEIGHT;
    int counterJ = 0;
    int counterI = 0;

    BT() : root(nullptr) {}

    TreeNode* getRoot() {
        return root;
    }

    TreeNode* setRoot(TreeNode* val) {
        return this->root = val;
    }

    vector<TreeNode*> getLeafs() {
        return leafs;
    }

    
    

    void findMinPaths(TreeNode* roota) {
        if (roota == nullptr)
            return;
        if (roota->isLeaf(roota) && roota->height > depth)
            depth = roota->height;
        findMinPaths(roota->left);
        findMinPaths(roota->right);
            /*for (const auto& path : paths) {
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i]->val << " ";
                if (i == 0) continue;
                if (path[i]->left) cout << path[i]->left->val << " ";
                if (path[i]->right) cout << path[i]->right->val << " ";
            }
            cout << endl;
        }*/
    }



    void findMinLengthPaths(TreeNode* roota) {
        if (roota == nullptr) return;

        findMinLengthPaths(roota->left);
        if (roota->left != nullptr && roota->left->naPuti) {
            roota->naPuti = true;
            roota->kts = roota->val;
        }
        findMinLengthPaths(roota->right);
        if (roota->right != nullptr && roota->right->naPuti) {
            roota->naPuti = true;
            roota->kts = roota->val;
        }
        if (roota->isLeaf(roota) && roota->height == depth) {
            roota->naPuti = true;
            roota->kts = roota->val;
        }


    }



    /*void traversePathsInOrder(const vector<vector<TreeNode*>>& paths) {
        for (const auto& path : paths) {
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i]->val << " ";
                if (i == 0) continue;
                if (path[i]->left) cout << path[i]->left->val << " ";
                if (path[i]->right) cout << path[i]->right->val << " ";
            }
            cout << endl;
        }
    }*/
    void insert(ll val) {
        if (root == nullptr)
            root = new TreeNode(val, 0);
        insert(root, val);
    }

    void insert(TreeNode* node, ll k) {
        if (k < node->val)
            if (node->left != nullptr)
                insert(node->left, k);
            else
                node->left = new TreeNode(k ,node->height - 1);
        else if (k > node->val)
            if (node->right != nullptr)
                insert(node->right, k);
            else
                node->right = new TreeNode(k, node->height - 1);
    }

    /*void setNodeHeights(TreeNode* node) {
        if (node == nullptr)
            return;

        setNodeHeights(node->left);
        setNodeHeights(node->right);

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getHeight(TreeNode* node) {
        return (node == nullptr) ? -1 : node->height;
    }

    void updateHeights() {
        setNodeHeights(root);
    }*/


    



    void Udali(TreeNode*& root, ll value) {
        TreeNode** ptr = &root;
        while (*ptr != nullptr && (*ptr)->val != value) {
            if (value < (*ptr)->val)
                ptr = &((*ptr)->left);
            else
                ptr = &((*ptr)->right);
        }

        if (*ptr == nullptr)
            return;

        TreeNode* q = *ptr;
        if (q->right == nullptr) {
            *ptr = q->left;
            delete q;
        }
        else if (q->left == nullptr) {
            *ptr = q->right;
            delete q;
        }
        else {
            TreeNode** r = &((*ptr)->left);
            while ((*r)->right != nullptr)
                r = &((*r)->right);

            q->val = (*r)->val;
            q = *r;
            *r = (*r)->left;
            delete q;
        }
    }


    void remove(ll val) {
        Udali(root, val);
    }





    void printInOrder() {
        printInOrder(root);
    }

    void printInOrder(TreeNode* root) {
        if (root == nullptr) return;

        printf("%lld\n", root->val);
        


        printInOrder(root->left);
        printInOrder(root->right);
    }


    void findMidToRemove(TreeNode* nod) {
        findMidToRemoveImpl(nod);
    }

    void findMidToRemoveImpl(TreeNode* nod) {
        
        pudge = root->height - depth + 1;
        if (nod == nullptr) return;
        if (!(nod->left == nullptr))
            nod->left->parent = nod;
        if (!(nod->right == nullptr))
            nod->right->parent = nod;
        if (nod->naPuti) {
                


                if (nod->parent != nullptr && nod->kts < nod->parent->kts) {
                    nod->howmuchmore = nod->parent->howmuchmore + 1;
                    nod->howmuchless = nod->parent->howmuchless;
                }
                else if (nod->parent != nullptr && nod->kts > nod->parent->kts) {
                    nod->howmuchless = nod->parent->howmuchless + 1;
                    nod->howmuchmore = nod->parent->howmuchmore;
                }
            
                if (
                    ((nod->howmuchless == (pudge / 2) + 1) || (nod->howmuchmore == (pudge / 2) + 1))
                    && ((nod->howmuchless <= (1 + pudge / 2)) && (nod->howmuchmore <= (1 + pudge / 2)))) {
                    toRemove.emplace(nod->parent->val);
                    nod->kts = nod->parent->kts;
                }
                else if (nod->howmuchless == nod->howmuchmore && nod->isLeaf(nod)) toRemove.emplace(nod->val);
                
        }

        findMidToRemoveImpl(nod->left);
        findMidToRemoveImpl(nod->right);
    }

    

};



int main() {

    ios_base::sync_with_stdio(false);

    freopen("tst.in", "r", stdin);
    freopen("tst.out", "w", stdout);

    cin.tie(NULL);
    cout.tie(NULL);


    BT tree;
    ll key;
    while (cin >> key) tree.insert(key);
    

    tree.findMinPaths(tree.root);

    if ((-tree.depth + 1) % 2 == 1) {
        tree.findMinLengthPaths(tree.root);
        tree.findMidToRemove(tree.root);
        for (ll znak : tree.toRemove) tree.remove(znak);
    }
    

    
    
    //sort(a.begin(), a.end());
    //for (int i = 0; i < a.size(); i++) tree.remove(a[i]);

    tree.printInOrder();




    return 0;
}