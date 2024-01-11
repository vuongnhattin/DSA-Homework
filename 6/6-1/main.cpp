#include <iostream>
#include <fstream>
#include <vector>

typedef struct Leader* lref;
typedef struct Trailer* tref;

struct Leader {
    int key;
    int count;
    lref next;
    tref trails;
};

struct Trailer {
    lref id;
    tref next;
};

// Find Leader with key x, if not exist yet then add to the end of Leader list
lref findLeader(lref& head, lref& tail, int x) {
    lref p = head;

    tail->key = x;

    while (p->key != x) {
        p = p->next;
    }

    if (p == tail) {
        tail = new Leader;

        p->count = 0;
        p->trails = NULL;
        p->next = tail;
    }

    return p;
}

void splitLeaderWithNoPrecedence(lref& head, lref& tail) {
	lref p = head;
    head = nullptr;

    while (p != tail) {
        lref tmp = p->next;

        if (p->count == 0) {
            p->next = head;
            head = p;
        }

        p = tmp;
    }
}

// Add new order x < y
void addOrder(lref& head, lref& tail, int x, int y) {
    lref xNode = findLeader(head, tail, x);
    lref yNode = findLeader(head, tail, y);

    tref xTrail = new Trailer{ yNode, xNode->trails };
    xNode->trails = xTrail;

    //increase the number of precedences
    yNode->count++;
}

void createLeadersFromPairs(lref& head, lref& tail, std::vector<std::pair<int, int>> orders) {
	head = new Leader{ -1, 0, nullptr, nullptr };
	tail = head;

	for (int i = 0; i < orders.size(); i++) {
        addOrder(head, tail, orders[i].first, orders[i].second);
    }
}

void topoSort(std::vector<std::pair<int, int>> orders) {
	lref head, tail;
	createLeadersFromPairs(head, tail, orders);

    splitLeaderWithNoPrecedence(head, tail);

    lref p = head;

    while (p) {
        std::cout << p->key << " ";

        tref t = p->trails;

        p = p->next;

        for (tref q = t; q; q = q->next) {
            lref succNode = q->id;

            succNode->count--;

            if (succNode->count == 0) {
                succNode->next = p;

                p = succNode;
            }
        }
    }
}

std::vector<std::pair<int, int>> parseFile(std::string fileName) {
    std::vector<std::pair<int, int>> orders;

    std::pair<int, int> p;
    char ch1, ch2, ch3;

    std::ifstream inFile;
    inFile.open(fileName);

    while (!inFile.eof()) {
        inFile >> ch1 >> p.first >> ch2 >> p.second >> ch3;

        if (inFile.eof()) {
            break;
        }
        
        orders.push_back(p);
    }

    inFile.close();

    return orders;
}

int main() {
    std::vector<std::pair<int, int>> orders = parseFile("input.txt");

    topoSort(orders);

    return 0;
}