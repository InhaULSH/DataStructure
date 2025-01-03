#include <iostream>
#include <string>
#include <vector>

class Heap {
public :
	Heap(int Direct) {
		Array.push_back(-1);
		this->SizeOfHeap = 0;
		this->RootIndex = 1;
		this->Direction = Direct;
	}
	void Swap(int Idx1, int Idx2) {
		Array[0] = Array[Idx1];
		Array[Idx1] = Array[Idx2];
		Array[Idx2] = Array[0];
	} // 두 인덱스의 값을 서로 바꿈, 갑 저장에 사용되지 않는 0번 인덱스를 활용
	void UpHeap(int Idx) {
		if (Idx == RootIndex) return; // 루트 인덱스에 도달하면 함수 종료
		else {
			int Parent = Idx / 2; // 부모 인덱스
			if (Array[Parent] * Direction > Array[Idx] * Direction) {
				this->Swap(Parent, Idx);
				UpHeap(Parent);
			} // Heap 오더를 만족시키지 못하면 현재와 부모의 값을 서로 바꾸고 부모 인덱스에서 다시 업힙 실행
		}
	} // 업힙 함수
	void DownHeap(int Idx) {
		int LeftChild = Idx * 2; // 왼쪽 자식 인덱스
		int RightChild = Idx * 2 + 1; // 오른쪽 자식 인덱스

		if (RightChild <= SizeOfHeap) {
			if (Array[LeftChild] * Direction <= Array[RightChild] * Direction) {
				if (Array[LeftChild] * Direction < Array[Idx] * Direction) {
					this->Swap(LeftChild, Idx);
					DownHeap(LeftChild);
				} // Heap 오더를 만족시키지 못하면 현재와 왼쪽 자식의 값을 서로 바꾸고 왼쪽 자식 인덱스에서 다시 다운힙 실행
				else return;
			} // 왼쪽 자식이 값이 더 작으면 왼쪽 자식으로 비교
			else {
				if (Array[RightChild] * Direction < Array[Idx] * Direction) {
					this->Swap(RightChild, Idx);
					DownHeap(RightChild);
				} // Heap 오더를 만족시키지 못하면 현재와 오른쪽 자식의 값을 서로 바꾸고 오른쪽 자식 인덱스에서 다시 다운힙 실행
				else return;
			} // 그렇지 않으면 오른쪽 자식으로 비교
		} // 오른쪽 자식이 존재할 경우 즉, 양쪽 모두 자식이 존재할 경우
		else if (LeftChild <= SizeOfHeap) {
			if (Array[RightChild] * Direction < Array[Idx] * Direction) {
				this->Swap(RightChild, Idx);
				DownHeap(RightChild);
			} // Heap 오더를 만족시키지 못하면 현재와 오른쪽 자식의 값을 서로 바꾸고 오른쪽 자식 인덱스에서 다시 다운힙 실행
			else return;
		} // 아니면 왼쪽 자식이 존재할 경우
		else return; // 자식이 없다면 함수 종료
	} // 다운힙 함수
	void Insert(int Value) {
		Array.push_back(Value);
		SizeOfHeap++;
		UpHeap(SizeOfHeap);
	} // 힙에 값을 삽입하는 함수, 벡터 가장 마지막에 값을 삽입하고 업힙
	void Pop() {
		Array[RootIndex] = Array[SizeOfHeap];
		SizeOfHeap--;
		Array.pop_back();
		DownHeap(RootIndex);
	} // 힙의 값을 삭제하는 함수, 루트에 가장 마지막 인덱스의 값을 복사하고 마지막 인덱스의 값을 삭제한 후 다운힙
	int Top() {
		return Array[RootIndex];
	} // 힙의 루트 값을 반환하는 함수
	int Size() {
		return SizeOfHeap;
	} // 힙의 현재 크기 반환하는 함수
	int isEmpty() {
		return SizeOfHeap == 0;
	} // 힙이 비었는지 반환하는 함수
private :
	std::vector<int> Array; // 힙을 담을 벡터
	int SizeOfHeap; // 힙의 현재 크기
	int RootIndex; // 루트의 인덱스
	int Direction; // Min-Heap 인지 Max-Heap 인지를 결정
}; // 힙 클래스

int main() {
	int Counter;
	std::cin >> Counter;
	int DirectionValue;
	std::cin >> DirectionValue;
	Heap H1(DirectionValue);

	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "Insert") {
			int ElementValue;
			std::cin >> ElementValue;
			H1.Insert(ElementValue);
		}
		else if (Command == "Pop") {
			H1.Pop();
		}
		else if (Command == "Top") {
			std::cout << H1.Top() << std::endl;
		}
		else if (Command == "Size") {
			std::cout << H1.Size() << std::endl;
		}
		else if (Command == "isEmpty") {
			std::cout << std::boolalpha << H1.isEmpty() << std::endl;
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	}
} // 메인 함수, 명령어와 필요한 매개변수를 받아 Heap의 기능을 실행할 수 있음