#include <iostream>
#include <vector>
#include <string>

class BigInt {
private:

    static const int radix = 1'000'000'000;

    std::vector<int> body; 

    size_t size;
    int sign; // 0 is =0; 1 is >0; -1 is <0

public:

    friend std::ostream& operator<<(std::ostream&, const BigInt&);
    friend std::istream& operator>>(std::istream&, const BigInt&);

    BigInt() : size(0), sign(0) {
        // body.clear();
    }

    BigInt(int x) : BigInt() {
        if (x < 0) {
            x = -x;
            sign = -1;
        }

        size++;
        body.push_back(x % radix);

        if (x / radix) {
            body.push_back(x / radix);
            size++;
        }
    }

    BigInt(const BigInt& bi) : body(bi.body), size(bi.size), sign(bi.sign) {}

    BigInt& operator=(const BigInt& bi) {
        body = bi.body;
        size = bi.size;
        sign = bi.sign;
        return *this;
    }

    ~BigInt() {}

    std::string toString() const {
        std::string str;
        if (sign == -1) str += '-';

        for (size_t i = size; i > 0; i--) {
            std::string frame = std::to_string(body[i-1]);
            if (i != size) {
                for (int j = 0; j + frame.size() < 9; str += '0', j++); // adding zeros 
            }
            str += frame;
        }

        return str;
    }

    BigInt operator+(const BigInt& bi) const {
    }

    BigInt operator-(const BigInt& bi) const;

    BigInt operator*(const BigInt& bi) const;

    BigInt operator/(const BigInt& bi) const;

    BigInt operator%(const BigInt& bi) const;


    BigInt& operator+=(const BigInt& bi) {
        size_t bi_size = bi.size;
        if (sign == bi.sign) {
            do {
                ++size;
                body.push_back(0);
            } while (size <= bi_size);

            for (size_t i = 0; i < size - 1; i++) {
                if (i < bi.size) {
                    body[i] += bi.body[i];
                }
                if (i && body[i-1] >= radix) {
                    ++body[i];
                    body[i-1] -= radix;
                }
            }

            if (!body[size - 1]) {
                body.pop_back();
                --size;
            }
        } else {
            // return *this -= -bi;
        }
        return *this;
    }

    BigInt& operator-=(const BigInt& bi);

    BigInt& operator*=(const BigInt& bi);

    BigInt& operator/=(const BigInt& bi);

    BigInt& operator%=(const BigInt& bi);


    BigInt operator-() const {
        BigInt copy = *this;
        copy.sign = -copy.sign;
        return copy;
    }

    BigInt operator++();

    // BigInt operator();    : increment and dicrement

    // maybe define it beyond class
    
    bool operator==(const BigInt& bi) const {
        if (size == bi.size) {
            if (sign == bi.sign) {
                if (body == bi.body) {
                    return true;
                }
                return false;
            }
            return false;
        }
        return false;
    }

    bool operator!=(const BigInt& bi) const {
        return !(*this == bi);
    }

    bool operator<(const BigInt& bi) const {
        if (sign == bi.sign) {
            if (size == bi.size) {
                for (size_t i = size; i > 0; i--) {
                    if (body[i-1] != bi.body[i-1]) {
                        return (sign == 1) ? (body[i-1] < bi.body[i-1]) : (body[i-1] > bi.body[i-1]);
                    }
                }
                return false;
            }
            return (sign == 1) ? (size < bi.size) : (size > bi.size);
        }
        return (sign < bi.sign);
    }

    bool operator>(const BigInt& bi) const {
        return !(*this < bi || *this == bi);
    }

    bool operator<=(const BigInt& bi) const {
        return (*this < bi || *this == bi);
    }

    bool operator>=(const BigInt& bi) const {
        return !(*this < bi);
    }
};

std::ostream& operator<<(std::ostream& out, const BigInt& bi) {
    out << bi.toString();
    return out;
}

std::istream& operator>>(std::istream& in, const BigInt& bi);

int main() {
    BigInt b(-1234567890);
    BigInt a = -b;
    // for (int i = 0; i < 6; i++) {
    //   a += 12332100;
    // }
    a += 1;
    std::cout << b << '\n' << a << '\n' << (a < b);
}