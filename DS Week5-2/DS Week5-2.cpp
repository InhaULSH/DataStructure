#include <iostream>
#include <string>

struct Node {
	int Element;
	Node* Next;
	Node* Prev;
};

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
		this->SizeOfList = 0;
	} // 생성자, Head 노드와 Trailer 노드를 초기화하고 반복자에 Trailer를 대입함
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
	} // 반복자가 현재 노드의 다음 노드를 가리키게 함, 단 Trailer 노드를 가리키고 있는 경우 작동하지 X
	// Node& operator++() 연산자 오버로딩을 통해 구현할 수도 있음
	void CurrP() {
		if (Iterator != Trailer) {
			std::cout << Iterator->Element << std::endl;
		}
	} // 반복자가 현재 노드의 데이터 값을 출력하게 함, 단 Trailer 노드를 가리키고 있는 경우 작동하지 X
	void PrevP() {
		if (Iterator != Head->Next) {
			Iterator = Iterator->Prev;
		}
	} // 반복자가 현재 노드의 이전 노드를 가리키게 함, 단 Head 노드의 다음 노드를 가리키고 있는 경우 작동하지 X
	// Node& operator--() 연산자 오버로딩을 통해 구현할 수도 있음
	void Print() {
		if (SizeOfList == 0) {
			std::cout << "Empty" << std::endl;
		}
		else {
			Begin();
			for (int i = 0; i < SizeOfList; i++) {
				std::cout << Iterator->Element << " ";
				NextP();
			}
			std::cout << std::endl;
		}
	} // 반복자가 Head 노드 다음 노드부터 순차적으로 노드를 순회하면서 각 노드의 데이터 값을 출력, 비었다면 메세지를 출력
	void Insert(int Value) {
		Node* NewNode = new Node;
		NewNode->Element = Value;
		NewNode->Next = Iterator;
		NewNode->Prev = Iterator->Prev;
		Iterator->Prev->Next = NewNode;
		Iterator->Prev = NewNode;
		SizeOfList++; // 리스트 현재크기 1 증가
	} // 현재 노드와 이전 노드 사이에 값을 삽입함, 새로운 노드에 값을 입력받고 새 노드와 현재 노드, 이전 노드를 연결함
	void Erase() {
		if (SizeOfList == 0) {
			std::cout << "Empty" << std::endl;
		}
		else if (Iterator == Trailer) {
			std::cout << "Trailer" << std::endl;
		}
		else {
			Node* TempNode = Iterator;
			Iterator->Next->Prev = Iterator->Prev;
			Iterator->Prev->Next = Iterator->Next;
			delete TempNode;
			Begin(); // 반복자는 다시 Head 노드의 다음을 가리키도록 함
			SizeOfList--; // 리스트 현재크기 1 감소
		}
	} // 현재 노드를 삭제함, 현재 노드를 임시노드에 담고 다음 노드와 이전 노드를 서로 연결한 다음 임시노드를 삭제함
	void Upper(int Criteria) {
		if (SizeOfList == 0) {
			std::cout << "Empty" << std::endl;
		}
		else {
			Begin();
			for (int i = 0; i < SizeOfList; i++) {
				if (Iterator->Element > Criteria) {
					std::cout << i << " ";
				}
				NextP();
			}
			std::cout << std::endl;
		}
	} // 반복자가 Head 노드의 다음 노드부터 순차적으로 노드를 순회하면서 데이터 값이 입력받은 기준치 이상일때 인덱스를 출력, 비었다면 메세지를 출력
private :
	Node* Head; // Head 노드, 데이터를 저장하지 않고 노드의 시작점 역할을함
	Node* Trailer; // Trailer 노드, 데이터를 저장하지 않고 노드의 마지막 지점 역할을 함
	Node* Iterator; // 반복자, 각 노드를 가리키면서 현재 노드의 값을 반환하거나 주변 노드에 순차적으로 접근하는 역할을 함
	int SizeOfList; // 리스트의 현재 크기
};

int main() {
	List List1;

	int Counter;
	std::cin >> Counter;

	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "Begin") {
			List1.Begin();
		}
		else if (Command == "End") {
			List1.End();
		}
		else if (Command == "Next") {
			List1.NextP();
		}
		else if (Command == "Current") {
			List1.CurrP();
		}
		else if (Command == "Previous") {
			List1.PrevP();
		}
		else if (Command == "Print") {
			List1.Print();
		}
		else if (Command == "Insert") {
			int InputValue;
			std::cin >> InputValue;
			List1.Insert(InputValue);
		}
		else if (Command == "Erase") {
			List1.Erase();
		}
		else if (Command == "Upper") {
			int InputValue;
			std::cin >> InputValue;
			List1.Upper(InputValue);
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	} // 필요한 명령어와 파라미터를 받아 기능을 실행
}