#include <vector>
#include <array>
#include <string>

class BigInteger {
private:

    static const int radix = 1'000'000'000;

    std::vector<int> body; 

    size_t size;
    bool is_positive; // 0 is =0; 1 is >0; -1 is <0

    void remove_leading_zeros() {
        while (size > 1 && body.back() == 0) {
            body.pop_back();
            --size;
        }
        if (size == 1 && body[0] == 0) {
            is_positive = true;
        }
    }

    void normalize() {
        long long next_digit;
        for (size_t i = 0; i < body.size(); ++i) {
            if (body[i] >= 0) {
                next_digit = body[i] / radix;
                body[i] = body[i] % radix;
                if (i == body.size() - 1) {
                    if (next_digit != 0) {
                        body.push_back(next_digit);
                        ++size;
                    }
                    continue;
                }
                body[i + 1] += next_digit;
            }
            else {
                if (i == body.size() - 1) {
                    is_positive = !is_positive;
                    for (size_t j = 0; j < body.size(); ++j) {
                        body[j] *= -1;
                    }
                    normalize();
                    return;
                }

                next_digit = (-body[i]) / radix;
                body[i] = body[i] % radix;
                if (body[i] < 0) {
                    body[i] += radix;
                    ++next_digit;
                }
                body[i + 1] -= next_digit;
            }
        }
    }


public:

    friend class Rational;

    friend std::ostream& operator<<(std::ostream&, const BigInteger&);
    friend std::istream& operator>>(std::istream&, BigInteger&);


    BigInteger() : size(1), is_positive(true) {
        body.push_back(0);
    }

    BigInteger(int x) : BigInteger() {
        if (x < 0) {
            x = -x;
            is_positive = false;
        }

        body[0] = x % radix;
        if (x / radix) {
            body.push_back(x / radix);
            size++;
        }
    }

    BigInteger(const BigInteger& bi) : body(bi.body), size(bi.size), is_positive(bi.is_positive) {}

    BigInteger& operator=(const BigInteger& bi) {
        body = bi.body;
        size = bi.size;
        is_positive = bi.is_positive;
        return *this;
    }

    ~BigInteger() {}


    std::string toString() const {
        std::string str;
        if (is_positive == false) str += '-';

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


    BigInteger& operator+=(const BigInteger& number) {
        size_t number_size = number.body.size();
        while (body.size() < number_size) {
            body.push_back(0);
            ++size;
        }
        int delta = (number.is_positive == is_positive)? 1 : -1;
        for (size_t i = 0; i < number_size; ++i) {
            body[i] += delta * number.body[i];
        }
        normalize();
        remove_leading_zeros();
        return *this;
    }

    BigInteger& operator-=(const BigInteger& number) {
        return *this += (-number);
    }

    BigInteger& operator*=(const BigInteger& bi) {
        BigInteger res;
        while (res.size <= size + bi.size) {
            ++res.size;
            res.body.push_back(0);
        }
        res.is_positive = !(is_positive ^ bi.is_positive);

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

    void halving() {
        long long remainder = 0;
        long long temporary;
        for (size_t i = size; i > 0; --i) {
            temporary = body[i - 1] + remainder * radix;
            body[i - 1] = (temporary / 2);
            remainder = (temporary % 2);
        }
        remove_leading_zeros();
    }

    void doubling() {
        long long remainder = 0;
        long long temporary;
        for (size_t i = 0; i < size || remainder; ++i) {
            if (i == size) {
                body.push_back(0);
                ++size;
            }
            temporary = remainder + body[i] * 2;
            body[i] = temporary % radix;
            remainder = temporary / radix;
        }
        remove_leading_zeros();
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
        b.is_positive = true;

        BigInteger res, curr;
        res.body.resize(size);
        res.size = size;

        for (long long i = static_cast<long long>(size) - 1; i >= 0; --i) {
            curr.is_positive = true;
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

        res.is_positive = !(is_positive ^ bi.is_positive);
        res.remove_leading_zeros();

        return (*this = res);
    }

    BigInteger& operator%=(const BigInteger& bi) {
        BigInteger r = (*this) - ((*this) / bi)*bi;
        return (*this = r);
    }


    BigInteger operator-() const {
        BigInteger copy = *this;
        if (copy != 0) {
            copy.is_positive = !copy.is_positive;
        }
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
        if (a.is_positive == b.is_positive) {
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
    if (a.is_positive == b.is_positive) {
        if (a.size == b.size) {
            for (size_t i = a.size; i > 0; i--) {
                if (a.body[i-1] != b.body[i-1]) {
                    return (a.is_positive == true) ? (a.body[i-1] < b.body[i-1]) : (a.body[i-1] > b.body[i-1]);
                }
            }
            return false;
        }
        return (a.is_positive == true) ? (a.size < b.size) : (a.size > b.size);
    }
    return (a.is_positive < b.is_positive);
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

    size_t start = 0;
    if (input[0] == '-') {
        bi.is_positive = false;
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
    if (bi < 0) return -bi;
    return bi;
}

BigInteger gcd(const BigInteger& first, const BigInteger& second) { // ускорить с четными мб
    BigInteger a = abs(first), b = abs(second);
    BigInteger ans = 1;
    if (a == 0 || b == 0) {
        return 1;
    }
    if (a > b) {
        std::swap(a, b);
    }
    bool evenA, evenB;
    while (a != 0 && b != 0) {
        evenA = isEven(a);
        evenB = isEven(b);
        if (evenA && evenB) {
            a.halving();
            b.halving();
            ans.doubling();
            continue;
        }
        if (evenA) {
            a.halving();
            continue;
        }
        if (evenB) {
            b.halving();
            continue;
        }
        if (a > b) {
            std::swap(a, b);
        }
        b -= a;
    }
    return (a ? a : b) * ans;
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

    res.is_positive = true; // mb mojno ybrat' + vse pohojee

    return res;
}


class Rational {
private:

    BigInteger numerator, denominator; // num \in Z    den \in N

    void reduce() {
        BigInteger d = gcd(numerator, denominator);
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
        if (numerator != 0) { 
            copy.numerator.is_positive = !copy.numerator.is_positive;
        }
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

    friend std::istream& operator>>(std::istream&, Rational&);
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

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////


template <size_t N, size_t I, size_t D>
struct IsPrimeHelper;

template <size_t N, size_t I>
struct IsPrimeHelper<N, I, 0> {
    static const bool value = false; 
};

template <size_t N, size_t I>
struct IsPrimeHelper<N, I, 1> {
    static const bool value = true; 
};

template <size_t N, size_t I>
struct IsPrimeHelper<N, I, 2> {
    static const bool value = IsPrimeHelper<N, I+2, (I*I > N) ? 1 :
                                                    (N % I == 0) ? 0 : 2>::value; 
};

template <size_t N>
struct IsPrime {
    static const bool value = (N <= 1) ? false :
                              (N==2 || N==3) ? true :
                              (N % 2 == 0) ? false :
                              IsPrimeHelper<N, 3, 2>::value;
};



template <size_t N>
class Residue {
private:

    size_t element;

public:

    Residue() : element(0) {}

    Residue(long long x) {
        while (x < 0) {
            x += N;
        }
        element = x % N;
    }


    Residue(const Residue<N>& r) : element(r.element) {}

    Residue& operator=(const Residue<N>& r) {
        element = r.element;
        return *this;
    }

    ~Residue() {}


    Residue& operator+=(const Residue<N>& r) {
        element = (element + r.element) % N;
        return *this;
    }

    Residue& operator-=(const Residue<N>& r) {
        element = (N + element - r.element) % N;
        return *this;
    }

    Residue& operator*=(const Residue<N>& r) {
        element = (element * r.element) % N;
        return *this;
    }

    Residue& operator/=(const Residue& r) {
        static_assert(IsPrime<N>::value, "Residue<N> has no operator /= if N is not prime\n");
        std::vector<size_t> inv(N);
        inv[1] = 1;
        for (size_t i = 2; i < N; ++i) {
            inv[i] = (N - (N/i) * inv[N%i] % N) % N;
        }
        element = (element * inv[r.element]) % N;
        return *this;
    }


    template <size_t M>
    friend bool operator<(const Residue<M>&, const Residue<M>&);
    template <size_t M>
    friend bool operator==(const Residue<M>&, const Residue<M>&);

    template <size_t M>
    friend std::ostream& operator<<(std::ostream&, const Residue<M>&);


    explicit operator int() const {
        return int(element);
    }
};

template <size_t N>
bool operator<(const Residue<N>& r1, const Residue<N>& r2) {
    return r1.element < r2.element;
}

template <size_t N>
bool operator==(const Residue<N>& r1, const Residue<N>& r2) {
    return r1.element == r2.element;
}

template <size_t N>
bool operator<=(const Residue<N>& r1, const Residue<N>& r2) {
    return (r1 == r2 || r1 < r2);
}

template <size_t N>
bool operator>(const Residue<N>& r1, const Residue<N>& r2) {
    return !(r1 <= r2);
}

template <size_t N>
bool operator>=(const Residue<N>& r1, const Residue<N>& r2) {
    return !(r1 < r2);
}

template <size_t N>
bool operator!=(const Residue<N>& r1, const Residue<N>& r2) {
    return !(r1 == r2);
}


template <size_t N>
Residue<N> operator+(const Residue<N>& r1, const Residue<N>& r2) {
    Residue<N> copy = r1;
    return (copy += r2);
}

template <size_t N>
Residue<N> operator-(const Residue<N>& r1, const Residue<N>& r2) {
    Residue<N> copy = r1;
    return (copy -= r2);
}

template <size_t N>
Residue<N> operator*(const Residue<N>& r1, const Residue<N>& r2) {
    Residue<N> copy = r1;
    return (copy *= r2);
}

template <size_t N>
Residue<N> operator/(const Residue<N>& r1, const Residue<N>& r2) {
    static_assert(IsPrime<N>::value, "Residue<N> has no operator / if N is not prime\n");
    Residue<N> copy = r1;
    return (copy /= r2);
}


template <size_t N>
std::ostream& operator<<(std::ostream& out, const Residue<N>& r) {
    return (out << r.element);
}





template <size_t M, size_t N, typename Field = Rational>
class Matrix {
public:

    // std::array<std::array<Field, N>, M> matrix;
    std::vector<std::vector<Field>> matrix;
public:

    using SquareMatrix = Matrix<N, N, Field>;


    Matrix() {
        for (size_t i = 0; i < M; ++i) {
            matrix.push_back(std::vector<Field>(N, Field(0)));
        }
    }

    //Matrix(const std::initializer_list<std::array<Field, N>>& init) {
    Matrix(const std::initializer_list<std::array<Field, N>>& init) : Matrix() {
        size_t i = 0;
        for (const auto& array : init) {
            for (const auto& element : array) {
                    matrix[i / N][i % N] = element;
                    ++i;
            }
        }
    }

    Matrix(const Matrix<M, N, Field>& other) : matrix(other.matrix) {}

    Matrix& operator=(const Matrix<M, N, Field>& other) {
        matrix = other.matrix;
        return *this;
    }

    ~Matrix() {}


    Matrix& operator+=(const Matrix<M, N, Field>& other) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                matrix[i][j] += other[i][j];
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix<M, N, Field>& other) const {
        Matrix<M, N, Field> copy = *this;
        return (copy += other);
    }

    Matrix& operator-=(const Matrix<M, N, Field>& other) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                matrix[i][j] -= other[i][j];
            }
        }
        return *this;
    }

    Matrix operator-(const Matrix<M, N, Field>& other) const {
        Matrix<M, N, Field> copy = *this;
        return (copy -= other);
    }

    Matrix& operator*=(const Field& f) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                matrix[i][j] *= f;
            }
        }
        return *this;        
    }

    Matrix operator*(const Field& f) const {
        Matrix copy = *this;
        return (copy *= f);
    }

    template<size_t K>
    Matrix<M, K, Field> operator*(const Matrix<N, K, Field>& other) const {
        Matrix<M, K, Field> result;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < K; ++j) {
                for (size_t k = 0; k < N; ++k) {
                    result[i][j] += matrix[i][k] * other[k][j];
                }
            }
        }
        return result;
    }


    Matrix<M, N, Field>& operator*=(const Matrix<N, N, Field>& other) {
        Matrix<M, N, Field> res = (*this) * other;
        return (*this = res);
    }

    bool operator==(const Matrix<M, N, Field>& other) const {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                if (matrix[i][j] != other[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix<M, N, Field>& other) const {
        return !(*this == other);
    }

    //std::array<Field, N>& operator[](size_t i) {
    std::vector<Field>& operator[](size_t i) {
        return matrix[i];
    }

    //const std::array<Field, N>& operator[](size_t i) const {
    const std::vector<Field>& operator[](size_t i) const {
        return matrix[i];
    }

    void add_row2_to_row1(size_t _row1, size_t _row2) {
        for (size_t j = 0; j < N; ++j) {
            matrix[_row1][j] += matrix[_row2][j];
        }
    }

    void add_col2_to_col1(size_t _col1, size_t _col2) {
        for (size_t i = 0; i < M; ++i) {
            matrix[i][_col1] += matrix[i][_col2];
        }
    }


    Matrix<N, M, Field> transposed() const {
        Matrix<N, M, Field> copy;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < M; ++j) {
                copy[i][j] = matrix[j][i];
            }
        }
        return copy;
    }

    void swap_columns(size_t _col1, size_t _col2) {
        for (size_t i = 0; i < M; ++i) {
            std::swap(matrix[i][_col1], matrix[i][_col2]);
        }
    }

    size_t rank() const {
        Matrix<M, N, Field> copy(*this);  // мб чтобы искать ранг у целочисленных типов придется кастить всё к Rational

        size_t K = std::min(M, N);
        
        for (size_t k = 0; k < K; ++k) {
            if (copy[k][k] == Field(0)) {   // сделать так же в детерминанте
                bool flag = false;
                for (size_t i = k; i < M; ++i) {
                    for (size_t j = k; j < N; ++j) {
                        if (copy[i][j] != Field(0)) {
                            std::swap(copy[i], copy[k]);
                            copy.swap_columns(j, k);
                            flag = true;
                            break;
                        }
                    }
                    if (flag) {
                        break;
                    }
                }
                if (!flag) {
                    return k;
                }
            }


            for (size_t i = k+1; i < N; ++i) {
                copy[k][i] /= copy[k][k];
            }
            copy[k][k] = Field(1);

            for (size_t i = k+1; i < M; ++i) {
                Field mult = copy[i][k];
                for (size_t j = k; j < N; ++j) {
                    copy[i][j] -= (copy[k][j] * mult);
                }
            }
        }

        return K;
    }

    std::vector<Field> getRow(unsigned idx) const {
        std::vector<Field> row;
        for (size_t j = 0; j < N; ++j) {
            row.push_back(matrix[idx][j]);
        }
        return row;
    }

    std::vector<Field> getColumn(unsigned idx) const {
        std::vector<Field> col;
        for (size_t i = 0; i < M; ++i) {
            col.push_back(matrix[i][idx]);
        }
        return col;
    }


    Field det() const {
        static_assert(M == N, "Matrix has no member det()\n");

        Field res(1);
        Matrix<N, N, Field> copy = *this;

        for (size_t k = 0; k < N; ++k) {
            if (copy[k][k] == Field(0)) {   // сделать так же в детерминанте
                bool flag = false;
                for (size_t i = k+1; i < N; ++i) {
                    if (copy[i][k] != Field(0)) {
                        copy.add_row2_to_row1(k, i);
                        flag = true;
                        break;
                    }
                }
                if (!flag) {    // если не нашлось элементов значит дет=0
                    return Field(0);
                }
            }

            for (size_t i = k+1; i < N; ++i) {
                Field mult = copy[i][k] / copy[k][k];
                for (size_t j = k; j < N; ++j) {
                    copy[i][j] -= (copy[k][j] * mult);
                }
            }
        }

        for (size_t i = 0; i < N; ++i) {
            res *= copy[i][i];
        }

        return res;
    }


    Matrix inverted() const {
        static_assert(M == N, "Matrix has no member inverted()\n");

        Matrix copy(*this);
        return copy.invert();
    }

    Matrix& invert() {
        static_assert(M == N, "Matrix has no member invert()\n");

        Matrix<N, 2*N, Field> advanced;
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                advanced[i][j] = matrix[i][j];
            }
            advanced[i][i+N] = Field(1);
        }

        for (size_t k = 0; k < N; ++k) {
            if (advanced[k][k] == Field(0)) {
                for (size_t i = k+1; i < N; ++i) {
                    if (advanced[i][k] != Field(0)) {
                        advanced.add_row2_to_row1(k, i);
                        break;
                    }
                }
            }

            for (size_t i = 0; i < N; ++i) {
                if (k != i) {
                    Field mult = advanced[i][k] / advanced[k][k];
                    for (size_t j = 0; j < 2*N; ++j) {
                        advanced[i][j] -= advanced[k][j] * mult;
                    }
                }
            }
        }

        // for (size_t k = N-1; k > 0; --k) {
        //     for (size_t i = 0; i < k; ++i) {
        //         Field mult = advanced[i][k] / advanced[k][k];
        //         for (size_t j = k; j < 2*N; ++j) {
        //             advanced[i][j] -= advanced[k][j] * mult;
        //         }
        //     }
        // }

        for (size_t i = 0; i < N; ++i) {
            Field dev = advanced[i][i];
            for (size_t j = N; j < 2*N; ++j) {
                advanced[i][j] /= dev;
            }
        }


        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                matrix[i][j] = advanced[i][j+N];
            }
        }

        return *this;
    }

    Field trace() const {
        static_assert(M == N, "Matrix has no member trace()\n");

        Field ans(0);
        for (size_t i = 0; i < N; ++i) {
            ans += matrix[i][i];
        }
        return ans;  
    }
};

template <size_t M, size_t N, typename Field>
Matrix<M, N, Field> operator*(const Field& f, const Matrix<M, N, Field>& matrix) {
    Matrix<M, N, Field> copy = matrix;
    return (copy *= f);        
}

template <size_t N, typename Field = Rational>
using SquareMatrix = Matrix<N, N, Field>;


/*
87 15 -69 -56 58 -85 52 -59 -72 88 60 -48 -43 -80 6 -91 -44 -72 -47 9 
-8 10 26 -10 -24 31 -96 58 81 -73 95 15 82 -37 -10 22 -64 -35 -52 -77 
-65 36 -53 -32 -42 69 -42 85 -80 -52 25 -59 57 49 -71 21 59 5 39 -91 
32 -29 -57 5 -22 -92 -7 85 74 30 64 -64 -71 21 1 -35 -25 -54 -73 -44 
-31 38 74 13 -86 35 94 18 67 40 -60 32 -33 83 -45 -95 -41 -1 -65 -26 
-97 73 -57 7 86 45 50 52 73 69 74 -90 33 33 96 -58 -1 -21 -66 45 
-75 -83 -30 67 30 59 -66 -46 -54 82 -52 60 -31 1 -58 -17 53 -19 87 3 
83 51 53 -30 -68 -96 -71 65 90 -55 -22 51 92 50 -61 -14 -18 80 58 41 
-4 -54 -48 -51 1 -93 -28 -83 52 -84 7 69 80 81 -98 1 -93 -45 -95 -45 
53 -78 16 10 44 -55 76 83 78 -80 47 45 -28 -79 12 42 -100 77 73 81 
-53 92 39 -96 -46 44 -68 87 96 48 60 -55 -8 26 -84 65 -23 -44 98 6 
18 48 -27 45 14 61 -38 -38 47 -70 -97 50 -17 13 72 54 -3 92 83 -41 
91 -9 94 81 -61 -66 -25 84 -57 55 -55 -99 -51 -71 -56 -41 -74 -90 -84 16 
-76 -51 -63 83 21 91 -92 -97 23 66 -61 69 96 8 -10 -75 25 -9 -18 44 
63 -80 -21 -86 -40 -89 23 -24 -6 10 -67 49 25 18 49 26 68 -48 55 -95 
-92 -62 -68 0 59 81 20 81 -86 88 -66 65 -23 70 98 -80 -61 -74 32 -89 
29 83 22 55 -75 34 -92 9 69 79 89 77 81 -74 -87 -95 -95 -92 99 29 
-98 47 -30 87 -71 -75 -51 -40 -22 50 52 29 -2 -69 -18 -20 -73 -91 17 -86 
-89 -24 -81 79 -65 63 -58 -23 22 -25 -31 70 -44 97 -90 5 9 -84 -19 -63 
-36 17 -30 51 78 -1 -85 -9 6 97 16 4 25 4 78 2 -62 -87 80 51
*/

// проблема в бигинтах или рэшнл с матрицами всё пиздато

// есть много чё исправлять + мб добавить штрассена