//tolltax
/*
	1-light vehicles
	2-heavy motor vehicle
	3-2 wheeler
	4-exempted
*/
#include <iostream>
#include <string>
using namespace std;
class Tolltax;
class Vehicle{
	string name;
	double toll;
	int count;
	friend class Tolltax;
	Vehicle(){
		name=" ";
		toll=0.00;
		count=0;
	}
	void setValues(){
		cout<<"Enter the name - ";
		cin>>name;
		cout<<"Enter the toll";
		cin>>toll;
		toll=((float)((int)(toll*100)))/100;
		count=0;
	}
};
class Tolltax{
	double total;//only 2 decimal places
	int number;
	Vehicle* list;
	public:
	Tolltax(int n=4){//default taken 4 types
		total=0.0;
		number=n;
		list=new Vehicle[number];
	}
	int numberOfVehicles(){
		int counts=0;
		for(int i=0;i<number;i++){
			counts+=list[i].count;
		}
		return counts;
	}
	double tollCollected(){
		return total;
	}
	void tollCalc(){
		total=0;
		for(int i=0;i<number;i++){
			total+=(list[i].toll*list[i].count);
		}
	}
	void display(){
		cout<<"List of cars crossing\n";
		for(int i=0;i<number;i++){
			cout<<list[i].name<<"\tcrossed\t"<<list[i].count<<" times\n";
		}
		cout<<"Total is\t"<<numberOfVehicles()<<endl;
		return;
	}
	void setValues(){
		for(int i=0;i<number;i++){
			list[i].Vehicle::setValues();
		}
	}
	void passVehicle(){
		int pos;
		cout<<"Enter the number of vehicle - ";
		cin>>pos;
		if(pos<number){
			list[pos].count++;
			cout<<"Car of type "<<pos<<" has passed\n";
			total+=list[pos].toll;
		}
		else{
			cout<<"Type entered invalid\n";
		}
	}
};

int main(){
	int n;
	cout<<"Enter the number of vehicle types - ";
	cin>>n;
	Tolltax obj(n);
	obj.setValues();
	do{
		cout<<"1.Receive toll\n";
		cout<<"2.Display total cars passed\n";
		cout<<"3.Display amount collected\n";
		cout<<"4.Exit\n";
		cin>>n;
		switch(n){
			case 1:obj.passVehicle();
					break;
			case 2:obj.display();
					break;
			case 3:obj.tollCalc();
					cout<<"The total - "<<obj.tollCollected()<<"\n";
					break;
			default: cout<<"The end";
		}
	}while(n>=1&&n<=3);
	return 0;
}
