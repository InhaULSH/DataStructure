#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

int V, E;
// V: 도시 개수 (정점 개수)
// E: 도로 개수 (간선 개수)

unordered_map<string, int> cityIdx;
vector<string> IdxtoCity;
// 도시 이름을 인덱스에 매핑
// IdxtoCity[i] 는 인덱스 i 에 해당하는 도시 이름을 저장
// cityIdx[city_name] 는 해당 도시 이름의 인덱스를 반환

vector<int> cityHeight;
// 도시별 고도

struct Edge {
    int to;              // 연결된 도시의 인덱스
    int length;           // 도로 길이
    int timestamp;       // 도로 개통 시기 (YYYYMM)
    int heightDiff;       // 도시 간 고도차 절댓값
};
// 도로(간선) 정보 저장

vector<vector<Edge>> adjList;
// 인접 리스트, adjList[u] 는 도시 u와 연결된 모든 도로 정보 저장

vector<bool> visited;
// 방문 여부 표시 변수

int parseTimestamp(string inputStr) {
    try {
        int y = stoi(inputStr.substr(0, 4));
        int m = stoi(inputStr.substr(5, 2));
        return y * 100 + m;
    }
    catch (const std::invalid_argument& e) {
        cerr << "invalid_argument : " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e) {
        cerr << "out_of_range : " << e.what() << std::endl;
    }
};
// 문자열 "YYYY-MM" 형태를 정수 YYYYMM으로 변환

pair<string, string> getCityLexPair(int U, int V) {
    string NameofU = IdxtoCity[U];
    string NameofV = IdxtoCity[V];
    if (NameofU < NameofV) {
        return { NameofU, NameofV };
    }
    else {
        return { NameofV, NameofU };
    }
};
// 두 도시 인덱스 U, V에 대해 사전순으로 작은 도시 이름과 큰 도시 이름 반환

struct EdgePQ {
	int U, V; 
    // MST에 포함된 정점 U, 인접한 정점 V
    int Length;
    int timeStamp;
    int heightDiff;
	// 간선 가중치 정보: 길이, 개통 시기, 고저차

    EdgePQ(int _u, int _v, int _length, int _timestamp, int _heightDiff) {
        U = _u;
        V = _v;
        Length = _length;
        timeStamp = _timestamp;
        heightDiff = _heightDiff;
    }
	// 생성자
};
// EdgePQ: Prim 알고리즘에서 우선순위 큐에 넣을 간선 정보 구조체

struct EdgeCompare {
    bool operator()(const EdgePQ& a, const EdgePQ& b) const {
        if (a.timeStamp != b.timeStamp) {
            return a.timeStamp > b.timeStamp;
        }
        // 오래된 간선일수록 우선순위 높음
        if (a.Length != b.Length) {
            return a.Length > b.Length;
        }
        // 짧은 길이일수록 우선순위 높음
        if (a.heightDiff != b.heightDiff) {
            return a.heightDiff > b.heightDiff;
        }
        // 고저차가 작은 간선이 우선순위 높음					
        string cityA_a, cityB_a;
        string cityA_b, cityB_b;
        tie(cityA_a, cityB_a) = getCityLexPair(a.U, a.V);
        tie(cityA_b, cityB_b) = getCityLexPair(b.U, b.V);
        // 사전순으로 도시 이름 비교		
        if (cityA_a != cityA_b) {
            return cityA_a > cityA_b;
        }
        // cityA가 다르면 cityA 비교       
        else if (cityB_a != cityB_b) {
            return cityB_a > cityB_b;
        }
        // cityA가 같으면 cityB 비교
        else {
            return false;
        }
		// 모든 조건이 같으면 우선순위 동일
    };
};
// EdgeCompare : EdgePQ를 우선순위 큐에 넣을 때 사용할 비교자

void PrimMST(int startIdx) {
    visited.resize(V);
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }
    // visited 초기화

    struct ResultEdge {
        int timestamp_rs = 0;
        string cityA_rs, cityB_rs = "";
        int length_rs = 0;
    };
    vector<ResultEdge> resultEdges;
    long long totalLength = 0;
    // resultEdges: MST 결과값 저장 벡터

    priority_queue<EdgePQ, vector<EdgePQ>, EdgeCompare> PQ;
    // EdgePQ를 저장할 우선순위 큐

    visited[startIdx] = true;
    for (const Edge& edg : adjList[startIdx]) {
        PQ.push(EdgePQ(startIdx, edg.to, edg.length, edg.timestamp, edg.heightDiff));
    };
    // 시작 도시의 인접한 모든 간선을 우선순위 큐에 추가

    int edgesNeeded = V - 1;
    while (edgesNeeded > 0 && !PQ.empty()) {
        EdgePQ topEdge = PQ.top();
        PQ.pop();
        int u = topEdge.U;
        int v = topEdge.V;

        if (visited[v]) continue;
        // 이미 방문한 도시라면 건너뜀
        visited[v] = true;
        edgesNeeded--;
        // 새로운 도시 v를 MST에 추가

        string cityA_output, cityB_output;
        tie(cityA_output, cityB_output) = getCityLexPair(u, v);
        cout << cityA_output << " " << cityB_output << "\n";
        // 도시 이름 출력

        ResultEdge res;
        res.timestamp_rs = topEdge.timeStamp;
        res.cityA_rs = cityA_output;
        res.cityB_rs = cityB_output;
        res.length_rs = topEdge.Length;
        resultEdges.push_back(res);
        // 결과 간선 정보 저장

        totalLength += topEdge.Length;
        // 총 길이 업데이트

        for (const Edge& edg2 : adjList[v]) {
            int next = edg2.to;
            if (!visited[next]) {
                PQ.push(EdgePQ(v, next, edg2.length, edg2.timestamp, edg2.heightDiff));
            }
        }
        // 도시와 연결된 모든 간선을 우선순위 큐에 추가
    };
    // edgesNeeded = 0이 되거나, 우선순위 큐가 빌때까지 반복

    cout << totalLength << "\n";
    // 총 길이 출력

    sort(resultEdges.begin(), resultEdges.end(), [](const ResultEdge& a, const ResultEdge& b) {
        if (a.cityA_rs != b.cityA_rs)
            return a.cityA_rs < b.cityA_rs;
        // cityA가 다르면 cityA 오름차순
        else
            return a.cityB_rs < b.cityB_rs;
    }); // cityA가 같으면 cityB 오름차순
	// 간선들을 cityA 오름차순, cityB 오름차순으로 정렬

    for (const ResultEdge& results : resultEdges) {
        int ts = results.timestamp_rs;
        int year = ts / 100;
        int month = ts % 100;
        ostringstream oss{};
        oss << std::setw(4) << std::setfill('0') << year << "-"
            << std::setw(2) << std::setfill('0') << month;

        cout << oss.str()
            << " " << results.cityA_rs
            << " " << results.cityB_rs
            << " " << results.length_rs
            << "\n";
    };
    // 결과  출력: YYYY-MM cityA cityB length
};
// PrimMST: Prim의 알고리즘을 사용하여 MST 계산 및 출력

int main() {
    cin >> V;
    IdxtoCity.resize(V);
    cityHeight.resize(V);
    // 도시 개수 V 입력

    for (int i = 0; i < V; i++) {
        string cityName;
        int height;
        cin >> cityName >> height;
        cityIdx[cityName] = i;  // 도시 이름과 인덱스 매핑
        IdxtoCity[i] = cityName; // 인덱스 i에 해당하는 도시 이름 저장
        cityHeight[i] = height;  // 도시 고도 저장
    };
    // 도시별 정보 입력

    cin >> E;
    adjList.resize(V);
    // 도로 개수 E 입력

    for (int i = 0; i < E; i++) {
        string cityA, cityB, inputStr;
        int length_main = 0;
        cin >> cityA >> cityB >> length_main >> inputStr;

        int u_main = cityIdx[cityA];
        int v_main = cityIdx[cityB];
        int timestamp_main = parseTimestamp(inputStr);
        int heightDiff_main = abs(cityHeight[u_main] - cityHeight[v_main]);
        // 도시 이름을 인덱스로 변환, 도로 개통 시기와 고도차 계산

        adjList[u_main].push_back(Edge{ v_main, length_main, timestamp_main, heightDiff_main });
        adjList[v_main].push_back(Edge{ u_main, length_main, timestamp_main, heightDiff_main });
    };
    // 도로 정보 입력  

    string startCity;
    cin >> startCity;
    int startIdx = cityIdx[startCity];
    // 시작 도시 입력

    PrimMST(startIdx);
    // Prim의 알고리즘 수행

    return 0;
};