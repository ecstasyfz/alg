#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
class Vector {
public:
    static const int kSpareCapacity = 16;

    typedef T* iterator;
    typedef const T* const_iterator;

    void Init(int size, int capacity) {
        size_ = size;
        capacity_ = capacity;
        items_ = new T[capacity_];
    }

    explicit Vector(int init_size = 0) {
        Init(init_size, init_size + kSpareCapacity);
    }

    Vector(int init_size, const T default_item) {
        Init(init_size, init_size + kSpareCapacity);
        for (int i = 0; i < size_; ++i) {
            items_[i] = default_item;
        }
    }

    Vector(const Vector &rhs)
        :size_{rhs.size_}, capacity_{rhs.capacity_}, items_{nullptr} {
        items_ = new T[capacity_];
        for(int i = 0; i < size_; ++i) {
            items_[i] = rhs.items_[i];
        }
    }

    Vector& operator=(const Vector &rhs) {
        Vector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    ~Vector() {
        delete[] items_;
    }

    Vector(Vector&& rhs)
       :size_{rhs.size_}, capacity_{rhs.capacity_}, items_{rhs.items_} {
        rhs.size_ = 0;
        rhs.capacity_ = 0;
        rhs.items_ = nullptr;
    }

    Vector& operator=(Vector &&rhs) {
        std::swap(size_, rhs.size_);
        std::swap(capacity_, rhs.capacity_);
        std::swap(items_, rhs.items_);
        return *this;
    }


    void resize(int new_size) {
        if (new_size > capacity_) {
            reserve(new_size * 2);
        }
        size_ = new_size;
    }
    
    void reserve(int new_capacity) {
        if (new_capacity <= size_) {
            return;
        }
        T *new_items = new T[new_capacity];
        for (int i = 0; i < size_; ++i) {
            new_items[i] = std::move(items_[i]);
        }
        capacity_ = new_capacity;
        std::swap(items_, new_items);
        delete[] new_items;
    }
     

    T& operator[](int index) {
        return items_[index];
    }

    const T& operator[](int index) const {
        return items_[index];
    }

    bool empty() const {
        return size_ == 0;
    }

    int size() const {
        return size_;
    }

    int capacity() const {
        return capacity_;
    }

    void push_back(const T &x) {
        if (size_ == capacity_) {
            reserve(capacity_ * 2 + 1);
        }
        items_[size_++] = x;
    }

    void push_back(const T &&x)  {
        if (size_ == capacity_) {
            reserve(capacity_ * 2 + 1);
        }
        items_[size_++] = std::move(x);
    }

    void pop_back() {
        --size_;
    }

    const T& back() const {
        return items_[size_ - 1];
    }

    iterator begin() {
        return &items_[0];
    }

    const_iterator begin() const {
        return &items_[0];
    }

    iterator end() {
        return &items_[size_];
    }
 
    const_iterator end() const {
        return &items_[size_];
    }
    
private:
    int size_;
    int capacity_;
    T* items_;
};

#endif
