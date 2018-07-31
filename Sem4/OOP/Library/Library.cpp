
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class Library;
class Transactions;
class Journal{
	int id;
	string name;
	string date;
	int vol;	
	int copies;
	public:
		Journal(int i,string n,string d,int v,int c=0){
			id=i;name=n;date=d;vol=v;copies=c;
		} 
		int get_id(){
			return id;
		}
		string get_name(){ 
			return name;
		}
		int get_copies(){
			return copies;
		}
		void display_journal(){
			cout<<id<<"\t"<<name<<"\t\t"<<date<<"\t"<<vol<<"\t"<<copies<<"\t"<<endl;
		}
		void write() {
			fstream fjournal_list;
			fjournal_list.open("Journal_list.txt", ios::app);
			fjournal_list << endl;
			fjournal_list << id << endl;
			fjournal_list << name << endl;
			fjournal_list << date << endl;
			fjournal_list << vol << endl;
			fjournal_list << copies << endl;
			fjournal_list.close();
		}
		void issue_journal(){
			copies--;
		}
		void return_journal(){
			copies++;
		}
};
class Book{
	int id;
	string name;
	int copies;
	public:
		Book(int i,string n,int c=0){
			id=i;name=n;copies=c;
		}
		int get_id(){
			return id;
		}
		string get_name(){ 
			return name;
		}
		int get_copies(){
			return copies;
		}
		void display_book(){
			cout<<id<<"\t"<<name<<"\t\t"<<copies<<endl;
		}
		void write() {
			fstream fbook_list;
			fbook_list.open("Book_list.txt", ios::app);
			fbook_list << endl;
			fbook_list << id << endl;
			fbook_list << name << endl;
			fbook_list << copies << endl;
			fbook_list.close();
		}
		void issue_book(){
			copies--;
		}
		void return_book(){
			copies++;
		}
};
class Student{
	int roll;
	string name;
	int issued_books[2];
	public:
		Student(int r,string n,int ib[]){
			roll=r;
			name=n;
			for (int i = 0; i < 2; ++i)
			{
				issued_books[i]=ib[i];
			}

		} 
		int get_roll(){
			return roll;
		}
		string get_name(){ 
			return name;
		}
		bool is_empty(int c){
			if(issued_books[c-1]==0){
				return true;
			}
			else{
				return false;
			}
		}
		void display_student(){
			cout<<"Roll: "<<roll<<endl;
			cout<<"Name: "<<name<<endl;
			cout<<"Books issued: ";
			bool flag=true;
			for (int i = 0; i < 2; ++i){
				if(issued_books[i]!=0){
					cout<<issued_books[i]<<" ";
					flag=false;
				}
			}
			if(flag)
				cout<<"None";
			cout<<endl;
		}
		void write() {
			fstream fstudent_list;
			fstudent_list.open("Student_list.txt", ios::app);
			fstudent_list << endl;
			fstudent_list << roll << endl;
			fstudent_list << name << endl;
			for (int i = 0; i < 2; i++) {
				fstudent_list << issued_books[i] << " ";
			}
			fstudent_list << endl;
			fstudent_list.close();
		}
		int return_book(int card_no){
			cout<<"Your fine due is Rs "<<0;
			int temp=issued_books[card_no-1];
			issued_books[card_no-1]=0;
			return temp;
		}
		bool issue_book(int id,int card_no){
			if(issued_books[card_no-1]!=0){
				cout<<"Book of card "<<card_no<<" still not returned"<<endl;
				return false;
			} else {
				issued_books[card_no-1]=id;
				return true;
			}
		}
};
class Faculty{
	int roll;
	string name;
	int issued_books[10];
	int issued_journals[10];
	public:
		Faculty(int r,string n,int ib[],int ij[]){
			roll=r;
			name=n;
			for (int i = 0; i < 10; ++i)
			{
				issued_books[i]=ib[i];
			}
			for (int i = 0; i < 10; ++i)
			{
				issued_journals[i]=ij[i];
			}
		}
		int get_roll(){
			return roll;
		}
		string get_name(){ 
			return name;
		}
		bool is_empty(int c){
			if(issued_books[c-1]==0){
				return true;
			}
			else{
				return false;
			}
		}
		void display_faculty(){
			cout<<"Roll: "<<roll<<endl;
			cout<<"Name: "<<name<<endl;
			cout<<"Books issued: ";
			bool flag=true;
			for (int i = 0; i < 10; ++i)
			{
				if(issued_books[i]!=0){				
					cout<<issued_books[i]<<" ";
					flag=false;
				}
			}
			if(flag){
				cout<<"None";
			}cout<<endl;
			
			flag=true;
			cout<<"Journal issued: ";
			for (int i = 0; i < 10; ++i)
			{
				if(issued_journals[i]!=0){
					cout<<issued_journals[i]<<" ";
					flag=false;
				}
			}
			if(flag){
				cout<<"None";
			}cout<<endl;
		}
		void write() {
			fstream ffaculty_list;
			ffaculty_list.open("Faculty_list.txt", ios::app);
			ffaculty_list << endl;
			ffaculty_list << roll << endl;
			ffaculty_list << name << endl;
			for (int i = 0; i < 10; i++) {
				ffaculty_list << issued_books[i] << " ";
			}
			ffaculty_list << endl;
			for (int i = 0; i < 10; i++) {
				ffaculty_list << issued_journals[i] << " ";
			}
			ffaculty_list << endl;
			ffaculty_list.close();
		}
		bool issue_book(int id,int card_no){
			if(issued_books[card_no-1]!=0){
				cout<<"Book of card "<<card_no<<" still not returned"<<endl;
				return false;
			} else {
				issued_books[card_no-1]=id;
				return true;
			}
		}
		bool issue_journal(int id,int card_no){
			if(issued_journals[card_no-1]!=0){
				cout<<"Journal of card "<<card_no<<" still not returned"<<endl;
				return false;
			} else {
				issued_journals[card_no-1]=id;
				return true;
			}
		}
		int return_book(int card_no){
			int temp=issued_books[card_no-1];
			issued_books[card_no-1]=0;
			return temp;
		}
		int return_journal(int card_no){
			int temp=issued_books[card_no-1];
			issued_books[card_no-1]=0;
			return temp;
		}
};

class Library{
	class Transactions{
		Library *L;
		char issue_type;char issue_person;char transaction_type;
		int card_no;
		int id;
		int roll;
		Book* book;
		Journal* journal;
		Student* student;
		Faculty* faculty;
		string date;
		bool bind_pointers(){
			if(issue_type='B'){
				journal=NULL;
				book=L->search_book(id);
			} else if(issue_type='J') {
				book=NULL;
				journal=L->search_journal(id);
			} else {
				return false; 
			}
			
			if(issue_person='S'){
				faculty=NULL;
				student=L->search_student(roll);
			} else if(issue_person='F') {
				student=NULL;
				faculty=L->search_faculty(id);
			} else {
				return false; 
			}
			return true;
		}
		void transact(){
			if       (issue_type=='B' && issue_person=='S' && transaction_type=='I'){
				book->issue_book();
				student->issue_book(id,card_no);
			} else if(issue_type=='B' && issue_person=='F' && transaction_type=='I'){
				book->issue_book();
				faculty->issue_book(id,card_no);
			} else if(issue_type=='B' && issue_person=='S' && transaction_type=='R'){
				book->return_book();
				student->return_book(card_no);
			} else if(issue_type=='B' && issue_person=='F' && transaction_type=='R'){
				book->return_book();
				faculty->return_book(card_no);
			} else if(issue_type=='J' && issue_person=='F' && transaction_type=='I'){
				journal->issue_journal();
				faculty->issue_journal(id,card_no);
			} else if(issue_type=='J' && issue_person=='F' && transaction_type=='R'){
				journal->return_journal();
				faculty->return_journal(card_no);
			} 
		}
		public:
			Transactions(Library *l,char it,char ip,char tt,int idT,int rollT,int card_noT) {
				L=l;
				issue_type=it;
				issue_person=ip;
				transaction_type=tt;
				id=idT;
				roll=rollT;
				card_no=card_noT;
				bind_pointers();
				transact();
				//ADD DATE INIT
			}

			void display_transaction(){ 
				cout<<issue_type<<"\t"<<id<<"\t";
				issue_type=='B'? cout<<book->get_name()<<"\t":cout<<journal->get_name()<<"\t";
				cout<<issue_person<<"\t"<<roll<<"\t";
				issue_person=='S'? cout<<student->get_name()<<"\t":cout<<faculty->get_name()<<"\t";
				cout<<transaction_type<<"\t";
				cout<<endl;
			}
			/*void write(){ 
				fstream ftransaction_list;
				ftransaction_list.open("Transaction_list.txt", ios::app);
				ftransaction_list << endl;
				ftransaction_list << i.get_name() << "\t";
				ftransaction_list << p.get_name() << "\t";
				ftransaction_list << date << "\t";
				ftransaction_list << txn_type << "\t";
				ftransaction_list << endl;
				ftransaction_list.close();	
			}*/
	};
	private:
		vector<Book> book_list;
		vector<Journal> journal_list;
		vector<Student> student_list;
		vector<Faculty> faculty_list;
		vector<Transactions> transaction_list;
		//LOADING INITIAL DATA
		void load_book_list(){
			fstream fbook_list;
			fbook_list.open("Book_list.txt",ios::in);
			while(!fbook_list.eof()){
				int i,c;string n;
				fbook_list>>i;
				fbook_list>>n;
				fbook_list>>c;
				Book new_book(i,n,c);
				book_list.push_back(new_book);
			}
			fbook_list.close();
			book_list.pop_back();
		}
		void load_journal_list(){
			fstream fjournal_list;
			fjournal_list.open("Journal_list.txt",ios::in);
			while(!fjournal_list.eof()){
				int i,v,c;string d,n;
				fjournal_list>>i;
				fjournal_list>>n;
				fjournal_list>>d;
				fjournal_list>>v;
				fjournal_list>>c;
				Journal new_journal(i,n,d,v,c);
				journal_list.push_back(new_journal);
			}
			fjournal_list.close();
			journal_list.pop_back();
		}
		void load_student_list(){
			fstream fstudent_list;
			fstudent_list.open("Student_list.txt",ios::in);
			while(!fstudent_list.eof()){
				int r;string n;int ib[2];
				fstudent_list>>r;
				fstudent_list>>n;
				for (int i = 0; i < 2; ++i)
				{
					fstudent_list>>ib[i];
				}
				Student new_student(r,n,ib);
				student_list.push_back(new_student);
			}
			fstudent_list.close();
			student_list.pop_back();
		}
		void load_faculty_list(){
			fstream ffaculty_list;
			ffaculty_list.open("Faculty_list.txt",ios::in);
			while(!ffaculty_list.eof()){
				int r;string n;
				int ib[10];
				int ij[10];
				ffaculty_list>>r;
				ffaculty_list>>n;
				for (int i = 0; i < 10; ++i)
				{
					ffaculty_list>>ib[i];
				}
				for (int i = 0; i < 10; ++i)
				{
					ffaculty_list>>ij[i];
				}
				Faculty new_faculty(r,n,ib,ij);
				faculty_list.push_back(new_faculty);
			}
			ffaculty_list.close();
			faculty_list.pop_back();
		}
		void load_transaction_list(){ 

		}
		
		//DUMP FINAL DATA
		void dump_book_list() {
			fstream f;f.open("Book_list.txt", ios::out);
			for (vector<Book>::iterator i = book_list.begin(); i !=book_list.end(); i++){
				i->write();
			}
			f.close();
		}
		void dump_journal_list() {
			fstream f;f.open("Journal_list.txt", ios::out);
			for (vector<Journal>::iterator i = journal_list.begin(); i != journal_list.end(); i++) {
				i->write();
			}
			f.close();
		}
		void dump_student_list() {
			fstream f;f.open("Student_list.txt", ios::out);
			for (vector<Student>::iterator i = student_list.begin(); i != student_list.end(); i++) {
				i->write();
			}
			f.close();
		}
		void dump_faculty_list() {
			fstream f;f.open("Faculty_list.txt",ios::out);
			for (vector<Faculty>::iterator i = faculty_list.begin(); i != faculty_list.end(); i++) {
				i->write();
			}
			f.close();
		}
		void dump_transaction_list(){ 
			fstream f;f.open("Transaction_list.txt",ios::out);
			for (vector<Transactions>::iterator i = transaction_list.begin(); i != transaction_list.end(); i++) {
				//i->write();
			}
			f.close();
		}


	public:
		//CONSTRUCTOR TO ALL DATA FOR THE FIRST TIME
		Library() {
			load_book_list();
			load_journal_list();
			load_student_list();
			load_faculty_list();
		}
		~Library() {
			dump_book_list();
			dump_journal_list();
			dump_student_list();
			dump_faculty_list();
			dump_transaction_list();
		}


		//SEARCH FUNCTIONS
		Book*    search_book(int id){
			for(vector<Book>::iterator i=book_list.begin();i!=book_list.end();++i)
				if(i->get_id()==id)
					return &(*i);
			return NULL;
		}
		Journal* search_journal(int id){
			for(vector<Journal>::iterator i=journal_list.begin();i!=journal_list.end();++i)
				if(i->get_id()==id)
					return &(*i);
			return NULL;
		}
		Student* search_student(int roll){
			for(vector<Student>::iterator i=student_list.begin();i!=student_list.end();++i)
				if(i->get_roll()==roll)
					return &(*i);
			return NULL;
		}
		Faculty* search_faculty(int roll){
			for(vector<Faculty>::iterator i=faculty_list.begin();i!=faculty_list.end();++i)
				if(i->get_roll()==roll)
					return &(*i);
			return NULL;
		}

		//ADDING NEW BOOKS JOURNALS STUDENTS OR FACULTY AND WRITING IT TO THE FILE END
		void add_book(){
			int i,c;string n;
			do{
				cout<<"Enter id:";cin>>i;
				if(search_book(i)==NULL)
					break;
				cout<<"Id already exist"<<endl;
			}while(true);
			cout<<"Enter name:";cin>>n;
			cout<<"Enter #copies:";cin>>c;
			Book new_book(i,n,c);
			book_list.push_back(new_book);
			/*fstream fbook_list;
			fbook_list.open("Book_list.txt",ios::app);
			fbook_list<<endl;
			fbook_list<<i<<endl;
			fbook_list<<n<<endl;
			fbook_list<<c<<endl;
			fbook_list.close();*/
		}
		void add_journal(){
			int i,c,v;string n,d;
			do{
				cout<<"Enter id:";cin>>i;
				if(search_journal(i)==NULL)
					break;
				cout<<"Id already exist"<<endl;
			}while(true);
			cout<<"Enter name:";cin>>n;
			cout<<"Enter volume:";cin>>v;
			cout<<"Enter date:";cin>>d;
			cout<<"Enter #copies:";cin>>c;
			Journal new_journal(i,n,d,v,c);
			journal_list.push_back(new_journal);
			/*fstream fjournal_list;
			fjournal_list.open("Journal_list.txt",ios::app);
			fjournal_list<<endl;
			fjournal_list<<i<<endl;
			fjournal_list<<n<<endl;
			fjournal_list<<d<<endl;
			fjournal_list<<v<<endl;
			fjournal_list<<c<<endl;
			fjournal_list.close();*/
		}
		void add_student(){
			int r;string n;int ib[2] = { 0,0 };
			do{
				cout<<"Enter roll:";cin>>r;
				if(search_student(r)==NULL)
					break;
				cout<<"Id already exist."<<endl;
			}while(true);
			cout<<"Enter name:";cin>>n;			
			Student new_student(r, n,ib);
			student_list.push_back(new_student);
			/*fstream fstudent_list;
			fstudent_list.open("Student_list.txt",ios::app);
			fstudent_list<<endl;
			fstudent_list<<r<<endl;
			fstudent_list<<n<<endl;
			for (int i = 0; i < 2; i++)
			{
				fstudent_list << ib[i] << " " ;
			}
			fstudent_list << endl;
			fstudent_list.close();*/
		}
		void add_faculty(){
			int r;string n;int ib[10] = { 0,0,0,0,0,0,0,0,0,0 };int ij[10] = { 0,0,0,0,0,0,0,0,0,0 };
			do {
				cout << "Enter roll:";cin >> r;
				if (search_faculty(r) == NULL)
					break;
				cout << "Id already exist." << endl;
			} while (true);
				cout << "Enter name:";cin >> n;
			Faculty new_faculty(r, n, ib,ij);
			faculty_list.push_back(new_faculty);
			/*fstream ffaculty_list;
			ffaculty_list.open("Faculty_list.txt", ios::app);
			ffaculty_list << endl;
			ffaculty_list << r << endl;
			ffaculty_list << n << endl;
			for (int i = 0; i < 10; i++)
			{
				ffaculty_list << ib[i] << " ";
			}
			ffaculty_list << endl;
			for (int i = 0; i < 10; i++)
			{
				ffaculty_list << ij[i] << " ";
			}
			ffaculty_list << endl;
			ffaculty_list.close();*/
		}	
		void add_transaction(Library *L,char it,char ip,char tt,int id,int roll,int card_no){
			Transactions T(L,it,ip,tt,id,roll,card_no);
			transaction_list.push_back(T);
		}

		//DISPLAY WHOLE LISTS
		void display_book_list(){
			cout<<"-------------------BOOK LIST-------------------"<<endl;
			cout<<"id\tnames\t\tcopies"<<endl;
			for(vector<Book>::iterator i=book_list.begin();i!=book_list.end();++i){
				i->display_book();
			}
		}
		void display_journal_list(){
			cout<<"-------------------JOURNAL LIST-------------------"<<endl;
			cout<<"id\tname\t\tdate\t\tvol\tcopies"<<endl;
			for(vector<Journal>::iterator i=journal_list.begin();i!=journal_list.end();++i){
				i->display_journal();
			}
		}
		void display_student_list(){
			cout<<"-------------------STUDENT LIST-------------------"<<endl;
			for(vector<Student>::iterator i=student_list.begin();i!=student_list.end();++i){
				i->display_student();
			}
		}
		void display_faculty_list(){
			cout<<"-------------------FACULTY LIST-------------------"<<endl;
			for(vector<Faculty>::iterator i=faculty_list.begin();i!=faculty_list.end();++i){
				i->display_faculty();
			}
		}
		void display_transaction_list(){
			cout<<"-------------------FACULTY LIST-------------------"<<endl;
			for(vector<Transactions>::iterator i=transaction_list.begin();i!=transaction_list.end();++i){
				i->display_transaction();
			}
		}
};


int main(){
	Library L;
	int choice;
	while (choice !=-1) {
		cout << endl;
		cout << "Enter Choice:" << endl;
		cout << "1.Add New " << endl;
		cout << "2.Issue Book " << endl;
		cout << "3.Return Book " << endl;
		cout << "4.Issue Journal" << endl;
		cout << "5.Return Journal" << endl;
		cout << "6.Display All" << endl;
		cout << "7.Display Transactions " <<endl;
		cout << "Any other option to exit" << endl;
		cin >> choice;
		switch (choice) {
			case 1:{
				cout << "1.Book " << endl;
				cout << "2.Journal " << endl;
				cout << "3.Student " << endl;
				cout << "4.Faculty" << endl;
				int choice2;cin >> choice2;
				switch (choice2) {
					case 1: {
						L.add_book();
						break;
					}
					case 2: {
						L.add_journal();
						break;
					}
					case 3: {
						L.add_student();
						break;
					}
					case 4: {
						L.add_faculty();
						break;
					}
					default:
						break;
				}
				break;
			} 
			case 2: {
				cout << "1.Student " << endl;
				cout << "2.Faculty" << endl;
				int choice2;cin >> choice2;
				switch (choice2) {
					case 1: {
						//ISSUE BOOK TO STUDENT
						int id;
						cout<<"Enter Book Id :";
						cin >> id;
						Book* b=L.search_book(id);
						if(b==NULL || b->get_copies()==0){
							cout<<"Wrong Book id"<<endl;
							break;
						}
						else if( b->get_copies()==0){
							cout<<"No Books Left"<<endl;
							break;
						}
						cout<<"Enter Student Roll :";
						int roll;
						cin>>roll;
						Student* s=L.search_student(roll);
						if(s==NULL){
							cout<<"Wrong Student roll"<<endl;
							break;
						}
						int card_no;
						cout<<"Enter Card No";
						cin>>card_no;
						if(!s->is_empty(card_no)){
							cout<<"Card is not free";
							break;
						}
						L.add_transaction(&L,'B','S','I',id,roll,card_no);
					}
					case 2: {
						//ISSUE BOOK TO FACULTY
						int id;
						cout<<"Enter Book Id :";
						cin >> id;
						Book* b=L.search_book(id);
						if(b==NULL || b->get_copies()==0){
							cout<<"Wrong Book id"<<endl;
							break;
						}
						else if( b->get_copies()==0){
							cout<<"No Books Left"<<endl;
							break;
						}
						cout<<"Enter Faculty Roll :";
						int roll;
						cin>>roll;
						Faculty* f=L.search_faculty(roll);
						if(f==NULL){
							cout<<"Wrong Faculty roll"<<endl;
							break;
						}
						int card_no;
						cout<<"Enter Card No";
						cin>>card_no;
						if(!f->is_empty(card_no)){
							cout<<"Card is not free";
							break;
						}
						L.add_transaction(&L,'B','F','I',id,roll,card_no);
					}
					default:
						break;
				}
				break;
			}
			case 3: {
				cout << "1.Student " << endl;
				cout << "2.Faculty" << endl;
				int choice2;cin >> choice2;
				switch (choice2) {
					case 1: {
						//RETURN BOOK TO STUDENT
						int id;
						cout<<"Enter Book Id :";
						cin >> id;
						Book* b=L.search_book(id);
						if(b==NULL || b->get_copies()==0){
							cout<<"Wrong Book id"<<endl;
							break;
						}
						cout<<"Enter Student Roll :";
						int roll;
						cin>>roll;
						Student* s=L.search_student(roll);
						if(s==NULL){
							cout<<"Wrong Student roll"<<endl;
							break;
						}
						int card_no;
						cout<<"Enter Card No";
						cin>>card_no;
						L.add_transaction(&L,'B','S','R',id,roll,card_no);
					}
					case 2: {
						//RETURN BOOK TO FACULTY
						int id;
						cout<<"Enter Book Id :";
						cin >> id;
						Book* b=L.search_book(id);
						if(b==NULL || b->get_copies()==0){
							cout<<"Wrong Book id"<<endl;
							break;
						}
						cout<<"Enter Faculty Roll :";
						int roll;
						cin>>roll;
						Student* s=L.search_student(roll);
						if(s==NULL){
							cout<<"Wrong Faculty roll"<<endl;
							break;
						}
						int card_no;
						cout<<"Enter Card No";
						cin>>card_no;
						L.add_transaction(&L,'B','F','R',id,roll,card_no);
					}
					default:
						break;
				}
				break;
			}
			case 4: {
				//ISSUE JOURNAL TO FACULTY
				int id;
				cout<<"Enter Journal Id :";
				cin >> id;
				Journal* j=L.search_journal(id);
				if(j==NULL || j->get_copies()==0){
					cout<<"Wrong Journal id"<<endl;
					break;
				}
				else if( j->get_copies()==0){
					cout<<"No Journal Left"<<endl;
					break;
				}
				cout<<"Enter Faculty Roll :";
				int roll;
				cin>>roll;
				Faculty* f=L.search_faculty(roll);
				if(f==NULL){
					cout<<"Wrong Faculty roll"<<endl;
					break;
				}
				int card_no;
				cout<<"Enter Card No";
				cin>>card_no;
				if(!f->is_empty(card_no)){
					cout<<"Card is not free";
					break;
				}
				L.add_transaction(&L,'J','F','I',id,roll,card_no);
				break;
			}
			case 5: {
				//RETURN JOURNAL TO FACULTY
				break;
			}
			case 6: {
				L.display_book_list();
				L.display_journal_list();
				L.display_student_list();
				L.display_faculty_list();
				break;
			}
			case 7: {
				L.display_transaction_list();
				break;
			}
			default:
				break;
		}

	}
	return 0;
}
