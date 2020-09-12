#include <algorithm>
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
        reverse(ans.begin(), ans.end());
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
        reverse(ans.begin(), ans.end());
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

    Bigint divideBy2() {
        string str1 = str;
        int n = str1.size();
        string res;
        int quotient = 0;
        int carry = 0;
        int a = 0;
        int i = 0;
        for (i = 0; i <= n - 2; i++) {
            a = str1[i] - '0';
            a += carry;
            if (a == 0 || a == 1) {
                // take a carry
                i++;
                res += "0";
                a *= 10;
                a += str1[i] - '0';
            }
            quotient = a / 2;
            res += to_string(quotient);
            if (a % 2 == 1) {
                carry = 10;
            } else {
                carry = 0;
            }
        }
        if (i == n - 1) {
            a = str1[n - 1] - '0' + carry;
            quotient = a / 2;
            res += to_string(quotient);
        }
        res.erase(0, min(res.find_first_not_of('0'), res.size() - 1));
        Bigint myBig(res);
        return myBig;
    }

    Bigint operator*(Bigint &obj) {
        Bigint b;
        Bigint temp;
        for (int i = str.size() - 1; i >= 0; i--) {
            int a = str[i] - '0';
            string result;
            int carry = 0;
            for (int j = obj.str.size() - 1; j >= 0; j--) {
                int b = obj.str[j] - '0';
                int product = (a * b) + carry;
                if (product > 9) {
                    carry = product / 10;
                    product = product % 10;
                } else {
                    carry = 0;
                }
                result += to_string(product);
            }
            if (carry > 0) {
                result += to_string(carry);
            }
            reverse(result.begin(), result.end());
            for (int k = 0; k < str.size() - i - 1; k++) {
                result += "0";
            }
            temp.setStr(result);
            b = b + temp;
            result = "";
        }
        return b;
    }

    Bigint factorial() {
        Bigint b_temp("1");
        if (str == "0" || str == "1") {
            return b_temp;
        }

        Bigint s(str);
        Bigint product("1");
        while (s.str != "0") {
            Bigint b_const("1");
            product = product * b_temp;
            b_temp = b_temp + b_const;
            s = s - b_const;
        }
        return product;
    }

    Bigint operator/(Bigint &obj) {
        string str1 = str;
        string str2 = obj.str;
        Bigint b1(str1), b2(str2);
        int res = b1.compare(b2);
        if (res == -1) {
            Bigint temp("0");
            return temp;
        } else if (res == 0) {
            Bigint temp("1");
            return temp;
        }

        Bigint temp1(str2); // this will subtract
        Bigint temp2("1");  // this is for the adding each time to the result
        Bigint result("0"); // this is for storing result
        while (res == 1) {
            result = result + temp2;
            temp2 = temp2 * b2;
            b1 = b1 - temp1;
            temp1 = temp1 * b2;
            res = b1.compare(temp1);
        }
        if (res == 0) {
            result = result + temp2;
            return result;
        }

        res = b1.compare(b2);
        Bigint count("1");
        Bigint const_one("1");
        Bigint sub_factor(obj.str);
        while (res == 1) {
            b1 = b1 - sub_factor;
            result = result + count;
            count = count + const_one;
            sub_factor = count * b2;
            res = b1.compare(sub_factor);
        }

        res = b1.compare(b2);
        count.setStr("1");
        const_one.setStr("1");
        while (res == 1) {
            b1 = b1 - b2;
            result = result + const_one;
            res = b1.compare(b2);
        }

        const_one.setStr("1");
        if (res == 0) {
            result = result + const_one;
        }
        return result;
    }

    Bigint operator%(Bigint &obj) {
        string str1 = str;
        string str2 = obj.str;
        Bigint b1(str1), b2(str2);
        int res = b1.compare(b2);
        if (res == -1) {
            return b1;
        } else if (res == 0) {
            Bigint temp("0");
            return temp;
        }

        Bigint c = b1 / b2;
        Bigint product = b2 * c;
        Bigint modulo = b1 - product;

        return modulo;
    }

    Bigint euclid_gcd(Bigint &obj) {
        string str1 = str;
        string str2 = obj.str;
        Bigint b1(str1), b2(str2);
        Bigint const_zero("0");
        int res = b2.compare(const_zero);
        while (res != 0) {
            Bigint temp = b2;
            b2 = b1 % b2;
            b1 = temp;
            res = b2.compare(const_zero);
        }
        return b1;
    }

    Bigint custom_gcd(Bigint &obj) {
        string str1 = str;
        string str2 = obj.str;
        Bigint b1(str1), b2(str2);
        Bigint const_zero("0");
        Bigint const_two("2");
        int res;

        res = b1.compare(b2);
        if (res == 0) {
            return b1;
        }

        res = b1.compare(const_zero);
        if (res == 0) {
            // b1 is zero
            return b2;
        }

        res = b2.compare(const_zero);
        if (res == 0) {
            // b2 is zero
            return b1;
        }

        if (b1.isEven()) {
            // b1 is even
            if (!b2.isEven()) {
                // b2 is odd
                Bigint temp(str1);
                temp = temp.divideBy2();
                return temp.custom_gcd(b2);
            } else {
                // means both b1 and b2 are even
                Bigint temp1(str1);
                Bigint temp2(str2);
                temp1 = temp1.divideBy2();
                temp2 = temp2.divideBy2();
                return (temp1.custom_gcd(temp2) * const_two);
            }
        }

        // its here, that means b1 is odd
        if (b2.isEven()) {
            Bigint temp2(str2);
            temp2 = temp2.divideBy2();
            return b1.custom_gcd(temp2);
        }

        // its here that means b1 and b2 are both odd
        res = b1.compare(b2);

        if (res == 1) {
            Bigint temp1(str1);
            temp1 = temp1 - b2;
            return temp1.custom_gcd(b2);
        }

        // its here that means b1 <= b2
        Bigint temp2(str2);
        temp2 = temp2 - b1;
        return temp2.custom_gcd(b1);
    }

    Bigint power(Bigint b1, int x) {
        string a = b1.str;
        bool append_minus = false;
        if (a[0] == '-') {
            if (x % 2 == 1) {
                append_minus = true;
            }
            a = a.substr(1, a.size() - 1);
        }

        Bigint bigNum(a);
        Bigint bigAns("1");
        while (x != 0) {
            if ((x % 2) == 1) {
                bigAns = bigAns * bigNum;
                x = x - 1;
            } else {
                bigNum = bigNum * bigNum;
                x = x >> 1;
            }
        }

        if (append_minus) {
            string temp = "-";
            temp += bigAns.str;
            bigAns.setStr(temp);
        }

        return bigAns;
    }

    int compare(Bigint b) {
        string str1 = str;
        string str2 = b.str;
        if (str1.size() > str2.size()) {
            return 1;
        } else if (str1.size() < str2.size()) {
            return -1;
        }
        int n1 = 0;
        int n2 = 0;
        while (n1 != str1.size() && n2 != str2.size()) {
            int x = str1[n1] - '0';
            int y = str2[n2] - '0';
            if (x < y)
                return -1;
            else if (x > y)
                return 1;
            n1++;
            n2++;
        }
        return 0;
    }

    bool isEven() {
        string str1 = str;
        int n = str1.size();
        if (str[n - 1] == '0' || str[n - 1] == '2' || str[n - 1] == '4' || str[n - 1] == '6' || str[n - 1] == '8') {
            return true;
        }
        return false;
    }

    void print() { cout << str << endl; }

    void setStr(string s) { str = s; }
};

int main() {
    int q;
    cin >> q;

    while (q--) {
        int choice;
        cin >> choice;

        if (choice == 1) {
            string x;
            cin >> x;
            int y;
            cin >> y;
            Bigint num1(x);
            Bigint z = num1.power(num1, y);
            z.print();
        } else if (choice == 2) {
            string x, y;
            cin >> x >> y;
            Bigint num1(x), num2(y);
            Bigint z = num1.custom_gcd(num2);
            z.print();
        } else if (choice == 3) {
            string x;
            cin >> x;
            Bigint num1(x);
            num1 = num1.factorial();
            num1.print();
        }
    }
    return 0;
}
