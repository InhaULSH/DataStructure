#include <iostream>
#include <iomanip>
#include <string>

class Array {
private:
	int SizeOfArr; // 배열의 크기
	int* Arr; // 정수 배열
public:
	Array(int Size) {
		SizeOfArr = Size;
		Arr = new int[SizeOfArr]; // 입력받은 크기만큼의 배열을 선언
		for (int i = 0; i < SizeOfArr; i++) {
			Arr[i] = 0;
		} // 배열 값을 초기화
	} // 생성자
	int At(int Idx) {
		return Arr[Idx];
	} // 해당 인덱스의 값을 출력하는 함수
	void Add(int Idx, int Val) {
		for (int i = SizeOfArr - 2; i >= Idx; i--) {
			Arr[i + 1] = Arr[i];
		} // 입력받은 인덱스부터 오른쪽으로 값을 Shift
		Arr[Idx] = Val; // 값을 추가
	} // 값 추가 함수
	void Remove(int Idx) {
		for (int i = Idx; i < SizeOfArr - 1; i++) {
			Arr[i] = Arr[i + 1];
		} // 입력받은 인덱스부터 왼쪽으로 값을 Shift
		Arr[SizeOfArr - 1] = 0; // 마지막 칸은 0으로 초기화
	} // 값 삭제 함수
	void Set(int Idx, int Val) {
		Arr[Idx] = Val;
	} // 해당 인덱스의 값을 재설정하는 함수
	void Print() {
		for (int i = 0; i < SizeOfArr; i++) {
			std::cout << Arr[i] << ' ';
		} // 배열을 순회하면서 값을 차례로 출력
		std::cout << std::endl;
	} // 값 출력 함수
};

int main() {
	Array IntAr(6);

	int Counter = 0;
	std::cin >> Counter;
	std::string Command;

	for (int i = 0; i < Counter; i++) {
		std::cin >> Command;

		if (Command == "At") {
			int Index;
			std::cin >> Index;
			std::cout << IntAr.At(Index);
		}
		else if (Command == "Add") {
			int Index;
			int Value;
			std::cin >> Index >> Value;
			IntAr.Add(Index, Value);
		}
		else if (Command == "Remove") {
			int Index;
			std::cin >> Index;
			IntAr.Remove(Index);
		}
		else if (Command == "Set") {
			int Index;
			int Value;
			std::cin >> Index >> Value;
			IntAr.Set(Index, Value);
		}
		else if (Command == "Print") {
			IntAr.Print();
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	} // 필요한 명령어와 파라미터를 입력받아 기능을 실행
}