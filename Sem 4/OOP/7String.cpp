#include <iostream>
#include <cstdio>
#include <cstring>
#define MAX 10
using namespace std;
class String{
	char* str;
	int compare(const String& s){//first bigger +, second larger -, same 0
		int len1=strlen(str),len2=strlen(s.str);
		if(len1>len2) return (1);
		else if(len1<len2) return (-1);
		else{
			for(int i=0;i<len1;i++){
				if(str[i]!=s.str[i]) return ((int)(str[i]-s.str[i]));
			}
		}
		return 0;
	}
	public:
		String(){
			str=NULL;
		}
		String(int sz,char ch=' '){
			str=new char[sz+1];
			for(int i=0;i<sz;i++) str[i]=ch;
			str[sz]='\0';
		}
		String(const String& s){
			int sz=strlen(s.str);
			str=new char[sz+1];
			strcpy(str,s.str);
		}
		String(const char* s){
			int len=strlen(s);
			str=new char[len+1];
			strcpy(str,s);
			cout<<"Initiation done  - "<<str<<"\n";
		}
		~String(){
			if(str!=NULL) delete(str);
		}
		String operator+(const String& s){
			int len2,len=strlen(str)+strlen(s.str)+1;//for the extra last space not needed
			String strn(len);//call to constructor
			len2=strlen(str);
			for(int i=0;i<len2;i++) strn.str[i]=str[i];
			for(int i=len2;i<len-1;i++) strn.str[i]=s.str[i-len2];
			str[len-1]='\0';
			return strn;
		}
		void operator=(const String& s){
			if(str!=NULL) delete(str);
			int len=strlen(s.str)+1;
			str=new char[len];
			strcpy(str,s.str);
		}
		bool operator==(const String& s){
			return (this->compare(s)==0);
		}
		bool operator>=(const String& s){
			return (this->compare(s)>=0);
		}
		bool operator<=(const String& s){
			return (this->compare(s)<=0);
		}
		bool operator>(const String& s){
			return (this->compare(s)>0);
		}
		bool operator<(const String& s){
			return (this->compare(s)<0);
		}
		void display(){
			cout<<"The string - "<<str<<"\n";
		}
};
int main(){
	String list[MAX];
	int ch,count=-1;
	char temp[50];
	int temp1,temp2;
	do{
		cout<<"1.Add string by entering string\n";
		cout<<"2.Add string by Assigning an object to another\n";
		cout<<"3.Concat 2 strings\n";
		cout<<"4.Comparison of strings\n";
		cout<<"5.Display string\n";
		cout<<"6.Exit\n";
		cin>>ch;
		if(count==14&&(ch==1||ch==2||ch==3)){
			cout<<"FULL. Cannot enter\n";
		}
		switch(ch){
			case 1: cout<<"Enter the string - ";
					//cin>>temp;
					getchar();
					gets(temp);
					cout<<temp<<"\n";
					list[++count]=String(temp);
					break;
			case 2: cout<<"Enter number of object - ";
					cin>>temp1;
					list[++count]=String(list[temp1]);
					break;
			case 3: int temp1,temp2;
					cout<<"Enter the 2 objects - ";
					cin>>temp1>>temp2;
					list[++count]=list[temp1]+list[temp2];
					break;
			case 4: cout<<"Enter the 2 objects - ";
					cin>>temp1>>temp2;
					if(list[temp1]==list[temp2]) cout<<"They are equal\n";
					else if(list[temp1]>list[temp2]) cout<<"First is greater\n";
					else cout<<"Second is greater\n";
					break;
			case 5: cout<<"Enter number of object - ";
					cin>>temp1;
					list[temp1].display();
					break;
			case 6:cout<<"Ending\n";
					break;
			default: cout<<"Wrong choice\n";
		}
	}while(ch!=6);
	cout<<"The End\n";
	return 0;
}
