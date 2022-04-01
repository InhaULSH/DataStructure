#include <iostream>
#include <string>

class ArrayQueue {
public :
	ArrayQueue(int Cap) {
		this->Capacity = Cap + 1; // 필요한 크기 + 1 만큼 큐의 크기를 설정
		Que = new int[Capacity]; // 배열을 동적할당
		Front = Rear = 0;
		for (int i = 0; i < Capacity; i++) {
			Que[i] = 0;
		} // 값을 0으로 초기화
	} // 생성자 
	void size() {
		std::cout << (Rear - Front + Capacity)%Capacity << std::endl;
	} // 큐의 크기 출력함수
	void isEmpty() {
		std::cout << std::boolalpha << (Front == Rear) << std::endl;
	} // 큐가 비었는지 를 출력하는 함수
	void front() {
		if (Front == Rear) {
			std::cout << "Empty" << std::endl;
		}
		else {
			std::cout << Que[(Front + 1) % Capacity] << std::endl;
		}
	} // 큐의 Front 값 출력함수, 비었다면 "Empty"라고 출력
	void rear() {
		if (Front == Rear) {
			std::cout << "Empty" << std::endl;
		}
		else {
			std::cout << Que[Rear] << std::endl;
		}
	} // 큐의 Rear 값 출력함수, 비었다면 "Empty"라고 출력
	void enqueue(int Value) {
		if (Front == (Rear + 1)%Capacity) {
			std::cout << "Full" << std::endl;
		}
		else {
			Rear = (Rear + 1)%Capacity;
			Que[Rear] = Value;
		}
	} // 값 추가 함수, Rear 다음 칸을 Rear로 만들고 그 자리에 값을 추가, 비었다면 "Empty"라고 출력
	void dequeue() {
		if (Front == Rear) {
			std::cout << "Empty" << std::endl;
		}
		else {
			Front = (Front + 1)%Capacity;
			Que[Front] = 0;
		}
	} // 값 삭제 함수, Front 다음 값을 Front로 만들고 Front가 있던 자리는 0으로 초기화, 비었다면 "Empty"라고 출력
private :
	int* Que; // 큐를 담을 배열
	int Rear; // 맨 나중 값
	int Front; // 맨 처음 값
	int Capacity; // 큐의 크기
};

int main() {
	int Counter;
	int SizeOfQueue;
	std::cin >> SizeOfQueue >> Counter;

	ArrayQueue Queue1(SizeOfQueue);
	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "size") {
			Queue1.size();
		}
		else if (Command == "isEmpty") {
			Queue1.isEmpty();
		}
		else if (Command == "front") {
			Queue1.front();
		}
		else if (Command == "rear") {
			Queue1.rear();
		}
		else if (Command == "enqueue") {
			int EnqueueValue;
			std::cin >> EnqueueValue;
			Queue1.enqueue(EnqueueValue);
		}
		else if (Command == "dequeue") {
			Queue1.dequeue();
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	} // 필요한 명령어와 파라미터를 입력받아 기능을 실행
}
