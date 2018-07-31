#include <iostream>
#include <cmath>
using namespace std;
class Complex{
		int x;
		int y;
	public:
		Complex(int a=0,int b=0){
			x=a;
			y=b;
		}
		void setComplex()
        {
            cout << "Enter the real and imaginary parts : ";
            cin >> x;
            cin >> y;
        }  
		Complex operator+(Complex B){
			Complex C;
			C.x=x +B.x;
			C.y=y +B.y;
			return C;
		}
		Complex operator-(Complex B){
			Complex C;
			C.x=x -B.x;
			C.y=y -B.y;
			return C;
		}
		void print(){
			if(x!=0)
				cout<<x;
			if(y!=0){
				if(y>0)
					cout<<"+i"<<y<<endl;
				else
					cout<<"-i"<<(int)abs(y)<<endl;
			}
			else{
				cout<<0<<endl;
			}	
		}
};
int main(){
	Complex a, b, c, d;
 
    cout << "Setting first complex number " << endl;
    a.setComplex();
    cout << "Setting second complex number " << endl;
    b.setComplex();
    /* Adding two complex numbers */
    cout << "Addition of a and b    : " << endl;
    c = a + b;
    c.print();
    /* Subtracting two complex numbers */
    cout << "Subtraction of a and b : " << endl;
    d = a - b;
    d.print();
	return 0;
}
