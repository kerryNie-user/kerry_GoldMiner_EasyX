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

    LinkedList(LinkedList&& other) noexcept : head(other.head), tail(other.tail), size_(other.size_) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
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

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size_ = other.size_;
            other.head = nullptr;
            other.tail = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    ~LinkedList() {
        clear();
    }

    void push_back(T&& value) {
        Node<T>* newNode = new Node<T>(std::move(value));
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size_;
    }

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

    T& operator[](int index) {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
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

    void removeAt(int index) {
        if (index < 0 || index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) {
            Node<T>* temp = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            delete temp;
        } else {
            Node<T>* prev = head;
            for (int i = 0; i < index - 1; ++i) {
                prev = prev->next;
            }
            Node<T>* current = prev->next;
            prev->next = current->next;
            if (current == tail) {
                tail = prev;
            }
            delete current;
        }
        --size_;
    }

    LinkedListIterator<T> erase(LinkedListIterator<T> it) {
        if (it == end()) {
            return it;
        }
        Node<T>* current = it.current;
        if (current == head) {
            head = current->next;
            if (head == nullptr) {
                tail = nullptr;
            }
        } else {
            Node<T>* prev = head;
            while (prev->next != current) {
                prev = prev->next;
            }
            prev->next = current->next;
            if (current == tail) {
                tail = prev;
            }
        }
        auto nextIt = LinkedListIterator<T>(current->next);
        delete current;
        --size_;
        return nextIt;
    }

    LinkedListIterator<T> begin() {
        return LinkedListIterator<T>(head);
    }

    LinkedListIterator<T> end() {
        return LinkedListIterator<T>(nullptr);
    }
};

#endif    