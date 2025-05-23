#ifndef _DLinkedList_HG_
#define _DLinkedList_HG_
#include <iostream>

template <class T>
class DLinkedList
{
public:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& item) : data(item), prev(nullptr), next(nullptr) {}
    };

    DLinkedList() : head(nullptr), tail(nullptr), current(nullptr), size(0) {}
    ~DLinkedList() { clear(); }

    // Mark methods that don't modify the list as const
    void moveToFirst() const { current = head; }
    void moveToLast() const { current = tail; }
    void moveNext() const { if (current && current->next) current = current->next; }
    void movePrevious() const { if (current && current->prev) current = current->prev; }
    T& getCurrent() const {
        static T dummy;
        if (!current) {
            std::cerr << "No current element, returning dummy object" << std::endl;
            return dummy;
        }
        return current->data;
    }
    unsigned int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }

    // Methods that modify the list (non-const)
    void insertBeforeCurrent(const T& item) {
        Node* newNode = new Node(item);
        if (!current) {
            head = tail = current = newNode;
        }
        else {
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev) {
                current->prev->next = newNode;
            }
            else {
                head = newNode;
            }
            current->prev = newNode;
            // If current was the tail, the new node is now the tail
            if (current == tail) {
                tail = newNode;
            }
        }
        size++;
    }

    void deleteAtCurrent() {
        if (!current) return;
        Node* temp = current;
        if (current->prev) {
            current->prev->next = current->next;
        }
        else {
            head = current->next;
        }
        if (current->next) {
            current->next->prev = current->prev;
            current = current->next;
        }
        else {
            tail = current->prev;
            current = head;
        }
        delete temp;
        size--;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = current = nullptr;
        size = 0;
    }
    template<typename Compare>
    void sort(Compare compareFunc);

    template<typename Compare>
    typename DLinkedList<T>::Node* mergeSort(Node* head, Compare compareFunc);

    template<typename Compare>
    typename DLinkedList<T>::Node* merge(Node* left, Node* right, Compare compareFunc);

private:
    Node* head;
    Node* tail;
    mutable Node* current; // Marked as mutable to allow modification in const methods
    unsigned int size;
};

template <class T>
template <typename Compare>
void DLinkedList<T>::sort(Compare compareFunc)
{
    if (size <= 1) return;
    head = mergeSort(head, compareFunc);

    // Update tail and size after sorting
    tail = head;
    if (tail) {
        while (tail->next) {
            tail = tail->next;
        }
    }
    current = head;  // Reset current to head after sorting
}

template <class T>
template <typename Compare>
typename DLinkedList<T>::Node* DLinkedList<T>::mergeSort(Node* head, Compare compareFunc)
{
    // Base cases: empty or single node
    if (!head || !head->next) {
        return head;
    }

    // Split list into two halves
    Node* slow = head;
    Node* fast = head->next;

    // Find middle point using slow and fast pointers
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Split the list
    Node* secondHalf = slow->next;
    slow->next = nullptr;
    if (secondHalf) {
        secondHalf->prev = nullptr;
    }

    // Recursively sort both halves
    Node* left = mergeSort(head, compareFunc);
    Node* right = mergeSort(secondHalf, compareFunc);

    // Merge the sorted halves
    return merge(left, right, compareFunc);
}

template <class T>
template <typename Compare>
typename DLinkedList<T>::Node* DLinkedList<T>::merge(Node* left, Node* right, Compare compareFunc)
{
    if (!left) return right;
    if (!right) return left;

    Node* result;
    if (compareFunc(left->data, right->data)) {
        result = left;
        result->next = merge(left->next, right, compareFunc);
        if (result->next) {
            result->next->prev = result;
        }
    }
    else {
        result = right;
        result->next = merge(left, right->next, compareFunc);
        if (result->next) {
            result->next->prev = result;
        }
    }

    result->prev = nullptr;  // First node should have no previous
    return result;
}

#endif