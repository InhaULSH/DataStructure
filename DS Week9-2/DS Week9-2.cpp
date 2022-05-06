#include <iostream>
#include <string>
#include <vector>
#include <iterator>

class Comparator {
	bool operator() (const int Num1, const int Num2) {
		if (Num1 <= Num2) {
			return true;
		}
		else {
			return false;
		}
	}

	friend class PriorityQueue;
}; // 비교자 클래스, 두 인수를 비교해 두번째 인수가 크거나 같으면 True 반환

class PriorityQueue {
public:
	int Size() {
		return this->Que.size();
	} // 큐의 현재 크기 반환 함수
	bool isEmpty() {
		return (this->Que.size() == 0);
	} // 큐가 비었는지 반환하는 함수
	void Print() {
		if (this->Size() == 1) {
			std::cout << Que[0] << std::endl;
		} // 큐의 현재 크기가 0이면 Que의 맨 처음 값만 출력
		else {
			for (std::vector<int>::iterator Itr = Que.begin(); Itr != Que.end(); Itr++) {
				std::cout << *Itr << " ";
			}
			std::cout << std::endl;
		} // 아니라면 Que를 마지막부터 순회하면서 반복자가 가리키는 값을 출력
	} // 큐의 데이터들을 출력하는 함수
	void Insert(int Value) {
		if (this->isEmpty()) {
			Que.push_back(Value);
			return;
		} // 큐가 비었다면 Que의 마지막에 값을 추가
		else {
			Comparator isLess;

			for (std::vector<int>::iterator Itr = Que.begin(); Itr != Que.end(); Itr++) {
				if (isLess(*Itr, Value)) {
					Que.insert(Itr, Value);
					return;
				}
			} // Que를 처음부터 순회하면서 삽입하는 값보다 작은 값을 가지는 위치를 찾고 해당 위치에 값을 삽입
			Que.push_back(Value);
			return; // Que에서 삽입하는 값보다 작은 값을 가지는 위치를 찾지 못하면 마지막에 값을 추가
		}
	} // 큐에 값을 삽입하는 함수
	int Min() {
		return Que.back();	// Iterator 사용시에는  return *Que.begin(); 
	} // 큐의 최솟값을 반환하는 함수, Que의 마지막 값을 반환
	void RemoveMin() {
		Que.pop_back(); 	// Iterator 사용시에는  return Que.erase(Que.begin()); 
	} // 큐의 최솟값을 삭제하는 함수, Que의 마지막 값을 삭제
private:
	std::vector<int> Que;
}; // 정렬 시퀀스 기반 우선순위 큐 클래스

int main() {
	PriorityQueue PQ1;
	int Counter;
	std::cin >> Counter;

	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "insert") {
			int InputValue;
			std::cin >> InputValue;
			PQ1.Insert(InputValue);
		}
		else if (Command == "removeMin") {
			PQ1.RemoveMin();
		}
		else if (Command == "min") {
			std::cout << PQ1.Min() << std::endl;
		}
		else if (Command == "empty") {
			std::cout << std::boolalpha << PQ1.isEmpty() << std::endl;
		}
		else if (Command == "size") {
			std::cout << PQ1.Size() << std::endl;
		}
		else if (Command == "print") {
			PQ1.Print();
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	}
} // 명령어와 필요한 인수를 입력받아 기능을 실행함