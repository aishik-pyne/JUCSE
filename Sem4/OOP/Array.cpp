#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Array{
	int* arr;
	int size;
	public:
		//Constructor
		Array(int n,int key=0){
			arr=new int[n];
			size=n;
			for(int i=0;i<n;i++){
				arr[i]=key;
			}
		}
		//Copy Constructor 
		Array(const Array &A){
			arr=new int[A.size];
			size=A.size;
			for(int i=0;i<A.size;i++){
				arr[i]=A.arr[i];
			}
		}
		int get_size(){
			return size;
		}
		//input elements
		void input_element(){
			for(int i=0;i<this->size;i++){
				cin>>arr[i];
			}
		}
		//display Array
		void display(){
			for(int i=0;i<this->size;i++){
				cout<<arr[i]<<" ";
			}
			cout<<endl;
		}
		//Operator overload *
		Array* operator+(Array B){
			if(this->size!=B.size){
				cout<<"Sizes don't match"<<endl;
				return NULL;
			}
			
			Array *sum=new Array(B.size);
			for(int i=0;i<this->size;i++){
				sum->arr[i]=this->arr[i]+B.arr[i];
			}return sum;
		}
		
		//Operator overload []
		int operator[](int i){
			if(i>=size){
				cout<<"Array out of bound";
				return 0;
			}
			return arr[i]; 
		}
		
		//Operator overload *
		Array* operator*(int n){
			for(int i=0;i<size;i++){
				this->arr[i]*=n;
			}
			return this;
		}
		
		//Operator overload =
		Array operator=(Array B){
			Array A(B);
			return A;
		}
};
int main(){
	
	cout<<"Enter array A size: ";
	int s;
	cin>>s;
	Array A(s);
	cout<<"Enter elements of Array A: ";
	A.input_element();
	
	
	cout<<"Enter array B size: ";
	cin>>s;
	Array B(s);
	cout<<"Enter elements of Array B: ";
	B.input_element();
	int n;
	
	do{
		cout<<"1.Input array A"<<endl;
		cout<<"2.Input array B"<<endl;
		cout<<"3.A=A+B"<<endl;
		cout<<"4.A=B"<<endl;
		cout<<"5.A=A*n"<<endl;
		cout<<"6.A[i]"<<endl;
		cout<<"7.Display Array"<<endl;
		cin>>n;
		switch(n){
			case 1:
					break;
			case 2:
					break;
			case 3:{
				if(A.get_size()!=B.get_size()){
					cout<<"Size dont match"<<endl;
				} else {
					A=*(A+B);
				}
				break;
			}
			case 4:{
				A=B;
				break;
			}
			case 5:{
				int n;
				cout<<"Enter n: ";
				cin>>n;
				A=*(A*n);
				break;
			}
			case 6:{
				int i;
				cout<<"Enter i: ";
				cin>>i;
				cout<<A[i];
				break;
			}
			case 7:{
				A.display();
				break;
			}
			default: cout<<"The end";
		}
	}while(n>=1&&n<=7);
	
	return 0;
}
