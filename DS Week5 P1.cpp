#include <iostream>
#include <string>
#include <algorithm>

struct Node {
	int Element;
	Node* Next;
	Node* Prev;
}; // 이중 연결 리스트 구현을 위한 노드 구조체

class List {
public:
	friend struct Node;

	List() {
		this->Head = new Node;
		this->Trailer = new Node;
		this->Head->Next = Trailer;
		this->Head->Prev = NULL;
		this->Trailer->Next = NULL;
		this->Trailer->Prev = Head;
		this->Iterator = Trailer;
	} // 생성자
	void Begin() {
		Iterator = Head->Next;
	} // 반복자가 Head 노드 다음 노드를 가리키게 함
	void End() {
		Iterator = Trailer;
	} // 반복자가 Trailer 노드를 가리키게 함
	void NextP() {
		if (Iterator != Trailer) {
			Iterator = Iterator->Next;
		}
	} // 반복자가 현재 노드의 다음 노드를 가리키게 함
	void PrevP() {
		if (Iterator != Head->Next) {
			Iterator = Iterator->Prev;
		}
	} // 반복자가 현재 노드의 이전 노드를 가리키게 함
	void Insert(int Value) {
		Node* NewNode = new Node;
		NewNode->Element = Value;
		NewNode->Next = Iterator;
		NewNode->Prev = Iterator->Prev;
		Iterator->Prev->Next = NewNode;
		Iterator->Prev = NewNode;
	} // 현재 노드와 이전 노드 사이에 값을 삽입함
	int Max(int Size) {
		int* DataList = new int[Size];
		Begin();
		for (int i = 0; i < Size; i++) {
			DataList[i] = Iterator->Element;
			NextP();
		}
		return *std::max_element(DataList, DataList + Size) - *std::min_element(DataList, DataList + Size);
	} // 반복자가 Head 노드의 다음 노드부터 순차적으로 순회하면서 데이터 값의 리스트를 작성, 라이브러리를 통해 최댓값과 최솟값 차를 구함
private:
	Node* Head; // Head 노드
	Node* Trailer; // Trailer 노드
	Node* Iterator; // 반복자
}; // 기능 구현을 위한 이중 연결 리스트 클래스

int main() {
	int Counter;
	std::cin >> Counter;

	for (int i = 0; i < Counter; i++) {
		int SizeOfList;
		std::cin >> SizeOfList;

		List List2;

		for (int i = 0; i < SizeOfList; i++) {
			int TempValue;
			std::cin >> TempValue;
			List2.Insert(TempValue);
		} // 리스트 크기만큼 값을 입력 받아 리스트에 삽입

		std::cout << List2.Max(SizeOfList) << std::endl; // 최대 최솟값 차이 출력
	}
}
