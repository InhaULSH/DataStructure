#include <iostream>
#include <string>

class Node {
public :
	int Data;
	Node* Next;

	Node(int Value) {
		this->Data = Value;
		this->Next = NULL;
	}
};

class LinkedList {
public :
	Node* Front;
	Node* Rear;

	LinkedList() {
		this->Front = NULL;
		this->Rear = NULL;
	}
	void addEnd(int Value) {
		Node* NewNode = new Node(Value);
		if (Front == NULL) {
			Front = Rear = NewNode;
		}
		else {
			Rear->Next = NewNode;
			Rear = NewNode;
		}
	}
	void removeFront() {
		if (Front != NULL) {
			Node* TempNode = Front;
			Front = Front->Next;
			delete TempNode;
		}
	}
};

class ListQueue {
public :
	ListQueue() {
		this->Que = new LinkedList();
		this->SizeOfQueue = 0;
	}
	void size() {
		std::cout << SizeOfQueue << std::endl;
	}
	void isEmpty() {
		std::cout << std::boolalpha << (this->Que->Front == NULL) << std::endl;
	}
	void front() {
		if (this->Que->Front == NULL) {
			std::cout << "Empty" << std::endl;
		}
		else {
			std::cout << this->Que->Front->Data << std::endl;
		}
	}
	void rear() {
		if (this->Que->Front == NULL) {
			std::cout << "Empty" << std::endl;
		}
		else {
			std::cout << this->Que->Rear->Data << std::endl;
		}
	}
	void enqueue(int Value) {
		this->Que->addEnd(Value);
		SizeOfQueue++;
	}
	void dequeue() {
		if (this->Que->Front == NULL) {
			std::cout << "Empty" << std::endl;
		}
		else {
			this->Que->removeFront();
			SizeOfQueue--;
		}
	}
private :
	LinkedList* Que;
	int SizeOfQueue;
};

int main() {
	ListQueue Queue2;

	int Counter;
	std::cin >> Counter;
	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "size") {
			Queue2.size();
		}
		else if (Command == "isEmpty") {
			Queue2.isEmpty();
		}
		else if (Command == "front") {
			Queue2.front();
		}
		else if (Command == "rear") {
			Queue2.rear();
		}
		else if (Command == "enqueue") {
			int EnqueueValue;
			std::cin >> EnqueueValue;
			Queue2.enqueue(EnqueueValue);
		}
		else if (Command == "dequeue") {
			Queue2.dequeue();
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	}
}