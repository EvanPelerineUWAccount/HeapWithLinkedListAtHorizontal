#include <iostream>
#include <string>
// Evan Pelerine & John Leeds Data Structures Heap With Linked List at Horizontal
// Orignal 4/30/2022 | Re-worked / Condensed to One File 3/14/2025
// ==================== Request Class ====================

class Request {
public:
    int priority;
    std::string name;

    // Default constructor
    Request() : priority(-1), name("None") {}

    // Parameterized constructor
    Request(int p, std::string n) : priority(p), name(n) {}
};

// ==================== Node Class ====================

class Node {
public:
    Request data;
    Node* lChild;
    Node* rChild;
    Node* parent;
    Node* right;

    // Default constructor
    Node() : lChild(nullptr), rChild(nullptr), parent(nullptr), right(nullptr), data(Request()) {}

    // Parameterized constructor
    Node(Request r) : lChild(nullptr), rChild(nullptr), parent(nullptr), right(nullptr), data(r) {}
};

// ==================== PriorityQueue Class ====================

class PriorityQueue {
public:
    PriorityQueue() : top(nullptr), botLevel(nullptr) {}

    bool insert(Request r) {
        Node* newNode = new Node(r);
        if (isEmpty()) {
            top = newNode;
            botLevel = newNode;
            return true;
        }
        Node* insertParent = findInsertParent();
        if (!insertParent) { // New layer
            insertParent = botLevel;
            insertParent->lChild = newNode;
            newNode->parent = insertParent;
            botLevel = newNode;
        }
        else if (!insertParent->lChild) {
            insertParent->lChild = newNode;
            newNode->parent = insertParent;
            findBot()->right = newNode;
        }
        else {
            insertParent->rChild = newNode;
            newNode->parent = insertParent;
            findBot()->right = newNode;
        }
        correctPosition(newNode);
        return true;
    }

    Request remove() {
        if (isEmpty()) {
            Request blankRequest;
            return blankRequest;
        }
        Request oldTop = top->data;
        if (!top->lChild && !top->rChild) { // Pop last node
            top = nullptr;
            return oldTop;
        }

        Node* oldBot = findBot();
        swap(top, oldBot); // Swap bottom value to top
        Node* oldBotParent = oldBot->parent;
        // Pop bottom node (former top)
        if (oldBotParent->rChild) {
            oldBotParent->rChild = nullptr;
        }
        else {
            oldBotParent->lChild = nullptr;
        }
        // Remove link in linked list of the level
        if (!botLevel->right) botLevel = botLevel->parent;
        else {
            Node* search = botLevel;
            while (search->right->right) {
                search = search->right;
            }
            search->right = nullptr;
        }

        correctPosition(top);

        return oldTop;
    }

    bool isFull() const {
        return false;
    }

    bool isEmpty() const {
        return !top;
    }

private:
    Node* top;
    Node* botLevel;

    bool swap(Node* n1, Node* n2) {
        if (!n1 || !n2) return false;

        Request temp = n1->data;
        n1->data = n2->data;
        n2->data = temp;
        return true;
    }

    void correctPosition(Node* cur) {
        int curPriority = cur->data.priority;
        if (cur->parent && curPriority < cur->parent->data.priority) { // move up
            swap(cur, cur->parent);
            correctPosition(cur->parent);
            return;
        }
        int childDirection = minChild(cur);
        if (childDirection == 0) { // no children
            return;
        }
        if (childDirection == 1 && curPriority > cur->lChild->data.priority) {
            swap(cur, cur->lChild);
            correctPosition(cur->lChild);
            return;
        }
        if (childDirection == 2 && curPriority > cur->rChild->data.priority) {
            swap(cur, cur->rChild);
            correctPosition(cur->rChild);
            return;
        }
    }

    int minChild(Node* cur) const {
        if (!cur->lChild && !cur->rChild) return 0;
        if (!cur->rChild) return 1;
        if (!cur->lChild) return 2;
        if (cur->lChild->data.priority <= cur->rChild->data.priority) {
            return 1;
        }
        return 2;
    }

    Node* findBot() const {
        Node* search = botLevel;
        while (search->right) {
            search = search->right;
        }
        return search;
    }

    Node* findInsertParent() const {
        Node* search = findBot();
        if (!search->parent) return nullptr; // special case: height == 0
        if (!search->parent->rChild) return search->parent;
        if (search->parent->right) return search->parent->right;
        return nullptr;
    }
};

// ==================== Test Function ====================

void testPriorityQueue() {
    PriorityQueue test;
    int priorities[9] = {5, 13, 2, 1, 55, 2, 15, 6, 17};
    std::string tasks[9] = {
        "Hope It Works", "Make it One File", "", "71827", "____",
        "TestSix", "TestSeven", "TestEight",
        "TestNine", 
    };
    for (int i = 0; i < 9; i++) {
        Request newRequest(priorities[i], tasks[i]);
        test.insert(newRequest);
    }
    while (!test.isEmpty()) {
        Request r = test.remove();
        std::cout << "Priority: " << r.priority << "\tTask: " << r.name << "\n";
    }
}

// ==================== Main Function Call ====================

int main() {
    testPriorityQueue();
    return 0;
}