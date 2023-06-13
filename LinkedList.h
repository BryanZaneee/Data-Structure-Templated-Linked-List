#ifndef PROJECT_1_LINKEDLIST_H
#define PROJECT_1_LINKEDLIST_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:

    class Node {
    public:
        T data;  // Hold the actual data
        Node* next; // A pointer to the next node in the list
        Node* prev;

        // Constructor to initialize a Node with certain data and set the next pointer to null
        Node(T data) {
            this->data = data;
            this->next = nullptr;
            this->prev = nullptr;
        }
    };
    typedef Node NodeType;
    typedef std::vector<Node*> NodeVector;
    // Constructor to initialize an empty list
    LinkedList (): head(nullptr), tail(nullptr), count(0) {}

    // LinkedList destructor to delete all the nodes in the list.
    ~LinkedList() {
        while (head){
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        head = nullptr;
        tail = nullptr;
    }

    // Add a node with data at the beginning of the list
    void AddHead(T data) {
            Node *newNode = new Node(data); // create a new node
            if (head == nullptr) { // If the list is empty
                head = newNode; // The new Node is now the head
                tail = newNode; // It is also the tail node
            } else {
                newNode->next = head; // the new Node points to the new head
                head->prev = newNode;
                head = newNode; // the new Node becomes the new head
            }
            count++; // Increase the Node count
        }

    // Add a node with data at the end of the list
    void AddTail(T data) {
        Node* newNode = new Node(data); // Create a new node with the data
        if (tail == nullptr){ // If the list is empty
            tail = newNode; // The new node will become the tail
            head = newNode; // As well as the head
        } else { // if it is not empty
            newNode->prev = tail;
            tail->next = newNode; // The new Node points to the current tail
            tail = newNode; // The new Node becomes the new tail
        }
        count++; // Increase the count size
    }

    // Method to add more than one node at the start of the list
    void AddNodesHead(T* data, int size) {
        for (int i = size -1; i >= 0; --i) {
            AddHead(data[i]); // Use AddHead to add each element to the head of the list
        }
    }

    // Method for adding multiple nodes at the tail of the list
    void AddNodesTail(T* data, int size) {
        for (int i = 0; i < size; ++i) {
            AddTail(data[i]); // Use AddTail to add each element to the head of the list
        }
    }

    // Method to get the number of nodes in the list.
    int NodeCount() {
        return count; // Return the count of nodes.
    }

    // Method to print the list from head to tail.
    void PrintForward() {
        Node* current = head; // Start from the head of the list.
        while (current) { // While the current node is not nullptr (i.e., not the end of the list)...
            cout << current->data << endl; // ...print the data of the current node...
            current = current->next; // ...and move to the next node.
        }
    }

    // Method to print the list from tail to head. This would require a doubly-linked list to implement.
    void PrintReverseHelper(Node* node) {
        if(node == nullptr) return; // base case, stop when we reach the end of the list
        PrintReverseHelper(node->next); // recursive call to the next node
        cout << node->data << endl; // print data on the way back
    }

    // Prints the list from tail to head
    void PrintReverse() {
        PrintReverseHelper(head); // start from the head
    }

    // Return a pointer to the head node
    Node* Head() {
        return head;
    }

    // Return a pointer to the tail node
    Node* Tail() {
        return tail;
    }

    // Get a node at a specific index
    Node* GetNode(int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    // Get a node at a specific index (const version)
    const Node* GetNode(int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    // Overload the [] operator to get a node at a specific index
    Node* operator[](int index) {
        return GetNode(index);
    }

    // Overload the [] operator to get a node at a specific index (const version)
    const Node* operator[](int index) const {
        return GetNode(index);
    }

    // Find the first node with a given value
    Node* Find(T value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return current; // node found
            }
            current = current->next;
        }
        return nullptr; // node not found
    }

    // Find the first node with a given value (const version)
    const Node* Find(T value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return current; // node found
            }
            current = current->next;
        }
        return nullptr; // node not found
    }

    // Find all nodes with a given value
    void FindAll(NodeVector& nodes, T value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                nodes.push_back(current);
            }
            current = current->next;
        }
    }

    // Copy constructor
    LinkedList(const LinkedList<T>& source) : head(nullptr), tail(nullptr), count(0) {
        Node* current = source.head;
        while (current) {
            this->AddTail(current->data);
            current = current->next;
        }
    }

    // Copy assignment operator
    LinkedList<T>& operator=(const LinkedList<T>& source) {
        if (this != &source) { // prevent self-assignment
            // First, deallocate any nodes that are currently in the list
            while (head) {
                Node* tmp = head;
                head = head->next;
                delete tmp;
            }
            head = nullptr;
            tail = nullptr;
            count = 0;

            // Then, copy nodes from the source list
            Node* current = source.head;
            while (current) {
                this->AddTail(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Insert a node with data before a given node
    void InsertBefore(Node* node, T data) { // Inserts node before given node
        if (node == nullptr) { // Check if node is null
            throw std::invalid_argument("Invalid node");
        }
        Node* newNode = new Node(data); // Create new node
        newNode->prev = node->prev; // Set prev pointer of new node
        newNode->next = node; // Set next pointer of new node
        if (node->prev) { // Check if given node has a prev node
            node->prev->next = newNode;
        } else { // If given node is head, set head to new node
            head = newNode;
        }
        node->prev = newNode; // Set prev of given node to new node
        count++; // Increase count
    }

    void InsertAfter(Node* node, T data) { // Inserts node after given node
        if (node == nullptr) { // Check if node is null
            throw std::invalid_argument("Invalid node");
        }
        Node* newNode = new Node(data); // Create new node
        newNode->prev = node; // Set prev pointer of new node
        newNode->next = node->next; // Set next pointer of new node
        if (node->next) { // Check if given node has a next node
            node->next->prev = newNode;
        } else { // If given node is tail, set tail to new node
            tail = newNode;
        }
        node->next = newNode; // Set next of given node to new node
        count++; // Increase count
    }

    void InsertAt(T data, int index) { // Inserts node at given index
        if (index < 0 || index > count) { // Check if index is in range
            throw std::out_of_range("Index out of range");
        }
        if (index == 0) { // If index is 0, add to head
            AddHead(data);
        } else if (index == count) { // If index is count, add to tail
            AddTail(data);
        } else { // Otherwise, insert before node at index
            Node* current = GetNode(index);
            InsertBefore(current, data);
        }
    }

    bool operator==(const LinkedList<T>& other) const { // Compares two linked lists
        if (count != other.count) { // Checks if counts are equal
            return false;
        }
        Node* current1 = head;
        Node* current2 = other.head;
        while (current1 && current2) {
            if (current1->data != current2->data) { // Compares data of nodes
                return false;
            }
            current1 = current1->next; // Move to next node in this list
            current2 = current2->next; // Move to next node in other list
        }
        return true; // Lists are equal
    }


private:
    Node* head; // The first node in the list
    Node* tail; // The last Node in the list
    int count;
};

#endif //PROJECT_1_LINKEDLIST_H