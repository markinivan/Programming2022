#include <math.h>
#include <locale>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>

class Decimal {
protected:
	std::string number;
public:
	Decimal(std::string input = "1.0") {
	//int size = input.size();
		number = input;
	}
	Decimal(const Decimal& num) {
		this->number = num.number;
	}
	~Decimal() {
		delete[] &number;
	}
	void PrintNum() {
		std::cout << number << "\n";
	}
	Decimal& operator=(const Decimal& num) {
		if (this != &num) {
			this->number = num.number;
		}
		return *this;
	}
	friend Decimal operator+(const Decimal& num1,const Decimal& num2) {
		Decimal res(num1);
		for (int i = num1.number.size(); i >= 0; i--) {
			if
		}
	}
};
int main() {
	Decimal a("3.1234567890");
	a.PrintNum();
	system("pause");
	return 0;
}