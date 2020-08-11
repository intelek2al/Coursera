#include "test_runner.h"

#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
	struct Node {
		T value;
		Node* next = nullptr;
	};

	~LinkedList() {
		while (head != nullptr)
			PopFront();
	}

	void PushFront(const T& value) {
		if (head == nullptr) {
			head = create_node(value);
		}
		else {
			Node *tmp_head = head;
			head = create_node(value);
			head->next = tmp_head;
		}
	}
	void InsertAfter(Node* node, const T& value) {
		if (node == nullptr) {
			PushFront(value);
		}
		else if (node->next == nullptr) {
			node->next = create_node(value);
		}
		else {
			Node *tmp_next = node->next;
			node->next = create_node(value);
			node->next->next = tmp_next;
		}
	}
	void RemoveAfter(Node* node) {
		// if (head == node)
		// 	PopFront();
		if (node == nullptr) {
			PopFront();
		}
		else if (node->next != nullptr) {
			Node *tmp_node = node->next;
			node->next = node->next->next;
			free_node(tmp_node);
		}
	}
	void PopFront() {
		if (head == nullptr)
			return;
		if (head->next != nullptr) {
			Node* tmp_head = head;
			head = head->next;
			free_node(tmp_head);
		}
		else {
			free_node(head);
			head = nullptr;
		}
	}

	Node* GetHead() {
		return head;
	}
	const Node* GetHead() const {
		return head;
	}

private:
	Node* head = nullptr;

	void free_node(Node* &node) {
		delete node;
	}
	Node *create_node(const T& value) {
		Node *node = new Node;
		node->value = value;
		return node;
	}
};

template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
	vector<T> result;
	for (auto node = list.GetHead(); node; node = node->next) {
		result.push_back(node->value);
	}
	return result;
}

void TestPushFront() {
	LinkedList<int> list;

	list.PushFront(1);
	ASSERT_EQUAL(list.GetHead()->value, 1);
	list.PushFront(2);
	ASSERT_EQUAL(list.GetHead()->value, 2);
	list.PushFront(3);
	ASSERT_EQUAL(list.GetHead()->value, 3);

	const vector<int> expected ={ 3, 2, 1 };
	ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
	LinkedList<string> list;

	list.PushFront("a");
	auto head = list.GetHead();
	ASSERT(head);
	ASSERT_EQUAL(head->value, "a");

	list.InsertAfter(head, "b");
	const vector<string> expected1 ={ "a", "b" };
	ASSERT_EQUAL(ToVector(list), expected1);

	list.InsertAfter(head, "c");
	const vector<string> expected2 ={ "a", "c", "b" };
	ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
	LinkedList<int> list;
	for (int i = 1; i <= 5; ++i) {
		list.PushFront(i);
	}

	const vector<int> expected ={ 5, 4, 3, 2, 1 };
	ASSERT_EQUAL(ToVector(list), expected);

	auto next_to_head = list.GetHead()->next;
	list.RemoveAfter(next_to_head);
	list.RemoveAfter(next_to_head);

	const vector<int> expected1 ={ 5, 4, 1 };
	ASSERT_EQUAL(ToVector(list), expected1);

	while (list.GetHead()->next) {
		list.RemoveAfter(list.GetHead());
	}
	ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
	LinkedList<int> list;

	for (int i = 1; i <= 5; ++i) {
		list.PushFront(i);
	}
	for (int i = 1; i <= 5; ++i) {
		list.PopFront();
	}
	ASSERT(list.GetHead() == nullptr);
}
void TestNull() {
	LinkedList<int> list;

	list.PopFront();
	ASSERT(list.GetHead() == nullptr);
}

void TestLast() {
	LinkedList<int> list;
	list.PushFront(1);
	LinkedList<int>::Node* node_to_remove = nullptr;
	list.RemoveAfter(node_to_remove);
	ASSERT(list.GetHead() == nullptr);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestPushFront);
	RUN_TEST(tr, TestInsertAfter);
	RUN_TEST(tr, TestRemoveAfter);
	RUN_TEST(tr, TestPopFront);
	RUN_TEST(tr, TestLast);
	RUN_TEST(tr, TestNull);
	system("leaks -q a.out");
	return 0;
}
