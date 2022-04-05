#include <iostream>
#include <string>

struct Node {
	int Element;
	Node* Next;
	Node* Prev;
};

class Sequence {
public:
	friend struct Node;

	Sequence() {
		this->Head = new Node;
		this->Trailer = new Node;
		this->Head->Next = Trailer;
		this->Head->Prev = NULL;
		this->Trailer->Next = NULL;
		this->Trailer->Prev = Head;
		this->Iterator = Trailer;
		this->Index = 0;
		this->SizeOfSequence = 0;
	} // 생성자, Head 노드와 Trailer 노드를 초기화하고 반복자에 Trailer를 대입함

private:
	Node* Head; // Head 노드, 데이터를 저장하지 않고 노드의 시작점 역할을함
	Node* Trailer; // Trailer 노드, 데이터를 저장하지 않고 노드의 마지막 지점 역할을 함
	Node* Iterator; // 반복자, 각 노드를 가리키면서 현재 노드의 값을 반환하거나 주변 노드에 순차적으로 접근하는 역할을 함
	int Index; // 현재 인덱스
	int SizeOfSequence; // 시퀀스의 현재 크기
};

int main() {

}