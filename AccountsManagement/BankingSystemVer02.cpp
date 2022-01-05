/*
Banking System Ver 0.2
Author : dskim9882, email - dskim9882@gmail.com
Contents : level 2 of Accounts Management Project
Reference : 열혈 C++ 프로그래밍, 윤성우 저
*/
#include <iostream>
#include <cstring>

using namespace std;


/*
typedef struct account {
	char name[20];
	int balance;
	int accID;
} ACC;// 고객 정보 struct
*/
void ShowMenu();
void CreateAcc();
void Deposit();
void Withdraw();
void ListAccs();

class Account {
private :
	char *name;
	int balance;
	int accID;

public :
	Account(int accID, int balance, char *name)
		: this->accID(accID), this->balance(balance)
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	int getID() { return accID; };
	int getBalance() { return balance; }
	void deposit(int money) { balance += money; };
	void withdraw(int money) { balance -= money; };
	void listAccs() {
		cout << "Account ID : " << accID << endl;
		cout << "Name : " << name << endl;
		cout << "Balance : " << balance << endl << endl;
	};
};

Account *accs[100]; // 고객 정보 저장을 위한 배열
int accNum; // 저장된 고객 정보 개수

int main() {
	int menuNum;

	while (1) {
		ShowMenu();
		cout << "Choice > ";
		cin >> menuNum;
		cout << endl;

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
	int id;
	char name[20];
	int money;
	
	cout << "[Create Account]" << endl;

	if (accNum >= 100) {
		cout << "[ERROR] Account array is full" << endl;
		return;
	}

	cout << "Account ID : " << endl;
	cin >> id;

	cout << "Name : " << endl;
	cin >> name;

	cout << "Balance : " << endl;
	cin >> money;

	cout << endl;

	accs[accNum] = new Account(id, money, name);
	
	accNum++;
	return;
}

void Deposit() {
	int accID;
	int amount;

	cout << "[Deposit]" << endl;

	cout << "Account ID : " << endl;
	cin >> accID;

	for (int i = 0; i < accNum; i++) {
		if (accID == accs[i]->getID()) {
			cout << "Deposit amount : " << endl;
			cin >> amount;
			accs[i]->deposit(amount);
			cout << "Successful deposit" << endl;
			return;
		}
	}

	cout << "No account information" << endl;
	return;
}

void Withdraw() {
	int accID;
	int amount;

	cout << "[Withdraw]" << endl;

	cout << "Account ID : " << endl;
	cin >> accID;

	for (int i = 0; i < accNum; i++) {
		if (accID == accs[i]->getID()) {
			cout << "Withdrawal amount" << endl;
			cin >> amount;
			if (accs[i]->getBalance() < amount) {
				cout << "Lack of balance" << endl;
				return;
			}
			accs[i]->withdraw(amount);
			cout << "Successful withdraw" << endl;
			return;
		}
	}

	cout << "No account information" << endl;
	return;
}

void ListAccs() {
	for (int i = 0; i < accNum; i++) {
		accs[i]->listAccs();
	}
}