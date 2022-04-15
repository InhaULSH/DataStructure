#include <iostream>
#include <vector>

class Node {
	int Element;
	Node* Parent;
	std::vector<Node*> Child;

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
		}
		int Counter = 0;
		while (ContainerNode != Root) {
			ContainerNode = ContainerNode->Parent;
			Counter++;
		}
		return Counter;
	} // 노드의 깊이 반환 함수
	void PostOrder(Node* N) {
		if (!N) return;

		for (int i = 0; i < N->Child.size(); i++) {
			PostOrder(N->Child[i]);
		}
		std::cout << this->DepthOf(N->Element) << " ";
	} // 트리 후위순회 함수, 노드의 데이터 대신 노드의 깊이를 출력
}; // 기능 구현을 위한 트리 클래스

int main() {
	int Counter;
	std::cin >> Counter;

	for (int i = 0; i < Counter; i++) {
		Tree_NLink Tree4;
		int NodeCounter;
		std::cin >> NodeCounter;

		for (int i = 1; i < NodeCounter; i++) {
			int ParentData;
			int ChildData;
			std::cin >> ParentData >> ChildData;

			Tree4.InsertNode(ParentData, ChildData);
		} // NodeCounter -1 번 만큼 노드들을 삽입
		Tree4.PostOrder(Tree4.Root); 
		std::cout << std::endl; // 삽입이 끝난 후 트리의 루트 노드를 기준으로 후위 순회하면서 각 노드의 깊이 출력
	} // Counter 번 만큼 이 작업을 반복
}