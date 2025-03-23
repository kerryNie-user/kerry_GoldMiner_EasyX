#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <iostream>
#include <stdexcept>

// 定义链表节点类模板
template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

// 定义链表迭代器类模板
template <typename T>
class LinkedListIterator {
private:
    Node<T>* current;

public:
    LinkedListIterator(Node<T>* node) : current(node) {}

    // 重载解引用运算符
    T& operator*() {
        return current->data;
    }

    // 重载前置递增运算符
    LinkedListIterator& operator++() {
        current = current->next;
        return *this;
    }

    // 重载比较运算符
    bool operator!=(const LinkedListIterator& other) const {
        return current != other.current;
    }
};

// 定义链表类模板
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size_;

public:
    // 构造函数
    LinkedList() : head(nullptr), tail(nullptr), size_(0) {}

    // 析构函数
    ~LinkedList() {
        clear();
    }

    // 在链表末尾添加元素
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

    // 访问指定位置的元素
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

    // 获取链表的大小
    int size() const {
        return size_;
    }

    // 清空链表
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
            // 删除头节点
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
        size_--;
    }

    // 按值删除元素
    bool remove(const T& value) {
        Node<T>* prev = nullptr;
        Node<T>* current = head;

        while (current != nullptr) {
            if (current->data == value) {
                if (prev == nullptr) {
                    // 删除头节点
                    head = current->next;
                    if (head == nullptr) {
                        tail = nullptr;
                    }
                } else {
                    prev->next = current->next;
                    if (current == tail) {
                        tail = prev;
                    }
                }
                delete current;
                size_--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    // 返回指向链表起始位置的迭代器
    LinkedListIterator<T> begin() {
        return LinkedListIterator<T>(head);
    }

    // 返回指向链表结束位置的迭代器
    LinkedListIterator<T> end() {
        return LinkedListIterator<T>(nullptr);
    }
};

#endif //LINK_LIST_H