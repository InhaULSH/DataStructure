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
		Arr = new int[SizeOfArr];
		for (int i = 0; i < SizeOfArr; i++) {
			Arr[i] = 0;
		}
	} // 생성자
	void Add(int Idx, int Val) {
		for (int i = SizeOfArr - 2; i >= Idx; i--) {
			Arr[i + 1] = Arr[i];
		}
		Arr[Idx] = Val;
	} // 값 추가 함수
	void Shift(int Dist) {
		int* TempArray = new int[Dist]; // 원소들을 담을 임시 배열
		for (int i = 0; i < Dist; i++) {
			TempArray[i] = Arr[SizeOfArr - Dist + i];
		} // Shift 과정에서 배열의 처음으로 옮길 원소들을 임시배열에 추가
		for (int i = SizeOfArr - Dist - 1; i >= 0; i--) {
			Arr[i + Dist] = Arr[i];
		} // 원소들 전체를 오른쪽으로 거리만큼 옮김
		for (int i = 0; i < Dist; i++) {
			Arr[i] = TempArray[i];
		} // 임시배열의 원소들을 원래 배열의 처음 부분에 덮어쓰기
	} // 배열을 특정 거리만큼 오른쪽으로 Shift하는 함수
	void Reverse(int Idx1, int Idx2) {
		int* TempArray2 = new int[Idx2 - Idx1 + 1]; // 원소들을 담을 임시 배열
		for (int i = 0; i < Idx2 - Idx1 + 1; i++) {
			TempArray2[i] = Arr[Idx2 - i];
		} // 구간의 마지막 인덱스부터 구간의 첫번째 인덱스까지 차례로 임시 배열에 추가
		for (int i = 0; i < Idx2 - Idx1 + 1; i++) {
			Arr[Idx1 + i] = TempArray2[i];
		} // 임시 배열을 원래 배열의 구간에 덮어쓰기
	} // 특정 구간의 원소들을 역순으로 재배열하는 함수
	void Print() {
		for (int i = 0; i < SizeOfArr; i++) {
			std::cout << Arr[i] << ' ';
		}
		std::cout << std::endl;
	} // 값 출력 함수
};

int main() {
	int CommandCounter;
	int ArraySize;
	std::cin >> CommandCounter >> ArraySize;

	Array IntAr2(ArraySize);
	for (int i = 0; i < ArraySize; i++) {
		int InputValue;
		std::cin >> InputValue;
		IntAr2.Add(0, InputValue);
	} // 배열 사이즈 만큼 배열에 원소 입력받음
	IntAr2.Reverse(0, ArraySize - 1); // 배열 전체를 Reverse해서 입력받은 순서대로 원소들이 정렬되게끔 함
	for (int i = 0; i < CommandCounter; i++) {
		std::string Command;
		std::cin >> Command;

		if (Command == "Shift") {
			int Distance;
			std::cin >> Distance;

			IntAr2.Shift(Distance);
		}
		else if (Command == "Reverse") {
			int Index1;
			int Index2;
			std::cin >> Index1 >> Index2;

			IntAr2.Reverse(Index1, Index2);
		}
		else if (Command == "Print") {
			IntAr2.Print();
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	} // 명령어와 필요한 파라미터를 입력받아 기능을 실행함
}