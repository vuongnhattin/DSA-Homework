#include <iostream>
#include <cmath>

struct Node {
	int key;
	Node* next;
};

struct Bucket {
	int key;
	Node* listHead;
	Node* listTail;
	Bucket* next;
};

Bucket* findInsertBucketPosition(Bucket* bucketHead, int key) {
	// bucketHead is Dummy head
	Bucket* slow = bucketHead, * fast = bucketHead->next;

	while (fast && fast->key < key) {
		slow = slow->next;
		fast = fast->next;
	}

	return slow;
}

Bucket* insertBucket(Bucket* bucketHead, int key) {
	Bucket* p = findInsertBucketPosition(bucketHead, key);
	if (p->next && p->next->key == key) return p->next;

	Bucket* newBucket = new Bucket{ key, nullptr, nullptr, p->next };

	p->next = newBucket;
	return newBucket;
}

void insertList(Node*& listHead, Node*& listTail, Node* insertNode) {
	if (!listHead) listHead = listTail = insertNode;
	else {
		listTail->next = insertNode;
		listTail = insertNode;
	}
	listTail->next = nullptr;
}

// For example: if a = 1238273, position = 2, length = 3, then it returns 827 (position is counted from the right of a)
int getDigits(int number, int position, int length) {
	return number / (int)pow(10, position - 1) % (int)pow(10, length);
}

void arrayToList(int a[], int n, Node*& listHead) {
	for (int i = n - 1; i >= 0; i--) {
		Node* newNode = new Node{ a[i], listHead };
		listHead = newNode;
	}
}

void radixSort(int a[], int n, int k) {
	Node* listHead = nullptr;
	arrayToList(a, n, listHead);

	int maxElement = -1;
	for (Node* p = listHead; p; p = p->next) {
		if (p->key > maxElement) maxElement = p->key;
	}

	int maxLength = log10(maxElement) + 1;

	Bucket* bucketHead = new Bucket{ -1, nullptr, nullptr, nullptr }; // Dummy head

	for (int digitPos = 1; digitPos <= maxLength; digitPos += k) {
		// Put elements into their corresponding buckets
		for (Node* p = listHead; p;) {
			int digits = getDigits(p->key, digitPos, k);
			Bucket* newBucket = insertBucket(bucketHead, digits);

			Node* temp = p->next;
			insertList(newBucket->listHead, newBucket->listTail, p);

			p = temp;
		}

		// Connect buckets's list together
		listHead = bucketHead->next->listHead;

		for (Bucket* p = bucketHead->next; p->next; p = p->next) {
			p->listTail->next = p->next->listHead;
		}

		// Delete buckets
		for (Bucket* p = bucketHead->next; p;) {
			Bucket* temp = p->next;
			delete[] p;
			p = temp;
		}
		bucketHead->next = nullptr;
	}

	// Copy list back to array
	int idx = 0;
	for (Node* p = listHead; p; p = p->next) a[idx++] = p->key;
}

int main() {
	int a[] = { 123,432,2,32,6554,0,432,123,65,43,1,44,5,32,543,3214,4333 }, n = sizeof(a) / sizeof(a[0]);

	radixSort(a, n, 3);

	for (int i = 0; i < n; i++) std::cout << a[i] << " ";
}