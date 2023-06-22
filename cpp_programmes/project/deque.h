#include <iostream>

template <typename T>
class Deque {
private:

    T** buckets;

    size_t sz = 0;
    size_t num_buckets = 8;

    struct deque_index {
        size_t bucket;
        size_t pos;
    };

    deque_index begin_idx, end_idx;

    static const size_t N = 32;

    void resize() {
        // если будет ТЛ, то стоит реинтерпрет кастить не все бакеты, а только окaймляющие

        T** new_buckets = new T*[2*num_buckets];
        for (size_t i = 0; i < 2*num_buckets; ++i) {
            new_buckets[i] = reinterpret_cast<T*>(new uint8_t[N * sizeof(T)]);
        }

        for (size_t i = 0, j = num_buckets/2; i < num_buckets; i++, j++) {
            delete [] reinterpret_cast<uint8_t*>(new_buckets[j]);
            new_buckets[j] = buckets[i];
        }

        delete [] buckets;
        buckets = new_buckets;

        begin_idx.bucket += num_buckets/2;
        end_idx.bucket += num_buckets/2;

        num_buckets *= 2;
    }

public:

    Deque() {
        buckets = new T*[num_buckets];
        for (size_t i = 0; i < num_buckets; i++) {
            buckets[i] = reinterpret_cast<T*>(new uint8_t[N * sizeof(T)]);
        }

        begin_idx.bucket = 4;
        end_idx.bucket = 4;

        begin_idx.pos = 0;
        end_idx.pos = 0;
    }

    Deque(size_t n) {
        while (2*n >= N * num_buckets) {
            num_buckets *= 2;
        }

        buckets = new T*[num_buckets];
        for (size_t i = 0; i < num_buckets; ++i) {
            buckets[i] = reinterpret_cast<T*>(new uint8_t[N * sizeof(T)]);
        }

        begin_idx.bucket = num_buckets / 2;
        begin_idx.pos = 0;

        end_idx.bucket = num_buckets / 2 + (n / N);
        end_idx.pos = n % N;

        sz = n;
    }

    Deque(size_t n, const T& t) : Deque(n) {

        for (size_t i = 0; i < n; i++) {
            new( &((*this)[i]) ) T(t);
        }
    }

    Deque(const Deque<T>& old) : Deque(old.num_buckets * N / 2) {
        
        sz = old.sz;

        begin_idx.bucket = old.begin_idx.bucket;
        begin_idx.pos = old.begin_idx.pos;

        end_idx.bucket = old.end_idx.bucket;
        end_idx.pos = old.end_idx.pos;

        for (size_t i = 0; i < sz; ++i) {
            new( &((*this)[i]) ) T(old[i]);
        }
    }

    Deque<T>& operator=(const Deque<T>& old) {

        for (size_t i = 0; i < sz; i++) {
            ( &((*this)[i]) )->~T(); 
        }

        if (num_buckets != old.num_buckets) {
            for (size_t i = 0; i < num_buckets; i++) {
                delete [] reinterpret_cast<uint8_t*>(buckets[i]);
            }
            delete [] buckets;

            num_buckets = old.num_buckets;

            buckets = new T*[num_buckets];
            for (size_t i = 0; i < num_buckets; ++i) {
                buckets[i] = reinterpret_cast<T*>(new uint8_t[N * sizeof(T)]);
            }
        }

        begin_idx.bucket = old.begin_idx.bucket;
        begin_idx.pos = old.begin_idx.pos;

        end_idx.bucket = old.end_idx.bucket;
        end_idx.pos = old.end_idx.pos;    

        sz = old.sz;
        for (size_t i = 0; i < sz; ++i) {
            new( &((*this)[i]) ) T(old[i]);
        }          

        return *this;
    }

    ~Deque() {
        for (size_t i = 0; i < sz; i++) {
            ( &((*this)[i]) )->~T(); 
        }

        for (size_t i = 0; i < num_buckets; i++) {
            delete [] reinterpret_cast<uint8_t*>(buckets[i]);
        }

        delete [] buckets;
    }

    size_t size() const {
        return sz;
    }

    T& operator[](size_t idx) {
        size_t _bucket = begin_idx.bucket + (idx + begin_idx.pos)/N;
        size_t _pos = (idx + begin_idx.pos)%N;

        return buckets[_bucket][_pos];
    }

    const T& operator[](size_t idx) const {
        size_t _bucket = begin_idx.bucket + (idx + begin_idx.pos)/N;
        size_t _pos = (idx + begin_idx.pos)%N;

        return buckets[_bucket][_pos];
    }

    T& at(size_t idx) {
        size_t _bucket = begin_idx.bucket + (idx + begin_idx.pos)/N;
        size_t _pos = (idx + begin_idx.pos)%N;

        if (_bucket > end_idx.bucket) {
            throw std::out_of_range("Out of range\n");
        } else if (_bucket == end_idx.bucket) {
            if (_pos >= end_idx.pos) {
                throw std::out_of_range("Out of range\n");
            }
        }

        return buckets[_bucket][_pos];
    }

    const T& at(size_t idx) const {
        size_t _bucket = begin_idx.bucket + (idx + begin_idx.pos)/N;
        size_t _pos = (idx + begin_idx.pos)%N;

        if (_bucket > end_idx.bucket) {
            throw std::out_of_range("Out of range\n");
        } else if (_bucket == end_idx.bucket) {
            if (_pos >= end_idx.pos) {
                throw std::out_of_range("Out of range\n");
            }
        }

        return buckets[_bucket][_pos];
    }

    void push_back(const T& t) {
        if (end_idx.bucket == num_buckets) {
            resize();
        }

        new( &((*this)[sz++]) ) T(t);

        ++end_idx.pos;
        if (end_idx.pos == N) {
            end_idx.pos = 0;
            ++end_idx.bucket;
        }
    }

    void pop_back() {
        if (sz == 0) {
            throw std::out_of_range("Empty deque poping\n");
        }

        ( &((*this)[sz-1]) )->~T();
        if (end_idx.pos == 0) {
            --end_idx.bucket;
            end_idx.pos = N-1;
        } else {
            --end_idx.pos;
        }

        --sz;
    }

    void push_front(const T& t) {
        if (begin_idx.bucket == 0 && begin_idx.pos == 0) { 
            resize();
        }

        if (begin_idx.pos == 0) {
            --begin_idx.bucket;
            begin_idx.pos = N-1;
        } else {
            --begin_idx.pos;
        }

        new( &((*this)[0]) ) T(t);
        ++sz;
    }

    void pop_front() {
        if (sz == 0) {
            throw std::out_of_range("Empty deque poping\n");
        }

        ( &((*this)[0]) )->~T();
        if (begin_idx.pos == N-1) {
            ++begin_idx.bucket;
            begin_idx.pos = 0;
        } else {
            ++begin_idx.pos;
        }

        --sz;
    }


    template <bool isConst>
    class base_iterator: 
    public std::iterator<std::random_access_iterator_tag, std::conditional_t<isConst, const T, T>> {

    private:

        friend class Deque<T>;

        T** main;
        size_t pos;
        size_t bucket;

        using iter_type = base_iterator<isConst>;

        using ptr_type = typename std::conditional<isConst, const T*, T*>::type;
        using ref_type = typename std::conditional<isConst, const T&, T&>::type;

        base_iterator(T** _main, size_t _pos, size_t _bucket) : main(_main), pos(_pos), bucket(_bucket) {}

    public:
        
        base_iterator(const base_iterator& it) : main(it.main), pos(it.pos), bucket(it.bucket) {}

        iter_type& operator+=(size_t n) {                   // exception-safety: переделать потому что бакет может начинаться не с 0, нужно сравнивать с бегином
            
            bucket += (pos + n) / N;
            pos = (pos + n) % N;

            return *this;
        }

        iter_type operator+(size_t n) const {                   // exception-safety: переделать потому что бакет может начинаться не с 0, нужно сравнивать с бегином
            auto copy = *this;
            return copy += n;
        }

        iter_type operator-=(size_t n) {
            if (n > bucket*N + pos) {
                throw std::out_of_range("wrong iterator substract\n");
            }

            if (n % N > pos) {
                pos = pos + N - (n % N);
                bucket  = bucket - (n / N) - 1;

                return *this;
            }

            pos = pos - (n % N);
            bucket  = bucket - (n / N);
            return *this;
        }

        iter_type operator-(size_t n) const {
            auto copy = *this;
            return copy -= n;
        }

        iter_type operator++(int) {
            auto copy = *this;

            if (pos == N-1) {
                pos = 0;
                ++bucket;
            } else {
                ++pos;
            }

            return copy;
        }

        iter_type operator--(int) {
            auto copy = *this;

            if (pos == 0) {
                pos = N-1;
                --bucket;
            } else {
                --pos;
            }

            return copy;
        }

        iter_type& operator++() {
            if (pos == N-1) {
                pos = 0;
                ++bucket;
            } else {
                ++pos;
            }

            return *this;
        }
        
        iter_type& operator--() {
            if (pos == 0) {
                pos = N-1;
                --bucket;
            } else {
                --pos;
            }

            return *this;
        }

        size_t operator-(const base_iterator& it) const {
            if (*this < it) {
                throw std::out_of_range("wrong iterator substract\n");
            }

            if (pos >= it.pos) return (bucket - it.bucket)*N + (pos - it.pos); 
            return (bucket - it.bucket - 1)*N + (pos + N - it.pos);
        }

        bool operator<(const base_iterator& it) const {
            if (bucket == it.bucket) {
                return pos < it.pos;
            }
            return bucket < it.bucket;
        }

        bool operator<=(const base_iterator& it) const {
            return (*this == it || *this < it);
        }

        bool operator>(const base_iterator& it) const {
            return !(*this <= it);
        }

        bool operator>=(const base_iterator& it) const {
            return !(*this < it);
        }

        bool operator==(const base_iterator& it) const {
            return (bucket == it.bucket && pos == it.pos);
        }

        bool operator!=(const base_iterator& it) const {
            return !(*this == it);
        }

        ref_type operator*() {
            return main[bucket][pos];
        }

        ptr_type operator->() {
            return &main[bucket][pos];
        }
    };

    using iterator = base_iterator<false>;
    using const_iterator = base_iterator<true>;

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin() {
        return iterator(buckets, begin_idx.pos, begin_idx.bucket);
    }

    iterator end() {
        return iterator(buckets, end_idx.pos, end_idx.bucket);
    }

    const_iterator begin() const {
        return const_iterator(buckets, begin_idx.pos, begin_idx.bucket);
    }

    const_iterator end() const {
        return const_iterator(buckets, end_idx.pos, end_idx.bucket);
    }

    const_iterator cbegin() const {
        return const_iterator(buckets, begin_idx.pos, begin_idx.bucket);
    }

    const_iterator cend() const {
        return const_iterator(buckets, end_idx.pos, end_idx.bucket);
    }

    ///////////////////////////////////////////////////////////////////

    reverse_iterator rbegin() {
        return reverse_iterator(buckets, begin_idx.pos, begin_idx.bucket);
    }

    reverse_iterator rend() {
        return reverse_iterator(buckets, end_idx.pos, end_idx.bucket);
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(buckets, begin_idx.pos, begin_idx.bucket);
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(buckets, end_idx.pos, end_idx.bucket);
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(buckets, begin_idx.pos, begin_idx.bucket);
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(buckets, end_idx.pos, end_idx.bucket);
    }

    void insert(iterator it, const T& t) {
        if (it > end() || it < begin()) {
            throw std::out_of_range("wrong iterator\n");
        }

        if (it == end()) {
            push_back(t);
            return;
        }

        iterator c = end()-1;
        T copy = *c;

        while (c != it) {
            new(&*c)  T(*(c-1));
            --c;
        }

        new(&*c) T(t);
        push_back(copy);
    }

    void erase(iterator it) {

        if (it >= end() || it < begin()) {
            throw std::out_of_range("wrong iterator\n");
        }

        (&(*it))->~T();

        while (it != end()) {
            new( &(*it) ) T(*(it+1));
            (&(*(++it)))->~T();
        }

        pop_back();
    }
};