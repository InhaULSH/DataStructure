#include <iostream>
#include <string>

class Node {
public:
	int Key; // 키값
	Node* Parent; // 부모 노드
	Node* Left; // 왼쪽 자식 노드
	Node* Right; // 오른쪽 자식 노드
	Node(int Value) {
		this->Key = Value;
		Parent = Left = Right = NULL;
	} // 노드 생성자, 키 값을 Value값으로 자식과 부모 노드를 NULL로 초기화
}; // 노드 구조체

class BinarySearchTree {
public:
	BinarySearchTree() {
		Root = NULL;
	} // 루트 노드를 NULL로 초기화
	Node* Search(Node* CurrentNode, int Value) {
		if (CurrentNode == NULL) {
			return NULL;
		} // 현재 노드가 NULL이면 NULL 반환
		else if (CurrentNode->Key == Value) {
			return CurrentNode;
		} // 현재 노드의 키값 == 찾는 값일 경우 현재 노드 반환
		else if (CurrentNode->Key < Value) {
			return Search(CurrentNode->Right, Value);
		} // 현재 노드의 키값 < 찾는 값일 경우 현재 노드의 왼족 자식 노드의 키값과 다시 비교
		else {
			return Search(CurrentNode->Left, Value);
		} // 현재 노드의 키값 > 찾는 값일 경우 현재 노드의 오른족 자식 노드의 키값과 다시 비교
	} // 검색 함수
	void Insert(int Value) {
		if (Search(this->Root, Value) != NULL) return; // 삽입하려는 키값을 검색해 이미 있으면 삽입과정은 생략

		Node* NewNode = new Node(Value); // 새 키값을 담는 임시노드
		if (Root = NULL) {
			Root = NewNode;
			return;
		} // 루트가 비었다면 임시노드를 루트노드로 하고 삽입과정은 생략

		Node* CurrentNode = Root; // 현재노드 <- 루트노드
		Node* ParentNode = NULL; // 부모노드
		while (CurrentNode != NULL) {
			ParentNode = CurrentNode;
			if (CurrentNode->Key < Value) {
				CurrentNode = CurrentNode->Right;
			}
			else {
				CurrentNode = CurrentNode->Left;
			}
		} // 현재 노드가 NULL이 될때까지 ParentNode와 CurrentNode를 갱신해가면서 삽입할 자리 탐색
		NewNode->Parent = ParentNode; // 임시노드를 부모노드와 연결
		if (ParentNode->Key < Value) {
			ParentNode->Right = NewNode;
		}
		else {
			ParentNode->Left = NewNode;
		} // 부모노드와 임시 노드의 키값에 따라 부모노드의 왼쪽/오른쪽 자식으로 임시노드를 연결
	} // 삽입 함수
	void Remove(int Value) {
		Node* RemoveNode = Search(this->Root, Value);
		if (RemoveNode == NULL) return; // 삭제하려는 키값을 검색해 없으면 삭제과정은 생략

		Node* ParentNode = RemoveNode->Parent; // 부모노드 <- 삭제할 노드의 부모노드
		Node* ChildNode; // 자식노드

		if (RemoveNode->Left == NULL && RemoveNode->Right == NULL) {
			ChildNode = NULL;
		} // 삭제할 노드의 자식이 없다면 자식노드를 NULL로 설정
		else if (RemoveNode->Left == NULL && RemoveNode->Right != NULL) {
			ChildNode = RemoveNode->Right;
		}
		else if (RemoveNode->Left != NULL && RemoveNode->Right == NULL) {
			ChildNode = RemoveNode->Left;
		} // 삭제할 노드의 자식이 하나라면 자식노드를 왼쪽 또는 오른쪽 자식으로 설정
		else {
			ChildNode = RemoveNode->Right;
			while (ChildNode->Left != NULL) {
				ChildNode = ChildNode->Left;
			}
			RemoveNode->Key = ChildNode->Key;
			RemoveNode = ChildNode;
			ParentNode = RemoveNode->Parent;
			ChildNode = RemoveNode->Right;
		} // 삭제할 노드의 자식이 두개라면 삭제할 노드에는 삭제할 노드와 가장 가까운 노드의 키값을 복사
		// 삭제할 노드를 삭제할 노드와 가장 가까운 노드로 변경하고 그에 맞춰 부모노드, 자식노드를 변경

		if (ParentNode == NULL) {
			Root = ChildNode;
			if (ChildNode != NULL) {
				Root->Parent = NULL;
			}
		} // 삭제할 노드가 루트라면 자식노드가 루트가 됨
		else if (RemoveNode == ParentNode->Left) {
			ParentNode->Left = ChildNode;
			if (ChildNode != NULL) {
				ChildNode->Parent = ParentNode;
			}
		} // 삭제할 노드가 부모노드의 왼쪽 자식이면 자식노드를 부모노드의 왼쪽 자식으로 연결
		else {
			ParentNode->Right = ChildNode;
			if (ChildNode != NULL) {
				ChildNode->Parent = ParentNode;
			}
		} // 삭제할 노드가 부모노드의 오른쪽 자식이면 자식노드를 부모노드의 오른쪽 자식으로 연결
		delete RemoveNode; // 삭제할노드를 Delete
	} // 노드 삭제 함수
	Node* Root; // 루트 노드
}; // 이진 탐색 트리 클래스

int main() {
	int Counter;
	std::cin >> Counter;
	BinarySearchTree BST1;

	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "Insert") {
			int InputValue;
			std::cin >> InputValue;

			BST1.Insert(InputValue);
		}
		else if (Command == "Remove") {
			int InputValue;
			std::cin >> InputValue;

			BST1.Remove(InputValue);
		}
		else if (Command == "Search") {
			int InputValue;
			std::cin >> InputValue;

			std::cout << BST1.Search(BST1.Root, InputValue)->Key << std::endl;
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	}
} // 메인 함수, 명령어와 필요한 매개변수를 입력받아 BST의 기능을 실행할 수 있음