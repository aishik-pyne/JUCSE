#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Item{
	int code;
	string name;
	float rate;
	int qty;
	public:
		Item(int c=0,string s="",float r=0.0,int q=0){
			code=c;
			name=s;
			rate=r;
			qty=q;
		}
		int get_code(){
			return code;
		}
		int get_qty(){
			return qty;
		}
		string get_name(){
			return name;
		}
		float get_rate(){
			return rate;
		}
		void update_rate(float r){
			cout<<"sdg"<<endl;
			this->rate=r;
		}
		void display_item(){
			cout<<"Code: "<<code<<endl;
			cout<<"Name: "<<name<<endl;
			cout<<"Rate: "<<rate<<endl;
			cout<<"Qty : "<<qty<<endl;
			cout<<endl;
		}
		void item_received(int amt=1){
			qty+=amt;
		}
		void item_issued(int amt=1){
			this->qty-=amt;
		}
};
class List{
	vector<Item> list;
	public:
		bool add_item(Item x){
			for(int i=0;i<list.size();i++){
				if(x.get_code()==list[i].get_code()){
					cout<<"Code already exists"<<endl;
					return false;
				}
			}
			list.push_back(x);
			return true;
		}
		bool add_item(int c,string n,float r,int q){
			Item x(c,n,r,q);
			for(int i=0;i<list.size();i++){
				if(x.get_code()==list[i].get_code()){
					cout<<"Code already exists"<<endl;
					return false;
				}
			}
			list.push_back(x);
			return true;
		}
		Item* search(int c){
			for(int i=0;i<list.size();i++){
				if(list[i].get_code()==c){
					return &list[i];
				}
			}
			return NULL;
		}
		Item* search(string n){
			for(int i=0;i<list.size();i++){
				if(list[i].get_name()==n){
					return &list[i];
				}
			}
			return NULL;
		}
		bool update_rate(int c,float r){
			Item* x=search(c);
			if(x==NULL){
				cout<<"Item not found";
				return false;
			}else{
				cout<<"Item Name: "<<x->get_name();
				x->update_rate(r);
			}return true;
		}
		bool update_rate(string n,float r){
			Item* x=search(n);
			if(x==NULL){
				cout<<"Item not found"<<endl;
				return false;
			}else{
				x->update_rate(r);
			}return true;
		}
		bool query(int code){
			Item* x=search(code);
			if(x==NULL){
				cout<<"Item not found"<<endl;
				return false;
			}else{
				x->display_item();
				return true;
			}
		}
		void query(string name){
			Item* x=search(name);
			if(x==NULL){
				cout<<"Item not found"<<endl;
			}else{
				x->display_item();
			}
		}
		bool issue(int c,int q){
			Item* x=search(c);
			if(x==NULL){
				cout<<"Item not found"<<endl;
				return false;
			}else{
				x->item_issued(q);  
				return true;
			}
		}
		bool receive(int c,int q){
			Item* x=search(c);
			if(x==NULL){
				cout<<"Item not found"<<endl;
				return false;
			}else{
				x->item_received(q);  
				return true;
			}
		} 
		void display_list(){
			for(int i=0;i<list.size();i++){
				list[i].display_item();	
			}
		}
		
};
int main(){
	List Amazon;
	Amazon.add_item(Item(123,"Chocolate"    ,40.0,44));
	Amazon.add_item(Item(124,"Vanilla"      ,20.0,102));
	Amazon.add_item(Item(125,"Butterscotch" ,30.0,321));
	Amazon.add_item(Item(126,"Black Current",50.0,2));
	Amazon.add_item(Item(127,"Two In One"   ,10.0,4));
	int choice;
	while(1)
	{
		cout<<"Enter:"<<endl;
		cout<<"1. Add items"<<endl;
		cout<<"2. Update Rate"<<endl;
		cout<<"3. Receive Item"<<endl;
		cout<<"4. Issue Items"<<endl;
		cout<<"5. Status"<<endl;
		cout<<"6. Display Whole List"<<endl;
		cout<<"7. Exit"<<endl;
		cin>>choice;
		
		switch (choice){
			case 1:{
				int c;string n;float r;int q;
				do{
					cout<<"Enter code:";
					cin>>c;
					cout<<"Enter name:";
					cin>>n;
					cout<<"Enter rate:";
					cin>>r;
					cout<<"Enter quantity:";
					cin>>q;	
				}while(!Amazon.add_item(c,n,r,q));
				break;
			}
			case 2:{
				int c;float r;
				cout<<"Enter code:";
				cin>>c;
				cout<<"Enter rate:";
				cin>>r;
				Amazon.update_rate(c,r);
				break;
			}
			case 3:{
				int c,q;
				cout<<"Enter code:";
				cin>>c;
				do{
					cout<<"Enter qty:";
					cin>>q;
				}while(c<=0);
				Amazon.receive(c,q);
				break;
			}
			case 4:{
				int c,q;
				cout<<"Enter code:";
				cin>>c;
				do{
					cout<<"Enter qty:";
					cin>>q;
				}while(c<=0);
				Amazon.issue(c,q);
				break;
			}
			case 5:{
				int c,q;
				cout<<"Enter code:";
				cin>>c;
				Amazon.query(c);
				break;
			}
			case 6:{
				Amazon.display_list();
				break;
			}
			case 7:
				exit(0);
				
			default:
				cout<<"Wrong choice";
		}				
	}

    return 0;
}
