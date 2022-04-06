#include <iostream>
#include <string>

struct Node {
	int Element;
	Node* Next;
	Node* Prev;
}; // 노드 객체

class Iterator {
public :
	friend class Sequence;

	Iterator(Node* Position) {
		Curr = Position;
	} // 생성자, 입력받은 노드를 가리키도록 함
	int& operator*() {
		if (Curr->Next == NULL) {
			int Error = -1;
			return Error;
		}
		else {
			return Curr->Element;
		}
	} // 반복자가 가리키는 노드의 데이터 값을 반환하는 연산자 오버로딩 함수, 현재 Trailer를 가리키는 경우 -1 값을 반환
	bool operator==(const Iterator& Itr) {
		return Curr == Itr.Curr;
	} // 입력받은 반복자가 자신과 동일한지를 반환하는 연산자 오버로딩 함수
	bool operator!=(const Iterator& Itr) {
		return Curr != Itr.Curr;
	} // 입력받은 반복자가 자신과 다른 지를 반환하는 연산자 오버로딩 함수
	Iterator operator++() {
		if (Curr->Next == NULL) {
			std::cout << "Trailer" << std::endl;
		}
		else {
			Curr = Curr->Next;
			return *this;
		}
	} // 반복자가 다음 노드를 가리키도록 하는 연산자 오버로딩 함수, 현재 Trailer를 가리키는 경우 작동하지 X
	Iterator operator--() {
		if (Curr->Prev->Prev == NULL) {
			std::cout << "Head" << std::endl;
		}
		else {
			Curr = Curr->Prev;
			return *this;
		}
	} // 반복자가 이전 노드를 가리키도록 하는 연산자 오버로딩 함수, 현재 Trailer를 가리키는 경우 작동하지 X
private :
	Node* Curr; // 반복자가 가리킬 노드를 담는 변수
}; // 반복자 클래스

class Sequence {
public :
	Sequence() {
		this->Head = new Node;
		this->Trailer = new Node;
		this->Head->Next = Trailer;
		this->Head->Prev = NULL;
		this->Trailer->Next = NULL;
		this->Trailer->Prev = Head;
		this->SizeOfSequence = 0;
	} // 생성자

	int Size() const {
		return SizeOfSequence;
	} // 시퀀스의 크기 반환 함수
	bool isEmpty() const {
		return SizeOfSequence == 0;
	} // 시퀀스가 비었는지를 반환하는 함수
	void Insesrt(const Iterator& P, const int& Value) {
		Node* CurrentNode = P.Curr;
		Node* PreviousNode = CurrentNode->Prev;
		Node* NewNode = new Node;
		NewNode->Element = Value;
		NewNode->Next = CurrentNode;
		NewNode->Prev = PreviousNode;
		CurrentNode->Prev = NewNode;
		PreviousNode->Next = NewNode;
		this->SizeOfSequence++;
	} // 시퀀스 값 삽입 함수, 입력받은 반복자를 삽입 기준 노드로 하는 것을 제외하고 리스트의 값 삽입과 동일
	void Erase(const Iterator& P) {
		if (this->isEmpty()) {
			std::cout << "Empty" << std::endl;
		}
		else if (P.Curr == Trailer) {
			std::cout << "Trailer" << std::endl;
		}
		else {
			Node* CurrentNode = P.Curr;
			Node* NextNode = CurrentNode->Next;
			Node* PreviousNode = CurrentNode->Prev;
			NextNode->Prev = PreviousNode;
			PreviousNode->Next = NextNode;
			delete CurrentNode;
			this->SizeOfSequence--;
		}
	} // 시퀀스 값 삭제 함수, 입력받은 반복자를 삭제 기준 노드로 하는 것을 제외하고 리스트의 값 삭제과 동일

	Iterator Begin() const {
		return Iterator(Head->Next);
	} // 반복자를 Head 노드 다음 노드로 이동시킴
	Iterator End() const {
		return Iterator(Trailer);
	} // 반복자를 Trailer 노드로 이동시킴
	Iterator AtIndex(int Idx) {
		Iterator P_Temp = Begin();

		for (int i = 0; i < Idx; i++) {
			++P_Temp;
		}
		return P_Temp;
	} // 인덱스 값을 통해 그 인덱스에 해당하는 노드를 가리키는 반복자를 반환하는 함수, 임시 반복자가 특정 인덱스에 이를때까지 시퀀스를 순회
	int IndexOf(const Iterator& P) {
		Iterator P_Temp = Begin();
		int Index = 0;

		while (P_Temp != P) {
			++P_Temp;
			Index++;
		} // Postfix Increment와 Prefix Increment는 일반적으로 차이가 거의 없으나, 반복자(또는 객체)를 사용할 때는 Prefix가 더 빠름
		return Index;
	} // 현재 반복자의 인덱스를 반환하는 함수, 임시 반복자가 현재반복자와 동일해질때까지 시퀀스를 순회
private :
	Node* Head; // Head 노드
	Node* Trailer; // Trailer 노드
	int SizeOfSequence; // 시퀀스의 현재크기
}; // 시퀀스 클래스

int main() {
	Sequence Seq1;
	Iterator Itr1(Seq1.End());
	int Counter;
	std::cin >> Counter;

	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "Size") {
			std::cout << Seq1.Size() << std::endl;
		}
		else if (Command == "isEmpty") {
			std::cout << Seq1.isEmpty() << std::endl;
		}
		else if (Command == "Insert") {
			std::string Mode;
			std::cin >> Mode;
			if (Mode == "Index") {
				int InputIndex;
				int InputValue;
				std::cin >> InputIndex >> InputValue;
				Seq1.Insesrt(Seq1.AtIndex(InputIndex), InputValue);
			}
			else if (Mode == "Position") {
				int InputValue;
				std::cin >> InputValue;
				Seq1.Insesrt(Itr1, InputValue);
			}
			else {
				std::cout << "Invalid Mode" << std::endl;
			}
		} // 현재 위치를 기준으로 값을 삭제할지 인덱스를 기준으로 값을 삭제할지 두개의 모드 존재
		else if (Command == "Erase") {
			std::string Mode;
			std::cin >> Mode;
			if (Mode == "Index") {
				int InputIndex;
				std::cin >> InputIndex;
				Seq1.Erase(Seq1.AtIndex(InputIndex));
			} 
			else if (Mode == "Position") {
				Seq1.Erase(Itr1);
			}
			else {
				std::cout << "Invalid Mode" << std::endl;
			}
		} // 현재 위치를 기준으로 값을 삽입할지 인덱스를 기준으로 값을 삽입할지 두개의 모드 존재
		else if (Command == "Begin") {
			Itr1 = Seq1.Begin();
		}
		else if (Command == "End") {
			Itr1 = Seq1.End();
		}
		else if (Command == "Next") {
			++Itr1;
		}
		else if (Command == "Previous") {
			--Itr1;
		}
		else if (Command == "Current") {
			if (*Itr1 == -1) {
				std::cout << "Trailer" << std::endl;
			}
			else {
				std::cout << "Index " << Seq1.IndexOf(Itr1) << " : " << *Itr1 << std::endl;
			}
		} // 반복자가 Trailer를 가리키고 있는 경우에는 메세지 출력, 아닌 경우 현재 노드의 인덱스와 데이터를 출력
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	} // 필요한 명령어와 파라미터를 받아 기능을 실행함
}