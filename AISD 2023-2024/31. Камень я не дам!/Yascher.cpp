#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;
const int MOD = 1e9 + 7;
#define ll long long

ll _hash(const string& str) {
    ll hashnum = 0;
    for (char c : str) {
        hashnum = (hashnum * 31 + c) % MOD;
    }
    return hashnum;
}

ll _hash(const vector<string>& matrix) {
    ll hashnum = 0;
    for (const string& row : matrix) {
        hashnum = (hashnum * 31 + _hash(row)) % MOD;
    }
    return hashnum;
}


size_t hashString(const string& str) {
    const size_t BASE = 257;
    size_t hashValue = 0;
    for (char ch : str) {
        hashValue = hashValue * BASE + ch;
    }
    return hashValue;
}

size_t hashSubmatrix(const vector<vector<char>>& submatrix) {
    const size_t BASE = 257;
    size_t hashValue = 0;
    for (const auto& row : submatrix) {
        for (char ch : row) {
            hashValue = hashValue * BASE + ch;
        }
    }
    return hashValue;
}
vector<pair<short, short>> fillVector(short M, short N) {
    vector<pair<short, short>> traversal;
    for (short i = 1; i <= M; ++i) {
        for (short j = 1; j <= N; ++j) {
            if (M % i == 0 && N % j == 0) {
                traversal.push_back({ i, j });
            }
        }
    }
    return traversal;
}


void _findUniqueSubmatrix(const std::vector<std::pair<short, short>>& obhod,
    const std::vector<std::vector<char>>& matrix,
    std::vector<std::pair<short, short>>& ans) {
    int numRows = matrix.size();
    int numCols = matrix[0].size();
    std::unordered_set<std::string> hashSet;
    std::unordered_set<int> divisors;
    for (short b = 1; b <= numCols; ++b) {
        if (numCols % b == 0)
            divisors.insert(b);
    }

    for (int katoe = 0; katoe < obhod.size(); katoe++) {
        short a = obhod[katoe].first;
        short b = obhod[katoe].second;

        if (b != 1 && divisors.find(b) == divisors.end())
            continue;

        hashSet.clear();
        int ssize = (numRows * numCols) / (a * b);
        hashSet.reserve(ssize * 2);
        bool foundDuplicate = false;

        for (int i = 0; i < numRows && !foundDuplicate; i += a) {
            for (int j = 0; j < numCols && !foundDuplicate; j += b) {
                char* submatrix = new char[a * b + 1];
                int ind = 0;
                for (int k = i; k < i + a; ++k) {
                    for (int l = j; l < j + b; ++l) {
                        submatrix[ind] = matrix[k][l];
                        ++ind;
                    }
                }
                if (!hashSet.insert(string(submatrix, a * b)).second) {
                    foundDuplicate = true;
                }
                delete[] submatrix;
            }
        }

        if (!foundDuplicate) {
            ans.emplace_back(a, b);
        }
    }

    std::sort(ans.begin(), ans.end(), [](const std::pair<short, short>& a, const std::pair<short, short>& b) {
        int areaA = a.first * a.second;
        int areaB = b.first * b.second;
        return areaA < areaB || (areaA == areaB && a.first < b.first);
        });
}









int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    short M = 0;
    short N = 0;

    cin >> M >> N;

    vector<vector<char>> matrix(M, vector<char>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> matrix[i][j];
        }
    }

    vector <pair <short, short>> obhod = fillVector(M, N);
    /*for (int i = 0; i < obhod.size(); i++) {
        cout << obhod[i].first << " " << obhod[i].second << "\n";
    }
    cout << "\n";*/

    vector<pair<short, short>> submatrices;
    _findUniqueSubmatrix(obhod, matrix, submatrices);
    for (int i = 0; i < submatrices.size(); i++) {
        cout << submatrices[i].first << " " << submatrices[i].second << "\n";
    }
    //answer = _findUniqueSubmatrix(obhod, matrix);
    //cout << answer[0].first << " " << answer[0].second;
    return 0;
}