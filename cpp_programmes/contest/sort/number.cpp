#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using std::vector;
using std::string;

bool cmp_str(const string& lhs, const string& rhs) {
    return lhs + rhs > rhs + lhs;
}

int main() {
    vector<string> arr;

    string tmp;
    std::ifstream in("number.in"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, tmp))
        {
            arr.push_back(tmp);
        }
    }
    in.close();

    std::sort(arr.begin(), arr.end(), cmp_str);

    std::ofstream out("number.out");
    if (out.is_open()) {
        for (int j = 0; j < arr.size(); j++) {
            out << arr[j];
        }
    }
    out.close();
}