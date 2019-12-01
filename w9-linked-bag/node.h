
#ifndef node_h
#define node_h

#include <iostream>
#include <cstdlib>
#include <cassert>

template <typename T>
class Node {
public:
    using value_type = T;
    
    // CONSTRUCTOR
    Node(const value_type& init_data, Node* init_link) {
        data_ = init_data;
        link_ = init_link;
    }
    
    // Member functions to set the data and link fields:
    void set_data(const value_type& new_data) {
        data_ = new_data;
    }
    
    void set_link(Node* new_link) {
        link_ = new_link;
    }
    
    // Constant member function to retrieve the current data:
    value_type data() const {
        return data_;
    }
    
    // Two slightly different member functions to retreive
    // the current link:
    const Node* link() const {
        return link_;
    }
    
    Node* link() {
        return link_;
    }
    
private:
    value_type data_;
    Node* link_;
};


//// Iterator class //////
template<typename T>
class Iterator {
public:
    
    // constructor
    Iterator(Node<T>* initial = nullptr) {
        current_ = initial;
    }
    
    // returns the ACTUAL data element in this node,
    // not a copy of it
    // this is the meaning of &
    T operator*() const {
        return current_->data();
    }
    
    // returns THIS iterator, not a copy of it
    // this is the meaning of &
    Iterator& operator++() { // pre-increment
        current_ = current_->link();
        return *this;
    }
    
    Iterator operator++(int) { // post-increment
        Iterator temp =  *this;
        current_ = current_->link();
        return temp;
    }
    
    bool operator==(const Iterator other) const {
        return current_ == other.current_;
    }
    
    bool operator!=(const Iterator other) const {
        return current_ != other.current_;
    }
    
private:
    Node<T>* current_;
};

////// FUNCTIONS for the linked list toolkit /////

// finding number of nodes in the list
template <typename T>
size_t list_length(const Node<T>* head_ptr) {
    const Node<T>* cursor;
    size_t answer;
    
    answer = 0;
    for (cursor = head_ptr; cursor != nullptr; cursor = cursor->link( ))
        ++answer;
    
    return answer;
}

// adding at first
template <typename T>
void list_head_insert(Node<T>*& head_ptr, const T& entry) {
    head_ptr = new Node<T>(entry, head_ptr);
}

// insert after a node
template <typename T>
void list_insert(Node<T>* previous_ptr, const T& entry) {
    Node<T> *insert_ptr;
    
    insert_ptr = new Node<T>(entry, previous_ptr->link( ));
    previous_ptr->set_link(insert_ptr);
}

// adding at last
template <typename T>
void list_tail_insert(Node<T>*& head_ptr, const T& entry) {
    Node<T>* new_node = new Node<T>(entry, nullptr);
    Node<T>* current = head_ptr;
    if (current == nullptr) {
        list_head_insert(head_ptr, entry);
    } else {
        while (current->link() != nullptr) {
            current = current->link();
        }
        current->set_link(new_node);
    }
}


// removing the head
template <typename T>
void list_head_remove(Node<T>*& head_ptr) {
    Node<T> *remove_ptr;
    
    remove_ptr = head_ptr;
    head_ptr = head_ptr->link( );
    delete remove_ptr;
}

// removing node that is not the head
template <typename T>
void list_remove(Node<T>* previous_ptr) {
    Node<T> *remove_ptr;
    
    remove_ptr = previous_ptr->link();
    previous_ptr->set_link( remove_ptr->link());
    delete remove_ptr;
}

// printing the nodes of the linked list
template <typename T>
void list_print(Node<T>* head_ptr) {
    std::cout << "[ " ;
    for (Node<T>* curr = head_ptr; curr != nullptr; curr = curr->link()) {
        std::cout << curr->data() << " ";
    }
    std::cout << "]" << std::endl;
}


// searching in the list
template <typename T>
Node<T>* list_search(Node<T>* head_ptr, const T& target) {
    Node<T> *cursor;
    
    for (cursor = head_ptr; cursor != nullptr; cursor = cursor->link( ))
        if (target == cursor->data( ))
            return cursor;
    return nullptr;
}

// searching in the list
// you can either use this or the other search depending on how you want to implement your code
//template <typename T>
//bool list_search(Node<T>* head_ptr, const T& target) {
//    Node<T> *cursor;
//    
//    for (cursor = head_ptr; cursor != nullptr; cursor = cursor->link( ))
//        if (target == cursor->data( ))
//            return true;
//    return false;
//}

// searching in the list
template <typename T>
const Node<T>* list_search(const Node<T>* head_ptr, const T& target) {
    const Node<T> *cursor;
    
    for (cursor = head_ptr; cursor != nullptr; cursor = cursor->link( ))
        if (target == cursor->data( ))
            return cursor;
    return nullptr;
}

// Locating a particular node at a specified position
template <typename T>
Node<T>* list_locate(Node<T>* head_ptr, size_t position) {
    Node<T> *cursor;
    size_t i;
    
    assert (0 < position);
    cursor = head_ptr;
    for (i = 1; (i < position) && (cursor != nullptr); i++)
        cursor = cursor->link( );
    return cursor;
}

// Locating a particular node at a specified position
template <typename T>
const Node<T>* list_locate(const Node<T>* head_ptr, size_t position) {
    const Node<T> *cursor;
    size_t i;
    
    assert (0 < position);
    cursor = head_ptr;
    for (i = 1; (i < position) && (cursor != nullptr); i++)
        cursor = cursor->link( );
    return cursor;
}

// removing the node of the linked list
template <typename T>
void list_clear(Node<T>*& head_ptr) {
    while (head_ptr != nullptr)
        list_head_remove(head_ptr);
}

// copying one linked into another
template <typename T>
void list_copy(const Node<T>* source_ptr, Node<T>*& head_ptr, Node<T>*& tail_ptr) {
    head_ptr = nullptr;
    tail_ptr = nullptr;
    
    // Handle the case of the empty list.
    if (source_ptr == nullptr)
        return;
    
    // Make the head Node for the newly created list, and put data in it.
    list_head_insert(head_ptr, source_ptr->data( ));
    tail_ptr = head_ptr;
    
    // Copy the rest of the Nodes one at a time, adding at the tail of new list.
    source_ptr = source_ptr->link( );
    while (source_ptr != nullptr)
    {
        list_insert(tail_ptr, source_ptr->data( ));
        tail_ptr = tail_ptr->link( );
        source_ptr = source_ptr->link( );
    }
}


#endif /* node_h */
