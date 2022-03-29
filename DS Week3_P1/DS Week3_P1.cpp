#include <iostream>
#include <string>

struct Node {
	char Data;
	Node* Next;
};

class ListStack {
public:
	ListStack() {
		this->TopNode = new Node;
		TopNode->Data = ' ';
		TopNode->Next = NULL;
		this->SizeOfStack = 0;
	}
	void isEmpty() {
		std::cout << std::boolalpha << (SizeOfStack == 0) << std::endl;
	}
	void Size() {
		std::cout << SizeOfStack << std::endl;
	}
	char Top() {
		if (SizeOfStack == 0) {
			std::cout << "Empty" << std::endl;
			return '-1';
		}
		else {
			return TopNode->Data;
		}
	}
	void Push(int Value) {
		Node* NewNode = new Node;
		NewNode->Data = Value;
		NewNode->Next = TopNode;
		TopNode = NewNode;
		SizeOfStack++;
	}
	char Pop() {
		if (SizeOfStack == 0) {
			std::cout << "Empty" << std::endl;
			return '-1';
		}
		else {
			Node* TempNode = TopNode;
			char NodeData = TopNode->Data;
			TopNode = TopNode->Next;
			delete TempNode;
			SizeOfStack--;
			return NodeData;
		}
	}
private:
	Node* TopNode;
	int SizeOfStack;
};

int main() {
	ListStack PostfixCalculator;
	std::string Formula;
	std::cin >> Formula;

	for (int i = 0; i < Formula.length(); i++) {
		if (Formula[i] == '+') {
			int Number1 = PostfixCalculator.Pop() - '0';
			int Number2 = PostfixCalculator.Pop() - '0';
			char Result = (Number2 + Number1) + '0';
			PostfixCalculator.Push(Result);
		}
		else if (Formula[i] == '-') {
			int Number1 = PostfixCalculator.Pop() - '0';
			int Number2 = PostfixCalculator.Pop() - '0';
			char Result = (Number2 - Number1) + '0';
			PostfixCalculator.Push(Result);
		}
		else if (Formula[i] == '*') {
			int Number1 = PostfixCalculator.Pop() - '0';
			int Number2 = PostfixCalculator.Pop() - '0';
			char Result = (Number2 * Number1) + '0';
			PostfixCalculator.Push(Result);
		}
		else if (Formula[i] == '/') {
			int Number1 = PostfixCalculator.Pop() - '0';
			int Number2 = PostfixCalculator.Pop() - '0';
			char Result = (Number2 / Number1) + '0';
			PostfixCalculator.Push(Result);
		}
		else {
			PostfixCalculator.Push(Formula[i]);
		}
	}
	std::cout << PostfixCalculator.Pop() - '0' << std::endl;
}