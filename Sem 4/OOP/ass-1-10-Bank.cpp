#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#define MAX 10
using namespace std;
class Date{
	public:
		int dd,mm,yy;
		Date(){
			dd=0;mm=0;yy=0;
		}
		void getDate(){
			bool flag=true;
			cout<<"Enter the date - ";
			while(flag){
				cin>>dd>>mm>>yy;
				if((dd>31)||(mm<=0||mm>12)||(yy<0)){
					cout<<"Wrong date\n";
					cout<<"Re-enter\n";
				}
				if(yy<1000){
					cout<<"Wrong date\n";
					cout<<"Re-enter\n";
				}
				else if(mm==2 && (( (dd>28) && (yy%4==0) ) || (dd>27 && (yy%4!=0) ) )){
					cout<<"Wrong date\n";
					cout<<"Re-enter\n";
				}
				else{
					flag=false;
				}
			}
			displayDate();
		}
		void displayDate(){
			cout<<"The date - "<<dd<<"."<<mm<<"."<<yy<<"\n";
		}
};
/*
types -
1. Withdrawl - 0
2. Deposit - 1
*/

class Transaction{
	Date date;
	long account_no;
	double amount;
	int type;
	bool executed;
	friend class Balance;
	public:
		Transaction(){
			account_no=0;
			amount=0;
			type=-1;
			executed=false;
		}
		void view(){
			cout<<"Account number  - "<<account_no<<"\n";
			cout<<"Amount - "<<amount<<"\n";
			//cout<<"Type - "<<type<<"\n";
			if(type==0) cout<<"Withdrawl\n";
			else cout<<"Deposit\n";
			if(executed) cout<<"Successfully executed\n";
			else cout<<"Not executed\n";
		}
		void setTransaction(long acc,int ch){
			cout<<"Enter the details - ";
			account_no=acc;
			cout<<"Enter the amount - ";
			cin>>amount;
			type=ch;
			date.getDate();
		}
};
class Balance{
	Transaction list[MAX];//maximum 10 transaction per balance
	long account_no;
	Date date;
	double balance;
	long count;
	public:
		Balance(){
			account_no=0;
			count=-1;
			balance=0;
		}
		bool update(int pos){
			bool flag=false;
			date=list[pos].date;//system provided
			switch(list[pos].type){
				case 0: if(balance>=list[pos].amount){
							balance=balance-list[pos].amount;
							cout<<"New balance - "<<balance<<"\n";
							list[pos].executed=true;
						}
						else{
							cout<<"Not sufficient balance for transaction\n";
							flag=false;
						}
						break;
				case 1: balance=balance+list[pos].amount;
						cout<<"New balace - "<<balance<<"\n";
						list[pos].executed=true;
						break;
				default:cout<<"Type not defined\n";
						flag=false;
			}
			return flag;
		}
		void display(){
			cout<<"Details - \n";
			cout<<"Account number - "<<account_no<<"\n";
			date.displayDate();
			cout<<"Balance - "<<balance<<endl;
		}
		void displayTransactions(){
			for(int i=0;i<=count;i++){
				cout<<"Transaction number - "<<(i+1)<<endl;
				list[i].view();
			}
		}
		bool isSame(Transaction t){//here the updation of balance function is called as well as t is added
			if(t.account_no!=account_no){
				return false;
			}
			else{
				list[++count]=t;//transaction entered
				update(count);
				return true;
			}
		}
		void setAccount_no(long acc){
			account_no=acc;
			cout<<"Enter the balance - ";
			cin>>balance;
			date.getDate();
		}
		bool checkAccount(long acc){
			return (acc==account_no);
		}
};
int main(){
	Balance array[MAX];
	int ch,i,count=-1;long acc;
	Transaction temp;
	srand(time(NULL));
	do{
		cout<<"1. Add account to list\n";
		cout<<"2. Withdrawl from account\n";
		cout<<"3. Deposit to account\n";
		cout<<"4. Display details of account\n";
		cout<<"5. Exit\n";
		cin>>ch;
		if(ch<5 && ch>=2 ){
			cout<<"Enter the account number - ";
			cin>>acc;
		}
		if(ch==1){
			//acc=count+2;
			acc=rand()%1000;
		}
		for(i=0;i<=count;i++){
			if(array[i].checkAccount(acc)) break;
		}
		switch(ch){
			case 1: {
				if(i>count){
					cout<<"Account number - "<<acc<<endl;
					array[++count].setAccount_no(acc);
				}
				else{
					cout<<"Already exists try again\n";
				}
				break;
			}
			case 2:
			case 3: {
				if(i<=count){
					temp.setTransaction(acc,ch-2);
					if(array[i].isSame(temp)){
						cout<<"Successful transaction\n";
					}
					else{
						cout<<"Unsuccessful transaction\n";
					}
				}
				else{
					cout<<"Wrong account number\n";
				}
				break;
			}
			case 4: {
				array[i].display();
				array[i].displayTransactions();
				break;
			}
			case 5:{
				cout<<"Ending\n";
				break;
			}
			default: cout<<"Wrong choice\n";
		}
	}while(ch!=5);
	cout<<"The End\n";
	return 0;
}
