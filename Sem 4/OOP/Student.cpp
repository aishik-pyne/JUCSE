#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Student{
	
	long roll;
	string name;
	string course;
	string date;
	int marks[5];
	public:
		static int count;
		static int last_roll;
		Student(string n="",string c="",string d=""){
			count++;last_roll++;
			roll=last_roll;
			name=n;
			course=c;
			date=d;
			for(int i=0;i<5;i++){
				marks[i]=0;
			}
		}
		~Student(){
			count--;
			delete this;
		}
		void total_count(){
			cout<<count<<endl;
		}
		void enter_marks(){
			cout<<roll<<endl;
			cout<<name<<endl;
			for(int i=0;i<5;i++){
				cout<<"Enter marks in subject "<<(i+1)<<":";
				cin>>marks[i];
			}
		}
		void mark_sheet(){
			cout<<roll<<endl;
			cout<<name<<endl;
			cout<<course<<endl;
			cout<<date<<endl;
			for(int i=0;i<5;i++){
				cout<<"Marks in subject "<<(i+1)<<":"<<marks[i]<<endl;
			}
		}
};
int Student :: count=0;
int Student :: last_roll=0;
int main(){
	Student S1("Aishik","CSE","2015");
	Student S2("Rajit","ETEC","2015");
	Student S3("Aisik","ETEC","2015");
	Student S4("Pallav","ETEC","2015");
	S1.enter_marks();
	S1.mark_sheet();
	S1.total_count();
	return 0;
}
