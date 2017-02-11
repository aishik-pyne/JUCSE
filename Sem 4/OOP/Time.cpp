#include <iostream> 
using namespace std;
class Time{
	int hh;
	int mm;
	int sec;
	public:
	Time(int h=0,int m=0,int s=0){
		hh=h;
		mm=m;
		sec=s;
	}
	void display12hr(){
		int h;
		if(hh=12)
			h=12;
		else
		{
			h=hh%12;
		}
		cout<<h<<":"<<mm<<":"<<sec;
		if(this->hh <12)
			cout<<"AM";
		else
			cout<<"PM";
		cout<<"\n";
	}	
	void display24hr(){
		cout<<(this->hh)<<":" << this->mm <<":"<<this->sec;
	}
	void input24hr(){
		cout<<"Enter Hours :";
		while(1){
			cin>>hh;
			if(hh>=0 && hh<=24)
				break;
			cout<<"Enter again";
		}
		cout<<"Enter Mins :";
		while(1){
			cin>>mm;
			if(mm>=0 && mm<60)
				break;
			cout<<"Enter again";
		}
		cout<<"Enter Secs :";
		while(1){
			cin>>sec;
			if(sec>=0 && sec<60)
				break;
			cout<<"Enter again";
		}
	}
	void input12hr(){
		int x;int h;
		cout<<"Enter Hours :";
		while(1){
			cin>>h;
			if(h>=0 && h<=12)
				break;
			cout<<"Enter again";
		}
		cout<<"Enter Mins :";
		while(1){
			cin>>mm;
			if(mm>=0 && mm<60)
				break;
			cout<<"Enter again";
		}
		cout<<"Enter Secs :";
		while(1){
			cin>>sec;
			if(sec>=0 && sec<60)
				break;
			cout<<"Enter again";
		}
		cout<<"Enter 1.AM/2.PM :";
		while(1){
			cin>>x;
			if(x>2 || x<1){
				cout<<"Enter again: ";
				continue;
			}
			if(h==0 && x ==2){
				cout<<"Not possible";
				continue;
			}
			if(h==12 && x==1){
				cout<<"Not possible";
				continue;
			}
			if(x==2 && h<12)
				hh=h+12;
			else
				hh=h;
			break;
		}	
	}
	void addmin(){
		int m;
		cout<<"Enter minutes:";
		cin>>m;
		int hour=hh;
		int min=mm;
		min=min+m;
		hour=(hour+(min/60))%24;
		min=min%60;
		hh=hour;
		mm=min;
	}
};
int main(){
	Time t;
	int choice;
	while(1)
	{
		cout<<"\nEnter:\n1. input time in 24 hrs format\n2. input time in 12 hrs format\n3. display in 24 hrs format";
		cout<<"\n4. display in 12 hrs format\n5. add extra minute\n6. exit\n";
		cin>>choice;


		
		switch (choice)
		{
			case 1:
				t.input24hr();
				break;
			case 2:
				t.input12hr();
				break;
			case 3:
				cout<<"time is: ";
				t.display24hr();
				break;
			case 4:
				cout<<"time is: ";
				t.display12hr();
				break;
			case 5:
				t.addmin();
				break;
			case 6:
				exit(0);
				
			default:
				cout<<"Wrong choice";
		}				
	}

    return 0;
}



