//student
#include <iostream>
#include <string>
#define MAX 15
using namespace std;
class Student{
	static int count;
	int roll,marks[5];
	string name,course,admdate;
	public:
	Student(){
		roll=-1;
		for(int i=0;i<5;i++){
			marks[i]=0;
		}
		name=" ";
		course=" ";
		admdate=" ";
	}
	void recData(){
		cout<<"Enter the name - ";
		cin>>name;
		cout<<"Enter the roll - ";
		cin>>roll;
		cout<<"Enter the course - ";
		cin>>course;
	}
	void recMarks(){
		cout<<"Enter the 5 marks received\n";
		cin>>marks[0];
		cin>>marks[1];
		cin>>marks[2];
		cin>>marks[3];
		cin>>marks[4];
	}
	void marksheet(){
		cout<<"The mark sheet - \n";
		cout<<"Name - "<<name<<"\n";
		cout<<"Roll number - "<<roll<<"\n";
		cout<<"Marks are - \n";
		cout<<marks[0]<<endl;
		cout<<marks[1]<<endl;
		cout<<marks[2]<<endl;
		cout<<marks[3]<<endl;
		cout<<marks[4]<<endl;
	}
	void recDate(){
		//checks must be entered
		cout<<"Enter the date - ";
		cin>>admdate;
	}
	bool isRoll(int r){
		return(r==roll);
	}
	static void initialize(){
		count=0;
	}
	static int retCount(){
		return count;
	}
	static void increment(){
		count++;
	}
};
int Student::count=-1;
int main(){
	Student::initialize();
	Student* list=new Student[MAX];
	int n,pos;
	bool flag;
	do{
		cout<<"1.Add new student\n";
		cout<<"2.Update marks\n";
		cout<<"3.Display marksheet\n";
		cout<<"4.Show number of students\n";
		cout<<"5.Exit\n";
		cin>>n;
		if(n==2||n==3){
			cout<<"Enter the student roll number - ";
			cin>>pos;
			flag=false;
			for(int i=0;i<=Student::retCount();i++){
				if(list[i].isRoll(pos)){
					flag=true;
					pos=i;
					break;
				}
			}
			if(!flag){
				cout<<"Roll number not present\n";
				continue;
			}
		}
		switch(n){
			case 1:Student::increment();
					list[Student::retCount()].recData();
					break;
			case 2:list[pos].recMarks();
					break;
			case 3:list[pos].marksheet();
					break;
			case 4:cout<<"The total number of students - "<<Student::retCount()<<"\n";
					break;
			default: cout<<"The end";
		}
	}while(n>=1&&n<=4);
	return 0;
}
