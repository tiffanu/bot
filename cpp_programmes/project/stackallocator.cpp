#include <iostream>
#include <vector>
#include <chrono>
#include <stdexcept>
#include <string>
#include <list>
#include <deque>
#include <memory>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <sys/resource.h>
#include <cstddef>

#define TT std::cout << __PRETTY_FUNCTION__ << '\n';

template <size_t N>
class alignas(std::max_align_t) StackStorage {
    alignas(std::max_align_t) uint8_t memory[N];
    size_t used = 0;

public:

    StackStorage() = default;

    StackStorage(const StackStorage&) = delete;

    uint8_t* mem_reserve(size_t size, size_t align) {
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

    StackAllocator() = default;

    StackAllocator(const StackAllocator<T, N>& alloc) {
        storage = alloc.storage;
    }

    template <typename U>
    StackAllocator(const StackAllocator<U, N>& alloc) {
        storage = alloc.storage;
    }

    StackAllocator(StackStorage<N>& other) {
        storage = &other;
    }

    ~StackAllocator() = default;

    StackAllocator& operator=(const StackAllocator<T, N>& alloc) {
        storage = alloc.storage;
        return *this;
    }

    template <typename U>
    StackAllocator& operator=(const StackAllocator<U, N>& alloc) {
        storage = alloc.storage;
        return *this;
    }

    T* allocate(size_t size) {
        return reinterpret_cast<T*>(storage->mem_reserve(size * sizeof(T), alignof(T)));
    }

    void deallocate(T*, size_t) {}

    bool operator==(const StackAllocator& alloc) const {
        return storage == alloc.storage;
    }

    bool operator!=(const StackAllocator& alloc) const {
        return storage.memory != alloc.storage.memory;
    }
};


template <typename T, typename Alloc = std::allocator<T>>
class List {
private:

    struct Node {
    	Node* prev = nullptr;
    	Node* next = nullptr;

        T val;

        Node() : val() {}

        explicit Node(const T& t) : val(t) {}
    };

    using AllocTraits = std::allocator_traits<Alloc>;

    using NodeAlloc = typename Alloc::template rebind<Node>::other;
    using NodeAllocTraits = std::allocator_traits<NodeAlloc>;
    NodeAlloc node_alloc;


    Node* fakeNode;
    size_t sz;

    Node* makeNode() {
        Node* node = NodeAllocTraits::allocate(node_alloc, 1);
        try {
            NodeAllocTraits::construct(node_alloc, node);
        } catch (...) {
            NodeAllocTraits::deallocate(node_alloc, node, 1);
            throw "ctor/dtor bruh\n";
        }
        return node;
    }

    Node* makeNode(const T& t) {
        Node* node = NodeAllocTraits::allocate(node_alloc, 1);
        try {
            NodeAllocTraits::construct(node_alloc, node, t);
        } catch (...) {
            NodeAllocTraits::deallocate(node_alloc, node, 1);
            throw "ctor/dtor bruh\n";
        }
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

    List() : node_alloc(NodeAlloc()) , fakeNode(NodeAllocTraits::allocate(node_alloc, 1)) { 

        fakeNode->prev = fakeNode;
        fakeNode->next = fakeNode;

        sz = 0;
    }

    List(const NodeAlloc& _alloc) : node_alloc(NodeAllocTraits::select_on_container_copy_construction(_alloc)),
                                    fakeNode(NodeAllocTraits::allocate(node_alloc, 1)) {

        fakeNode->prev = fakeNode;
        fakeNode->next = fakeNode;

        sz = 0;
    }

    List(size_t n) : List(Alloc()) {
        for (size_t i = 0; i < n; ++i) {
            try {
                push_back();
            } catch (...) {
                for (size_t j = 0; j < i; ++j) {
                    pop_back();
                }
                throw "construction ex\n";
            }
        }
    }

    List(size_t n, const T& t) : List(Alloc()) {
        for (size_t i = 0; i < n; ++i) {
            try {
                push_back(t);
            } catch (...) {
                for (size_t j = 0; j < i; ++j) {
                    pop_back();
                }
                throw "construction ex\n";
            }
        }
    }

    List(size_t n, const NodeAlloc& _alloc) : node_alloc(NodeAllocTraits::select_on_container_copy_construction(_alloc)), 
                                              fakeNode(NodeAllocTraits::allocate(node_alloc, 1)) {
        
        fakeNode->prev = fakeNode;
        fakeNode->next = fakeNode;

        sz = 0;
        
        for (size_t i = 0; i < n; ++i) {
            try {
                push_back();
            } catch (...) {
                for (size_t j = 0; j < i; ++j) {
                    pop_back();
                }
                throw "construction ex\n";
            }
        }
    }

    List(size_t n, const T& t, const NodeAlloc& _alloc) : node_alloc(NodeAllocTraits::select_on_container_copy_construction(_alloc)), 
                                                fakeNode(NodeAllocTraits::allocate(node_alloc, 1)){
        
        fakeNode->prev = fakeNode;
        fakeNode->next = fakeNode;

        sz = 0;
        
        for (size_t i = 0; i < n; ++i) {
            try {
                push_back(t);
            } catch (...) {
                for (size_t j = 0; j < i; ++j) {
                    pop_back();
                }
                throw "construction ex\n";
            }
        }
    }

    NodeAlloc get_allocator() const {
        return node_alloc;
    }

    List(const List& old) : node_alloc(NodeAllocTraits::select_on_container_copy_construction(old.node_alloc)),
                            fakeNode(NodeAllocTraits::allocate(node_alloc, 1)) {
        
        fakeNode->prev = fakeNode;
        fakeNode->next = fakeNode;

        sz = 0;

        Node* curr = old.fakeNode->next;
        while (sz < old.sz) {
            push_back(curr->val);
            curr = curr->next;
        }
    }

    ~List() {
        while (sz) pop_back();

        NodeAllocTraits::deallocate(node_alloc, fakeNode, 1);
    }

    List<T, Alloc>& operator=(const List<T, Alloc>& old) {

        while (sz) {
            pop_back();
        }

        if (NodeAllocTraits::propagate_on_container_copy_assignment::value) {
            node_alloc = old.node_alloc;
        } else {
            node_alloc = NodeAllocTraits::select_on_container_copy_construction(old.node_alloc);
        }
        
        fakeNode = NodeAllocTraits::allocate(node_alloc, 1);

        fakeNode->prev = fakeNode;
        fakeNode->next = fakeNode;

        Node* curr = old.fakeNode->next;
        while (sz < old.sz) {
            push_back(curr->val);
            curr = curr->next;
        }

        return *this;
    }

    size_t size() const {
        return sz;
    }

    void push_back(const T& t) {
        Node* new_node = makeNode(t);

        new_node->prev = fakeNode->prev;
        fakeNode->prev->next = new_node;

        new_node->next = fakeNode;
        fakeNode->prev = new_node;

        ++sz;
    }

    void push_front(const T& t) {
        Node* new_node = makeNode(t);

        new_node->next = fakeNode->next;
        fakeNode->next->prev = new_node;

        new_node->prev = fakeNode;
        fakeNode->next = new_node;

        ++sz;
    }

    void pop_back() {
        Node* last = fakeNode->prev;

        fakeNode->prev = last->prev;
        last->prev->next = fakeNode;

        NodeAllocTraits::destroy(node_alloc, last);
        NodeAllocTraits::deallocate(node_alloc, last, 1);

        --sz;
    }

    void pop_front() {
        Node* first = fakeNode->next;

        fakeNode->next = first->next;
        first->next->prev = fakeNode;

        NodeAllocTraits::destroy(node_alloc, first);
        NodeAllocTraits::deallocate(node_alloc, first, 1);

        --sz;
    }

    template <bool isConst>
    class base_iterator: 
    public std::iterator<std::bidirectional_iterator_tag, std::conditional_t<isConst, const T, T>> {

    private:

        friend class List<T, Alloc>;

        Node* node;

        using ptr_type = typename std::conditional<isConst, const T*, T*>::type;
        using ref_type = typename std::conditional<isConst, const T&, T&>::type;
    
    
    public:

        base_iterator(Node* new_node) : node(new_node) {}

        base_iterator(const base_iterator<false>& it) : node(it.node) {}

        base_iterator& operator=(const base_iterator<false>& it) {
            node = it.node;
            return *this;
        }

        base_iterator operator++(int) {
            auto copy = *this;
            ++(*this);

            return copy;
        }

        base_iterator operator--(int) {
            auto copy = *this;
            --(*this);

            return copy;
        }

        base_iterator& operator++() {
            node = node->next;
            return *this;
        }
        
        base_iterator& operator--() {
            node = node->prev;
            return *this;        
        }

        bool operator==(const base_iterator& it) const {
            return node == it.node;
        }

        bool operator!=(const base_iterator& it) const {
            return node != it.node;
        }

        ref_type operator*() const {
            return node->val;
        }

        ptr_type operator->() const {
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
        return reverse_iterator(fakeNode);
    }

    reverse_iterator rend() {
        return reverse_iterator(fakeNode->prev);
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(fakeNode);
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(fakeNode->prev);
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(fakeNode);
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(fakeNode->prev);
    }

    void insert(const_iterator it, const T& t) {
        Node* new_node = makeNode(t);

        new_node->next = it.node;
        new_node->prev = it.node->prev;

        it.node->prev = new_node;
        new_node->prev->next = new_node;

        ++sz;
    }

    void erase(const_iterator it) {
        it.node->next->prev = it.node->prev;
        it.node->prev->next = it.node->next;

        NodeAllocTraits::destroy(node_alloc, it.node);
        NodeAllocTraits::deallocate(node_alloc, it.node, 1);

        --sz;
    }
};

#include <algorithm>
#include <chrono>
#include <cassert>

// struct Accountant {
//     // Some field of strange size
//     char arr[40];

//     static size_t ctor_calls;
//     static size_t dtor_calls;

//     static void reset() {
//         ctor_calls = 0;
//         dtor_calls = 0;
//     }

//     Accountant() {
//         ++ctor_calls;
//     }
//     Accountant(const Accountant&) {
//         ++ctor_calls;
//     }

//     Accountant& operator=(const Accountant&) {
//         // Actually, when it comes to assign one list to another,
//         // list can use element-wise assignment instead of destroying nodes and creating new ones
//         ++ctor_calls;
//         ++dtor_calls;
//         return *this;
//     }

//     Accountant(Accountant&&) = delete;
//     Accountant& operator=(Accountant&&) = delete;

//     ~Accountant() {
//         ++dtor_calls;
//     }
// };

// size_t Accountant::ctor_calls = 0;
// size_t Accountant::dtor_calls = 0;


// int main() {
//         Accountant::reset();

//         List<Accountant> lst(5);
//         assert(lst.size() == 5);
//         assert(Accountant::ctor_calls == 5);

//         List<Accountant> another = lst;
//         assert(another.size() == 5);
//         std::cout << Accountant::ctor_calls << '\n';
//         assert(Accountant::ctor_calls == 10);
//         assert(Accountant::dtor_calls == 0);

//         another.pop_back();
//         another.pop_front();
//         assert(Accountant::dtor_calls == 2);

//         lst = another; // dtor_calls += 5, ctor_calls += 3
//         assert(another.size() == 3);
//         assert(lst.size() == 3);

//         assert(Accountant::ctor_calls == 13);
//         assert(Accountant::dtor_calls == 7);

//     assert(Accountant::ctor_calls == 13);
//     assert(Accountant::dtor_calls == 13);
// }

