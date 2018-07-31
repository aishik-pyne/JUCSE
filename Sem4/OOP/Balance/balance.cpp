
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
//BASE CLASSES
class Bank;
class Balance
{	
	friend class Transaction;
	private:
		int acc_no;
		string last_update;
		float balance;

	public:
		Balance(int a,string d,float b){
			acc_no=a;
			last_update=d;
			balance=b;
		}
		int get_acc_no(){
			return acc_no;
		}
		display_balance(){
			cout<<"Account number :"<<acc_no<<endl;
			cout<<"Last Date of Transaction :"<<last_update<<endl;
			cout<<"Balance :"<<balance<<endl;
		}
};
class Transaction:public Bank
{
	private:
		int acc_no;
		string date;
		float amount;
		string type;
	public:
		Transaction(int a,string d,float amt,string t){
			acc_no=a;
			date=d;
			amount=amt;
			type=t;
		}
		void transact(){
			Balance* bal=Bank::search_balance(acc_no);
			if(bal==NULL){
				cout<<"Wrong Account Number"<<endl;
			} else if(bal->balance < amount && type=="withdrawal"){
				cout<<"Balance insuficient"<<endl;
			} else {
				bal->last_update=date;
				if(type=="withdrawal")
					bal->balance=bal->balance - amount;
				else
					bal->balance=bal->balance + amount;

			}
			write_transaction();
		}
		void write_transaction(){
			fstream wt;
			wt.open("Transaction_list.txt",ios::app);
			wt<<acc_no<<" "<<date<<" "<<amount<<" "<<type<<" "<<endl;
			wt.close();
		}

};
class Bank
{
	friend class Transaction;
	vector<Balance> balance_list;
	public:
		Bank(){
		}
		Balance* search_balance(int acc_no){
			for(vector<Balance>::iterator i=balance_list.begin();i!=balance_list.end();++i){
				if(i->get_acc_no()==acc_no){
					return i;
				}
			}
			return NULL;
		}
		void load_balances(){
			fstream fload_balances;
			fload_balances.open("Balance_sheet.txt",ios::in);
			while(!fload_balances.eof()){
				int acc_no;
				string date;
				float balance;
				string type;
				fload_balances>>acc_no;
				fload_balances>>date;
				fload_balances>>balance;
				Balance new_record(acc_no,date,balance);
				balance_list.push_back(new_record);
			}
			fload_balances.close();
		}
		void add_balance(){
			int acc_no;
			do{
				cout<<"Enter Account Number(6 digit) :";cin>>acc_no;
				if(acc_no>=100000 && acc_no <= 999999 && search_balance(acc_no)!=NULL){
					break;
				}
				cout<<"Sorry wrong format or dublicate number!"<<endl;	
			}while(true);
			cout<<"Enter Date in DD/MM/YYYY :";string date;cin>>date;
			cout<<"Enter Balance:";float balance;cin>>balance;
			Balance new_record(acc_no,date,balance);
			balance_list.push_back(new_record);
		}
		void display_status(){
			Balance* bal=search_balance(acc_no);
			if(bal==NULL){
				cout<<:"wrong Account Number"<<endl;
			} else {
				bal->display_balance();
			}
		}

		void display_all(){
			for(vector<Balance>::iterator i=balance_list.begin();i!=balance_list.end();++i){
				i->display_balance();
			}
		}
};


//MAIN FUNCTION
int main(){
	Bank HDFC;flag=true;
	while(flag){
		int choice;clrscr();
		cout<<"1.Create Account"<<endl;
		cout<<"2.Transaction"<<endl;
		cout<<"3.Status"<<endl;
		cout<<"4.Display All"<<endl;
		cout<<"5.Exit"<<endl;
		cout<<"Enter Choice:";cin>>choice;
		switch(choice){
			case 1:{
				HDFC.add_balance();
				
				break;
			}
			case 2:{
				HDFC.transaction();
				break;
			}
			case 3:{
				HDFC.display_status();
				break;
			}
			case 4:{
				HDFC.display_all();
			}
			case 5:{
				flag=false;
				break;
			}
			default:{
				exit(1);
			}
		}
	}
}
