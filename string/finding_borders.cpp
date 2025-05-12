
#include<bits/stdc++.h>

using namespace std;


class RollingHashUtil {
    // large random prime. but dont take too large prime such that overflow happens 
    // in between some computation (before taking mod)
    const long long Q = 30158354233661; 
    const int R = 26; // radix size

    const string &s;
    int n; // s.size()

    long long R_POWER;
    long long rolling_hash_left, rolling_hash_right;
    int left, right;
    

    long long posMod(long long x, long long mod) {
        x = x % mod;
        if (x < 0) x += mod;
        return x;
    }

public:
    RollingHashUtil(const string &s): s(s) {
        n = s.size();
        left = 0, right = n - 1;
        R_POWER = 1;

        // compute initial rolling hashes
        rolling_hash_left = (s[0] - 'a') % Q;
        rolling_hash_right = (s[n - 1] - 'a') % Q;
    }

    long long getLeftHash() { return rolling_hash_left; }
    long long getHashRight() { return rolling_hash_right; }

    //* returns false if not possible to increase the window
    bool increaseWindowByOne() {
        if (left == n - 1) return false;
        // update: 
        // left_hash -> left_hash * R  + s[left + 1]
        // right_hash -> R^(something) * s[right - 1] + right_hash
        left += 1;
        rolling_hash_left = ((rolling_hash_left * R) % Q + (s[left] - 'a')) % Q;

        right -= 1;
        R_POWER = (R_POWER * R) % Q;
        rolling_hash_right = ((R_POWER * (s[right] - 'a')) % Q + rolling_hash_right) % Q;
        return true;
    }
};


int main() {
    string s;
    cin >> s;

    RollingHashUtil rollingHashUtil(s);
    vector<int> res;
    for (int len = 1; len < s.size(); ++len) {
        if (rollingHashUtil.getLeftHash() == rollingHashUtil.getHashRight()) {
            res.push_back(len);
        }
        rollingHashUtil.increaseWindowByOne();
    }
    for (int len: res) {
        cout << len << " ";
    }




    return 0;
}