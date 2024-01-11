#include <iostream>
#include <string>

using namespace std;

struct Object {
    string id;
    int order;
    int priority;
};

struct Node {
    Object key;
    Node* next;
};

struct PriorityQueueList {
    Node* front;

    PriorityQueueList() : front(nullptr) {}
};

bool isEmpty(const PriorityQueueList& pq) {
    return pq.front == nullptr;
}

void insert(PriorityQueueList& pq, const Object& obj) {
    Node* newNode = new Node{obj, nullptr};

    if (isEmpty(pq)) {
        pq.front = newNode;
        return;
    }

    // Find the correct position to insert based on priority
    Node* current = pq.front;
    Node* prev = nullptr;
    while (current != nullptr && current->key.priority < obj.priority) {
        prev = current;
        current = current->next;
    }

    // Insert the new node
    if (prev == nullptr) {
        // Insert at the beginning
        newNode->next = pq.front;
        pq.front = newNode;
    } 
    else {
        newNode->next = current;
        prev->next = newNode;
    }
}

Object extract(PriorityQueueList& pq) {
    if (isEmpty(pq)) {
        cerr << "Error: Priority queue is empty." << endl;
        // Handle error accordingly, here we just return an Object with an empty string.
        return Object{"", 0, 0};
    }

    Object result = pq.front->key;
    Node* temp = pq.front;
    pq.front = pq.front->next;

    delete temp;
    return result;
}

void remove(PriorityQueueList& pq, const string& objectId) {
    if (isEmpty(pq)) {
        cerr << "Error: Priority queue is empty." << endl;
        return;
    }

    Node* current = pq.front;
    Node* prev = nullptr;

    // Search for the node with the specified objectId
    while (current != nullptr && current->key.id != objectId) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cerr << "Error: Object with id " << objectId << " not found." << endl;
        return;
    }

    // Remove the found node
    if (prev == nullptr) {
        // Removing from the front
        pq.front = current->next;
    } 
    else {
        prev->next = current->next;
    }

    delete current;
}

void changePriority(PriorityQueueList& pq, const string& objectId, int newPriority) {
    if (isEmpty(pq)) {
        cerr << "Error: Priority queue is empty." << endl;
        return;
    }

    Node* current = pq.front;

    // Search for the node with the specified objectId
    while (current != nullptr && current->key.id != objectId) {
        current = current->next;
    }

    if (current == nullptr) {
        cerr << "Error: Object with id " << objectId << " not found." << endl;
        return;
    }

    // Update the priority of the found node
    Object newObj = current->key;
    newObj.priority = newPriority;

    // Reorganize the queue based on the updated priority
    remove(pq, objectId);
    insert(pq, newObj);
}

int main() {
    // Example usage
    PriorityQueueList priorityQueue;

    insert(priorityQueue, {"A", 1, 10});
    insert(priorityQueue, {"B", 2, 5});
    insert(priorityQueue, {"C", 3, 8});
    insert(priorityQueue, {"D", 4, 8});

    changePriority(priorityQueue, "B", 1);
    remove(priorityQueue, "A");

    cout << "Priority queue content:" << endl;
    while (!isEmpty(priorityQueue)) {
        Object obj = extract(priorityQueue);
        cout << "Object ID: " << obj.id << ", Priority: " << obj.priority << endl;
    }

    return 0;
}
