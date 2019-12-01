//

#ifndef lbag_h
#define lbag_h

#include <stdio.h>
#include <cstdlib>
#include "node.h"

template <typename T>
class LBag {
public:
    using value_type = T;
    using size_type = std::size_t;
    using iterator = Iterator<T>;
    
    // pre: none
    // post: creates an empty lbag
    LBag();
    
    // pre: none
    // post: creates an lbag that is a copy of given lbag
    LBag(const LBag &); // copy constructor
    
    ~LBag();
    
    void operator =(const LBag& other);
    
    size_type size() const;
    
    // finding the number of occurrence of the target
    size_type count(const T& target) const;
    
    // inserting an element at front
    void insert(const T& target);
    void append(const T& target); // inserting at end
    
    // printing the elements present in the LBag
    void print() const;
    
    //    void operator +=(const LBag &);
    
    bool find(const T& target);
    void find_replace(const T& target, const T& new_target);
    
    // removing one occurrence of the target
    bool erase_one(const T& target);
    
    // removing all occurrences of the target
    size_type erase(const T& target);
    
    ///// for iterating over the elements of the bag /////
    iterator begin();
    iterator end();
    
private:
    Node<T>* head_;
};

// TODO
template <typename T>
LBag<T> operator +(const LBag<T>& a, const LBag<T>& b);


template <typename T>
LBag<T>::LBag() {
    std::cout << "Constructor invoked:  " << this << std::endl;
    head_ = nullptr;
}

template <typename T>
LBag<T>::~LBag() {
    std::cout << "Desctructor invoked:  " << this << std::endl;
    list_clear(head_);
}

// copy constructor
template <typename T>
LBag<T>::LBag(const LBag<T> & b) {
    Node<T>* tail;
    list_copy(b.head_, head_, tail);
}

// overloading = operator to copy one bag into another
// same as copy constructor
template <typename T>
void LBag<T>::operator =(const LBag<T>& other) {
    
    if (this == &other)
        return;
    
    Node<T>* tail;
    list_clear(head_);
    list_copy(other.head_, head_, tail);
}

template <typename T>
typename LBag<T>::size_type LBag<T>::size() const {
    return list_length(head_);
}

template <typename T>
typename LBag<T>::size_type LBag<T>::count(const T & value) const {
    size_type ans = 0;
    
    for (Node<T>* p = head_; p != nullptr; p = p->link()) {
        if (p->data() == value)
            ++ans;
    }
    return ans;
}

// inserting at front
template <typename T>
void LBag<T>::insert(const T & value) {
    list_head_insert(head_, value);
}

// inserting at the end
template<typename T>
void LBag<T>::append(const T& target) {
    list_tail_insert(head_, target);
}


template<typename T>
void LBag<T>::print() const {
    list_print(head_);
}

// finding a specific element in the list
template<typename T>
bool LBag<T>::find(const T& target) {
    if (list_search(head_, target) != nullptr) {
        return true;
    }
    return false;
}

// replacing the element found with the new value
template<typename T>
void LBag<T>::find_replace(const T& target, const T& new_target) {
    Node<T>* target_ptr = list_search(head_, target);
    if (target_ptr == nullptr)
        return; // target isn't in the list, so no work to do
    target_ptr->set_data(new_target); // setting the new data
}

template<typename T>
bool LBag<T>::erase_one(const T& target) {
    Node<T>* target_ptr = list_search(head_, target);
    if (target_ptr == nullptr)
        return false; // target isn't in the list, so no work to do
    target_ptr->set_data(head_->data());
    list_head_remove(head_);
    return true;
}

template<typename T>
typename LBag<T>::size_type LBag<T>::erase(const T& target) {
    typename LBag<T>::size_type ans = 0;
    Node<T>* target_ptr;
    target_ptr = list_search(head_, target);
    while (target_ptr != nullptr) {
        // each time the target pointer is not a nullptr, we have another occurrence of the target
        // we remove this target using the same technique we used for erase_one
        target_ptr->set_data(head_->data());
        target_ptr = target_ptr->link();
        target_ptr = list_search(target_ptr,target);
        list_head_remove(head_);
        ++ans;
    }
    return ans;
}

//// for iterating the elements of the LBag

template <typename T>
typename LBag<T>::iterator LBag<T>::begin(){ //need typename for templated typedefs ONLY
    iterator i(head_);
    return i; //return iterator(head)
}

template <typename T>
typename LBag<T>::iterator LBag<T>::end(){
    return nullptr;
    
}

#endif /* lbag_h */
