#ifndef LIST_H
#define LIST_H

template <typename T>
class List {
private:
    struct Node {
    T item;
    Node *prev;
    Node *next;

    Node(const T& d = T{}, Node *p = nullptr, Node *n = nullptr)
        :item{d}, prev{p}, next{n} {}

    Node(const T&& d, Node *p = nullptr, Node *n = nullptr)
        :item{std::move(d)}, prev{p}, next{n} {}
    };

public:
    class const_iterator {
    public:
        const_iterator()
            :current{nullptr} {}

        const T& operator*() const {
            return current->item;
        }

        const_iterator& operator++() {
            current = current->next;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator& operator--() {
            current = current->prev;
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const const_iterator &rhs) const {
            return current == rhs.current;
        } bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }

    protected:
        Node *current;
        
        const_iterator(Node *p)
            :current{p} {}

        friend class List<T>;
    };

    class iterator : public const_iterator {
    public:
        iterator() {}

        T& operator*() {
            return this->current->item;
        }
        const T& operator*() const {
            return const_iterator::operator*();
        }

        iterator& operator++() {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator& operator--() {
            this->current = this->current->prev;
            return *this;
        }

        iterator operator--(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

    protected:
        iterator(Node *p)
            :const_iterator{p} {}
        
        friend class List<T>;
    };

    void Init() {
        size_ = 0;
        head_ = new Node;
        tail_ = new Node;
        head_->next = tail_;
        tail_->prev = head_;
    }

    List() {
        Init();
    }

    List(const List &rhs) {
        Init();
        for(auto &x : rhs) {
            push_back(x);
        }
    }

    List& operator=(const List &rhs) {
        List copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    ~List() {
        clean();
        delete head_;
        delete tail_;
    }

    List(List &&rhs)
        :size_{rhs.size_}, head_{rhs.head_}, tail_{rhs.tail_} {
        rhs.size_ = 0;
        rhs.head_ = nullptr;
        rhs.tail_ = nullptr;
    }

    List& operator=(List &&rhs) {
        std::swap(size_, rhs.size_);
        std::swap(head_, rhs.head_);
        std::swap(tail_, rhs.tail_);
        return *this;
    }

    iterator begin() {
        return {head_->next};
    }

    const_iterator begin() const {
        return {head_->next};
    }

    iterator end() {
        return {tail_};
    }

    const_iterator end() const {
        return {tail_};
    }

    int size() const {
        return size_;
    }
    
    bool empty() const {
        return size_ == 0;
    }

    void clean() {
        while (!empty()) {
            pop_back();
        }
    }

    T& front() {
        return *begin();
    }

    const T& front() const {
        return *begin();
    }

    T& back() {
        return *--end();
    }

    const T& back() const {
        return *--end();
    }

    void push_front(const T& x) {
        insert(begin(), x);
    }

    void push_front(const T&& x) {
        insert(begin(), std::move(x));
    }

    void push_back(const T& x) {
        insert(end(), x);
    }

    void push_back(const T&& x) {
        insert(end(), std::move(x));
    }

    void pop_front() {
        erase(begin());
    }
    
    void pop_back() {
        erase(--end());
    }

    iterator insert(iterator it, const T& x) {
        Node *p = it.current;
        size_++;
        return {p->prev = p->prev->next = new Node{std::move(x), p->prev, p}};
    }

    iterator insert(iterator it, const T&& x) {
        Node *p = it.current;
        size_++;
        return {p->prev = p->prev->next = new Node{x, p->prev, p}};
    }

    iterator erase(iterator it) {
        Node *p = it.current;
        iterator retVal{p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        size_--;
        return retVal;
    }

    iterator erase(iterator from, iterator to) {
        for (iterator it = from; it != to;) {
            it = erase(it);
        }
        return to;
    }

private:
    int size_;
    Node *head_;
    Node *tail_;
};

#endif
