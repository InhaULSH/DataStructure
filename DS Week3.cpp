#include <iostream>
#include <string>

struct Node {
	int Data;
	Node* Next;
}; // 연결리스트 구현을 위한 노드

class ListStack {
public:
	ListStack() {
		this->TopNode = new Node;
		TopNode->Data = 0;
		TopNode->Next = NULL;
		this->SizeOfStack = 0;
	} // 생성자
	void isEmpty() {
		std::cout << std::boolalpha << (SizeOfStack == 0) << std::endl;
	} // 스택이 비었는지 출력하는 함수
	void Size() {
		std::cout << SizeOfStack << std::endl;
	} // 스택의 크기 출력 함수
	void Top() {
		if (SizeOfStack == 0) {
			std::cout << "Empty" << std::endl;
		}
		else {
			std::cout << TopNode->Data << std::endl;
		}
	} // 스택의 맨 윗 값 출력함수, 비었다면 "Empty"라고 출력
	void Push(int Value) {
		Node* NewNode = new Node;
		NewNode->Data = Value;
		NewNode->Next = TopNode;
		TopNode = NewNode;
		SizeOfStack++;
	} // 값 추가 함수, 임시노드를 만들어 값을 담고 임시노드를 Top 노드와 연결한 다음 임시노드를 Top 노드로 설정, 스택 크기 증가시킴
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
	} // 값 삭제 함수, Top 노드를 임시노드에 담고 Top 노드의 다음 노드를 Top 노드로 설정한 다음 임시 노드 Delete, 스택 크기 감소시킴
private:
	Node* TopNode; // 탑 노드
	int SizeOfStack; // 스택의 크기
}; // 연결리스트로 구현한 스택 클래스

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
	} // 필요한 명령어와 파라미터를 입력받아 기능을 실행
}