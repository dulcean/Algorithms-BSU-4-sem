#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

unordered_map<char, char> table = {
    {'I', '1'}, {'J', '1'},
    {'A', '2'}, {'B', '2'}, {'C', '2'},
    {'D', '3'}, {'E', '3'}, {'F', '3'},
    {'G', '4'}, {'H', '4'},
    {'K', '5'}, {'L', '5'},
    {'M', '6'}, {'N', '6'},
    {'P', '7'}, {'R', '7'}, {'S', '7'},
    {'T', '8'}, {'U', '8'}, {'V', '8'},
    {'W', '9'}, {'X', '9'}, {'Y', '9'},
    {'O', '0'}, {'Q', '0'}, {'Z', '0'},
    {'0' , '0'},
    {'1', '1'},
    {'2', '2'},
    {'3', '3'},
    {'4', '4'},
    {'5', '5'},
    {'6', '6'},
    {'7', '7'},
    {'8' , '8'},
    {'9', '9'}
};

const int P = 31;
const int MOD = 1e9 + 7;

vector<long long> p_pow, h;
void compute_hashes(const string& s) {
    p_pow.resize(s.size());
    h.resize(s.size());
    p_pow[0] = 1;
    h[0] = s[0];
    for (size_t i = 1; i < s.size(); ++i) {
        p_pow[i] = (p_pow[i - 1] * P) % MOD;
        h[i] = (h[i - 1] + s[i] * p_pow[i]) % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string number;
    fin >> number;

    int n;
    fin >> n;

    vector<string> words(n);
    unordered_map<int, unordered_map<long long, int>> word_to_indices;
    for (int i = 0; i < n; ++i) {
        fin >> words[i];
        long long word_hash = 0;
        for (char c : words[i]) {
            word_hash = (word_hash * P + table[c]) % MOD;
        }
        if (word_to_indices[words[i].size()].count(word_hash) == 0) {
            word_to_indices[words[i].size()][word_hash] = i;
        }
    }

    compute_hashes(number);

    vector<int> dp(number.size() + 1, 1e9);
    vector<int> prev(number.size() + 1, -1);
    vector<int> id(number.size() + 1, -1);

    dp[0] = 0;
    for (int i = 0; i < number.size(); ++i) { // dp[i] = min(dp[j] + 1)
        if (dp[i] == 1e9) continue;
        long long hash_value = 0;
        for (int j = i; j < number.size() && (j - i + 1 <= 100); ++j) {
                hash_value = (hash_value * P + number[j]) % MOD;
                if (word_to_indices[j - i + 1].count(hash_value)) {
                    int k = word_to_indices[j - i + 1][hash_value];
                    if (dp[j + 1] > dp[i] + 1) {
                        dp[j + 1] = dp[i] + 1;
                        prev[j + 1] = i;
                        id[j + 1] = k;
                    }
                }
        }
    }

    if (dp[number.size()] == 1e9) {
        fout << "No solution" << endl;
    }
    else {
        vector<string> answer;
        for (int i = number.size(); i > 0; i = prev[i]) {
            answer.push_back(words[id[i]]);
        }
        reverse(answer.begin(), answer.end());

        fout << answer.size() << endl;
        for (const string& word : answer) {
            fout << word << " ";
        }
    }

    return 0;
}