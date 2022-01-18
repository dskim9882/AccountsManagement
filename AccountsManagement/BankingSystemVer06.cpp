/*
Banking System Ver 0.6
Author : dskim9882, email - dskim9882@gmail.com
Contents : level 6 of Accounts Management Project
Reference : 열혈 C++ 프로그래밍, 윤성우 저
*/
#pragma warning(disable:4996)
#include <iostream>
#include <cstring>

using namespace std;

class Account {
private :
	char *name;
	int balance;
	int accID;

public :
	Account(int id, int money, char *name)
		: accID(id), balance(money)
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	Account(const Account& copy) // 복사 생성자 - 깊은 복사
		: accID(copy.accID), balance(copy.balance)
	{
		name = new char[strlen(copy.name) + 1];
		strcpy(name, copy.name);
	}
	int getID() const { return accID; };
	int getBalance() const { return balance; }
	virtual void deposit(int money) { balance += money; };
	void withdraw(int money) { balance -= money; };
	void listAccs() const {
		cout << "Account ID : " << accID << endl;
		cout << "Name : " << name << endl;
		cout << "Balance : " << balance << endl << endl;
	};

	~Account() {
		delete []name;
	}
};

class NormalAccount : public Account {
private:
	int interestRate;

public:
	NormalAccount(int id, int money, char *name, int interRate)
		: Account(id, money, name), interestRate(interRate)
	{
	
	}

	NormalAccount(const NormalAccount& normAcc)
		:  Account(normAcc), interestRate(normAcc.interestRate)
	{
	
	}
	
	virtual void deposit(int money) { 
		Account::deposit(money);
		Account::deposit(money * (interestRate / 100.0));
	};

};

class HighCreditAccount : public NormalAccount {
private:
	int creditInterestRate;

public:
	HighCreditAccount(int id, int money, char *name, int interRate, int level)
		: NormalAccount(id, money, name, interRate), creditInterestRate(level)
	{
	
	}

	HighCreditAccount(const HighCreditAccount& highAcc)
		:  NormalAccount(highAcc), creditInterestRate(highAcc.creditInterestRate)
	{
	
	}
	
	virtual void deposit(int money) { 
		NormalAccount::deposit(money);
		Account::deposit(money * (creditInterestRate / 100.0));
	};
};

class AccountHandler {
private:
	Account* accs[100]; // 고객 정보 저장을 위한 배열
	int accNum; // 저장된 고객 정보 개수

public:
	AccountHandler() 
		: accNum(0)
	{
	
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
		int choice;
		int id;
		char name[20];
		int money;
		int interestRate;
		int creditLevel;

		cout << "[Create Account]" << endl;

		if (accNum >= 100) {
			cout << "[ERROR] Account array is full" << endl;
			return;
		}

		cout << "1. Normal Account 2. High Credit Account" << endl;
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Account ID : " << endl;
			cin >> id;

			cout << "Name : " << endl;
			cin >> name;

			cout << "Balance : " << endl;
			cin >> money;

			cout << "Interest Rate : " << endl;
			cin >> interestRate;

			cout << endl;

			accs[accNum++] = new NormalAccount(id, money, name, interestRate);

			break;
		case 2:
			cout << "Account ID : " << endl;
			cin >> id;

			cout << "Name : " << endl;
			cin >> name;

			cout << "Balance : " << endl;
			cin >> money;

			cout << "Interest Rate : " << endl;
			cin >> interestRate;

			cout << "Credit Level : " << endl;
			cin >> creditLevel;

			cout << endl;
			switch (creditLevel) {
			case 1:
				accs[accNum++] = new HighCreditAccount(id, money, name, interestRate, 7);
				break;
			case 2:
				accs[accNum++] = new HighCreditAccount(id, money, name, interestRate, 4);
				break;
			case 3:
				accs[accNum++] = new HighCreditAccount(id, money, name, interestRate, 2);
				break;
			default:
				cout << "[ERROR] incorrect number" << endl;
				break;
			}
			break;
		default :
			cout << "[ERROR] incorrect number" << endl;
			break;
		}

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
				cout << "Withdrawal amount : " << endl;
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

	~AccountHandler() {
		for (int i = 0; i < accNum; i++) {
			delete accs[i];
		} 
	}
};

int main() {
	AccountHandler manager;
	int menuNum;

	while (1) {
		manager.ShowMenu();
		cout << "Choice > ";
		cin >> menuNum;
		cout << endl;

		switch (menuNum) {
		case 1 :
			manager.CreateAcc();
			break;
		case 2 :
			manager.Deposit();
			break;
		case 3 :
			manager.Withdraw();
			break;
		case 4 :
			manager.ListAccs();
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
