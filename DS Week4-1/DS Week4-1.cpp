#include <iostream>
#include <string>

class ArrayQueue {
public :
	ArrayQueue(int Cap) {
		this->Capacity = Cap + 1;
		Que = new int[Capacity];
		Front = Rear = 0;
		for (int i = 0; i < Capacity; i++) {
			Que[i] = 0;
		}
	}
	void size() {
		std::cout << (Rear - Front + Capacity)%Capacity << std::endl;
	}
	void isEmpty() {
		std::cout << std::boolalpha << (Front == Rear) << std::endl;
	}
	void front() {
		if (Front == Rear) {
			std::cout << "Empty" << std::endl;
		}
		else {
			std::cout << Que[(Front + 1) % Capacity] << std::endl;
		}
	}
	void rear() {
		if (Front == Rear) {
			std::cout << "Empty" << std::endl;
		}
		else {
			std::cout << Que[Rear] << std::endl;
		}
	}
	void enqueue(int Value) {
		if (Front == (Rear + 1)%Capacity) {
			std::cout << "Full" << std::endl;
		}
		else {
			Rear = (Rear + 1)%Capacity;
			Que[Rear] = Value;
		}
	}
	void dequeue() {
		if (Front == Rear) {
			std::cout << "Empty" << std::endl;
		}
		else {
			Front = (Front + 1)%Capacity;
			Que[Front] = 0;
		}
	}
private :
	int* Que;
	int Rear;
	int Front;
	int Capacity;
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
	}
}
