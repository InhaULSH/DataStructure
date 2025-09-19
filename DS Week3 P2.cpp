#include <iostream>
#include <string>

struct Node {
	char Data;
	Node* Next;
}; // 연결리스트 구현을 위한 노드

class ListStack {
public:
	ListStack() {
		this->TopNode = new Node;
		TopNode->Next = NULL;
		this->SizeOfStack = 0;
	} // 생성자
	bool isEmpty() {
		return SizeOfStack == 0;
	} // 스택이 비었는지 출력하는 함수
	void Size() {
		std::cout << SizeOfStack << std::endl;
	} // 스택의 크기 출력 함수
	char Top() {
		if (SizeOfStack == 0) {
			std::cout << "Empty" << std::endl;
		}
		else {
		return TopNode->Data;
		}
	} // 스택의 맨 윗 값 출력함수
	void Push(const char& Value) {
		Node* NewNode = new Node;
		NewNode->Data = Value;
		NewNode->Next = TopNode;
		TopNode = NewNode;
		SizeOfStack++;
	} // 값 추가 함수
	void Pop() {
		if (SizeOfStack == 0) {
			std::cout << "Empty" << std::endl;
		}
		else {
			Node* TempNode = TopNode;
			std::cout << TopNode->Data;
			TopNode = TopNode->Next;
			delete TempNode;
			SizeOfStack--;
		}
	} // 값 삭제 함수
private:
	Node* TopNode;
	int SizeOfStack;
}; // 연결리스트로 구현한 스택 클래스

int main() {
	int Counter;
	std::cin >> Counter;

	for (int i = 0; i < Counter; i++) {
		ListStack Stack3;
		std::string Formula;
		std::cin >> Formula;

		for (int j = 0; j < Formula.length(); j++) {
			if (Formula[j] == '/' || Formula[j] == '*') {
				while (!Stack3.isEmpty() && (Stack3.Top() == '/' || Stack3.Top() == '*')) {
					Stack3.Pop();
				}
				Stack3.Push(Formula[j]);
			}
			else if (Formula[j] == '+' || Formula[j] == '-') {
				while (!Stack3.isEmpty()) {
					Stack3.Pop();
				}
				Stack3.Push(Formula[j]);
			}
			else {
				std::cout << Formula[j];
			}
		}
		while (!Stack3.isEmpty()) {
			Stack3.Pop();
		}
		std::cout << std::endl;
	}
}