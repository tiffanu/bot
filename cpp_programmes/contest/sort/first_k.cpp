#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class BinHeap {
private:

    static const int N = 1000+1; // max number of elements in heap

    long long heap[N];
    size_t sz;


    void swap(int v, int u) {
        std::swap(heap[v], heap[u]);
    }

    void siftUp(int v) {
        while (v != 1) {
            if (heap[v] > heap[v/2]) {
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
            if (2*v + 1 <= sz && heap[2*v + 1] > heap[2*v]) {
                u = 2*v + 1;
            }

            if (heap[v] < heap[u]) {
                swap(v, u);
                v = u;
            } else {
                break;
            }
        }
    }

public:

    BinHeap() : sz(0) {}

    size_t size() const {
        return sz;
    }

    void insert(int el) {
        if (sz+1 == N) {
            heap[1] = el;
            siftDown(1);
        } else {
            heap[++sz] = el;
            siftUp(sz);
        }
    }

    long long getMax() const {
        return heap[1];
    }

    void extractMax() {
        heap[1] = heap[sz--];
        siftDown(1);
    }
};


const long long mod = 1 << 30;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    BinHeap heap;

    int n, k;
    cin >> n >> k;

    long long a, x, y;
    cin >> a >> x >> y;

    for (int i = 0; i < n; ++i) {
        a = ((a * x) % mod + y) % mod;
        if (heap.size() < 1000 || (heap.size() == 1000 && heap.getMax() > a)) {
            heap.insert(a);
        }
    }

    vector<int> ans;
    int size = heap.size();
    for (int i = 0; i < size; ++i) {
        ans.push_back(heap.getMax());
        heap.extractMax();
    }

    for (int i = size-1; i >= size-k; --i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}