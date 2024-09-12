#ifndef __UNORDERED_SET_H
#define __UNORDERED_SET_H

#include <iostream>
#include "tuples.h"
#include "..\deque\deque.h"
#include "exceptions.h"

template<typename T>
class Stack {
    public:
        Stack() = default;
        Stack(int size) {
            size = (size < 1) ? 8 : size;
            this->A = new T[size];
            this->arrSize = size;
        }
        bool isEmpty() {
            return (!(this->n));
        }
        Stack& push(const T& item) {
            this->A[(this->n)++] = item;
            return *this;
        }
        Stack& pop() {
            --(this->n);
            return *this;
        }
        T top() {
            return this->A[this->n - 1];
        }
        ~Stack() {
            delete[] this->A;
            this->A = {};
        }
    private:
        T* A{};
        int n{};
        int arrSize{};
};

template<typename string_tp>
struct StringHash {
    unsigned long long operator()(const string_tp& str) const {
        unsigned long long h{}, mul{A};
        for (size_t i{}; i < str.size(); mul *= A, ++i)
            h += (mul * static_cast<int>(str[i]));
        return h;
    }
    constexpr static int A{(1 << 7) + 1};
};

template<>
struct StringHash<const char*> {
    unsigned long long operator()(const char* str) const {
        unsigned long long h{}, mul{A};
        for (; *str; mul *= A, ++str)
            h += (mul * static_cast<int>(*str));
        return h;
    }
    constexpr static int A{(1 << 7) + 1};
};

struct Identity {
    template<typename T>
    const T& operator()(const T& val) {
        return val;
    }
    template<typename T>
    T&& operator()(T&& val) {
        return static_cast<T&&>(val);
    }
};

template<typename key_tp, typename value_tp>
struct __UnOrderedMapNode {
    __UnOrderedMapNode(key_tp key, const value_tp& value):
        m_key{key}, m_value{new value_tp{value}}, left{}, right{} {}
    
    __UnOrderedMapNode(key_tp key, value_tp&& value):
        m_key{key}, m_value{new value_tp{static_cast<value_tp&&>(value)}}, left{}, right{} {}
    
    __UnOrderedMapNode(key_tp key, value_tp* ptr):
        m_key{key}, m_value{ptr}, left{}, right{} {}
    
    template<typename ...Args>
    __UnOrderedMapNode(key_tp key, Args&& ...args):
        m_key{key}, m_value{new value_tp(args...)}, left{}, right{} {}
    
    ~__UnOrderedMapNode() {
        delete this->m_value;
        this->m_value = {};
    }
    
    key_tp m_key;
    value_tp* m_value{};
    __UnOrderedMapNode* left{};
    __UnOrderedMapNode* right{};
    int height{1};
};
template<typename key_tp, typename value_tp>
class OrderedMap {
    using SetNode = __UnOrderedMapNode<key_tp, value_tp>;
    public:
        typedef                        value_tp                       value_type;
        typedef                          key_tp                       key_type;
        typedef                       value_tp&                       reference;
        typedef                 const value_tp&                       const_reference;
        typedef                       value_tp*                       pointer;
        typedef                 const value_tp*                       const_pointer;
        typedef                   deque<key_tp>                       KeyList;
    
    public:
        OrderedMap() = default;
        ~OrderedMap() {
            this->_clear(this->root);
            this->root = {};
        }

        OrderedMap& insert(key_tp key, const value_tp& value) {
            bool inserted{false};
            SetNode* x = this->newNode(key, value);
            this->root = this->_insert(this->root, x, inserted);
            if (inserted)
                ++(this->setSize);
            return *this;
        }
        OrderedMap& insert(key_tp key, value_tp&& value) {
            bool inserted{false};
            SetNode* x = this->newNode(static_cast<key_tp&&>(key), static_cast<value_tp&&>(value));
            this->root = this->_insert(this->root, x, inserted);
            if (inserted)
                ++(this->setSize);
            return *this;
        }
        template<typename ...Args>
        OrderedMap& insert(key_tp key, Args&& ...args) {
            bool inserted{false};
            this->root = this->_insert(this->root, new SetNode(args...), inserted);
            if (inserted)
                ++(this->setSize);
            return *this;
        }
        constexpr bool isEmpty() const {
            return (this->root == nullptr);
        }
        constexpr bool contains(const key_tp& key) const {
            const SetNode* n = this->_search(this->root, key);
            if (n)
                return (n->m_key == key);
            else
                return false;
        }
        value_type* search(const key_type& key) const {
            const SetNode* n = this->_search(this->root, key);
            return (n == nullptr) ? nullptr : n->m_value;
        }
        constexpr size_t size() const {
            return this->setSize;
        }
        const key_type& maxKey() const {
            if (this->isEmpty())
                throw SetEmptyError("OrderedMap::maxKey(): Set is empty");
            const SetNode* maxNode = this->getMaxNode(this->root);
            return maxNode->m_key;
        }
        const key_type& minKey() const {
            if (this->isEmpty())
                throw SetEmptyError("OrderedMap::minKey(): Set is empty");
            const SetNode* minNode = this->getMinNode(this->root);
            return minNode->m_key;
        }
        const value_type& maxValue() const {
            if (this->isEmpty())
                throw SetEmptyError("OrderedMap::maxValue(): Set is empty");
            const SetNode* maxNode = this->getMaxNode(this->root);
            return *(maxNode->m_value);
        }
        const value_type& minValue() const {
            if (this->isEmpty())
                throw SetEmptyError("OrderedMap::minValue(): Set is empty");
            const SetNode* minNode = this->getMinNode(this->root);
            return *(minNode->m_value);
        }
        KeyList keys() const {
            KeyList keyList(this->setSize);
            this->makeKeyList(this->root, keyList);
            return keyList;
        }
        value_tp& operator[](const key_tp& key) {
            const SetNode* n = this->_search(this->root, key);
            if (n == nullptr) {
                bool inserted{false};
                SetNode* x = this->newNode(key, value_tp{});
                this->root = this->_insert(this->root, x, inserted);
                return *(x->m_value);
            }
            else
                return *(n->m_value);
        }
        const value_tp& operator[](const key_tp& key) const {
            const SetNode* n = this->_search(this->root, key);
            if (n == nullptr)
                return {};
            return *(n->m_value);
        }
        friend std::ostream& operator<<(std::ostream& out, const OrderedMap& S) {
            out << "{ ";
            S._inorder(out, S.root);
            out << "}";
            return out;
        }

        const key_tp& getRoot() const {
            return this->root->m_key;
        }
        void traverse() {
            Stack<SetNode*> s{static_cast<int>(this->setSize)};
            SetNode* cur = {this->root};
            s.push(cur);
            while (!s.isEmpty()) {
                if (cur) {
                    do {
                        cur = cur->left;
                        s.push(cur);
                    } while(cur);
                }
                cur = s.top();
                if (cur)
                    std::cout << cur->m_key << ", ";
                s.pop();
                cur = s.top();
                if (cur)
                    std::cout << cur->m_key << ", ";
                s.pop();
                cur = cur->right;
                s.push(cur);
            }
        }
        int getHeight() {
            return this->height(this->root);
        }
        void inorder() {
            this->__inorder(this->root);
        }
        void preorder() {
            this->__preorder(this->root);
        }
        static void __inorder(SetNode* r) {
            if (r) {
                __inorder(r->left);
                std::cout << r->m_key << "  ";
                __inorder(r->right);
            }
        }
        static void __preorder(SetNode* r) {
            if (r) {
                std::cout << r->m_key << "  ";
                __preorder(r->left);
                __preorder(r->right);
            }
        }
    
    private:
        SetNode* root{};
        size_t setSize{};

        template<typename T>
        static SetNode* newNode(const key_tp& key, T&& value) {
            return new SetNode{key, std::forward<T>(value)};
        }
        SetNode* _insert(SetNode* r, SetNode* x, bool& flag) {
            if (r == nullptr) {
                flag = true;
                r = x;
            }
            else if (x->m_key < r->m_key) {
                r->left = _insert(r->left, x, flag);
            }
            else if (r->m_key < x->m_key) {
                r->right = _insert(r->right, x, flag);
            }
            else
                return r;
            r->height = max(height(r->left), height(r->right)) + 1;
            int k = balance(r);
            if (k > 1) {
                if (x->m_key > r->right->m_key)
                    return rotateLeft(r);
                else {
                    r->right = rotateRight(r->right);
                    return rotateLeft(r);
                }
            }
            else if (k < -1) {
                if (x->m_key < r->left->m_key)
                    return rotateRight(r);
                else {
                    r->left = rotateLeft(r->left);
                    return rotateRight(r);
                }
            }
            return r;
        }
        static const SetNode* _search(const SetNode* r, const key_tp& key) {
            if (r == nullptr)
                return nullptr;
            else if (key < r->m_key)
                return _search(r->left, key);
            else if (key > r->m_key)
                return _search(r->right, key);
            else
                return r;
        }
        static const SetNode* getMaxNode(const SetNode* r) {
            for (; r->right; r = r->right);
            return r;
        }
        static const SetNode* getMinNode(const SetNode* r) {
            for (; r->left; r = r->left);
            return r;
        }
        static SetNode* rotateLeft(SetNode* root) {
            SetNode* tmp = root->right;
            root->right = root->right->left;
            tmp->left = root;
            updateHeight(root);
            updateHeight(tmp);
            return tmp;
        }
        static SetNode* rotateRight(SetNode* root) {
            SetNode* tmp = root->left;
            root->left = root->left->right;
            tmp->right = root;
            updateHeight(root);
            updateHeight(tmp);
            return tmp;
        }
        static void _inorder(std::ostream& out, SetNode* root) {
            if (root) {
                _inorder(out, root->left);
                out << "(" << root->m_key << ", "
                    << *(root->m_value) << ", " 
                    << "h: " << height(root) << ", "
                    << "k: " << balance(root)
                    << ") ";
                _inorder(out, root->right);
            }
        }
        static void _clear(SetNode* root) {
            if (root) {
                _clear(root->left);
                _clear(root->right);
                delete root;
            }
        }
        static int max(int x, int y) {
            return (x > y) ? x : y;
        }
        static int height(SetNode* root) {
            return (root == nullptr) ? 0 : root->height;
        }
        static int balance(SetNode* root) {
            return height(root->right) - height(root->left);
        }
        static void updateHeight(SetNode* root) {
            root->height = max(height(root->left), height(root->right)) + 1;
        }
        static void makeKeyList(const SetNode* root, KeyList& keyList) {
            if (root) {
                makeKeyList(root->left, keyList);
                keyList += root->m_key;
                makeKeyList(root->right, keyList);
            }
        }
};

template<typename string_tp, typename value_tp>
struct __UnOrderedSMapNode {
    typedef unsigned long long hash_type;
    __UnOrderedSMapNode(const string_tp& key, const value_tp& value):
        m_key{key}, m_hash{hash(key)}, m_value{new value_tp{value}}, left{}, right{} {}
    
    __UnOrderedSMapNode(string_tp&& key, const value_tp& value):
        m_key{static_cast<string_tp&&>(key)}, m_hash{hash(key)}, m_value{new value_tp{value}}, left{}, right{} {}
    
    __UnOrderedSMapNode(const string_tp& key, hash_type h, const value_tp& value):
        m_key{key}, m_hash{h}, m_value{new value_tp{value}}, left{}, right{} {}
    
    __UnOrderedSMapNode(string_tp&& key, hash_type h, const value_tp& value):
        m_key{static_cast<string_tp&&>(key)}, m_hash{h}, m_value{new value_tp{value}}, left{}, right{} {}
    
    __UnOrderedSMapNode(const string_tp& key, hash_type h, value_tp&& value):
        m_key{key}, m_hash{h}, m_value{new value_tp{static_cast<value_tp&&>(value)}}, left{}, right{} {}
    
    __UnOrderedSMapNode(string_tp&& key, hash_type h, value_tp&& value):
        m_key{static_cast<string_tp&&>(key)}, m_hash{h}, m_value{new value_tp{static_cast<value_tp&&>(value)}}, left{}, right{} {}
    
    __UnOrderedSMapNode(string_tp&& key, value_tp&& value):
        m_key{static_cast<string_tp&&>(key)}, m_hash{hash(key)}, m_value{new value_tp{static_cast<value_tp&&>(value)}}, left{}, right{} {}
    
    __UnOrderedSMapNode(string_tp&& key, value_tp* ptr):
        m_key{static_cast<string_tp&&>(key)}, m_hash{hash(key)}, m_value{ptr}, left{}, right{} {}
    
    template<typename ...Args>
    __UnOrderedSMapNode(string_tp&& key, hash_type h, Args&& ...args):
        m_key{static_cast<string_tp&&>(key)}, m_hash{h}, m_value{new value_tp{args...}}, left{}, right{} {}

    template<typename ...Args>
    __UnOrderedSMapNode(const string_tp& key, hash_type h, Args&& ...args):
        m_key{key}, m_hash{h}, m_value{new value_tp{args...}}, left{}, right{} {}
    
    ~__UnOrderedSMapNode() {
        delete this->m_value;
        this->m_value = {};
    }
    
    static constexpr StringHash<string_tp> hash{};
    string_tp m_key;
    unsigned long long m_hash{};
    value_tp* m_value{};
    __UnOrderedSMapNode* left{};
    __UnOrderedSMapNode* right{};
    int height{1};
};

template<typename string_tp, typename value_tp>
class OrderedSMap {
    using SetNode = __UnOrderedSMapNode<string_tp, value_tp>;
    public:
        typedef                       string_tp                       key_type;
        typedef              unsigned long long                       hash_type;
        typedef                        value_tp                       value_type;
        typedef                       value_tp&                       reference;
        typedef                 const value_tp&                       const_reference;
        typedef                       value_tp*                       pointer;
        typedef                 const value_tp*                       const_pointer;
        typedef                 deque<key_type>                       KeyList;
    
    public:
        OrderedSMap() = default;
        ~OrderedSMap() {
            this->_clear(this->root);
            this->root = {};
        }
        OrderedSMap(std::initializer_list<Pair<string_tp, value_tp>>&& args) {
            auto it = args.begin();
            for (; it != args.end(); ++it)
                this->insert(it->getFirst(), it->getSecond());
        }
        OrderedSMap(OrderedSMap&& src): root{src.root}, setSize{src.setSize} {
            src.root = {};
            src.setSize = {};
        }
        OrderedSMap& operator=(OrderedSMap&& src) {
            if (this != &src) {
                this->_clear(this->root);
                this->root = src.root;
                this->setSize = src.setSize;
                src.root = {};
                src.setSize = {};
            }
            return *this;
        }
        OrderedSMap& insert(const key_type& key, const value_type& value) {
            hash_type h{hash(key)};
            bool inserted{false};
            SetNode* x = this->newNode(key, h, value);
            this->root = this->_insert(this->root, x, inserted);
            if (inserted)
                ++(this->setSize);
            return *this;
        }
        OrderedSMap& insert(key_type&& key, value_tp&& value) {
            hash_type h{hash(key)};
            bool inserted{false};
            SetNode* x = this->newNode(static_cast<key_type&&>(key), h, static_cast<value_tp&&>(value));
            this->root = this->_insert(this->root, x, inserted);
            if (inserted)
                ++(this->setSize);
            return *this;
        }
        template<typename ...Args>
        OrderedSMap& insert(const key_type& key, Args&& ...args) {
            hash_type h{hash(key)};
            bool inserted{false};
            this->root = this->_insert(this->root, new SetNode(key, args...), inserted);
            if (inserted)
                ++(this->setSize);
            return *this;
        }
        template<typename ...Args>
        OrderedSMap& insert(key_type&& key, Args&& ...args) {
            hash_type h{hash(key)};
            bool inserted{false};
            this->root = this->_insert(this->root, new SetNode(static_cast<key_type&&>(key), h, args...), inserted);
            if (inserted)
                ++(this->setSize);
            return *this;
        }
        bool isEmpty() const {
            return (this->root == nullptr);
        }
        constexpr size_t size() const noexcept {
            return this->setSize;
        }
        constexpr int getHeight() const noexcept {
            return this->height(this->root);
        }
        bool contains(const key_type& key) const {
            hash_type h{hash(key)};
            const SetNode* n = this->_search(this->root, h);
            if (n)
                return (n->m_hash == h);
            else
                return false;
        }
        value_type* search(const key_type& key) const {
            const SetNode* n = this->_search(this->root, hash(key));
            return (n == nullptr) ? nullptr : n->m_value;
        }
        KeyList keys() const {
            KeyList keyList(this->setSize);
            this->makeKeyList(this->root, keyList);
            return keyList;
        }
        value_tp& operator[](const key_type& key) {
            hash_type h = hash(key);
            const SetNode* n = this->_search(this->root, h);
            if (n == nullptr) {
                bool inserted{false};
                SetNode* x = this->newNode(key, h, value_tp{});
                this->root = this->_insert(this->root, x, inserted);
                if (inserted)
                    ++(this->setSize);
                return *(x->m_value);
            }
            else
                return *(n->m_value);
        }
        value_tp& operator[](key_type&& key) {
            hash_type h = hash(key);
            const SetNode* n = this->_search(this->root, h);
            if (n == nullptr) {
                bool inserted{false};
                SetNode* x = this->newNode(static_cast<key_type&&>(key), h, value_tp{});
                this->root = this->_insert(this->root, x, inserted);
                if (inserted)
                    ++(this->setSize);
                return *(x->m_value);
            }
            else
                return *(n->m_value);
        }
        const value_tp& operator[](const key_type& key) const {
            const SetNode* n = this->_search(this->root, hash(key));
            if (n == nullptr)
                return {};
            return *(n->m_value);
        }
        friend std::ostream& operator<<(std::ostream& out, const OrderedSMap& S) {
            out << "{ ";
            S._inorder(out, S.root);
            out << "}";
            return out;
        }

        const key_type& getRoot() const {
            return this->root->m_key;
        }
        void traverse() {
            Stack<SetNode*> s{static_cast<int>(this->setSize)};
            SetNode* cur = {this->root};
            s.push(cur);
            while (!s.isEmpty()) {
                if (cur) {
                    do {
                        cur = cur->left;
                        s.push(cur);
                    } while(cur);
                }
                cur = s.top();
                if (cur)
                    std::cout << cur->m_key << ", ";
                s.pop();
                cur = s.top();
                if (cur)
                    std::cout << cur->m_key << ", ";
                s.pop();
                cur = cur->right;
                s.push(cur);
            }
        }
        void inorder() {
            this->__inorder(this->root);
        }
        void preorder() {
            this->__preorder(this->root);
        }
        static void __inorder(SetNode* r) {
            if (r) {
                __inorder(r->left);
                std::cout << r->m_key << "  ";
                __inorder(r->right);
            }
        }
        static void __preorder(SetNode* r) {
            if (r) {
                std::cout << r->m_key << "  ";
                __preorder(r->left);
                __preorder(r->right);
            }
        }
    
    private:
        SetNode* root{};
        constexpr static StringHash<string_tp> hash{};
        size_t setSize{};

        template<typename T>
        static SetNode* newNode(const key_type& key, T&& value) {
            return new SetNode{key, std::forward<T>(value)};
        }
        template<typename T>
        static SetNode* newNode(const key_type& key, hash_type h, T&& value) {
            return new SetNode{key, h, std::forward<T>(value)};
        }
        template<typename T>
        static SetNode* newNode(key_type&& key, T&& value) {
            return new SetNode{static_cast<key_type&&>(key), std::forward<T>(value)};
        }
        template<typename T>
        static SetNode* newNode(key_type&& key, hash_type h, T&& value) {
            return new SetNode{static_cast<key_type&&>(key), h, std::forward<T>(value)};
        }
        SetNode* _insert(SetNode* r, SetNode* x, bool& flag) {
            if (r == nullptr) {
                flag = true;
                r = x;
            }
            else if (x->m_hash < r->m_hash) {
                r->left = _insert(r->left, x, flag);
            }
            else if (x->m_hash > r->m_hash) {
                r->right = _insert(r->right, x, flag);
            }
            else
                return r;
            r->height = max(height(r->left), height(r->right)) + 1;
            int k = balance(r);
            if (k > 1) {
                if (x->m_hash > r->right->m_hash)
                    return rotateLeft(r);
                else {
                    r->right = rotateRight(r->right);
                    return rotateLeft(r);
                }
            }
            else if (k < -1) {
                if (x->m_hash < r->left->m_hash)
                    return rotateRight(r);
                else {
                    r->left = rotateLeft(r->left);
                    return rotateRight(r);
                }
            }
            return r;
        }
        static const SetNode* _search(const SetNode* r, hash_type key) {
            if (r == nullptr)
                return nullptr;
            else if (key < r->m_hash)
                return _search(r->left, key);
            else if (key > r->m_hash)
                return _search(r->right, key);
            else
                return r;
        }
        static SetNode* rotateLeft(SetNode* root) {
            SetNode* tmp = root->right;
            root->right = root->right->left;
            tmp->left = root;
            updateHeight(root);
            updateHeight(tmp);
            return tmp;
        }
        static SetNode* rotateRight(SetNode* root) {
            SetNode* tmp = root->left;
            root->left = root->left->right;
            tmp->right = root;
            updateHeight(root);
            updateHeight(tmp);
            return tmp;
        }
        static void _inorder(std::ostream& out, SetNode* root) {
            if (root) {
                _inorder(out, root->left);
                out << "(" << root->m_key << ", "
                    << "h(x): " << root->m_hash << ", "
                    << *(root->m_value) << ", " 
                    << "h: " << height(root) << ", "
                    << "k: " << balance(root)
                    << ") ";
                _inorder(out, root->right);
            }
        }
        static void _clear(SetNode* root) {
            if (root) {
                _clear(root->left);
                _clear(root->right);
                delete root;
            }
        }
        static int max(int x, int y) {
            return (x > y) ? x : y;
        }
        static int height(SetNode* root) {
            return (root == nullptr) ? 0 : root->height;
        }
        static int balance(SetNode* root) {
            return height(root->right) - height(root->left);
        }
        static void updateHeight(SetNode* root) {
            root->height = max(height(root->left), height(root->right)) + 1;
        }
        static void makeKeyList(const SetNode* root, KeyList& keyList) {
            if (root) {
                makeKeyList(root->left, keyList);
                keyList += root->m_key;
                makeKeyList(root->right, keyList);
            }
        }
};

#endif  // __UNORDERED_SET_H
