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
	} // 노드 생성자, 값을 받아 Element를 초기화하고 Parent를 NULL로 설정
}; // 트리 구현을 위한 노드 클래스

class Tree_NLink {
public :
	Node* Root;
	std::vector<Node*> Nodes;

	Tree_NLink() {
		Node* NewNode = new Node(1);
		this->Root = NewNode;
		this->Nodes.push_back(NewNode);
	} // 생성자, 1의 값을 가지는 루트노드 생성
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
	} // 노드 삽입 함수, 임시노드에 값을 받아 저장하고 부모노드의 데이터값을 받아 부모노드를 찾으면 부모노드의 Child 벡터에 임시노드를 푸시
	  // 이미 같은 값을 가진 노드가 존재하거나 부모노드를 찾지 못하면 -1 출력
	void DeleteNode(int Data) {
		Node* CurrNode;
		Node* ParentNode;
		for (int i = 0; i < Nodes.size(); i++) {
			if (Nodes[i]->Element == Data) {
				if (Nodes[i] == Root) {
					std::cout << -1 << std::endl;
					return;
				} // 삭제하려는 노드가 루트이면 -1 출력
				else {
					CurrNode = Nodes[i];
					ParentNode = CurrNode->Parent;
					for (Node* Child : CurrNode->Child) {
						ParentNode->Child.push_back(Child);
						Child->Parent = ParentNode;
					} // 삭제하고 싶은 노드의 자식 노드들을 부모 노드의 자식 노드로 푸시
					for (int j = 0; j < ParentNode->Child.size(); j++) {
						if (ParentNode->Child[j]->Element == Data) {
							ParentNode->Child.erase(ParentNode->Child.begin() + j);
						}
					} // 삭제하고 싶은 노드를 Child 벡터에서 삭제
					Nodes.erase(Nodes.begin() + i); // 삭제하고 싶은 노드를 Nodes 벡터에서 삭제
					delete CurrNode;
					return;
				}				
			}
		}
		std::cout << -1 << std::endl; // 삭제할 노드를 찾지 못하면 -1 출력
	} // 노드 삭제 함수
	void ParentOf(int Data) {
		for (int i = 0; i < Nodes.size(); i++) {
			if (Nodes[i]->Element == Data) {
				std::cout << Nodes[i]->Parent->Element << std::endl;
				return;
			}
		}
		std::cout << -1 << std::endl; // 노드를 찾지 못하면 -1 출력
	} // 부모 노드 출력 함수, Nodes 벡터를 순회하면서 원하는 노드를 찾으면 그 부모 노드의 값을 출력
	void ChildOf(int Data) {
		for (int i = 0; i < Nodes.size(); i++) {
			if (Nodes[i]->Element == Data) {
				if (Nodes[i]->Child.size() == 0) {
					std::cout << -1 << std::endl;
					return;
				} // 찾은 노드의 자식 노드가 없으면 -1 출력
				else {
					for (int j = 0; j < Nodes[i]->Child.size(); j++) {
						std::cout << Nodes[i]->Child[j]->Element << " ";
					}
					std::cout << std::endl;
					return;
				} // 찾은 노드의 Child 벡터를 순회하면서 각 노드의 값을 출력
			}
		}
		std::cout << -1 << std::endl; // 노드를 찾지 못하면 -1 출력
	} // 자식 노드 출력 함수
	void MinChildOf(int Data) {
		for (int i = 0; i < Nodes.size(); i++) {
			if (Nodes[i]->Element == Data) {
				if (Nodes[i]->Child.size() == 0) {
					std::cout << -1 << std::endl;
					return;
				} // 찾은 노드의 자식 노드가 없으면 -1 출력
				else {
					int Minimum = Nodes[i]->Child[0]->Element;
					for (int j = 1; j < Nodes[i]->Child.size(); j++) {
						if (Nodes[i]->Child[j]->Element < Minimum) {
							Minimum = Nodes[i]->Child[j]->Element;
						}
					}
					std::cout << Minimum << std::endl;
					return;
				}
			} // 찾은 노드의 Child 벡터를 순회하면서 벡터 첫 노드의 값보다 더 작은 데이터값을 가진 노드가 있다면
			  // 최솟값을 그 노드의 데이터값으로 변경, 반복문 종료 후 최솟값 출력
		}
		std::cout << -1 << std::endl; // 노드를 찾지 못하면 -1 출력
	} // 자식 노드의 최솟값 출력함수
}; // 노드로 구현한 트리 클래스

int main() {
	Tree_NLink Tree1;
	int Counter;
	std::cin >> Counter;

	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "insert") {
			int InputValue;
			int NodeData;
			std::cin >> NodeData >> InputValue;
			Tree1.InsertNode(NodeData, InputValue);
		}
		else if (Command == "delete") {
			int NodeData;
			std::cin >> NodeData;
			Tree1.DeleteNode(NodeData);
		}
		else if (Command == "parent") {
			int NodeData;
			std::cin >> NodeData;
			Tree1.ParentOf(NodeData);
		}
		else if (Command == "child") {
			int NodeData;
			std::cin >> NodeData;
			Tree1.ChildOf(NodeData);
		}
		else if (Command == "minChild") {
			int NodeData;
			std::cin >> NodeData;
			Tree1.MinChildOf(NodeData);
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	} // 명령어와 필요한 파라미터를 입력받아 기능을 실행시킴
}