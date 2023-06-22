#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class BinHeap {
private:

    static const int N = 100'000; // max number of elements in heap
    static const int num = 1'000'000;    // max number of commands

    long long heap[N];
    size_t sz;

    long long pos[num];          // pos[i] -- is such index v, that 
                                 // heap[v] -- is an element, inserted on i_th request

    long long num_insert[N];     // num_insert[v] -- is such index i, that 
                                 // heap[v] was inserted on i_th request

    void swap(int v, int u) {
        std::swap(pos[num_insert[v]], pos[num_insert[u]]);
        std::swap(num_insert[v], num_insert[u]);

        std::swap(heap[v], heap[u]);
    }

    void siftUp(int v) {
        while (v != 1) {
            if (heap[v] < heap[v/2]) {
                swap(v, v/2);
                v /= 2;
            } else {
                break;
            }
        }
    }

    void siftDown(int v) {
        while (2*v <= sz) {
            int u = 2*v;
            if (2*v + 1 <= sz && heap[2*v + 1] < heap[2*v]) {
                u = 2*v + 1;
            }

            if (heap[v] > heap[u]) {
                swap(v, u);
                v = u;
            } else {
                break;
            }
        }
    }

public:

    BinHeap() : sz(0) {}

    void insert(int el, int idx) {           // добавить параметр i, отвечающий за номер запроса
        heap[++sz] = el;
        pos[idx] = sz;
        num_insert[sz] = idx;

        siftUp(sz);
    }

    long long getMin() const {
        return heap[1];
    }

    void extractMin() {
        pos[num_insert[sz]] = 1;
        num_insert[1] = num_insert[sz];
        heap[1] = heap[sz--];

        siftDown(1);
    }

    void decreaseKey(long long idx, long long delta) {
        heap[pos[idx]] -= delta;

        siftUp(pos[idx]);
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    BinHeap b;

    int q;
    std::cin >> q;

    for (int i = 1; i <= q; ++i) {
        string command;
        std::cin >> command;

        if (command == "insert") {
            int el;
            std::cin >> el;

            b.insert(el, i);

        } else if (command == "getMin") {

            std::cout << b.getMin() << '\n';

        } else if (command == "extractMin") {

            b.extractMin();

        } else if (command == "decreaseKey") {
            long long idx, delta;
            std::cin >> idx >> delta;

            b.decreaseKey(idx, delta);
        }
    }
}