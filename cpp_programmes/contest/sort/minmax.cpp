#include <bits/stdc++.h> 

using namespace std;

class MinMax {
private:

    multiset<int> s; // mb 2 бин кучи 

public:

    void insert(int el) {
        s.insert(el);
    }

    int getMin() {
        int ans = *(s.begin());
        s.erase(s.begin());

        return ans;
    }

    int getMax() {
        int ans = *(--s.end());
        s.erase(--s.end());

        return ans;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    MinMax m;

    int q;
    std::cin >> q;

    for (int i = 1; i <= q; ++i) {
        string command;
        std::cin >> command;

        if (command[0] == 'I') {
            int el = std::stoi(command.substr(7, command.size() - 8));

            m.insert(el);

        } else if (command == "GetMin") {

            std::cout << m.getMin() << '\n';

        } else if (command == "GetMax") {

            std::cout << m.getMax() << '\n';

        }
    }
}