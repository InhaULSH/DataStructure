#include <iostream>
#include <vector>
#include <string>

struct Vertex {
	int VertexId;
	int MatrixIndex;
	Vertex* Previous;
	Vertex* Next;

	Vertex() {
		this->VertexId = this->MatrixIndex = -1;
		this->Previous = this->Next = NULL;
	}
	Vertex(int VertexIdx) {
		this->VertexId = VertexIdx;
		this->MatrixIndex = -1;
		this->Previous = this->Next = NULL;
	}
}; // 정점 구조체

struct Edge {
	Vertex* Start;
	Vertex* Destination;
	Edge* Previous;
	Edge* Next;

	Edge() {
		this->Start = this->Destination = NULL;
		this->Previous = this->Next = NULL;
	}
	Edge(Vertex* Src, Vertex* Dst) {
		this->Start = Src;
		this->Destination = Dst;
		this->Previous = this->Next = NULL;
	}
}; // 간선 구조체

class VertexList {
public:
	VertexList() {
		this->Header = new Vertex();
		this->Trailer = new Vertex();
		Header->Next = Trailer;
		Trailer->Previous = Header;
		Header->MatrixIndex = -1;
	}
	void InsertVertex(Vertex* NewVertex) {
		NewVertex->Previous = Trailer->Previous;
		NewVertex->Next = Trailer;
		NewVertex->MatrixIndex = Trailer->Previous->MatrixIndex + 1;
		Trailer->Previous->Next = Trailer->Previous = NewVertex;
	}
	void EraseVertex(Vertex* TargetVertex) {
		for (Vertex* CurrentVertex = TargetVertex; CurrentVertex != Trailer; CurrentVertex = CurrentVertex->Next) {
			CurrentVertex->MatrixIndex--;
		}
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
	}
private:
	Vertex* Header;
	Vertex* Trailer;
}; // 정점 리스트 클래스

class EdgeList {
public:
	EdgeList() {
		this->Header = new Edge();
		this->Trailer = new Edge();
		Header->Next = Trailer;
		Trailer->Previous = Header;
	}
	void InsertEdge(Edge* NewEdge) {
		NewEdge->Previous = Trailer->Previous;
		NewEdge->Next = Trailer;
		Trailer->Previous->Next = Trailer->Previous = NewEdge;
	}
	void EraseEdge(Edge* TargetEdge) {
		TargetEdge->Previous->Next = TargetEdge->Next;
		TargetEdge->Next->Previous = TargetEdge->Previous;
		delete TargetEdge;
	}
private:
	Edge* Header;
	Edge* Trailer;
}; // 간선 리스트 클래스


class Graph {
public:
	void InsertVertex(int VertexId) {
		if (VertexSequence.FindVertex(VertexId) != NULL) return; // 그래프에 정점이 이미 존재하면 함수 종료

		Vertex* NewVertex = new Vertex(VertexId); // 추가할 정점
		for (int i = 0; i < EdgeMatrix.size(); i++) {
			EdgeMatrix[i].push_back(NULL);
		}
		EdgeMatrix.push_back(std::vector<Edge*>(EdgeMatrix.size() + 1, NULL)); // 정점 추가에 따라 인접행렬을 확장
		VertexSequence.InsertVertex(NewVertex); // 정점리스트에 정점 추가
	} // 정점 추가 함수
	void EraseVertex(int VertexId) {
		Vertex* TargetVertex = VertexSequence.FindVertex(VertexId); // 삭제할 정점
		if (TargetVertex == NULL) return; // 삭제할 정점을 못 찾은 경우 함수 종료

		int MatrixIdx = TargetVertex->MatrixIndex;
		for (int i = 0; i < EdgeMatrix.size(); i++) {
			if (i != MatrixIdx) {
				if (EdgeMatrix[i][MatrixIdx] != NULL) {
					EdgeSequence.EraseEdge(EdgeMatrix[i][MatrixIdx]);
				}
				EdgeMatrix[i].erase(EdgeMatrix[i].begin() + MatrixIdx);
			}
		}

		EdgeMatrix.erase(EdgeMatrix.begin() + MatrixIdx); // 정점 삭제에 따라 인접한 간선을 삭제하고 인접행렬을 축소
		VertexSequence.EraseVertex(TargetVertex); // 정점 리스트에서 정점 삭제
	} // 정점 삭제 함수
	void InsertEdge(int SrcVertexId, int DstVertexId) {
		Vertex* Src = VertexSequence.FindVertex(SrcVertexId); // 정점 리스트에서 시작 정점을 탐색
		Vertex* Dst = VertexSequence.FindVertex(DstVertexId); // 정점 리스트에서 목적지 정점을 탐색
		if (Src == NULL || Dst == NULL) return; // 둘 중 하나라도 찾지 못 하면 함수 종료

		int SrcMatrixIdx = Src->MatrixIndex;
		int DstMatrixIdx = Dst->MatrixIndex;
		if (EdgeMatrix[SrcMatrixIdx][DstMatrixIdx] != NULL || EdgeMatrix[DstMatrixIdx][SrcMatrixIdx] != NULL) return;
		// 두 정점을 잇는 간선이 이미 존재하면 함수 종료

		Edge* NewEdge = new Edge(Src, Dst); // 아니면 두 간선을 잇는 임시간선 생성
		EdgeSequence.InsertEdge(NewEdge); // 간선리스트에 간선 추가
		EdgeMatrix[SrcMatrixIdx][DstMatrixIdx] = EdgeMatrix[DstMatrixIdx][SrcMatrixIdx] = NewEdge; // 인접행렬에 간선 추가
	} // 간선 추가 함수
	void EraseEdge(int SrcVertexId, int DstVertexId) {
		Vertex* Src = VertexSequence.FindVertex(SrcVertexId); // 정점 리스트에서 시작 정점 탐색
		Vertex* Dst = VertexSequence.FindVertex(DstVertexId); // 정점 리스트에서 목적지 정점 탐색
		if (Src == NULL || Dst == NULL) return; // 둘중 하나라도 찾지 못 하면 함수 종료

		int SrcMatrixIdx = Src->MatrixIndex;
		int DstMatrixIdx = Dst->MatrixIndex;
		if (EdgeMatrix[SrcMatrixIdx][DstMatrixIdx] == NULL || EdgeMatrix[DstMatrixIdx][SrcMatrixIdx] == NULL) return;
		// 두 정점을 잇는 간선이 없다면 함수 종료

		EdgeSequence.EraseEdge(EdgeMatrix[SrcMatrixIdx][DstMatrixIdx]); // 아니면 해당 간선을 간선리스트에서 삭제
		EdgeMatrix[SrcMatrixIdx][DstMatrixIdx] = EdgeMatrix[DstMatrixIdx][SrcMatrixIdx] = NULL; // 인접행렬에서 간선 삭제
	} // 간선 삭제 함수
private:
	std::vector<std::vector<Edge*> > EdgeMatrix; // 인접 행렬
	VertexList VertexSequence; // 정점 리스트
	EdgeList EdgeSequence; // 간선 리스트
}; // 인접 행렬로 구현한 그래프 클래스

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