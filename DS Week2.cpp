#include <iostream>
#include <string>
using namespace std;

class Node {
    int Element; // 노드의 데이터
    Node* Next; // 노드가 가리키는 주소

    friend class LinkedList;
}; // 연결리스트 구현을 위한 노드 구조체

class LinkedList {
public:
    LinkedList() {
        this->Head = new Node;
        this->Tail = new Node;

        this->Head = NULL;
        this->Tail = NULL; // Head와 Tail 노드를 NULL로 초기화
    }; // 생성자
    int ListSize() {
        int Size = 0;
        if (Head == NULL && Tail == NULL) {
            return Size;
        }
        else {
            Node* CurrentNode = Head;
            while (CurrentNode->Next != NULL) {
                Size++;
                CurrentNode = CurrentNode->Next;
            }
            Size++;
            return Size;
        }
    }; // 리스트 크기 반환 함수, 각 노드를 순회하면서 Size 변수에 1씩 더해줌, 비었다면 0을 출력
    void Print() {
        if (Head == NULL && Tail == NULL) {
            cout << "This List is Empty" << endl;
        }
        else {
            Node* CurrentNode = Head;
            while (CurrentNode->Next != NULL) {
                cout << CurrentNode->Element << ' ';
                CurrentNode = CurrentNode->Next;
            }
            cout << CurrentNode->Element << endl;
        }
    }; // 리스트 출력 함수, 각 노드를 순회하면서 데이터를 출력, 비었다면 메세지를 출력
    void Append(int Value) {
        Node* NewNode = new Node;
        NewNode->Element = Value;
        NewNode->Next = NULL;

        if (Head == NULL && Tail == NULL) {
            Head = NewNode;
            Tail = NewNode;
        }
        else {
            Tail->Next = NewNode;
            Tail = NewNode;
        }
        Print();
    }; // 값 추가 함수, 임시노드에 값을 담고 Tail 노드와 연결한 다음 임시노드를 Tail 노드로 설정, 비었다면 임시노드를 Head와 Tail 노드로 설정
    int Delete(int Idx) {
        int RemovedValue = 0; // 삭제되는 노드의 데이터
        int CurrentIdx = 0; // 현재 인덱스
        Node* CurrentNode; // 현재 인덱스에 위치한 노드
        Node* PreviousNode; // 이전 인덱스에 위치한 노드

        if (Head == NULL && Tail == NULL) {
            return -1;
        } // 비었다면 -1을 출력
        else if (Idx >= ListSize()) {
            return -1;
        } // 삭제하는 인덱스가 리스트 크기를 벗어난 경우에도 -1을 출력
        else if (Idx == 0) {
            if (ListSize() == 1) {
                RemovedValue = Head->Element;
                Tail = NULL;
                Head = NULL;
            } // 리스트 크기가 1이면 Head와 Tail을 모두 NULL로 초기화 함
            else {
                CurrentNode = Head;
                RemovedValue = CurrentNode->Element;
                Head = CurrentNode->Next;
            } // 크기가 2 이상이면 Head 노드의 다음 노드를 Head로 설정
        } // 리스트 첫 노드에 값을 추가
        else {
            PreviousNode = CurrentNode = Head;
            while (CurrentIdx != Idx) {
                PreviousNode = CurrentNode;
                CurrentNode = CurrentNode->Next;
                CurrentIdx++;
            }
            RemovedValue = CurrentNode->Element;
            PreviousNode->Next = CurrentNode->Next;

            if (CurrentNode == Tail) {
                Tail = PreviousNode;
            } // Head에서 시작해 리스트를 순회하다가 삭제하는 인덱스를 만나면 그 다음 노드와 이전노드를 연결
            // 만약 마지막 값을 삭제하면 Tail을 이전 노드에 설정해줌
        } // 리스트 중간 또는 마지막에 값을 추가
        return RemovedValue;
    }; // 값 삭제 함수
    void Insert(int Idx, int Value) {
        Node* NewNode = new Node;
        NewNode->Element = Value; // 임시노드에 추가하는 값을 담음

        int CurrentIdx = 0;
        Node* CurrentNode;
        Node* PreviousNode; // 현재 인덱스, 현재 인덱스에 해당 하는 노드, 이전 인덱스에 해당하는 노드

        if (Idx > ListSize()) {
            cout << "Index Error" << endl;
            return;
        } // 삽입하는 인덱스가 리스트 크기를 벗어난 경우 메세지 출력
        else if (Idx == 0) {
            if (Head == NULL && Tail == NULL) {
                Head = NewNode;
                Tail = NewNode;
            } // 비었다면 Head와 Tail을 임시노드롤 설정해줌
            else {
                NewNode->Next = Head;
                Head = NewNode;
            } // 아니라면 임시노드와 Head를 연결하고 임시노드를 Head로 설정해줌
        } // 리스트 첫 노드에 값을 삽입
        else if (Idx == ListSize()) {
            Append(Value);
        } // 리스트 마지막 노드 다음에 삽입 하는 경우는 추가와 동일함
        else {
            PreviousNode = CurrentNode = Head;
            while (CurrentIdx != Idx) {
                PreviousNode = CurrentNode;
                CurrentNode = CurrentNode->Next;
                CurrentIdx++;
            }
            PreviousNode->Next = NewNode;
            NewNode->Next = CurrentNode; // Head에서 시작해 리스트를 순회하다가 삽입하는 인덱스를 만나면 그 다음 노드와 이전노드를 연결
        } // 리스트 중간 또는 마지막에 값을 추가
        Print();
    }; // 값 삽입 함수
    void Sum() {
        int SumOfThisList = 0; // 합계 값을 담는 변수
        if (Head == NULL && Tail == NULL) {
            cout << SumOfThisList << endl;
        }
        else {
            Node* CurrentNode = Head;
            for (int i = 0; i < this->ListSize(); i++) {
                SumOfThisList += CurrentNode->Element;
                if (CurrentNode->Next != NULL) {
                    CurrentNode = CurrentNode->Next;
                }
            }
            cout << SumOfThisList << endl;
        }
    }; // 값 합계 출력 함수, Head에서 시작해 리스트를 순회하면서 SumOfThisList에 값을 더해 나감, 순회가 끝나면 합계값을 출력, 비었다면 0을 출력
private:
    Node* Head; // 시작 노드
    Node* Tail; // 마지막 노드
};

int main()
{
    int Counter = 0;
    cin >> Counter;

    LinkedList L1;

    for (int i = 0; i < Counter; i++) {
        string Menu;
        cin >> Menu;
        if (Menu == "Append") {
            int Param1 = 0;
            cin >> Param1;
            L1.Append(Param1);
        }
        else if (Menu == "Delete") {
            int Param1 = 0;
            cin >> Param1;
            L1.Delete(Param1);
        }
        else if (Menu == "Print") {
            L1.Print();
        }
        else if (Menu == "Sum") {
            L1.Sum();
        }
        else if (Menu == "Insert") {
            int Param1 = 0;
            int Param2 = 0;
            cin >> Param1 >> Param2;
            L1.Insert(Param1, Param2);
        }
        else {
            cout << "Invalid Command";
        }
    } // 필요한 명령어와 파라미터를 입력받아 기능을 실행
}