#include <iostream>
#include <vector>
#include <string>
#include <set>

using std::vector;
using std::string;
using std::set;

class MinMax {
private:

    set<int> s;

public:

    void insert(int el) {
        s.insert(el);
    }

    int getMin() {
        int ans = *(s.begin());
        s.erase(ans);

        return ans;
    }

    int getMax() {
        int ans = *(--s.end());
        s.erase(ans);

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