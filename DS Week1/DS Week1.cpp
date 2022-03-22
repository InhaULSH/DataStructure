#include <iostream>
#include <iomanip>
#include <string>

class Array {
private:
	int SizeOfArr;
	int* Arr;
public:
	Array(int Size) {
		SizeOfArr = Size;
		Arr = new int[SizeOfArr];
		for (int i = 0; i < SizeOfArr; i++) {
			Arr[i] = 0;
		}
	}
	int At(int Idx) {
		return Arr[Idx];
	}
	void Add(int Idx, int Val) {
		for (int i = SizeOfArr - 2; i >= Idx; i--) {
			Arr[i + 1] = Arr[i];
		}
		Arr[Idx] = Val;
	}
	void Remove(int Idx) {
		for (int i = Idx; i < SizeOfArr - 1; i++) {
			Arr[i] = Arr[i + 1];
		}
		Arr[SizeOfArr - 1] = 0;
	}
	void Set(int Idx, int Val) {
		Arr[Idx] = Val;
	}
	void Print() {
		for (int i = 0; i < SizeOfArr; i++) {
			std::cout << Arr[i] << ' ';
		}
		std::cout << std::endl;
	}
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
	}
}