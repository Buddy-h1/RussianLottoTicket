#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <locale>
#include <iomanip> 

using namespace std;

class Russian_lotto_ticket {
public:
	Russian_lotto_ticket() {
		ticket_2m.resize(3);
		for (int i = 0; i < 3; i++) {
			ticket_2m[i].resize(9);
		}
		Ticket_generation()
		ticket_id = Random(1, 100000);
		price = Random(80, 120);
	}

	void Ticket_generation() {
		for (int number_line = 0; number_line < 3; number_line++) {
			for (int number_column = 0; number_column < 9; number_column++) {
				int flag = false;
				while (flag == false) {
					int random_value = Random(10 * number_column + 1, 10 * (number_column + 1));
					if (isNumber_in_column(number_column, random_value) == false) {
						ticket_2m[number_line][number_column] = random_value;
						ticket_1m.push_back(random_value);
						flag = true;
					}
				}
			}
		}
		for (int number_line = 0; number_line < 3; number_line++) {
			for (int number_of_passes = 0; number_of_passes < 4; number_of_passes++) {
				int pass_number = Random(0, 8);
				ticket_2m[number_line][pass_number] = 0;
				ticket_1m[number_line * 9 + pass_number] = 0;
			}
		}
	}

	bool isNumber(int value) {
		if (value == 0) return false;
		return (find(ticket_1m.begin(),
			ticket_1m.end(), value) ==
			ticket_1m.end()) ? false : true;
	}

	bool isWin(vector<int>& values) {
		for (int line = 0; line < 3; line++) {
			int similarities = 0;
			for (int counter_values = 0; counter_values < 5; counter_values++) {
				for (int counter_check = 0; counter_check < 5; counter_check++) {
					if (find(ticket_2m[line].begin(), ticket_2m[line].end(), values[counter_values]) != ticket_2m[line].end()) {
						similarities++;
						break;
					}
				}
			}
			if (similarities == 5) return true;
			else similarities = 0;
		}
		return false;
	}

	void Print() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j++) {
				cout << setw(3) << ticket_2m[i][j] << " ";
			}
			cout << endl;
		}
	}

	int Getid() {
		return ticket_id;
	}

	int Getprice() {
		return price;
	}

private:
	int ticket_id;
	int price;
	vector<vector<int>> ticket_2m;
	vector<int> ticket_1m;

	int Random(int min, int max) {
		return min + rand() % (max - min);
	}

	bool isNumber_in_column(int number_column, int value) {
		for (int i = 0; i < 3; i++) {
			if (ticket_2m[i][number_column] == value) return true;
			else return false;
		}
	}
};

void PrintMenu() {
	cout << "[1] - Перегенерировать билет" << endl;
	cout << "[2] - Вывести билет" << endl;
	cout << "[3] - Проверить наличие выпавшего числа в билете" << endl;
	cout << "[4] - Проверить выигрыш" << endl;
	cout << "[5] - ID билета" << endl;
	cout << "[6] - Цена билета" << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	Russian_lotto_ticket ticket_1;

	int number_command;
	while (true) {
		PrintMenu();
		cin >> number_command;
		if (number_command == 1) ticket_1.Ticket_generation();
		else if (number_command == 2) ticket_1.Print();
		else if (number_command == 3) {
			int number;
			cin >> number;
			if (ticket_1.isNumber(number)) cout << "Число " << number << " находится в билете" << endl;
			else cout << "Числа " << number << " нет в билете" << endl;
		}
		else if (number_command == 4) {
			vector<int> numbers(5);
			for (int i = 0; i < 5; i++) {
				cin >> numbers[i];
			}
			if (ticket_1.isWin(numbers)) cout << "Ваш билет выиграл" << endl;
			else cout << "Билет не выиграл" << endl;
		}
		else if (number_command == 5) {
			cout << ticket_1.Getid() << endl;
		}
		else if (number_command == 6) {
			cout << ticket_1.Getprice() << endl;
		}
	}
	return 0;
}