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
                T *temp = new T[(2 * max_size)];
                int temp_idx = 0;
                while (head != tail) {
                    temp[temp_idx] = arr[head];
                    temp_idx++;
                    head = (head + 1) % max_size;
                }
                temp[temp_idx] = arr[head];
                temp[temp_idx + 1] = x;
                delete[] arr;
                arr = temp;
                head = 0;
                tail = size();
                max_size *= 2;
            } else {
                // deque is not empty and also not full
                tail = (tail + 1) % max_size;
                arr[tail] = x;
            }
        }
    }

    void pop_back() {
        if (empty()) {
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
        if (empty()) {
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
            cout << "Resizing into a smaller size...Not allowed" << endl;
        } else if (max_size - size() >= x) {
            // this means no need of new memory
            if (head == -1) {
                for (int i = 0; i < x; i++) {
                    arr[i] = d;
                }
                head = 0;
                tail = x - 1;
            } else {
                // just let old elements as it is
                // copy after rear
                int temp_idx = (tail + 1) % max_size;
                int n = x - size();
                while (n--) {
                    arr[temp_idx] = d;
                    temp_idx = (temp_idx + 1) % max_size;
                }
                tail = (tail + x) % max_size;
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
        }
    }

    void clear() {
        head = -1;
        tail = 0;
    }

    bool empty() { return (head == -1); }

    int get_max_size() { return max_size; }

    ~deque() { delete[] arr; }
};

int main() {
    deque<int> d(2, 0);
    cout << "Initial pseudo size of d is: " << d.size() << endl;
    cout << "Initial max_size of d is: " << d.get_max_size() << endl;
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 10; i++) {
            d.push_front(i);
            cout << "j is: " << j << endl;
            cout << "Pushing front " << i << endl;
            cout << "Pseudo size is: " << d.size() << endl;
            cout << "Max size is: " << d.get_max_size() << endl;
            cout << "-----------------------------------" << endl;
        }
        for (int i = 0; i < d.size(); i++) {
            cout << d[i] << " ";
        }
        cout << "Clearing..." << endl;
        cout << "Gone..." << endl;
        d.clear();
        cout << "Attempting to pop_front" << endl;
        d.pop_front();
        cout << endl;
        for (int i = d.size() - 1; i >= 0; i--) {
            d.pop_front();
            cout << "j is: " << j << endl;
            cout << "Popping front " << i << endl;
            cout << "Pseudo size is: " << d.size() << endl;
            cout << "Max size is: " << d.get_max_size() << endl;
            cout << "-----------------------------------" << endl;
        }
        for (int i = 0; i < d.size(); i++) {
            cout << "Not here" << endl;
            cout << d[i] << " ";
        }
        cout << endl;
    }
    cout << "Hello" << endl;
    for (int i = 0; i < d.size(); i++) {
        cout << d[i] << endl;
    }
    return 0;
}
