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
		for (std::vector<int>::iterator Itr = --Que.end(); Itr != Que.begin(); Itr--) {
			std::cout << *Itr << " ";
		}
		std::cout << *Que.begin() << std::endl;
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
	void SelectionSort(int CurrentQueSize) {
		PriorityQueue TempQue; // 큐의 값을 담을 임시 우선순위 큐

		for (int i = 0; i < CurrentQueSize; i++) {
			TempQue.Insert(*Que.begin());
			Que.erase(Que.begin());
		} // 큐의 값을 임시 큐로 모두 옮김
		int CurrentTempQueSize = TempQue.Size();
		for (int i = 0; i < CurrentTempQueSize; i++) {
			int RemovedMin = TempQue.RemoveMin();
			Que.push_back(RemovedMin);
		} // 임시큐의 크기만큼 임시 큐에서 최솟값을 삭제해 Que 벡터에 다시 Push_Back하는 것을 반복
	} // 큐를 선택정렬하는 함수
private:
	std::vector<int> Que;
}; // 비정렬 시퀀스 기반 우선순위 큐 클래스

int main() {
	int CommandCounter;
	std::cin >> CommandCounter;
	for (int i = 0; i < CommandCounter; i++) {
		PriorityQueue PQ2;

		int SizeCounter;
		std::cin >> SizeCounter;
		
		for (int j = 0; j < SizeCounter; j++) {
			int InputValue;
			std::cin >> InputValue;

			PQ2.Insert(InputValue);
		}
		PQ2.SelectionSort(PQ2.Size());
		PQ2.Print();
	}
} // 큐의 크기와 큐의 원소를 입력받아 선택정렬한 후 큐의 데이터를 출력