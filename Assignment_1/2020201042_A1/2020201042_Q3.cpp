#include <iostream>
using namespace std;

template <class T> class deque {
  private:
    T *arr;
    int head;
    int tail;
    int max_size;

  public:
    deque() {
        max_size = 1;
        arr = new T[max_size];
        head = -1;
        tail = 0;
    }

    deque(int n, T x) {
        T *temp = new T[n];
        for (int i = 0; i < n; i++) {
            temp[i] = x;
        }
        head = 0;
        tail = n - 1;
        max_size = n;
        arr = temp;
    }

    T &operator[](int n) { return *(arr + ((head + n) % max_size)); }

    void push_back(T x) {
        if (head == -1) {
            if (max_size > 1) {
                // pseudo empty
                head = 0;
                tail = 0;
                arr[tail] = x;
            } else {
                // this means deque is really empty :P
                max_size *= 2;
                T *temp = new T[max_size];
                arr = temp;
                arr[tail] = x;
                head++; // head and tail would be zero here
            }
        } else {
            if (size() == max_size) {
                // that means deque is really full
                int previous_size = size();
                T *temp = new T[(2 * max_size)];
                int temp_idx = 0;
                while (head != tail) {
                    temp[temp_idx] = arr[head];
                    temp_idx++;
                    head = (head + 1) % max_size;
                }
                temp[temp_idx] = arr[head];
                temp[temp_idx + 1] = x;
                tail = previous_size;
                head = 0;
                delete[] arr;
                arr = temp;
                max_size *= 2;
            } else {
                // deque is not empty and also not full
                tail = (tail + 1) % max_size;
                arr[tail] = x;
            }
        }
    }

    void pop_back() {
        if (isEmpty()) {
            cout << "Empty deque...Cannot pop_back() anymore!" << endl;
            exit(0);
        } else {
            if (size() == 1) {
                tail = 0;
                head = -1;
            } else {
                tail = (tail - 1 + max_size) % max_size;
            }
        }
    }

    void push_front(T x) {
        if (head == -1) {
            if (max_size > 1) {
                // pseudo empty
                head = 0;
                tail = 0;
                arr[head] = x;
            } else {
                // this means deque is really empty :P
                max_size *= 2;
                T *temp = new T[max_size];
                arr = temp;
                head++; // head and tail would be zero here
                arr[head] = x;
            }
        } else {
            if (size() == max_size) {
                // that means deque is really full
                T *temp = new T[(2 * max_size)];
                int temp_idx = 1;
                while (head != tail) {
                    temp[temp_idx] = arr[head];
                    temp_idx++;
                    head = (head + 1) % max_size;
                }
                temp[temp_idx] = arr[head];
                head = 0;
                tail = max_size;
                temp[head] = x;
                delete[] arr;
                arr = temp;
                max_size *= 2;
            } else {
                // deque is not empty and also not full
                head = (head - 1 + max_size) % max_size;
                arr[head] = x;
            }
        }
    }

    void pop_front() {
        if (isEmpty()) {
            cout << "Empty deque...Cannot pop_front() anymore!" << endl;
            exit(0);
        } else {
            if (size() == 1) {
                tail = 0;
                head = -1;
            } else {
                head = (head + 1) % max_size;
            }
        }
    }

    T front() { return arr[head]; }

    T back() { return arr[tail]; }

    int size() {
        if (head == -1)
            return 0;
        else if (head > tail)
            return max_size - (head - tail - 1);
        else
            return tail - head + 1;
    }

    void resize(int x, T d) {
        if (x < size()) {
            if (x < 0) {
            } else if (x == 0) {
                head = -1;
                tail = 0;
            } else {
                tail = (head + x - 1) % max_size;
            }
        } else {
            // this means max_size - size() < x
            // we need to create a new temp array, copy etc.
            T *temp = new T[x];
            int temp_idx = 0;
            while (head != tail) {
                temp[temp_idx] = arr[head];
                temp_idx++;
                head = (head + 1) % max_size;
            }
            temp[temp_idx] = arr[head];
            temp_idx++;
            while (temp_idx != (x - 1)) {
                temp[temp_idx] = d;
                temp_idx++;
            }
            temp[temp_idx] = d;
            delete[] arr;
            arr = temp;
            head = 0;
            tail = x - 1;
            max_size = x;
        }
    }

    void clear() {
        head = -1;
        tail = 0;
        delete[] arr;
        max_size = 1;
    }

    bool isEmpty() { return (head == -1); }

    string empty() {
        string str;
        if (isEmpty()) {
            str = "true";
        } else {
            str = "false";
        }
        return str;
    }

    int get_max_size() { return max_size; }

    void display() {
        if (head != -1) {
            int i = head;
            while (i != tail) {
                cout << arr[i] << " ";
                i = (i + 1) % max_size;
            }
            cout << arr[i] << endl;
        }
    }

    ~deque() { delete[] arr; }
};

int main() {
    int q;
    cin >> q;
    q--;
    int constructorChoice;
    cin >> constructorChoice;
    if (constructorChoice == 5) {
        // no parameter for constructor here
        deque<int> d1;
        while (q--) {
            int choice;
            cin >> choice;
            if (choice == 1) {
                int x;
                cin >> x;
                d1.push_front(x);
                d1.display();
            } else if (choice == 2) {
                d1.pop_front();
                d1.display();
            } else if (choice == 3) {
                int x;
                cin >> x;
                d1.push_back(x);
                d1.display();
            } else if (choice == 4) {
                d1.pop_back();
                d1.display();
            } else if (choice == 7) {
                cout << d1.front() << endl;
            } else if (choice == 8) {
                cout << d1.back() << endl;
            } else if (choice == 9) {
                cout << d1.empty() << endl;
            } else if (choice == 10) {
                cout << d1.size() << endl;
            } else if (choice == 11) {
                int x, d;
                cin >> x >> d;
                d1.resize(x, d);
                d1.display();
            } else if (choice == 12) {
                d1.clear();
                d1.display();
            } else if (choice == 13) {
                int n;
                cin >> n;
                cout << d1[n] << endl;
            } else {
                d1.display();
            }
        }
    } else {
        int num, def_val;
        cin >> num >> def_val;
        deque<int> d2(num, def_val);
        while (q--) {
            int choice;
            cin >> choice;
            if (choice == 1) {
                int x;
                cin >> x;
                d2.push_front(x);
                d2.display();
            } else if (choice == 2) {
                d2.pop_front();
                d2.display();
            } else if (choice == 3) {
                int x;
                cin >> x;
                d2.push_back(x);
                d2.display();
            } else if (choice == 4) {
                d2.pop_back();
                d2.display();
            } else if (choice == 7) {
                cout << d2.front() << endl;
            } else if (choice == 8) {
                cout << d2.back() << endl;
            } else if (choice == 9) {
                cout << d2.empty() << endl;
            } else if (choice == 10) {
                cout << d2.size() << endl;
            } else if (choice == 11) {
                int x, d;
                cin >> x >> d;
                d2.resize(x, d);
                d2.display();
            } else if (choice == 12) {
                d2.clear();
                d2.display();
            } else if (choice == 13) {
                int n;
                cin >> n;
                cout << d2[n] << endl;
            } else {
                d2.display();
            }
        }
    }
    return 0;
}
