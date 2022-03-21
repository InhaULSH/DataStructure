#include <iostream>
#include <string>
using namespace std;

class Node {
    int Element;
    Node* Next;

    friend class LinkedList;
};

class LinkedList {
public:
    LinkedList() {
        this->Head = new Node;
        this->Tail = new Node;

        this->Head = NULL;
        this->Tail = NULL;
    };
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
    };
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
    };
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
    };
    int Delete(int Idx) {
        int RemovedValue = 0;
        int CurrentIdx = 0;
        Node* CurrentNode;
        Node* PreviousNode;

        if (Head == NULL && Tail == NULL) {
            return -1;
        }
        else if (Idx >= ListSize()) {
            return -1;
        }
        else if (Idx == 0) {
            if (ListSize() == 1) {
                RemovedValue = Head->Element;
                Tail = NULL;
                Head = NULL;
            }
            else {
                CurrentNode = Head;
                RemovedValue = CurrentNode->Element;
                Head = CurrentNode->Next;
            }
        }
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
            }
        }
        return RemovedValue;
    };
    void Insert(int Idx, int Value) {
        Node* NewNode = new Node;
        NewNode->Element = Value;

        int CurrentIdx = 0;
        Node* CurrentNode;
        Node* PreviousNode;

        if (Idx > ListSize()) {
            cout << "Index Error" << endl;
            return;
        }
        else if (Idx == 0) {
            if (Head == NULL && Tail == NULL) {
                Head = NewNode;
                Tail = NewNode;
            }
            else {
                NewNode->Next = Head;
                Head = NewNode;
            }
        }
        else if (Idx == ListSize()) {
            Append(Value);
        }
        else {
            PreviousNode = CurrentNode = Head;
            while (CurrentIdx != Idx) {
                PreviousNode = CurrentNode;
                CurrentNode = CurrentNode->Next;
                CurrentIdx++;
            }
            PreviousNode->Next = NewNode;
            NewNode->Next = CurrentNode;
        }
        Print();
    };
    void Sum() {
        int SumOfThisList = 0;
        if (Head == NULL && Tail == NULL) {
            cout << SumOfThisList << endl;
        }
        else {
            Node* CurrentNode = Head;
            while (CurrentNode->Next != NULL) {
                SumOfThisList += CurrentNode->Element;
                CurrentNode = CurrentNode->Next;
            }
            cout << SumOfThisList << endl;
        }
    };
private:
    Node* Head;
    Node* Tail;
};

int main()
{
    int Command = 0;
    int Counter = 0;
    cin >> Command;

    LinkedList L1;
    
    while(Counter != Command) {
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
            L1.Insert(Param1 ,Param2);
        }
        else {
            cout << "Invalid Command";
        }
        Counter++;
    }
}