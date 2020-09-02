#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

template <typename T> struct node {
    T data;
    struct node<T> *next;
};

template <typename T> class stack {
  private:
    struct node<T> *head; // assumption: head itself is top

  public:
    stack() { head = NULL; }

    void push(T t) {
        struct node<T> *temp;
        temp = new node<T>;
        temp->data = t;
        temp->next = head;
        head = temp;
    }

    T pop() {
        T data = head->data;
        struct node<T> *temp;
        temp = head;
        head = head->next;
        free(temp);
        return data;
    }

    bool isEmpty() { return head == NULL; }

    T top() { return head->data; }
};

bool isdigit(char c) {
    if (c - '0' >= 0 && c - '0' <= 9) {
        return true;
    }
    return false;
}

bool isdot(char c) { return c == '.'; }

double compute(double val1, double val2, char op) {
    switch (op) {
    case '*':
        return val1 * val2;
    case '/':
        return val1 / val2;
    case '%':
        return fmod(val1, val2);
    case '+':
        return val1 + val2;
    case '-':
        return val1 - val2;
    }
    return -1;
}

int precedence(char c) {
    if (c == '*' || c == '/' || c == '%') {
        return 2;
    } else if (c == '+' || c == '-') {
        return 1;
    }
    // return 0 in case of parenthesis.
    // Parenthesis is handled seperately
    return 0;
}

double calculate(string exp) {
    stack<double> value_stack;
    stack<char> operator_stack;
    for (int i = 0; i < exp.size(); i++) {
        if (exp[i] == '(') {
            // simply push left bracket
            operator_stack.push(exp[i]);
        } else if (exp[i] == ')') {
            // pop everything and compute till you see left bracket
            while (operator_stack.top() != '(' && !value_stack.isEmpty()) {
                double val2 = value_stack.pop();
                double val1 = value_stack.pop();
                char op = operator_stack.pop();
                value_stack.push(compute(val1, val2, op));
            }
            if (operator_stack.top() == '(') {
                char c = operator_stack.pop();
            }

        } else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '%') {
            // it is an operator in this case
            // if top of operator_stack has greater precedence than
            // the current character. Then pop out the operator and compute
            // the value. Else, simply push the current character onto
            // the operator stack.
            // since all are left associative, equal precedence is computed l to r.
            while (!operator_stack.isEmpty() && precedence(operator_stack.top()) >= precedence(exp[i])) {
                double val2 = value_stack.pop();
                double val1 = value_stack.pop();
                char op = operator_stack.pop();

                value_stack.push(compute(val1, val2, op));
            }
            // otherwise you need to simply push exp[i] onto the operator stack
            operator_stack.push(exp[i]);
        } else if (isdigit(exp[i])) {
            double val = 0;
            // you might need to read multiple digits
            while (isdigit(exp[i]) && i < exp.size()) {
                val = val * 10 + exp[i] - '0';
                i++;
            }
            if (isdot(exp[i])) {
                i++; // ignore the dot
                double k = 10;
                while (isdigit(exp[i]) && i < exp.size()) {
                    val += (exp[i] - '0') / k;
                    i++;
                    k *= 10;
                }
            }
            i--;
            value_stack.push(val);
        }
    }
    // apply remaining operators to all the values
    while (!operator_stack.isEmpty()) {
        double val2 = value_stack.pop();
        double val1 = value_stack.pop();
        char op = operator_stack.pop();

        value_stack.push(compute(val1, val2, op));
    }
    return value_stack.top();
}

int main() {
    string exp;
    cin >> exp;
    double ans = calculate(exp);
    cout << fixed << setprecision(5) << ans << endl;
    return 0;
}
