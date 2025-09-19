#include <iostream>
#include <vector>

class Node {
	int Element;
	int Capacity;
	Node* Parent;
	std::vector<Node*> Child; // std::vector <데이터 타입> 벡터 이름;

	friend class Tree_NLink;

	Node(int Value) {
		this->Element = Value;
		this->Capacity = 0;
		this->Parent = NULL;
	}
}; // 트리 구현을 위한 노드 클래스

class Tree_NLink {
public:
	Node* Root;
	std::vector<Node*> Nodes;
	int SumOfCapacity;

	Tree_NLink() {
		Node* NewNode = new Node(1);
		this->Root = NewNode;
		this->Nodes.push_back(NewNode);
		this->SumOfCapacity = 0;
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
	void SetCapacity(int Value, int Cap) {
		for (int i = 0; i < Nodes.size(); i++) {
			if (Nodes[i]->Element == Value) {
				Nodes[i]->Capacity = Cap;
				return;
			}
		}
	} // 노드 용량 설정 함수
	void PreOrder(Node* N) {
		if (!N) return;

		this->SumOfCapacity += N->Capacity;
		for (int i = 0; i < N->Child.size(); i++) {
			PreOrder(N->Child[i]);
		}
	} // 트리 전위순회 함수, 입력받은 노드를 기준으로 전위순위하면서 SumOfCapacity에 노드의 용량을 더해줌
	Node* FindOf(int Value) {
		for (int i = 0; i < Nodes.size(); i++) {
			if (Nodes[i]->Element == Value) {
				return Nodes[i];
			}
		}
		return this->Root;
	} // 노드 검색 함수
}; // 기능 구현을 위한 트리 클래스

int main() {
	Tree_NLink Tree5;
	int NodeCounter;
	int QuestionCounter;
	std::cin >> NodeCounter >> QuestionCounter;

	for (int i = 1; i < NodeCounter; i++) {
		int ParentData;
		int ChildData;
		std::cin >> ParentData >> ChildData;

		Tree5.InsertNode(ParentData, ChildData);
	} // NodeCounter -1 번 만큼 노드들을 삽입
	for (int i = 0; i < NodeCounter; i++) {
		int Data;
		int InputCap;
		std::cin >> Data >> InputCap;

		Tree5.SetCapacity(Data, InputCap);
	} // NodeCounter  번 만큼 노드의 용량을 설정
	for (int i = 0; i < QuestionCounter; i++) {
		int Data;
		std::cin >> Data;

		Tree5.PreOrder(Tree5.FindOf(Data));
		std::cout << Tree5.SumOfCapacity << std::endl;
		Tree5.SumOfCapacity = 0; // 용량의 합을 출력한 후 SumOfCapacity 변수를 다시 0으로 초기화
	} // QuestionCounter 번 만큼 용량을 계산
}