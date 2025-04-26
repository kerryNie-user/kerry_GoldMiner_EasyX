#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(T&& value) : data(std::move(value)), next(nullptr) {}
    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedListIterator {
private:
    Node<T>* current;
    template <typename> friend class LinkedList;

public:
    LinkedListIterator(Node<T>* node) : current(node) {}

    T& operator*() {
        return current->data;
    }

    LinkedListIterator& operator++() {
        current = current->next;
        return *this;
    }

    bool operator!=(const LinkedListIterator& other) const {
        return current != other.current;
    }

    bool operator==(const LinkedListIterator& other) const {
        return current == other.current;
    }
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size_;

public:
    LinkedList() : head(nullptr), tail(nullptr), size_(0) {}

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size_(0) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            push_back(*it);
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            for (auto it = other.begin(); it != other.end(); ++it) {
                push_back(*it);
            }
        }
        return *this;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Index out of range for operator[]");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    
    ~LinkedList() { clear(); }

    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size_;
    }

    T back() {
        return tail->data;
    }

    int size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size_ = 0;
    }

    void erase(const T& t) {
        if (head == nullptr) {
            return;
        }
    
        if (head->data == t) {
            Node<T>* temp = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            delete temp;
            --size_;
            return;
        }
    
        Node<T>* prev = head;
        Node<T>* current = head->next;
    
        while (current != nullptr) {
            if (current->data == t) {
                prev->next = current->next;
                if (current == tail) {
                    tail = prev;
                }
                delete current;
                --size_;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    LinkedListIterator<T> begin() {
        return LinkedListIterator<T>(head);
    }

    LinkedListIterator<T> end() {
        return LinkedListIterator<T>(nullptr);
    }
};

#endif    