
#include<bits/stdc++.h>

using namespace std;
class Solution {
public:

    int i;
    string s;
    
    bool peek(char target) { return i < s.size() && s[i] == target; }

    bool eval_expr() {
        int backup_i = i;
        if (peek('t')) { ++i; return true; }
        if (peek('f')) { ++i; return false; }
        
        char op = s[i++];
        // ignore (
        ++i;
        bool res;
        if (op == '!') {
            res = !eval_expr();
        } else if (op == '&') {
            res = true;
            do {
                res = res && eval_expr();
                if (!peek(',')) break;
                ++i; // ignore ,
            } while (true);
        } else if (op == '|') {
            res = false;
            do {
                bool temp = eval_expr();
                cout << "\ntemp=" << temp;
                res = res || temp;
                if (!peek(',')) break;
                ++i; // ignore ,
            } while (true);
        }
        // ignore )
        ++i;
        printf("\ni=%d, res=%d, last_i=%d", backup_i, res, i);
        return res;
    }

    bool parseBoolExpr(string expression) {
        i = 0;
        s = expression;

        return eval_expr();
    }
};

int main()
{
    cout << "\n\nHello earth\n\n\n";
    string str = "|(&(t,f,t),t)";
    cout << Solution().parseBoolExpr(str);
    




    return 0;
}