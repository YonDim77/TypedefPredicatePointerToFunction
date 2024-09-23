#include <iostream>

void removeEven(int *numbers, int &count) {
	int removed = 0;
	for (int c = 0; c < count; c++) {
		numbers[c - removed] = numbers[c];
		if (numbers[c] % 2 == 0) {
			removed++;
		}
	}
	for (int i = count - removed; i < count; i++)
		numbers[i] = 0;
	count -= removed;
}

void removeDiv(int *numbers, int &count, int divisor) {
	int removed = 0;
	for (int c = 0; c < count; c++) {
		numbers[c - removed] = numbers[c];
		if (numbers[c] % divisor == 0) {
			removed++;
		}
	}
	for (int i = count - removed; i < count; i++)
		numbers[i] = 0;
	count -= removed;
}

void removeDiv2(int *numbers, int &count, int div1, int div2) {
	int removed = 0;
	for (int c = 0; c < count; c++) {
		numbers[c - removed] = numbers[c];
		if (numbers[c] % div1 == 0 && numbers[c] % div2 == 0) {
			removed++;
		}
	}
	for (int i = count - removed; i < count; i++)
		numbers[i] = 0;
	count -= removed;
}

void removeDiv3(int *numbers, int &count, int div1, int div2, int div3) {
	int removed = 0;
	for (int c = 0; c < count; c++) {
		numbers[c - removed] = numbers[c];
		if (numbers[c] % div1 == 0 && numbers[c] % div2 == 0 || numbers[c] % div3 == 0) {
			removed++;
		}
	}
	for (int i = count - removed; i < count; i++)
		numbers[i] = 0;
	count -= removed;
}

enum OperationType {
	RemoveOne, RemoveTwo, RemoveTwoOrOne
};

int div1 = 2;
int div2 = 1;
int div3 = 1;

bool canRemoveOne(int value) {
	return value % div1 != 0;
}
bool canRemoveTwo(int value) {
	return value % div1 == 0 && value % div2 == 0;
}
bool canRemoveTwoOrOne(int value) {
	return value % div1 == 0 && value % div2 == 0 || value % div3 == 0;
}
bool isSecondDigitOdd(int value) {
	return ((value / 10) % 10) % 2 == 0;
}



bool checkPredicate(OperationType op, int value) {
	switch (op) {
	case RemoveOne:
		return canRemoveOne(value);
	case RemoveTwo:
		return canRemoveTwo(value);
	case RemoveTwoOrOne:
		return canRemoveTwoOrOne(value);
	}
}

typedef int my_int;
typedef bool(*UnaryPredicate)(int);

void removeGeneric(int *numbers, int &count, OperationType op) {
	int removed = 0;
	for (int c = 0; c < count; c++) {
		numbers[c - removed] = numbers[c];
		if (checkPredicate(op, numbers[c])) {
			++removed;
		}
	}
	count -= removed;
}

void printGeneric(int *numbers, int &count, OperationType op) {
	for (int c = 0; c < count; c++) {
		if (checkPredicate(op, numbers[c])) {
			std::cout << numbers[c] << ' ';
		}
	}
}

void filter(int *numbers, int &count, UnaryPredicate predicate) {
	int removed = 0;
	for (int c = 0; c < count; c++) {
		numbers[c - removed] = numbers[c];
		if (predicate(numbers[c])) {
			++removed;
		}
	}
	count -= removed;
}

typedef int(*BinaryFunction)(int, int);

int sum(int a, int b) {
	return a + b;
}

int ordered(int a, int b) {
	return a <= b;
}

int (*pFunc) (int, int) = sum;

void apply(int *numbers, int &count, BinaryFunction callback, int identity = 0) {
	for (int c = 0; c < count - 1; c++) {
		numbers[c] = callback(numbers[c], numbers[c + 1]);
	}
}


#if 0
1 2 3 3 4 5 5 6 7 8 9 10 11 12 5 5 5 f
#endif

int main() {

	int numbers[100] = { 0 };
	int count = 0;

	while (count < 100 && std::cin >> numbers[count]) 
		++count;
	
	printGeneric(numbers, count, RemoveOne);
	std::cout << std::endl;

	apply(numbers, count, pFunc);
	for (int c = 0; c < count; c++) {
		std::cout << numbers[c] << ' ';
	}
	std::cout << std::endl;
	
	removeGeneric(numbers, count, RemoveOne);
	for (int c = 0; c < count; c++) {
		std::cout << numbers[c] << ' ';
	}

	return 0;
}