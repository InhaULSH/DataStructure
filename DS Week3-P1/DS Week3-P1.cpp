#include <iostream>
#include <string>

struct Node {
	char Data;
	Node* Next;
}; // 스택 구현을 위한 연결리스트 구조체

class ListStack {
public:
	ListStack() {
		this->TopNode = new Node;
		TopNode->Data = ' ';
		TopNode->Next = NULL;
		this->SizeOfStack = 0;
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
}; // 계산기 구현을 위한 연결리스트 기반 스택 클래스

int main() {
	ListStack PostfixCalculator;
	std::string Formula; // 후위표기법 식을 문자열 형태로 저장
	std::cin >> Formula;

	for (int i = 0; i < Formula.length(); i++) { // 문자열의 각 원소를 순회하면서
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
		} // 연산자의 경우 스택에서 Pop을 두번 실행해 각각 int로 바꾼 다음 필요한 연산을 수행한 후 그 값을 다시 char 형태로 스택에 푸시
		else {
			PostfixCalculator.Push(Formula[i]);
		} // 피연산자의 경우 스택에 바로 푸시
	}
	std::cout << PostfixCalculator.Pop() - '0' << std::endl; // 마지막으로 스택에 남은 값을 int 형태로 출력
}