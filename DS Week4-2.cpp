#include <iostream>
#include <string>

struct Node {
	int Data;
	Node* Next;

	Node(int Value) {
		this->Data = Value;
		this->Next = NULL;
	}
}; // 연결리스트 구현을 위한 노드 구조체

struct LinkedList {
	Node* Front;
	Node* Rear;

	LinkedList() {
		this->Front = NULL;
		this->Rear = NULL; // Front와 Rear노드를 NULL로 초기화
	} // 생성자
	void addEnd(int Value) {
		Node* NewNode = new Node(Value);
		if (Front == NULL) {
			Front = Rear = NewNode;
		}
		else {
			Rear->Next = NewNode;
			Rear = NewNode;
		}
	} // 추가하는 값을 담는 임시노드를 생성해 그 노드를 Rear와 연결하고 임시노드를 Rear노드로 설정, 비었다면 임시노드를 Front와 Rear로 설정
	void removeFront() {
		if (Front != NULL) {
			Node* TempNode = Front;
			Front = Front->Next;
			delete TempNode;
		}
	} // 삭제하는 노드를 담는 임시노드를 생성하고 Front를 Front 다음 노드로 옮긴다음 임시노드를 Delete함
}; // 큐 구현을 위한 연결리스트 구조체

class ListQueue {
public :
	ListQueue() {
		this->Que = new LinkedList();
		this->SizeOfQueue = 0;
	}
	void size() {
		std::cout << SizeOfQueue << std::endl;
	} // 큐의 크기 출력함수
	void isEmpty() {
		std::cout << std::boolalpha << (this->Que->Front == NULL) << std::endl;
	} // 큐가 비었는지를 출력하는 함수
	void front() {
		if (this->Que->Front == NULL) {
			std::cout << "Empty" << std::endl;
		}
		else {
			std::cout << this->Que->Front->Data << std::endl;
		}
	} // 큐의 Front 값 출력함수, 비었다면 "Empty"라고 출력
	void rear() {
		if (this->Que->Front == NULL) {
			std::cout << "Empty" << std::endl;
		}
		else {
			std::cout << this->Que->Rear->Data << std::endl;
		}
	} // 큐의 Rear 값 출력함수, 비었다면 "Empty"라고 출력
	void enqueue(int Value) {
		this->Que->addEnd(Value);
		SizeOfQueue++;
	} // 값 추가 함수, 연결리스트의 addEnd 함수를 실행하고 큐의 크기를 증가시킴
	void dequeue() {
		if (this->Que->Front == NULL) {
			std::cout << "Empty" << std::endl;
		}
		else {
			this->Que->removeFront();
			SizeOfQueue--;
		}
	} // 값 삭제 함수, 연결리스트의 removeFront 함수를 실행시키고 큐의 크기를 감소시킴, 비었다면 "Empty"라고 출력
private :
	LinkedList* Que; // 큐를 담는 연결리스트
	int SizeOfQueue; // 큐의 크기
}; // 리스트를 기반으로 큐 구현

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
	} // 필요한 명령어와 파라미터를 입력받아 기능을 실행
}