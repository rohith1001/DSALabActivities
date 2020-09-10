#include <iostream>
using namespace std;

class Bigint {
  private:
    string str;

  public:
    Bigint() { str = ""; }
    Bigint(string s) { str = s; }

    Bigint operator+(Bigint &obj) {
        int n1 = str.size() - 1;
        int n2 = obj.str.size() - 1;
        string ans;
        int carry = 0;
        int res;
        while (n1 >= 0 && n2 >= 0) {
            res = (str[n1] - '0') + (obj.str[n2] - '0') + carry;
            if (res > 9) {
                res = res - 10;
                carry = 1;
            } else {
                carry = 0;
            }
            ans += to_string(res);
            n1--;
            n2--;
        }
        while (carry > 0) {
            if (n1 > n2) {
                res = (str[n1] - '0') + carry;
                if (res > 9) {
                    res = res - 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                ans += to_string(res);
                n1--;
            } else if (n2 > n1) {
                res = (obj.str[n2] - '0') + carry;
                if (res > 9) {
                    res = res - 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                ans += to_string(res);
                n2--;
            } else {
                ans += to_string(carry);
                carry = 0;
            }
        }
        ans = string(ans.rbegin(), ans.rend());
        if (n1 > n2 && n1 >= 0) {
            // copy every char from 0 to n1 to temp
            string temp;
            for (int i = 0; i <= n1; i++) {
                temp += str[i];
            }
            temp += ans;
            ans = temp;
        } else if (n2 > n1 && n2 >= 0) {
            string temp;
            for (int i = 0; i <= n2; i++) {
                temp += obj.str[i];
            }
            temp += ans;
            ans = temp;
        }
        ans.erase(0, min(ans.find_first_not_of('0'), ans.size() - 1));
        Bigint myobj(ans);
        return myobj;
    }

    Bigint operator-(Bigint &obj) {
        int n1 = str.size() - 1;
        int n2 = obj.str.size() - 1;
        string ans;
        bool borrow = false;
        int res, a, b;
        while (n1 >= 0 && n2 >= 0) {
            a = str[n1] - '0';
            b = obj.str[n2] - '0';
            if (borrow) {
                if (a > 0) {
                    a--;
                    borrow = false;
                } else {
                    // a is zero here
                    a = a - 1;
                    borrow = true;
                }
            }
            if (a < b) {
                // borrow logic
                a = a + 10;
                borrow = true;
            }
            res = a - b;
            ans += to_string(res);
            n1--;
            n2--;
        }
        while (borrow) {
            a = str[n1] - '0';
            if (a > 0) {
                a--;
                borrow = false;
                n1--;
                ans += to_string(a);
            } else {
                // 0 or less than 0 case
                a--;
                a = a + 10;
                borrow = true;
                n1--;
                ans += to_string(a);
            }
        }
        ans = string(ans.rbegin(), ans.rend());
        if (n1 > n2) {
            // copy every char from 0 to n1 to temp
            string temp;
            for (int i = 0; i <= n1; i++) {
                temp += str[i];
            }
            temp += ans;
            ans = temp;
        }
        ans.erase(0, min(ans.find_first_not_of('0'), ans.size() - 1));
        Bigint myobj(ans);
        return myobj;
    }

    Bigint operator*(Bigint &obj) {
        Bigint b;
        Bigint temp;
        for (int i = str.size() - 1; i >= 0; i--) {
            int a = str[i] - '0';
            cout << "a: " << a << endl;
            string result;
            int carry = 0;
            for (int j = obj.str.size() - 1; j >= 0; j--) {
                int b = obj.str[j] - '0';
                cout << "b: " << b << endl;
                int product = (a * b) + carry;
                cout << "a:" << a << " b:" << b << endl;
                if (product > 9) {
                    carry = product / 10;
                    cout << "setting carry to:" << carry << endl;
                    product = product % 10;
                } else {
                    carry = 0;
                    cout << "Here" << endl;
                }
                cout << "product:" << product << " carry:" << carry << endl;
                result += to_string(product);
            }
            if (carry > 0) {
                result += to_string(carry);
            }
            result = string(result.rbegin(), result.rend());
            cout << "result is: " << result << endl;
            temp.setStr(result);
            b = b + temp;
            result = "";
        }
        return b;
    }

    void print() { cout << str << endl; }

    void setStr(string s) { str = s; }
};

int main() {
    string a, b;
    cin >> a >> b;
    Bigint b1(a);
    Bigint b2(b);
    Bigint b3 = b1 * b2;
    b3.print();
}