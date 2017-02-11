#include <iostream> 
using namespace std;
class Tolltax{
		int carCount;
		int collection;
	public:
		TollTax(){
			carCount=0;
			collection=0;
		}
		void displayCollection(){
			cout<<collection<<endl;
		}
		void displaycarCount(){
			cout<<carCount<<endl;
		}
		void receiveToll(){
			int amt;
			cout<<"Enter Amount";
			cin>>amt;
			collection+=amt;
			carCount++;			
		}
		
};
int main(){
	Tolltax T=new Tolltax();
	
	while(1){
		cout<<"1.Display Collection"<<endl;
		cout<<"2.Display CarCount"<<endl;
		cout<<"3.Receive Toll"<<endl;
		cout<<"4.Exit"<<endl;
		int choice;
		cin>>choice;
		switch(choice){
			case 1:T.displayCollection();
					break;
			case 2:T.displaycarCount();
					break;
			case 3:T.receiveToll();
					break;
			case 4:exit(0);
			default:cout<<"Wrong Choice";
		}
	}
	return 0;
}
