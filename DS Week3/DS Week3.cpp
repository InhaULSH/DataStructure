#include <iostream>
#include <string>

struct Node {
	int Data;
	Node* Next;
};

class ListStack {
public :
	ListStack() {
		this->TopNode = new Node;
		TopNode->Data = 0;
		TopNode->Next = NULL;
		this->SizeOfStack = 0;
	}
	void isEmpty() {
		std::cout << std::boolalpha << (SizeOfStack == 0) << std::endl;
	}
	void Size() {
		std::cout << SizeOfStack << std::endl;
	}
	void Top() {
		if (SizeOfStack == 0) {
			std::cout << "Empty" << std::endl;
		}
		else {
			std::cout << TopNode->Data << std::endl;
		}
	}
	void Push(int Value) {
		Node* NewNode = new Node;
		NewNode->Data = Value;
		NewNode->Next = TopNode;
		TopNode = NewNode;
		SizeOfStack++;
	}
	void Pop() {
		if (SizeOfStack == 0) {
			std::cout << "Empty" << std::endl;
		}
		else {
			Node* TempNode = TopNode;
			TopNode = TopNode->Next;
			delete TempNode;
			SizeOfStack--;
		}
	}
private :
	Node* TopNode;
	int SizeOfStack;
};

int main() {
	int Counter;
	std::cin >> Counter;
	ListStack Stack1;

	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "isEmpty") {
			Stack1.isEmpty();
		}
		else if (Command == "Size") {
			Stack1.Size();
		}
		else if (Command == "Top") {
			Stack1.Top();
		}
		else if (Command == "Push") {
			int InputValue;
			std::cin >> InputValue;
			Stack1.Push(InputValue);
		}
		else if (Command == "Pop") {
			Stack1.Pop();
		}
		else {
			std::cout << "Invalid Value" << std::endl;
		}
	}
}