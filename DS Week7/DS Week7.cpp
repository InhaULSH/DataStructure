#include <iostream>
#include <string>
#include <vector>

class Node {
	int Element;
	Node* Parent;
	std::vector<Node*> Child; // std::vector <데이터 타입> 벡터 이름;

	friend class Tree_NLink;

	Node(int Value) {
		this->Element = Value;
		this->Parent = NULL;
	}
}; // 트리 구현을 위한 노드 클래스

class Tree_NLink {
public:
	Node* Root;
	std::vector<Node*> Nodes;

	Tree_NLink() {
		Node* NewNode = new Node(1);
		this->Root = NewNode;
		this->Nodes.push_back(NewNode);
	}
	void InsertNode(int ParentData, int Value) {
		Node* NewNode = new Node(Value);
		for (int i = 0; i < Nodes.size(); i++) {
			if (Nodes[i]->Element == Value) {
				std::cout << -1 << std::endl;
				return;
			}
			else if (Nodes[i]->Element == ParentData) {
				Nodes[i]->Child.push_back(NewNode);
				Nodes.push_back(NewNode);
				NewNode->Parent = Nodes[i];
				return;
			}
		}
		std::cout << -1 << std::endl;
	} // 노드 삽입 함수
	void PreOrder(Node* N) {
		if (!N) return;

		std::cout << N->Element << " ";
		for (int i = 0; i < N->Child.size(); i++) {
			PreOrder(N->Child[i]);
		}
	} // 트리 전위순회 함수
	void PostOrder(Node* N) {
		if (!N) return;

		for (int i = 0; i < N->Child.size(); i++) {
			PostOrder(N->Child[i]);
		}
		std::cout << N->Element << " ";
	} // 트리 후위순회 함수
	Node* FindOf(int Value) {
		for (int i = 0; i < Nodes.size(); i++) {
			if (Nodes[i]->Element == Value) {
				return Nodes[i];
			}
		}
		return this->Root;
	} // 노드 검색 함수, 받아온 값에 해당하는 노드를 찾아 리턴, 찾지 못하면 루트 노드를 리턴
}; // 트리 클래스

int main() {
	Tree_NLink Tree3;
	int Counter;
	std::cin >> Counter;

	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "Insert") {
			int ParentData;
			int InputData;
			std::cin >> ParentData >> InputData;

			Tree3.InsertNode(ParentData, InputData);
		} // 노드 삽입
		else if (Command == "Preorder") {
			int InputData;
			std::cin >> InputData;

			Tree3.PreOrder(Tree3.FindOf(InputData));
			std::cout << std::endl;
		} // 전위 순회
		else if (Command == "Postorder") {
			int InputData;
			std::cin >> InputData;

			Tree3.PostOrder(Tree3.FindOf(InputData));
			std::cout << std::endl;
		} // 후위 순회
		else {
			std::cout << "Invalid Input" << std::endl;
		} // 그외의 입력에는 메세지를 출력
	} // 명령어와 필요한 파라미터를 입력받아 클래스의 함수들을 실행함
}