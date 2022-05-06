#include <iostream>
#include <string>
#include <vector>
#include <iterator>

class Comparator {
	bool operator() (const int Num1, const int Num2) {
		if (Num1 < Num2) {
			return true;
		}
		else {
			return false;
		}
	}

	friend class PriorityQueue;
}; // 비교자 클래스

class PriorityQueue {
public:
	int Size() {
		return this->Que.size();
	} // 큐의 현재 크기 반환 함수
	bool isEmpty() {
		return (this->Que.size() == 0);
	} // 큐가 비었는지 반환하는 함수
	void Print() {
		for (std::vector<int>::iterator Itr = Que.begin(); Itr != Que.end(); Itr++) {
			std::cout << *Itr << " ";
		}
		std::cout << std::endl;
	} // 큐의 데이터들을 출력하는 함수
	void Insert(int Value) {
		this->Que.push_back(Value);
	} // 큐에 값을 삽입하는 함수
	int RemoveMin() {
		std::vector<int>::iterator Position = Que.begin();
		Comparator isLess;
		int Minimum = *Que.begin();

		for (std::vector<int>::iterator Itr = Que.begin(); Itr != Que.end(); Itr++) {
			if (!isLess(Minimum, *Itr)) {
				Minimum = *Itr;
				Position = Itr;
			}
		}
		Que.erase(Position);
		return Minimum; // 최솟값을 삭제 한 후 그 값을 반환하도록 변경
	} // 큐의 최솟값을 삭제하는 함수
	void SpecialSort(int CurrentQueSize) {
		PriorityQueue TempEvenQue; // 짝수를 담는 임시 큐
		PriorityQueue TempOddQue; // 홀수를 담는 임시 큐

		for (int i = 0; i < CurrentQueSize; i++) {
			if (Que[i] % 2 == 0) {
				TempEvenQue.Insert(Que[i]);
			}
			else {
				TempOddQue.Insert(Que[i]);
			}
		} // Que의 원소들을 모두 짝수와 홀수 임시큐에 추가
		Que.clear(); // Que를 비움
		int CurrentEvenQueSize = TempEvenQue.Size();
		int CurrentOddQueSize = TempOddQue.Size();
		for (int i = 0; i < CurrentEvenQueSize; i++) {
			int RemovedMin = TempEvenQue.RemoveMin();
			Que.push_back(RemovedMin);
		} // 짝수 임시 큐의 최솟값을 순서대로 원래 큐에 추가함 
		for (int i = 0; i < CurrentOddQueSize; i++) {
			int RemovedMin = TempOddQue.RemoveMin();
			Que.push_back(RemovedMin);
		} // 홀수 임시 큐의  최솟값을 순서대로 원래 큐에 추가함
	} // 큐를 주어진 조건에 따라 정렬하는 함수
private:
	std::vector<int> Que;
}; // 비정렬 시퀀스 기반 우선순위 큐 클래스

int main() {
	int CommandCounter;
	std::cin >> CommandCounter;
	for (int i = 0; i < CommandCounter; i++) {
		PriorityQueue PQ3;

		int SizeCounter;
		std::cin >> SizeCounter;

		for (int j = 0; j < SizeCounter; j++) {
			int InputValue;
			std::cin >> InputValue;

			PQ3.Insert(InputValue);
		}
		PQ3.SpecialSort(PQ3.Size());
		PQ3.Print();
	}
} // 큐의 크기와 큐의 원소를 입력받아 짝수를 먼저 정렬한 후 짝수/홀수 사이에서 작은 순서대로 정렬 한 후 큐의 데이터를 출력