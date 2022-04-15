#include <iostream>
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
	int DepthOf(int Data) {
		Node* ContainerNode = new Node(0);
		for (int i = 0; i < Nodes.size(); i++) {
			if (Nodes[i]->Element == Data) {
				ContainerNode = Nodes[i];
				break;
			}
		} // 받아온 값에 해당하는 노드를 임시노드에 저장
		int Counter = 0;
		while (ContainerNode != Root) {
			ContainerNode = ContainerNode->Parent;
			Counter++;
		} // Root 노드에 이를때 까지 부모노드로 접근하면서 Counter에 1씩 더해줌
		return Counter; // Counter 반환
	} // 노드의 깊이 반환 함수
}; // 기능 구현을 위한 트리 클래스

int main() {
	Tree_NLink Tree2;
	int NodeCounter;
	int QuestionCounter;
	std::cin >> NodeCounter >> QuestionCounter;

	for (int i = 1; i < NodeCounter; i++) {
		int ParentData;
		int ChildData;
		std::cin >> ParentData >> ChildData;

		Tree2.InsertNode(ParentData, ChildData);
	} // NodeCounter -1 번 만큼 노드들을 삽입
	for (int i = 0; i < QuestionCounter; i++) {
		int NodeData;
		std::cin >> NodeData;
		std::cout << Tree2.DepthOf(NodeData) << std::endl;
	} // QuestionCounter 번 만큼 노드의 깊이를 찾음
}