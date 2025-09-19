#include <iostream>
#include <string>

class Vector {
public:
	Vector(int Size) {
		this->Capacity = Size;
		this->SizeOfVector = 0;
		this->Array = new int[Capacity];
	} // 생성자, 최대크기를 파라미터만큼 현재 크기를 0만큼 설정하고 Array 배열을 동적할당
	int Size() {
		return SizeOfVector;
	} // 현재 크기 반환 함수
	bool isEmpty() {
		return (SizeOfVector == 0);
	} // 벡터가 비었는지 반환하는 함수
	int At(int Idx) {
		if (Idx >= SizeOfVector) {
			return -1;
		}
		else {
			return Array[Idx];
		}
	} // 해당 인덱스의 배열의 원소를 출력하는 함수, 인덱스가 크기를 벗어난 경우 -1 반환
	int& operator[](int Idx) {
		return Array[Idx];
	} // At 과는 달리 범위를 벗어나면 오류 발생시킴
	void Erase(int Idx) {
		if (isEmpty()) {
			std::cout << "Empty" << std::endl;
		}
		else {
			for (int i = Idx; i < SizeOfVector; i++) {
				Array[i] = Array[i + 1];
			}
			SizeOfVector--; // 현재 크기 1 감소
		}
	} // 값 삭제 함수, 원하는 인덱스를 기준으로  오른쪽에 위치한 원소들을 왼쪽으로 Shift함, 비었다면 메세지를 출력
	void Insert(int Idx, int Value) {
		if (SizeOfVector == Capacity) {
			Reserve(Capacity * 2);
		} // 최대크기 = 현재크기라면 최대크기를 두배로 늘림

		for (int i = SizeOfVector - 1; i >= Idx; i--) {
			Array[i + 1] = Array[i];
		}
		Array[Idx] = Value;
		SizeOfVector++; // 현재 크기 1 증가
	} // 값 삽입 함수, 원하는 인덱스의 원소 및 그 오른쪽에 위치한 원소들을 오른쪽으로 Shift함, 원하는 인덱스는 원하는 값으로 설정
	void Reserve(int Cap) {
		if (Cap <= this->Capacity) return; // 늘리려는 크기가 기존 최대크기보다 작으면 작동하지 X

		int* NewArray = new int[Cap];
		for (int j = 0; j < this->SizeOfVector; j++) {
			NewArray[j] = Array[j];
		}
		delete[] Array;
		Array = NewArray;
		Capacity = Cap; // 최대크기를 입력받은 크기로 설정
	} // 벡터의 최대크기 증가 함수, 입력받은 크기만큼의 새 배열을 선언해 기존 벡터의 원소들을 새 배열에 복사, 기존벡터는 새 벡터로 대체함
private:
	int* Array; // 벡터를 담을 배열
	int Capacity; // 벡터의 최대 크기
	int SizeOfVector; // 백터의 현재 크기
}; // 배열을 통해 구현한 벡터 클래스

int main() {
	Vector Vector1(5);

	int Counter;
	std::cin >> Counter;

	for (int i = 0; i < Counter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "Size") {
			std::cout << Vector1.Size() << std::endl;
		}
		else if (Command == "isEmpty") {
			std::cout << Vector1.isEmpty() << std::endl;
		}
		else if (Command == "At") {
			int InputIdx;
			std::cin >> InputIdx;
			std::cout << Vector1.At(InputIdx) << std::endl;
		}
		else if (Command == "Erase") {
			int InputIdx;
			std::cin >> InputIdx;
			Vector1.Erase(InputIdx);
		}
		else if (Command == "Insert") {
			int InputIdx;
			int InputValue;
			std::cin >> InputIdx >> InputValue;
			Vector1.Insert(InputIdx, InputValue);
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	} // 필요한 명령어와 파라미터를 입력받아 기능을 실행
}