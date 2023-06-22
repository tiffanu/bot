#include <iostream>
#include <vector>

#define TT std::cout << __PRETTY_FUNCTION__ << '\n';

template <size_t N>
class StackStorage {
public:

    int memory[N];
    size_t used;

public:

    void print() {
        std::cout << used << '\n';
        std::cout << memory << '\n';
    }

    StackStorage() {
        used = 0;
    }

    StackStorage(const StackStorage&) = delete;

    int* mem_reserve(size_t size, size_t align) { // used and memory arent initialized
        print();
        if (used % align != 0) {
            used += align - (used % align);
        }
        used += size;
        return memory + used - size;
    }
};

template <typename T, size_t N>
class StackAllocator {
private:

    StackStorage<N> *storage;

public:

    using value_type = T;

    template <typename U, size_t M>
    friend class StackAllocator;

    template <typename U>
    struct rebind {
        using other = StackAllocator<U, N>;
    };

    StackAllocator() {}

    template <typename U>
    StackAllocator(const StackAllocator<U, N>& alloc) {
        storage = alloc.storage;
    }

    StackAllocator(StackStorage<N>& other) {
        storage = &other;
    }

    ~StackAllocator() = default;

    StackAllocator& operator=(StackAllocator& alloc) {
        storage = alloc.storage;
        return *this;
    }

    T* allocate(size_t size) {
        return reinterpret_cast<T*>(storage->mem_reserve(size * sizeof(T), sizeof(T)));
    }

    void deallocate(T*, size_t) {}

    bool operator==(const StackAllocator& alloc) const {
        return storage.memory == alloc.storage.memory;
    }

    bool operator!=(const StackAllocator& alloc) const {
        return storage.memory != alloc.storage.memory;
    }
};


template <typename T, typename Alloc = std::allocator<T>>
class List {
private:

    struct BaseNode {
    	BaseNode* prev = nullptr;
    	BaseNode* next = nullptr;
    };

    struct Node : BaseNode {
        T val;

        Node() : val() {}

        Node(BaseNode* b) : Node() {
            prev = b->prev;
            next = b->next;
        }
    };


    Alloc alloc;

    using AllocTraits = std::allocator_traits<Alloc>;

    using BaseNodeAlloc = typename Alloc::template rebind<BaseNode>::other;
    using BaseNodeAllocTraits = std::allocator_traits<BaseNodeAlloc>;
    BaseNodeAlloc base_node_alloc;

    using NodeAlloc = typename Alloc::template rebind<Node>::other;
    using NodeAllocTraits = std::allocator_traits<NodeAlloc>;
    NodeAlloc node_alloc;


    BaseNode* fakeNode;
    size_t sz;

    Node* makeNode() {
        Node* node = NodeAllocTraits::allocate(node_alloc, 1);
        return node;
    }

    void push_back() {
        Node* new_node = makeNode();

        new_node->prev = fakeNode->prev;
        fakeNode->prev->next = new_node;

        new_node->next = fakeNode;
        fakeNode->prev = new_node;

        ++sz;
    }

public:

    List() : base_node_alloc(BaseNodeAlloc()),
             fakeNode(BaseNodeAllocTraits::allocate(base_node_alloc, 1))
        { 

        fakeNode->prev = fakeNode;
        fakeNode->next = fakeNode;

        sz = 0;

        TT;
    }

    List(size_t n) : List() {
        for (size_t i = 0; i < n; ++i) {   
            push_back();
        }
        TT;
    }

    List(size_t n, const T& t) : List(n) {
        Node* curr_node = fakeNode->next;
        for (size_t i = 0; i < n; ++i) {
            push_back(t);
        }
    }

    List(Alloc _alloc) : alloc(_alloc), fakeNode(BaseNodeAllocTraits::allocate(base_node_alloc, 1)) {

        fakeNode->prev = fakeNode;
        fakeNode->next = fakeNode;

        sz = 0;
    }

    List(size_t n, Alloc _alloc) : alloc(_alloc) {
        for (size_t i = 0; i < n; ++i) {
            push_back();
        }
    }

    List(size_t n, const T& t, Alloc _alloc) : alloc(_alloc) {
        for (size_t i = 0; i < n; ++i) {
            push_back(t);
        }
    }

    Alloc get_allocator() const {
        return alloc;
    }

    List(const List& old) : List() {
        Node* curr_node = static_cast<Node*>(old.fakeNode->next);
        for (size_t i = 0; i < old.size(); ++i) {
            push_back(curr_node->val);
            curr_node = static_cast<Node*>(curr_node->next);
        }
    }

    ~List() {
        while (sz) pop_back();
    }

    List<T, Alloc>& operator=(const List<T, Alloc>& old) {
        while (sz) pop_back();

        Node* curr_node = static_cast<Node*>(old.fakeNode->next); // manage to separate function
        for (size_t i = 0; i < old.size(); ++i) {
            push_back(curr_node->val);
            curr_node = static_cast<Node*>(curr_node->next);
        }        

        return *this;
    }

    size_t size() const {
        return sz;
    }

    void push_back(const T& t) {
        Node* new_node = makeNode();

        new_node->prev = fakeNode->prev;
        fakeNode->prev->next = new_node;

        new_node->next = fakeNode;
        fakeNode->prev = new_node;

        new_node->val = t;

        ++sz;
    }

    void push_front(const T& t) {
        Node* new_node = makeNode();

        new_node->next = fakeNode->next;
        fakeNode->next->prev = new_node;

        new_node->prev = fakeNode;
        fakeNode->next = new_node;

        new_node->val = t;

        ++sz;
    }

    void pop_back() {
        Node* last = static_cast<Node*>(fakeNode->prev);  // maybe without static_cast

        fakeNode->prev = last->prev;
        last->prev->next = fakeNode;

        NodeAllocTraits::deallocate(node_alloc, last, 1);

        --sz;
    }

    void pop_front() {
        Node* first = fakeNode->next;

        fakeNode->next = first->next;
        first->next->prev = fakeNode;

        NodeAllocTraits::deallocate(node_alloc, first, 1);

        --sz;
    }

    template <bool isConst>
    class base_iterator: 
    public std::iterator<std::random_access_iterator_tag, std::conditional_t<isConst, const T, T>> {

    private:

        friend class List<T, Alloc>;

        Node* node;

        using iter_type = base_iterator<isConst>;

        using ptr_type = typename std::conditional<isConst, const T*, T*>::type;
        using ref_type = typename std::conditional<isConst, const T&, T&>::type;
    
        base_iterator(Node* new_node) : node(new_node) {}
        base_iterator(BaseNode* new_node) : node(new_node) {}

    public:

        base_iterator(const base_iterator& it) : node(it.node) {}

        iter_type& operator+=(size_t n) {
            for (size_t i = 0; i < n; ++i) {
                ++(*this);
            }
            return *this;
        }

        iter_type operator++(int) {
            auto copy = *this;
            ++(*this);

            return copy;
        }

        iter_type operator--(int) {
            auto copy = *this;
            --(*this);

            return copy;
        }

        iter_type& operator++() {
            node = *Node(node->next);
            return *this;
        }
        
        iter_type& operator--() {
            node = node->prev;
            return *this;        
        }

        bool operator==(const base_iterator& it) {
            return node == it.node;
        }

        bool operator!=(const base_iterator& it) {
            return node != it.node;
        }

        ref_type operator*() {
            return node->val;
        }

        ptr_type operator->() {
            return &(node->val);
        }
    };

    using iterator = base_iterator<false>;
    using const_iterator = base_iterator<true>;

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    iterator begin() {
        return iterator(fakeNode->next);
    }

    iterator end() {
        return iterator(fakeNode);
    }

    const_iterator begin() const {
        return const_iterator(fakeNode->next);
    }

    const_iterator end() const {
        return const_iterator(fakeNode);
    }

    const_iterator cbegin() const {
        return const_iterator(fakeNode->next);
    }

    const_iterator cend() const {
        return const_iterator(fakeNode);
    }

    /////////////////////////////////////////////////////////////////

    reverse_iterator rbegin() {
        return reverse_iterator(fakeNode->next);
    }

    reverse_iterator rend() {
        return reverse_iterator(fakeNode);
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(fakeNode->next);
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(fakeNode);
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(fakeNode->next);
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(fakeNode);
    }

    void insert(iterator it, const T& t) {
        Node* new_node = makeNode();

        new_node->next = it.node;
        new_node->prev = it.node->prev;

        it.node->prev = new_node;
        new_node->prev->next = new_node;

        new_node->val = t;

        ++sz;
    }

    void insert(const_iterator it, const T& t) {
        Node* new_node = makeNode();

        new_node->next = it.node;
        new_node->prev = it.node->prev;

        it.node->prev = new_node;
        new_node->prev->next = new_node;

        new_node->val = t;

        ++sz;
    }

    void erase(iterator it) {
        it.node->next->prev = it.node->prev;
        it.node->prev->next = it.node->next;

        NodeAllocTraits::deallocate(node_alloc, it.node, 1);

        --sz;
    }

    void erase(const_iterator it) {
        it.node->next->prev = it.node->prev;
        it.node->prev->next = it.node->next;

        NodeAllocTraits::deallocate(node_alloc, it.node, 1);

        --sz;
    }
};

// int main() {
//     StackStorage<100000> storage;
//     StackAllocator<int, 100000> alloc;
//     storage.print();
//     List<int, StackAllocator<int, 100000>> lst;
//     // List<int, StackAllocator<int, 100000>> lst2(lst);
// }
