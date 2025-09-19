#include <iostream>
#include <string>

struct Entry {
	int Key; // 키 값
	std::string Value; // 밸류 값
	int Status; // 엔트리의 현재 상태, 0이면 비어있고 1이면 값이 존재하고 2이면 '사용가능한' 상태

	Entry() {
		Key = 0;
		Value = "";
		Status = 0;
	} // 기본 생성자
	Entry(int Key, std::string Value) {
		this->Key = Key;
		this->Value = Value;
		this->Status = 1;
	} // 키값과 밸류값을 받아와 저장하는 생성자
	void Erase() {
		this->Status = 2;
	} // 엔트리 삭제 함수, Status를 2로 변경
}; // 엔트리 구조체

class HashTable_L {
public :
	HashTable_L(int Cap) {
		this->Capacity = Cap;
		this->Table = new Entry[Capacity];
	} // 해시 테이블 생성자
	void Put(int Key, std::string Value) {
		int Index = HashFunction(Key); // 해시값
		int Probe = 1; // 조사 횟수

		while (Table[Index].Status == 1 && Probe <= Capacity) {
			Index = HashFunction(Index + 1);
			Probe++;
		} // 사용가능하거나 비어있는 셀을 찾을 때까지 탐색

		if (Probe > Capacity) return; // Probe가 Capacity를 벗어나면 함수 종료
		else {
			Table[Index] = Entry(Key, Value);
			return;
		} // 아니라면 해당 인덱스에 엔트리를 저장
	} // 값 삽입 함수
	void Erase(int Key) {
		int Index = HashFunction(Key); // 해시값
		int Probe = 1; // 조사횟수

		while (Table[Index].Status == 0 && Probe <= Capacity) {
			if (Table[Index].Status == 1 && Table[Index].Key == Key) {
				Table[Index].Erase();
				return;
			}
			Index = HashFunction(Index + 1);
			Probe++;
		} // 빈 셀을 찾을때까지 탐색하다가 찾는 값이 존재하는 엔트리를 발견하면 해당 엔트리를 삭제하고 함수 종료
		return; // 또는 찾는 값을 발견하지 못하면 함수 종료
	} // 값 삭제 함수
	std::string Find(int Key) {
		int Index = HashFunction(Key); // 해시값
		int Probe = 1; // 조사횟수

		while (Table[Index].Status == 0 && Probe <= Capacity) {
			if (Table[Index].Status == 1 && Table[Index].Key == Key) {
				return Table[Index].Value;
			}
			Index = HashFunction(Index + 1);
			Probe++;
		} // 빈 셀을 찾을때까지 탐색하다가 찾는 값이 존재하는 엔트리를 발견하면 밸류값을 반환하고 함수 종료
		return "Not Found"; // 또는 찾는 값을 발견하지 못하면 "Not Found" 메세지를 반환하고 함수 종료
	} // 값 검색 함수
private :
	Entry* Table; // 해시 테이블
	int Capacity; // 해시 테이블의 크기
	int HashFunction(int Key) {
		return Key % Capacity;
	}; // 해시함수, 모듈러 연산으로 해시값을 계산
}; // 선형계획법을 사용한 해시테이블 클래스

int main() {
	int Counter;
	std::cin >> Counter;
	HashTable_L HL1(7);

	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "Put") {
			int InputKey;
			std::string InputValue;
			std::cin >> InputKey >> InputValue;
			HL1.Put(InputKey, InputValue);
		}
		else if (Command == "Erase") {
			int InputKey;
			std::cin >> InputKey;
			HL1.Erase(InputKey);
		}
		else if (Command == "Find") {
			int InputKey;
			std::cin >> InputKey;
			HL1.Find(InputKey);
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	}
} // 메인 함수, 명령어와 필요한 매개변수를 받아 해시테이블의 기능을 실행할 수 있음