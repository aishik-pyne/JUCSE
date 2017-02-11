
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
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
		void return_book(int fine_days,int card_no){
			cout<<"Your fine due is Rs "<<fine_days;
			issued_books[card_no-1]=0;
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
		/*void fine_paid(){
			int fine;
			cout<<"Your due fine is : "<<fine_due<<endl;
			cout<<"Enter fine paid :";
			cin>>fine;
			fine_due-=fine;
		}*/
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
		void return_book(int fine_days,int card_no){
			issued_books[card_no-1]=0;
		}
		void return_journal(int fine_days,int card_no){
			issued_journals[card_no-1]=0;
		}
};
class Transactions{

};
class Library{
	private:
		vector<Book> book_list;
		vector<Journal> journal_list;
		vector<Student> student_list;
		vector<Faculty> faculty_list;

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
		
		//DUMP FINAL DATA
		void dump_book_list() {
			for (vector<Book>::iterator i = book_list.begin(); i !=book_list.end(); i++){
				i->write();
			}
		}
		void dump_journal_list() {
			for (vector<Journal>::iterator i = journal_list.begin(); i != journal_list.end(); i++) {
				i->write();
			}
		}
		void dump_student_list() {
			for (vector<Student>::iterator i = student_list.begin(); i != student_list.end(); i++) {
				i->write();
			}
		}
		void dump_faculty_list() {
			for (vector<Faculty>::iterator i = faculty_list.begin(); i != faculty_list.end(); i++) {
				i->write();
			}
		}

		//UNFINISHED BUG VECTOR ITERATOR POINTER
		Book*    search_book(int id){
			for(vector<Book>::iterator i=book_list.begin();i!=book_list.end();++i)
				if(i->get_id()==id)
					return NULL;
			return NULL;
		}
		Journal* search_journal(int id){
			for(vector<Journal>::iterator i=journal_list.begin();i!=journal_list.end();++i)
				if(i->get_id()==id)
					return NULL;
			return NULL;
		}
		Student* search_student(int roll){
			for(vector<Student>::iterator i=student_list.begin();i!=student_list.end();++i)
				if(i->get_roll()==roll)
					return NULL;
			return NULL;
		}
		Faculty* search_faculty(int roll){
			for(vector<Faculty>::iterator i=faculty_list.begin();i!=faculty_list.end();++i)
				if(i->get_roll()==roll)
					return NULL;
			return NULL;
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
			fstream fbook_list;
			fbook_list.open("Book_list.txt",ios::app);
			fbook_list<<endl;
			fbook_list<<i<<endl;
			fbook_list<<n<<endl;
			fbook_list<<c<<endl;
			fbook_list.close();
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
			fstream fjournal_list;
			fjournal_list.open("Journal_list.txt",ios::app);
			fjournal_list<<endl;
			fjournal_list<<i<<endl;
			fjournal_list<<n<<endl;
			fjournal_list<<d<<endl;
			fjournal_list<<v<<endl;
			fjournal_list<<c<<endl;
			fjournal_list.close();
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
			fstream fstudent_list;
			fstudent_list.open("Student_list.txt",ios::app);
			fstudent_list<<endl;
			fstudent_list<<r<<endl;
			fstudent_list<<n<<endl;
			for (int i = 0; i < 2; i++)
			{
				fstudent_list << ib[i] << " " ;
			}
			fstudent_list << endl;
			fstudent_list.close();
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
			fstream ffaculty_list;
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
			ffaculty_list.close();
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
};
int main(){
	Library L;
	L.display_book_list();
	L.display_journal_list();
	L.display_student_list();
	L.display_faculty_list();

	return 0;
}
