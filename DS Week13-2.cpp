#include <iostream>
#include <vector>
#include <string>

struct Vertex {
	int VertexId;
	int Degree; // 정점과 연결된 간선의 수 
	Vertex* Previous;
	Vertex* Next;
	EdgeList IncidentEdge; // 정점과 인접한 간선을 담는 리스트

	Vertex() {
		this->VertexId = -1;
		this->Degree = 0;
		this->Previous = this->Next = NULL;
	}
	Vertex(int VertexIdx) {
		this->VertexId = VertexIdx;
		this->Degree = 0;
		this->Previous = this->Next = NULL;
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
	EdgeNode* IncidentEdgeNode_Src; // 시작 정점의 인접 리스트에서의 주소
	EdgeNode* IncidentEdgeNode_Dst; // 목적지 정점의 인접 리스트에서의 주소
	EdgeNode* TotalEdgeNode; // 그래프의 간선 리스트에서의 주소

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
	} // 간선 검색 함수, 시작과 목적지 정점 중 Degree가 작은 정점에서 인접 리스트를 순회하면서 해당 간선을 검색
	void InsertVertex(int VertexId) {
		if (VertexSequence.FindVertex(VertexId) != NULL) return; // 그래프에 정점이 이미 존재하면 함수 종료

		Vertex* NewVertex = new Vertex(VertexId); // 추가할 정점
		VertexSequence.InsertVertex(NewVertex); // 정점리스트에 정점 추가
	} // 정점 추가 함수
	void EraseVertex(int VertexId) {
		Vertex* TargetVertex = VertexSequence.FindVertex(VertexId); // 삭제할 정점
		if (TargetVertex == NULL) return; // 삭제할 정점을 못 찾은 경우 함수 종료

		for (EdgeNode* CurrentEdge = TargetVertex->IncidentEdge.Header->Next; CurrentEdge != TargetVertex->IncidentEdge.Trailer; CurrentEdge = CurrentEdge->Next) {
			EdgeSequence.EraseEdge(CurrentEdge->EdgeInfomation->TotalEdgeNode); // 그래프의 간선리스트에서 간선 삭제
			if (CurrentEdge == CurrentEdge->EdgeInfomation->IncidentEdgeNode_Src) {
				CurrentEdge->EdgeInfomation->Destination->IncidentEdge.EraseEdge(CurrentEdge->EdgeInfomation->IncidentEdgeNode_Dst);
			}
			else {
				CurrentEdge->EdgeInfomation->Start->IncidentEdge.EraseEdge(CurrentEdge->EdgeInfomation->IncidentEdgeNode_Src);
			} // 반대편 정점의 인접 리스트에서 간선 삭제
			delete CurrentEdge->EdgeInfomation; // 간선 Delete
		} // 삭제할 정점의 인접 리스트를 순회
		VertexSequence.EraseVertex(TargetVertex); // 정점 리스트에서 정점 삭제
	} // 정점 삭제 함수
	void InsertEdge(int SrcVertexId, int DstVertexId) {
		Vertex* Src = VertexSequence.FindVertex(SrcVertexId); // 정점 리스트에서 시작 정점을 탐색
		Vertex* Dst = VertexSequence.FindVertex(DstVertexId); // 정점 리스트에서 목적지 정점을 탐색
		if (Src == NULL || Dst == NULL) return; // 둘 중 하나라도 찾지 못 하면 함수 종료
		if (FindEdge(Src, Dst) != NULL) return; // 두 정점을 연결하는 간선이 없으면 함수 종료

		Edge* NewEdge = new Edge(Src, Dst); // 아니면 두 정점을 잇는 임시간선 생성
		Src->IncidentEdge.InsertEdge(NewEdge);
		Dst->IncidentEdge.InsertEdge(NewEdge); // 두 정점의 인접 리스트에 간선 삽입
		EdgeSequence.InsertEdge(NewEdge); // 그래프의 간선 리스트에 간선 삽입
		NewEdge->IncidentEdgeNode_Src = Src->IncidentEdge.Trailer->Previous;
		NewEdge->IncidentEdgeNode_Dst = Dst->IncidentEdge.Trailer->Previous; 
		NewEdge->TotalEdgeNode = EdgeSequence.Trailer->Previous; // 간선을 두 정점의 인접 리스트 주소, 그래프의 간선 리스트 주소에 연결
		Src->Degree++;
		Dst->Degree++; // 두 정점의 Degree 갱신
	} // 간선 추가 함수
	void EraseEdge(int SrcVertexId, int DstVertexId) {
		Vertex* Src = VertexSequence.FindVertex(SrcVertexId); // 정점 리스트에서 시작 정점 탐색
		Vertex* Dst = VertexSequence.FindVertex(DstVertexId); // 정점 리스트에서 목적지 정점 탐색
		if (Src == NULL || Dst == NULL) return; // 둘중 하나라도 찾지 못 하면 함수 종료

		Edge* TargetEdge = FindEdge(Src, Dst); // 삭제할 간선
		if (TargetEdge == NULL) return; // 삭제할 정점이 없다면 함수 종료

		Src->IncidentEdge.EraseEdge(TargetEdge->IncidentEdgeNode_Src);
		Dst->IncidentEdge.EraseEdge(TargetEdge->IncidentEdgeNode_Dst); // 두 정점의 인접리스트에서 간선 삭제
		EdgeSequence.EraseEdge(TargetEdge->TotalEdgeNode); // 그래프의 간선리스트에서 간선 삭제
		Src->Degree--;
		Dst->Degree--; // 두 정점의 Degree 갱신
		delete TargetEdge; // 임시간선 Delete
	} // 간선 삭제 함수
private:
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
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	}
} // 메인 함수, 명령어와 필요한 매개변수를 입력받아 그래프의 기능을 실행할 수 있음
