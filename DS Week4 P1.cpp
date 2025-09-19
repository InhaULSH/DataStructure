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
	int removeFront() {
		if (Front != NULL) {
			Node* TempNode = Front;
			int FrontData = Front->Data;
			Front = Front->Next;
			delete TempNode;
			return FrontData;
		}
	} // 삭제한 Front 노드의 데이터를 반환하도록 수정
}; // 큐 구현을 위한 연결리스트 구조체 

class ListQueue {
public:
	ListQueue() {
		this->Que = new LinkedList();
		this->SizeOfQueue = 0;
	}
	int size() {
		return SizeOfQueue;
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
	int dequeue() {
		if (this->Que->Front == NULL) {
			std::cout << "Empty" << std::endl;
			return -1;
		}
		else {
			SizeOfQueue--;
			return this->Que->removeFront();
		}
	} // 리턴타입을 int로 바꾸고 removeFront 값을 리턴하도록 수정
private:
	LinkedList* Que;
	int SizeOfQueue;
}; // 연결리스트로 큐를 구현한 클래스

int main() {
	ListQueue Player1;
	ListQueue Player2;

	int Counter;
	std::cin >> Counter; // 테스트 케이스 횟수

	for (int i = 0; i < Counter; i++) {
		int Number;
		std::cin >> Number; // 카드의 개수

		for (int i = 0; i < Number; i++) {
			int TempValue;
			std::cin >> TempValue;
			Player1.enqueue(TempValue);
		}
		for (int i = 0; i < Number; i++) {
			int TempValue;
			std::cin >> TempValue;
			Player2.enqueue(TempValue);
		} // 카드의 개수만큼 숫자를 입력 받아 큐에 enqueue함

		int Rounds = Player1.size(); // 큐의 사이즈만큼 라운드 설정
		int P1_Point = 0; 
		int P2_Point = 0; // 각 플레이어의 승점
		int P1_Advantage = 0;
		int P2_Advantage = 0; // 각 플레이어의 추가 점수 
		for (int i = 0; i < Rounds; i++) {
			int P1 = Player1.dequeue() + P1_Advantage;
			int P2 = Player2.dequeue() + P2_Advantage; // 각 플레이어의 체력(카드의 숫자 + 추가점수)
			if (P1 == P2) {
				std::cout << "Round" << i+1 << " Draw" << std::endl;
				P1_Advantage = 0;
				P2_Advantage = 0;
			} // 무승부라면 추가 점수를 모두 0으로 설정하고 승점을 더하지 않음
			else if (P1 > P2) {
				std::cout << "Round" << i+1 << " P1 " << P1 - P2 << std::endl;
				P1_Advantage = 0;
				P2_Advantage = P1 - P2;
				P1_Point++;
			} // P1이 승리하면 P2의 추가점수를 점수차 만큼 설정하고 P1에게 승점 부여
			else {
				std::cout << "Round" << i+1 << " P2 " << P2 - P1 << std::endl;
				P1_Advantage = P2 - P1;
				P2_Advantage = 0;
				P2_Point++;
			} // P2가 승리하면 P1의 추가점수를 점수차 만큼 설정하고 P2에게 승점 부여
		} // 게임 진행

		if (P1_Point > P2_Point) {
			std::cout << "Winner P1" << std::endl;
		}
		else if (P1_Point < P2_Point) {
			std::cout << "Winner P2" << std::endl;
		}
		else {
			std::cout << 'Draw' << std::endl;
		} // 게임 종료, 승점을 비교해 승자가 누구인지 출력 
	} // 테스트 케이스
}