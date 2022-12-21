#ifndef LAB4_CPP_LIBRARY_MY_VECTOR_H
#define LAB4_CPP_LIBRARY_MY_VECTOR_H

#include <iostream>

template <typename T>
class my_vector {
private:
    T *arr_;
    size_t size_{};
    size_t capacity_{};
public:
    class iterator{
        private:
            T* iterator_;
        public:
            iterator(T* other = nullptr){
                iterator_ = other;
            }
            iterator operator =(iterator other){
                std::swap((*this).iterator_, iter.iterator_);
                return *this;
            }
            T& operator *(){
                return *iterator_;
            }
            iterator& operator++(){
                iterator_++;
                return *this;
        };
    my_vector() {
        arr_ = new T[1];
        capacity_ = 1;
    }
    [[nodiscard]] bool isEmpty () const{
        return size_ == 0;
    }
    [[nodiscard]] size_t size () const {
        return size_;
    }
    [[nodiscard]] size_t capacity () const {
        return capacity_;
    }
    void add_memory () {
        T *tmp = arr_;
        capacity_ *= 2;
        arr_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) { arr_[i] = tmp[i]; }
        delete []tmp;
    }
    void push_back (const T &value) {
        if (size_ >= capacity_) add_memory();
        arr_[size_++] = value;
    }
    void erase (iterator iter) {
        for (auto i = iter; i < cend() - 1; i++) {
            arr_[i] = arr_[i + 1];
        }
        size_--;
    }
    iterator begin() {
        return iterator(arr_);
    }
    iterator end() {
        return iterator(arr_ + size_);
    }
    T &operator [] (size_t index)  {
        return arr_[index];
    }
    const T &operator [] (size_t index) const {
        return arr_[index];
    }
    ~my_vector () {
        delete [] arr_;
    }
};

#endif
