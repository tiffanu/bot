#include <iostream>
#include <vector>
#include <array>
#include <string>

class BigInteger {
private:

    static const int radix = 1'000'000'000;

    std::vector<int> body; 

    size_t size;
    int sign; // 0 is =0; 1 is >0; -1 is <0


    void chech_if_zero() {
        if (size == 1 && body[0] == 0) {
            sign = 0;
        }
    }

    void remove_leading_zeros() {
        size_t i = size - 1;
        while (i > 0 && body[i] == 0) {
            --size;
            body.pop_back();
            --i;
        }
        chech_if_zero();
    }


public:

    friend class Rational;

    friend std::ostream& operator<<(std::ostream&, const BigInteger&);
    friend std::istream& operator>>(std::istream&, BigInteger&);


    BigInteger() : size(1), sign(0) {
        body.push_back(0);
    }

    BigInteger(int x) : BigInteger() {
        if (x < 0) {
            x = -x;
            sign = -1;
        }

        body[0] = x % radix;
        if (x > 0 && sign == 0) {
            sign = 1;
        }

        if (x / radix) {
            body.push_back(x / radix);
            size++;
        }
    }

    BigInteger(const BigInteger& bi) : body(bi.body), size(bi.size), sign(bi.sign) {}

    BigInteger& operator=(const BigInteger& bi) {
        body = bi.body;
        size = bi.size;
        sign = bi.sign;
        return *this;
    }

    ~BigInteger() {}


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


    friend BigInteger abs(const BigInteger&);
    friend BigInteger tenth_power(size_t);
    friend bool isEven(const BigInteger&);


    BigInteger& operator+=(const BigInteger& bi) {
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
                if (i && body[i-1] >= radix) {        // so complicated bc of  a+=a 
                    ++body[i];
                    body[i-1] -= radix;
                }
            }

            remove_leading_zeros();

        } else {
            return (*this -= -bi);
        }

        return *this;
    }

    BigInteger& operator-=(const BigInteger& bi) {
        if (sign == -bi.sign) {
            return (*this += -bi);
        }
        
        BigInteger first_bi = *this, second_bi = bi;
        if (abs(first_bi) < abs(bi)) {
            std::swap(first_bi, second_bi);
        }
        first_bi.sign = (*this >= bi) ? 1 : -1;

        while (second_bi.size < first_bi.size) {
            ++second_bi.size;
            second_bi.body.push_back(0);
        }
        for (size_t i = 0; i < first_bi.size; ++i) {
            first_bi.body[i] -= second_bi.body[i];
            if (first_bi.body[i] < 0) {
                first_bi.body[i] += radix;
                first_bi.body[i+1] -= 1;
            }
        }

        first_bi.remove_leading_zeros();

        return (*this = first_bi);
    }

    BigInteger& operator*=(const BigInteger& bi) {
        BigInteger res;
        while (res.size <= size + bi.size) {
            ++res.size;
            res.body.push_back(0);
        }
        res.sign = sign * bi.sign;

        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0, carry = 0; j < bi.size || carry; ++j) {
                long long curr = res.body[i+j] + body[i] * 1ll * ((j < bi.size) ? bi.body[j] : 0) + carry;
                carry = int(curr / radix);
                res.body[i+j] = int(curr % radix);
            }
        }

        res.remove_leading_zeros();

        return (*this = res);
    }

    void shift_right() {
        body.push_back(body.back());
        ++size;
        for (size_t i = size-2; i > 0; --i) {
            body[i] = body[i-1];
        }
        body[0] = 0;
    }

    BigInteger& operator/=(const BigInteger& bi) {
        if (bi == 0) throw "Dividing by zero\n";

        BigInteger b = bi;
        b.sign = 1;

        BigInteger res, curr;
        res.body.resize(size);
        res.size = size;

        for (long long i = static_cast<long long>(size) - 1; i >= 0; --i) {
            curr.sign = 1;
            curr.shift_right();
            curr.body[0] = body[i];
            curr.remove_leading_zeros();

            int x = 0, l = 0, r = radix;
            while (l <= r) {
                int mid = (l + r) / 2;
                BigInteger t = b * mid;
                if (t <= curr) {
                    x = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }

            res.body[i] = x;
            curr -= (b * x);

        }

        res.sign = sign * bi.sign;
        res.remove_leading_zeros();

        return (*this = res);
    }

    BigInteger& operator%=(const BigInteger& bi) {
        BigInteger r = (*this) - ((*this) / bi)*bi;
        return (*this = r);
    }


    BigInteger operator-() const {
        BigInteger copy = *this;
        copy.sign = -copy.sign;
        return copy;
    }


    BigInteger& operator++() {
        return (*this += 1);
    }

    BigInteger operator++(int) {
        *this += 1;
        return (*this - 1);
    }

    BigInteger& operator--() {
        return (*this -= 1);
    }

    BigInteger operator--(int) {
        *this -= 1;
        return (*this + 1);
    }
    

    explicit operator bool() const {
        return (*this != 0);
    }

    friend BigInteger operator+(const BigInteger&, const BigInteger&);
    friend BigInteger operator-(const BigInteger&, const BigInteger&);
    friend BigInteger operator*(const BigInteger&, const BigInteger&);
    friend BigInteger operator/(const BigInteger&, const BigInteger&);
    friend BigInteger operator%(const BigInteger&, const BigInteger&);


    friend bool operator<(const BigInteger&, const BigInteger&);
    friend bool operator>(const BigInteger&, const BigInteger&);
    friend bool operator>=(const BigInteger&, const BigInteger&);
    friend bool operator<=(const BigInteger&, const BigInteger&);
    friend bool operator==(const BigInteger&, const BigInteger&);
    friend bool operator!=(const BigInteger&, const BigInteger&);
};


BigInteger operator""_bi(unsigned long long n) {
    return BigInteger(n);
}
 

bool operator==(const BigInteger& a, const BigInteger& b) {
    if (a.size == b.size) {
        if (a.sign == b.sign) {
            if (a.body == b.body) {
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

bool operator!=(const BigInteger& a, const BigInteger& b) {
    return !(a == b);
}

bool operator<(const BigInteger& a, const BigInteger& b) {
    if (a.sign == b.sign) {
        if (a.size == b.size) {
            for (size_t i = a.size; i > 0; i--) {
                if (a.body[i-1] != b.body[i-1]) {
                    return (a.sign == 1) ? (a.body[i-1] < b.body[i-1]) : (a.body[i-1] > b.body[i-1]);
                }
            }
            return false;
        }
        return (a.sign == 1) ? (a.size < b.size) : (a.size > b.size);
    }
    return (a.sign < b.sign);
}

bool operator>(const BigInteger& a, const BigInteger& b) {
    return !(a < b || a == b);
}

bool operator<=(const BigInteger& a, const BigInteger& b) {
    return (a < b || a == b);
}

bool operator>=(const BigInteger& a, const BigInteger& b) {
    return !(a < b);
}


BigInteger operator+(const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    return (copy += b);
}

BigInteger operator-(const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    return (copy -= b);
}

BigInteger operator*(const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    return (copy *= b);
}

BigInteger operator/(const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    return (copy /= b);
}

BigInteger operator%(const BigInteger& a, const BigInteger& b) {
    BigInteger copy = a;
    return (copy %= b);
}


std::ostream& operator<<(std::ostream& out, const BigInteger& bi) {
    out << bi.toString();
    return out;
}

std::istream& operator>>(std::istream& in, BigInteger& bi) {
    std::string input;
    in >> input;

    bi = BigInteger(0);
    bi.sign = 1;

    size_t start = 0;
    if (input[0] == '-') {
        bi.sign = -1;
        start = 1;
    } else if (input[0] == '+') {
        start = 1;
    }

    while (start < input.length() && input[start] == '0') {
        ++start;
    }

    if (start == input.length()) {
        bi = BigInteger(0);
    } else {
        input = input.substr(start);

        bi.size = 0;
        bi.body.pop_back();
        for (size_t i = input.length(); i >= 9; i -= 9) {
            std::string str = input.substr(i-9, 9);
            bi.body.push_back(std::stoi(str));
            ++bi.size;
        }
        if (input.length() % 9) {
            bi.body.push_back(std::stoi(input.substr(0, input.length() % 9)));
            ++bi.size;
        }
    }

    return in;
}

bool isEven(const BigInteger& bi) {
    return (bi.body[0] % 2 == 0);
}

BigInteger abs(const BigInteger& bi) {
    BigInteger a(bi);
    a.sign = (a != 0);
    return a;
}

BigInteger gcd(BigInteger a, BigInteger b) {
    while (a != 0 && b != 0) {
        if (a >= b) a %= b;
        else b %= a;
    }
    return a+b;
}

// BigInteger gcd(BigInteger a, BigInteger b) {
//     while (a != 0 && b != 0) {
//         if (a >= b) a -= b;
//         else b -= a;
//     }
//     return a+b;
// }

// BigInteger gcd(BigInteger a, BigInteger b) {
//     if (a == 0 || b == 0) {
//         return a+b;
//     }
//     if (isEven(a) && isEven(b)) {
//         return 2*gcd(a/2, b/2);
//     } else if (isEven(a)) {
//         return gcd(a/2, b);
//     } else if (isEven(b)) {
//         return gcd(a, b/2);
//     }
//     return gcd(b,a%b);
// }

BigInteger tenth_power(size_t degree) {
    BigInteger res;
    while (degree >= 9) {
        ++res.size;
        res.body.push_back(0);
        degree -= 9;
    }

    res.body.back() = 1; 
    for (size_t i = 0; i < degree; ++i) {
        res.body.back() *= 10;
    }

    res.sign = 1;

    return res;
}


class Rational {
private:

    BigInteger numerator, denominator; // num \in Z    den \in N

    void reduce() {
        BigInteger d = gcd(abs(numerator), abs(denominator));
        if (d < 0) {
            d = -d;
        }
        numerator /= d;
        denominator /= d;
    }

    void set_null() {
        if (numerator == 0) {
            denominator = 1;
        }
    }

    void change_signs() {
        if (denominator < 0) {
            denominator = -denominator;
            numerator = -numerator;
        }
    }

public:

    Rational() : numerator(0), denominator(1) {}

    Rational(int x) {
        numerator = x;
        denominator = 1;
    }

    Rational(BigInteger bi) {
        numerator = bi;
        denominator = 1;
    }

    Rational(const Rational& r) : numerator(r.numerator), denominator(r.denominator) {}

    Rational& operator=(const Rational& r) {
        numerator = r.numerator;
        denominator = r.denominator;
        return *this;
    }

    ~Rational() {}


    std::string toString() const {
        std::string str = numerator.toString();
        if (denominator != 1) {
            str += '/' + denominator.toString();
        }
        return str;
    }

    std::string asDecimal(size_t precision = 0) const {
        std::string str;
        BigInteger q = numerator / denominator, r = numerator % denominator;
        if (numerator < 0) {
            r = -r;
            str += '-';
        }

        str += abs(q).toString();
        if (r != 0 && precision > 0) {
            str += '.';
            BigInteger power = tenth_power(precision);

            r *= power;
            r /= denominator;  

            std::string r_str = r.toString();
            while (r_str.length() < precision) {
                str += '0';
                r_str += '0';
            }
            str += r.toString();
            while (str.back() == '0') {
                str.pop_back();
            }
        }

        return str;
    }


    Rational& operator+=(const Rational& r) {
        numerator = numerator*r.denominator + r.numerator*denominator;
        denominator *= r.denominator;

        set_null();
        reduce();
        return *this;
    }

    Rational& operator-=(const Rational& r) {
        numerator = numerator*r.denominator - r.numerator*denominator;
        denominator *= r.denominator;

        set_null();
        reduce();
        return *this;
    }

    Rational& operator*=(const Rational& r) {
        numerator *= r.numerator;
        denominator *= r.denominator;

        set_null();
        reduce();
        return *this;
    }

    Rational& operator/=(const Rational& r) {
        if (r == Rational(0)) {
            throw "dividing by zero\n";
        }

        numerator *= r.denominator;
        denominator *= r.numerator;

        change_signs();
        set_null();
        reduce();
        return *this;
    }

    Rational operator-() {
        Rational copy(*this);
        copy.numerator.sign *= -1;
        return copy;
    }


    explicit operator double() const {
        return std::stod(asDecimal(30));
    }


    friend Rational operator+(const Rational&, const Rational&);
    friend Rational operator-(const Rational&, const Rational&);
    friend Rational operator*(const Rational&, const Rational&);
    friend Rational operator/(const Rational&, const Rational&);


    friend bool operator<(const Rational&, const Rational&);
    friend bool operator>(const Rational&, const Rational&);
    friend bool operator>=(const Rational&, const Rational&);
    friend bool operator<=(const Rational&, const Rational&);
    friend bool operator==(const Rational&, const Rational&);
    friend bool operator!=(const Rational&, const Rational&);

    friend std::istream& operator>>(const std::istream&, Rational&);
};


std::istream& operator>>(std::istream& in, Rational& r) {
    BigInteger bi;
    in >> bi;
    r = bi;
    return in;
}


bool operator<(const Rational& r, const Rational& q) {
    Rational c = r-q;
    return (c.numerator < 0);
}

bool operator>(const Rational& r, const Rational& q) {
    return !(r <= q);
}

bool operator<=(const Rational& r, const Rational& q) {
    return (r == q && r < q);
}

bool operator>=(const Rational& r, const Rational& q) {
    return !(r < q);
}

bool operator==(const Rational& r, const Rational& q) {
    return (r.numerator == q.numerator && r.denominator == q.denominator);
}

bool operator!=(const Rational& r, const Rational& q) {
    return !(r == q);
}


Rational operator+(const Rational& r, const Rational& q) {
    Rational copy(r);
    return (copy += q);
}
Rational operator-(const Rational& r, const Rational& q) {
    Rational copy(r);
    return (copy -= q);
}

Rational operator*(const Rational& r, const Rational& q) {
    Rational copy(r);
    return (copy *= q);
}

Rational operator/(const Rational& r, const Rational& q) {
    Rational copy(r);
    return (copy /= q);
}

std::ostream& operator<<(std::ostream& out, const Rational& r) {
    out << r.toString();
    return out;
}