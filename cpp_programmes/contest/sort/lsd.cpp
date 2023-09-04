#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Bytes {
    int bytes[8]; // 8 bytes big-ending

    void getBytes(long long x) {
        for (int i = 0; i < 8; ++i) {
            bytes[i] = x & 255;
            x >>= 8;
        }
    }
};

std::ostream& operator<<(std::ostream& out, const Bytes& b) {
    long long x = 0;
    for (int i = 0; i < 8; ++i) {
        x <<= 8;
        x += b.bytes[7-i];
    }
    out << x;
    return out;
}

void sort_bytes(vector<Bytes>& nums, int exp) {
    vector<int> cnt(256, 0);
    int n = nums.size();
    vector<Bytes> ans(n);

    for (int i = 0; i < n; ++i) {
        cnt[nums[i].bytes[exp]]++;
    }

    for (int i = 1; i < 256; ++i) {
        cnt[i] += cnt[i-1];
    }

    for (int i = n-1; i >= 0; --i) {
        ans[--cnt[nums[i].bytes[exp]]] = nums[i];
    }

    nums = ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;

    vector<Bytes> nums(n);
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        nums[i].getBytes(x);
    }

    for (int exp = 0; exp < 8; ++exp) {
        sort_bytes(nums, exp);
    }

    for (int i = 0; i < n; ++i) {
        cout << nums[i] << ' ';
    }
    cout << '\n';
}