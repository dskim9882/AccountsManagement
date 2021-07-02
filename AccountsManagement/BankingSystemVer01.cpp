/*
Banking System Ver 0.1
Author : dskim9882, email - dskim9882@gmail.com
Contents : level 1 of Accounts Management Project
Reference : 열혈 C++ 프로그래밍, 윤성우 저
*/
#include <iostream>
#include <cstring>

using namespace std;

void ShowMenu();
void CreateAcc();
void Deposit();
void Withdraw();
void ListAccs();

int main() {
	int menuNum;

	while (1) {
		ShowMenu();
		cout << "Choice > ";
		cin >> menuNum;

		switch (menuNum) {
		case 1 :
			CreateAcc();
			break;
		case 2 :
			Deposit();
			break;
		case 3 :
			Withdraw();
			break;
		case 4 :
			ListAccs();
			break;
		case 5 :
			cout << "[exiting...]" << endl;
			return 0;
		default :
			cout << "[ERROR] incorrect number" << endl;
			break;
		}
	}
	
	return 0;
}

void ShowMenu() {
	cout << "-----MENU-----" << endl;
	cout << "1. Create Account" << endl;
	cout << "2. Deposit Money" << endl;
	cout << "3. Withdraw Money" << endl;
	cout << "4. List Accounts" << endl;
	cout << "5. Exit" << endl;
}

void CreateAcc() {

}

void Deposit() {}

void Withdraw() {}

void ListAccs() {}