#include <iostream>
#include <string>
#include <queue>

struct Vertex {
	bool isVisited;
	int VertexId;
	int Degree;
	Vertex* Previous;
	Vertex* Next;
	EdgeList IncidentEdge;

	Vertex() {
		this->VertexId = -1;
		this->Degree = 0;
		this->Previous = this->Next = NULL;
		this->isVisited = false;
	}
	Vertex(int VertexIdx) {
		this->VertexId = VertexIdx;
		this->Degree = 0;
		this->Previous = this->Next = NULL;
		this->isVisited = true;
	}
}; // 정점 구조체

struct EdgeNode {
	Edge* EdgeInfomation;
	EdgeNode* Previous;
	EdgeNode* Next;
	EdgeNode() {
		this->EdgeInfomation = NULL;
		this->Previous = this->Next = NULL;
	}
	EdgeNode(Edge* EdgInfo) {
		this->EdgeInfomation = EdgInfo;
		this->Previous = this->Next = NULL;
	}
}; // 간선 리스트 구성하는 노드 구조체

struct Edge {
	Vertex* Start;
	Vertex* Destination;
	EdgeNode* IncidentEdgeNode_Src;
	EdgeNode* IncidentEdgeNode_Dst;
	EdgeNode* TotalEdgeNode;

	Edge() {
		this->Start = this->Destination = NULL;
	}
	Edge(Vertex* Src, Vertex* Dst) {
		this->Start = Src;
		this->Destination = Dst;
	}
}; // 간선 구조체

class VertexList {
public:
	VertexList() {
		this->Header = new Vertex();
		this->Trailer = new Vertex();
		Header->Next = Trailer;
		Trailer->Previous = Header;
	}
	void InsertVertex(Vertex* NewVertex) {
		NewVertex->Previous = Trailer->Previous;
		NewVertex->Next = Trailer;
		Trailer->Previous->Next = Trailer->Previous = NewVertex;
	}
	void EraseVertex(Vertex* TargetVertex) {
		TargetVertex->Previous->Next = TargetVertex->Next;
		TargetVertex->Next->Previous = TargetVertex->Previous;
		delete TargetVertex;
	}
	Vertex* FindVertex(int VertexId) {
		for (Vertex* CurrentVertex = Header->Next; CurrentVertex != Trailer; CurrentVertex = CurrentVertex->Next) {
			if (CurrentVertex->VertexId == VertexId) {
				return CurrentVertex;
			}
		}
		return NULL;
	}
	Vertex* Header;
	Vertex* Trailer;
}; // 정점 리스트 클래스

class EdgeList {
public:
	EdgeList() {
		this->Header = new EdgeNode();
		this->Trailer = new EdgeNode();
		Header->Next = Trailer;
		Trailer->Previous = Header;
	}
	void InsertEdge(Edge* NewEdge) {
		EdgeNode* NewEdgeNode = new EdgeNode(NewEdge);
		NewEdgeNode->Previous = Trailer->Previous;
		NewEdgeNode->Next = Trailer;
		Trailer->Previous->Next = Trailer->Previous = NewEdgeNode;
	}
	void EraseEdge(EdgeNode* TargetEdge) {
		TargetEdge->Previous->Next = TargetEdge->Next;
		TargetEdge->Next->Previous = TargetEdge->Previous;
		delete TargetEdge;
	}
	EdgeNode* Header;
	EdgeNode* Trailer;
}; // 간선 리스트 클래스

class Graph {
public:
	Edge* FindEdge(Vertex* Src, Vertex* Dst) {
		if (Src->Degree < Dst->Degree) {
			for (EdgeNode* CurrentEdge = Src->IncidentEdge.Header->Next; CurrentEdge != Src->IncidentEdge.Trailer; CurrentEdge = CurrentEdge->Next) {
				if (CurrentEdge->EdgeInfomation->Destination == Dst) {
					return CurrentEdge->EdgeInfomation;
				}
			}
		}
		else {
			for (EdgeNode* CurrentEdge = Dst->IncidentEdge.Header->Next; CurrentEdge != Dst->IncidentEdge.Trailer; CurrentEdge = CurrentEdge->Next) {
				if (CurrentEdge->EdgeInfomation->Destination == Src) {
					return CurrentEdge->EdgeInfomation;
				}
			}
		}
		return NULL;
	}
	void InsertVertex(int VertexId) {
		if (VertexSequence.FindVertex(VertexId) != NULL) return;

		Vertex* NewVertex = new Vertex(VertexId);
		VertexSequence.InsertVertex(NewVertex);
	} // 정점 추가 함수
	void EraseVertex(int VertexId) {
		Vertex* TargetVertex = VertexSequence.FindVertex(VertexId);
		if (TargetVertex == NULL) return;

		for (EdgeNode* CurrentEdge = TargetVertex->IncidentEdge.Header->Next; CurrentEdge != TargetVertex->IncidentEdge.Trailer; CurrentEdge = CurrentEdge->Next) {
			EdgeSequence.EraseEdge(CurrentEdge->EdgeInfomation->TotalEdgeNode);
			if (CurrentEdge == CurrentEdge->EdgeInfomation->IncidentEdgeNode_Src) {
				CurrentEdge->EdgeInfomation->Destination->IncidentEdge.EraseEdge(CurrentEdge->EdgeInfomation->IncidentEdgeNode_Dst);
			}
			else {
				CurrentEdge->EdgeInfomation->Start->IncidentEdge.EraseEdge(CurrentEdge->EdgeInfomation->IncidentEdgeNode_Src);
			}
			delete CurrentEdge->EdgeInfomation;
		}
		VertexSequence.EraseVertex(TargetVertex);
	} // 정점 삭제 함수
	void InsertEdge(int SrcVertexId, int DstVertexId) {
		Vertex* Src = VertexSequence.FindVertex(SrcVertexId);
		Vertex* Dst = VertexSequence.FindVertex(DstVertexId);
		if (Src == NULL || Dst == NULL) return;
		if (FindEdge(Src, Dst) != NULL) return;

		Edge* NewEdge = new Edge(Src, Dst);
		Src->IncidentEdge.InsertEdge(NewEdge);
		Dst->IncidentEdge.InsertEdge(NewEdge);
		EdgeSequence.InsertEdge(NewEdge);
		NewEdge->IncidentEdgeNode_Src = Src->IncidentEdge.Trailer->Previous;
		NewEdge->IncidentEdgeNode_Dst = Dst->IncidentEdge.Trailer->Previous;
		NewEdge->TotalEdgeNode = EdgeSequence.Trailer->Previous;
		Src->Degree++;
		Dst->Degree++;
	} // 간선 추가 함수
	void EraseEdge(int SrcVertexId, int DstVertexId) {
		Vertex* Src = VertexSequence.FindVertex(SrcVertexId);
		Vertex* Dst = VertexSequence.FindVertex(DstVertexId);
		if (Src == NULL || Dst == NULL) return;

		Edge* TargetEdge = FindEdge(Src, Dst);
		if (TargetEdge == NULL) return;

		Src->IncidentEdge.EraseEdge(TargetEdge->IncidentEdgeNode_Src);
		Dst->IncidentEdge.EraseEdge(TargetEdge->IncidentEdgeNode_Dst);
		EdgeSequence.EraseEdge(TargetEdge->TotalEdgeNode);
		Src->Degree--;
		Dst->Degree--;
		delete TargetEdge;
	} // 간선 삭제 함수

	void DFS(Vertex* CurrentVertex) {
		CurrentVertex->isVisited = true; // 현재 정점을 방문한 정점으로 체크
		for (EdgeNode* Edg = CurrentVertex->IncidentEdge.Header->Next; Edg != CurrentVertex->IncidentEdge.Trailer; Edg = Edg->Next) {
			if (CurrentVertex == Edg->EdgeInfomation->Start && Edg->EdgeInfomation->Destination->isVisited == false) {
				DFS(Edg->EdgeInfomation->Destination);
			}
			else if (Edg->EdgeInfomation->Start->isVisited == false) {
				DFS(Edg->EdgeInfomation->Start);
			}
		} // 현재 정점과 인접한 정점을 탐색하면서 방문 되지 않은 인접정점들에서 다시 DFS 실행
	} // DFS 실행 함수
	void BFS(int VertexId) {
		Vertex* StartVertex = VertexSequence.FindVertex(VertexId); // 탐색 시작 정점
		std::queue<Vertex*> Que;
		Que.push(StartVertex); // 큐에 탐색 시작 정점 푸시
		StartVertex->isVisited = true; // 탐색 시작 정점에 방문한 것으로 체크
		while (!Que.empty()) {
			Vertex* CurrentVertex = Que.front(); // 큐의 맨 앞의 정점에서 탐색 시작
			Que.pop(); // 큐의 맨 앞의 정점을 큐에서 삭제
			for (EdgeNode* Edg = CurrentVertex->IncidentEdge.Header->Next; Edg != CurrentVertex->IncidentEdge.Trailer; Edg = Edg->Next) {
				if (CurrentVertex == Edg->EdgeInfomation->Start && Edg->EdgeInfomation->Destination->isVisited == false) {
					Que.push(Edg->EdgeInfomation->Destination);
					Edg->EdgeInfomation->Destination->isVisited = true;
				}
				else if (Edg->EdgeInfomation->Start->isVisited == false) {
					Que.push(Edg->EdgeInfomation->Start);
					Edg->EdgeInfomation->Start->isVisited = true;
				}
			} // 현재 노드와 연결된 정점을 탐색
		} // 큐가 비어있지 않을 때 즉, 모든 정점을 방문할 때까지 탐색, 아직 방문하지 않은 정점을 큐에 삽입하고 방문한 정점으로 체크
	} // BFS 실행 함수

	VertexList VertexSequence; // 정점 리스트
	EdgeList EdgeSequence; // 간선 리스트
}; // 인접 리스트로 구현한 그래프 클래스

int main() {
	int Counter;
	std::cin >> Counter;

	Graph G1;
	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "InsertVertex") {
			int InputVertexId;
			std::cin >> InputVertexId;
			G1.InsertVertex(InputVertexId);
		}
		else if (Command == "EraseVertex") {
			int InputVertexId;
			std::cin >> InputVertexId;
			G1.EraseVertex(InputVertexId);
		}
		else if (Command == "InsertEdge") {
			int InputSrcVertexId;
			int InputDstVertexId;
			std::cin >> InputSrcVertexId >> InputDstVertexId;
			G1.InsertEdge(InputSrcVertexId, InputDstVertexId);
		}
		else if (Command == "EraseEdge") {
			int InputSrcVertexId;
			int InputDstVertexId;
			std::cin >> InputSrcVertexId >> InputDstVertexId;
			G1.EraseEdge(InputSrcVertexId, InputDstVertexId);
		}
		else if (Command == "DFS") {
			int InputVertexId;
			std::cin >> InputVertexId;
			G1.DFS(G1.VertexSequence.FindVertex(InputVertexId));
		}
		else if (Command == "BFS") {
			int InputVertexId;
			std::cin >> InputVertexId;
			G1.BFS(InputVertexId);
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	}
} // 메인 함수, 명령어와 필요한 매개변수를 입력받아 그래프의 기능을 실행할 수 있음