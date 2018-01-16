# SIC/XE Assembler in CPP

## Setting up the OPTAB and the REGISTERS

We create a TABLES.cpp file which defines the structs for holding **OPCODES** and the **REGISTERS**
(Some parts of the code are missing to reduce the size of the report. Refer to actual files)


```cpp
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<cstdio>
#include<map>

using namespace std;


//stores info of ach mnemonic instruction
struct info_op
{
    string opcode;
    int format;
    char exist;
    info_op()
    {
        exist='n';
    }
};

struct info_reg
{
    int num;
    char exist;
    info_reg()
    {
        exist='n';
    }
};
struct info_label
{
     string address;
     string value;
     string block;
     char exist;
     info_label()
     {
         exist='n';
     }
};

struct info_block
{
    string address,length;
    int num;
    char exist;
    info_block()
    {
        exist='n';
    }
};

typedef string mnemonic,label;

typedef std::map<mnemonic,info_op>   MapType1;
typedef std::map<mnemonic,info_reg>  MapType2;
typedef std::map<label,info_label>   MapType3;
typedef std::map<label,info_block>   MapType4;
//USING MAPS ALLOWS SEARCHING FOR ANY ENTRY IN LOG(N) TIME

//This maps the instructions(mnemonic codes) with thier Opcode and their format
MapType1 OPTAB;

//This maps the register mnemonic with their number
MapType2 REGISTER;

//This map forms the symbol table : Label and  Address
MapType3 SYMTAB;

//This maps the program block name with its info
MapType4 BLOCK;



int reg_num(char a)
{
    if(a=='A') return 0;
    if(a=='X') return 1;
    if(a=='L') return 2;
    if(a=='B') return 3;
    if(a=='S') return 4;
    if(a=='T') return 5;
    if(a=='F') return 6;
}


/*---------OPTABLE-----------*/
void create()
{

    OPTAB["ADD"].opcode="18";
    OPTAB["ADD"].format=3;
    OPTAB["ADD"].exist='y';

    OPTAB["ADDF"].opcode="58";
    OPTAB["ADDF"].format=3;
    OPTAB["ADDF"].exist='y';

    OPTAB["ADDR"].opcode="90";
    OPTAB["ADDR"].format=2;
    OPTAB["ADDR"].exist='y';

    ///////////////////////////////////
    // DEFINE REST OF THE OBTABS HERE//
    ///////////////////////////////////

    OPTAB["WD"].opcode="DC";
    OPTAB["WD"].format=3;
    OPTAB["WD"].exist='y';

    /*-------------------------*/



    /*---REGISTERS'-INFO-------*/

    REGISTER["A"].num=0;
    REGISTER["A"].exist='y';

    REGISTER["X"].num=1;
    REGISTER["X"].exist='y';

    REGISTER["L"].num=2;
    REGISTER["L"].exist='y';

    REGISTER["B"].num=3;
    REGISTER["B"].exist='y';

    REGISTER["S"].num=4;
    REGISTER["S"].exist='y';

    REGISTER["T"].num=5;
    REGISTER["T"].exist='y';

    REGISTER["F"].num=6;
    REGISTER["F"].exist='y';

    REGISTER["PC"].num=8;
    REGISTER["PC"].exist='y';

    REGISTER["SW"].num=9;
    REGISTER["SW"].exist='y';

    /*--------------------------*/

}


string find_block(int num)
{
     for (MapType4::const_iterator it = BLOCK.begin();;++it)
         if(it->second.num==num)
            return it->first;
}

```

---
## Pass1

The pass1 goes though each line of code and store the address of each **SYMBOL** in the **SYMTAB**, checks each **OPCODE** with the **OPTAB**, maintains an **ERROR LOG** and finally creates an **intermediate file** for the **Pass2** to work on

```cpp
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<cstdio>
#include<map>
using namespace std;

#include "TABLES.cpp"
#include "HEXA_DEC.cpp"

bool isWhiteSpace(char a)
{
    if(a==' ')  return true;
    if(a=='\t') return true;
    return false;
}

void extract(string a,string word[],int& count)
{
    int i;
    for(i=0;i<5;++i) word[i]="";
    count=0;
    i=0;
    while(isWhiteSpace(a[i])&&i<a.length()) {++i;continue;}
    if(i==a.length()||a[i]=='.')   return;
    for(;i<a.length();)
    {
        while(isWhiteSpace(a[i])&&i<a.length()) {++i;continue;}
        if(i==a.length()) break;
        for(;!isWhiteSpace(a[i])&&i<a.length();++i) word[count]+=a[i];
        ++count;
    }
}

void execute(string[],int);

int block_num,line;
hexa pc;
string curr_block;
bool error_flag=0;


ifstream fin1;
ofstream fout1,error,fout2;

void run()
{
    create();
    char ch;
    string s,word[5];
    int count=0;
    fin1.open("input_fibonacci.txt");
    fout1.open("intermediate.txt");
    fout2.open("symbol.txt");
    error.open("error.txt");
    line=5;
    getline(fin1,s);
    extract(s,word,count);
    while(count==0)
    {
        fout1<<line<<endl;
        fout1<<"$";
        fout1<<s<<endl;
        fout1<<""<<endl;
        fout1<<""<<endl;
        line+=5;
        cout<<"s: "<<s<<endl;
    }
    pc="0";
    BLOCK["DEFAULT"].num=0;
    BLOCK["DEFAULT"].address=pc;
    BLOCK["DEFAULT"].length="0";
    BLOCK["DEFAULT"].exist='y';
    curr_block="DEFAULT";
    block_num=1;
    line=5;
    if(word[0]=="START")
    {
        pc=word[1];
        fout1<<line<<endl;
        fout1<<""<<endl;
        fout1<<"START"<<endl;
        fout1<<pc<<endl;
        fout1<<pc<<endl;
        fout1<<""<<endl;
        cout<<"0 is start!"<<endl;
    }
    else if(word[1]=="START")
    {
    	fout2<<word[0]<<endl;

        pc=word[2];
        fout1<<line<<endl;
        fout1<<word[0]<<endl;
        fout1<<"START"<<endl;
        fout1<<pc<<endl;
        fout1<<pc<<endl;
        fout1<<""<<endl;
        cout<<"1 is start!"<<endl;
    }
    else
        execute(word,count);
    while(true)
    {
        getline(fin1,s);
        extract(s,word,count);
        line+=5;

        cout<<"s: "<<s<<endl;
        fout1<<line<<endl;
        if(count==0)
        {
            cout<<"Comment detected!"<<endl;
            fout1<<"$"<<endl;
            fout1<<s<<endl;
            fout1<<""<<endl;
            fout1<<""<<endl;
            fout1<<""<<endl;
            continue;
        }
        if(word[0]=="END")
        {
            BLOCK[curr_block].length=pc;
            fout1<<""<<endl;
            fout1<<word[0]<<endl;
            fout1<<word[1]<<endl;
            fout1<<pc<<endl;
            fout1<<""<<endl;
            break;
        }
        execute(word,count);
       // cin>>ch;
     }
     hexa addr,len;
     string temp=find_block(0);
     addr=BLOCK[temp].address;
     len=BLOCK[temp].length;
     for(int i=1;i<block_num;++i)
     {
            temp=find_block(i);
            BLOCK[temp].address=toHex(toDec(addr)+toDec(len));
            addr=BLOCK[temp].address;
            len=BLOCK[temp].length;

     }
}

void execute(string word[],int count)
{
    string STRING;
    ifstream infile;
    ifstream lsf;

    cout<<"word[0]: "<<word[0]<<" pc: "<<pc<<endl;
    if(word[0]=="USE")
    {
        cout<<"USE detected!"<<endl;
        BLOCK[curr_block].length=pc;
        if(word[1]=="")
        {
            curr_block="DEFAULT";
            pc=BLOCK["DEFAULT"].length;
        }
        else if(BLOCK[word[1]].exist=='y')
        {
            curr_block=word[1];
            pc=BLOCK[word[1]].length;
        }
        else
        {
            BLOCK[word[1]].num=block_num;
            BLOCK[word[1]].exist='y';
            BLOCK[word[1]].length="0";
            curr_block=word[1];
            pc="0";
            ++block_num;
        }
        fout1<<""<<endl;
        fout1<<word[0]<<endl;
        fout1<<word[1]<<endl;
        fout1<<pc<<endl;
        fout1<<""<<endl;
        return;
    }
    if(word[0][0]=='+')
    {
        cout<<"Format 4"<<endl;
        fout1<<""<<endl;
        fout1<<word[0]<<endl;
        fout1<<word[1]<<endl;
        fout1<<pc<<endl;
        pc=toHex(toDec(pc)+4);
        fout1<<pc<<endl;
        return;
    }
    if(OPTAB[word[0]].exist=='y')
    {
        cout<<"0 is opcode!"<<endl;
        fout1<<""<<endl;
        fout1<<word[0]<<endl;
        fout1<<word[1]<<endl;
        fout1<<pc<<endl;
        pc=toHex(toDec(pc)+OPTAB[word[0]].format);
        fout1<<pc<<endl;
        return;
    }
    if(OPTAB[word[0]].exist=='n')
    {

        if(SYMTAB[word[0]].exist=='y')
        {
            error<<"Line "<<line<<": Duplicate Symbol"<<endl;
            error_flag=1;
        }
        else
        {

            SYMTAB[word[0]].address=pc;
            SYMTAB[word[0]].block=curr_block;
            SYMTAB[word[0]].exist='y';
            fout1<<word[0]<<endl;
            int ggg;

            fout2<<"##  SYMBOL -->> "<<word[0]<<" ||   ADDRESS -->> ";
            fout2<<SYMTAB[word[0]].address<<"   ##"<<endl;

            fout1<<word[1]<<endl;
            fout1<<word[2]<<endl;
            fout1<<pc<<endl;
            if(word[1][0]=='+')
                pc=toHex(toDec(pc)+4);
            else if(OPTAB[word[1]].exist=='y')
                pc=toHex(toDec(pc)+OPTAB[word[1]].format);
            else if(word[1]=="WORD")      pc=toHex(toDec(pc)+3);
            else if(word[1]=="RESW")      pc=toHex(toDec(pc)+(atoi(word[2].c_str())*3));
            else if(word[1]=="RESB")      pc=toHex(toDec(pc)+atoi(word[2].c_str()));
            else if(word[1]=="BYTE")
            {
                 int len=word[1].length()-3;
                 if(word[1][0]=='X') len/=2;
                 pc=toHex(toDec(pc)+len);
            }
            else
            {
                error<<"Line "<<line<<": Opcode not found"<<endl;
                error_flag=1;
            }
            fout1<<pc<<endl;
        }
    }
}
```

#### SYMTAB:

```text
FIBO
##  SYMBOL -->> FIRST ||   ADDRESS -->> 0   ##
##  SYMBOL -->> LENGTH ||   ADDRESS -->> E   ##
##  SYMBOL -->> RDREC ||   ADDRESS -->> 11   ##
##  SYMBOL -->> RLOOP ||   ADDRESS -->> 13   ##
##  SYMBOL -->> INPUT ||   ADDRESS -->> 2C   ##
##  SYMBOL -->> WRREC ||   ADDRESS -->> 2D   ##
##  SYMBOL -->> WLOOP ||   ADDRESS -->> 39   ##
##  SYMBOL -->> OUTPUT ||   ADDRESS -->> 55   ##
##  SYMBOL -->> VALUE1 ||   ADDRESS -->> 56   ##
##  SYMBOL -->> VALUE2 ||   ADDRESS -->> 59   ##
```

#### INTERMEDIATE FILE

```text
5
FIBO
START
0
0

10
FIRST
LDT
#1
0
3
15

LDS
#10
3
6
20

+JSUB
RDREC
6
A
25

+JSUB
WRREC
A
E
30
LENGTH
RESW
1
E
11
35
$
.



40
$
. SUBROUTINE RDREC



45
$
.



50
RDREC
CLEAR
A
11
13
55
RLOOP
TD
INPUT
13
16
60

JEQ
RLOOP
16
19
65

RD
INPUT
19
1C
70

COMPR
A,T
1C
1E
75

JLT
RLOOP
1E
21
80

COMPR
A,S
21
23
85

JGT
RLOOP
23
26
90

STA
LENGTH
26
29
95

RSUB

29
2C
100
INPUT
BYTE
X'F1'
2C
2D
105
$
.



110
$
.SUBROUTINE WDREC



115
$
.



120
WRREC
LDX
#0
2D
30
125

LDS
#1
30
33
130

LDA
#0
33
36
135

LDT
LENGTH
36
39
140
WLOOP
TD
OUTPUT
39
3C
145

JEQ
WLOOP
3C
3F
150

WD
OUTPUT
3F
42
155

ADDR
S,A
42
44
160

STA
VALUE1
44
47
165

STS
VALUE2
47
4A
170

LDA
VALUE2
4A
4D
175

LDS
VALUE1
4D
50
180

TIXR
T
50
52
185

JLT
WLOOP
52
55
190
OUTPUT
BYTE
X'05'
55
56
195
VALUE1
RESW
1
56
59
200
VALUE2
RESW
1
59
5C
205

END
FIRST
5C

```

#### ERROR LOG:

There was no error

---


## Pass2

This sections reads from the **intermediate file** , verifies each **OPCODE** with **OPTAB**, assigns addresses to **SYMBOLS** from the **SYMTAB** and finally creates the object code.

```cpp
#include<bits/stdc++.h>
#include<cstdlib>
#include<fstream>
#include<string>
#include<cstdio>
#include<map>
#include<conio.h>
#include<stdio.h>
#include<climits>

using namespace std;

#include "Pass1.cpp"

ofstream obj,lst,mod;
ifstream intm;
int curr_block_num;
string object_code;
void modify_object_file()
{
   ifstream fin;
   fin.open("modification.txt");
   string s;
   while(true)
   {
       getline(fin,s);
       if(s=="") break;
       obj<<s<<endl;
   }
   //fin.close();
}

bool imm,ind;

void input(string a[])
{
    int i;
    for(i=0;i<6;++i)
        getline(intm,a[i]);
    cout<<"\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n";
    cout<<"do you want to execute the instruction???\n1.'y' for yes\n2.'n' for NO skip displaying current instruction\n";
    cout<<"\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n";
    char c;
    cin>>c;
    if(c=='y')
    {
	cout<<"Input for line: "<<a[0]<<endl;
    for(i=1;i<6;++i)
        cout<<a[i]<<"    ";
    cout<<"\n";
	}
}

void assemble(string[],char);
string gen_code(string[]);

string text_s="",text_e="";
int text_length=0,base=INT_MAX;

void ClearScreen()
    {
    int n;
    for (n = 0; n < 6; n++)
      printf( "\n\n\n\n\n\n\n" );
    }
int main()
{
    run();
    ClearScreen();
    string a[6];
    char ch;
    hexa start;
    if(error_flag)
    {
        cout<<"Errors encountered! Listing file not prepared!"<<endl;
        cout<<"Have a look at the error file to know more!"<<endl;
        exit(1);
    }
    cout<<"\n\n\n $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";
    cout<<"\n\n  [[  MENU DRIVEN EXECUTION OF TWO   PASS  ASSEMBLER  \n";
    cout<<"\n\n\n $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n";
    intm.open("intermediate.txt");
    obj.open("object.txt");
    lst.open("list.txt");
    mod.open("modification.txt");
    lst<<"Line\tLoc   Block\t\tSource Statement\t\tObject Code"<<endl;
    lst<<"----------------------------------------------------------------"<<endl<<endl;
    input(a);
    curr_block="DEFAULT";
    curr_block_num=0;
    int xy=0;
    string STRING;
		ifstream infile;
		ifstream lsf;
do
{
    cout<<"\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n";
    cout<<"\n\n1.display instruction details\n2.display current symtab\n3.exit\n";
    cout<<"\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n";
    cin>>xy;
switch(xy)
{
	case 1:
    while(a[1]=="$")
    {
        lst<<a[0]<<"\t\t "<<a[2]<<endl;
        input(a);
    }
    if(a[2]=="START")
    {
        lst<<a[0]<<"\t"<<extendTo(4,a[4])<<"  "<<curr_block_num<<"\t\t"<<a[1]<<"\t\t"<<a[2]<<"\t\t"<<a[3]<<endl;
        obj<<"H^";
        int i;
        for(i=0;i<a[1].length();++i)
            obj<<a[1][i];
        for(;i<6;++i)
            obj<<" ";
        string temp=find_block(block_num-1);
        hexa len;
        len=toHex(toDec(BLOCK[temp].address)+toDec(BLOCK[temp].length));
        obj<<"^"<<extendTo(6,a[3])<<"^"<<extendTo(6,len)<<endl;
        start=a[3];
    }
    else
    {
        error_flag=1;
        error<<"Intermediate File has no start!"<<endl;
    }
    while(true)
    {
        input(a);
        if(a[1]=="$")
        {
            lst<<a[0]<<"\t\t "<<a[2]<<endl;
            continue;
        }
        if(a[2]=="END")
        {
            lst<<a[0]<<"\t\t\t\t\t\t"<<a[2]<<"\t\t"<<a[3]<<endl;
            if(text_length>0)
            {
                obj<<text_s<<"^"<<extendTo(2,toHex(text_length/2))<<text_e<<endl;
                cout<<"!!"<<endl;
            }
            text_length=0;
            text_s="";
            text_e="";
            modify_object_file();
            obj<<"E^"<<extendTo(6,start)<<endl;
            break;
        }
       // cout<<a[2]<<endl;
       //cout<<"wait assembling the program  ######\n";
       //sleep(2);
       int xz=0;
       assemble(a,'n');

        cout<<"\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n";
        cout<<"1.displaying opcode\n2.generated object code\n3.OR both opcode and object code\n4.display listed table\n5.exit\n";
        cout<<"\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n";
        //cin>>xz;
        switch(xz)
        {
        	case 1:
        	assemble(a,'n');
        	cout<<"\n\ndisplaying current opcode ::  -->>   ";
        	cout<<"opcode: "<<a[2]<<"\n";
        	break;
        	case 2:
        	assemble(a,'n');
        	cout<<"displaying generated object code :: -->>   ";
			cout<<"object code of "<<a[2]<<" is "<<object_code<<"\n";
			break;
			case 3:
				assemble(a,'b');
				break;
			case 4:
    		cout<<"displaying current listed table :: -->>\n";
			lsf.open ("list.txt");
        	while(!lsf.eof() )// To get you all the lines.
        	{
	        	getline(lsf,STRING); // Saves the line in STRING.
	        	cout<<STRING<<"\n"; // Prints our STRING.
       	 	}
        	lsf.close();
    		break;
		}

       // cin>>ch;
    }
    if(error_flag)
    {
        cout<<"Errors encountered! Listing file not prepared!"<<endl;
        cout<<"Have a look at the error file to know more!"<<endl;
    }
    else
    {
        cout<<"INPUT FILE ASSEMBLED SUCCESSFULY!!"<<endl;
    }
    break;
    case 2:
    	cout<<"displaying symbol table\n";

		infile.open ("symbol.txt");
        while(!infile.eof() )// To get you all the lines.
        {
	        getline(infile,STRING); // Saves the line in STRING.
	        cout<<STRING<<"\n"; // Prints our STRING.
        }
		infile.close();
    	break;

    case 3:
    	break;
}
}while(xy!=3);
}

void assemble(string a[],char xyz)
{

    hexa loc_ctr;
    int format;
    if(a[2]=="USE")
    {
        curr_block=a[3];
        curr_block_num=BLOCK[curr_block].num;
        lst<<a[0]<<"\t0000  "<<curr_block_num<<"\t\t\t"<<a[2]<<"\t\t"<<a[3]<<endl;
        if(text_length>0) obj<<text_s<<"^"<<extendTo(2,toHex(text_length/2))<<text_e<<endl;
        text_s="";
        text_e="";
        text_length=0;
        return;
    }
    if(a[2]=="RESB"||a[2]=="RESW")
    {
        lst<<a[0]<<"\t"<<extendTo(4,a[4])<<"  "<<curr_block_num<<"\t\t"<<a[1]<<"\t"<<a[2]<<"\t\t"<<a[3]<<endl;
        if(text_length>0) obj<<text_s<<"^"<<extendTo(2,toHex(text_length/2))<<text_e<<endl;
        text_s="";
        text_e="";
        text_length=0;
        return;
    }
    imm=ind=false;
    object_code=gen_code(a);
    if(xyz=='b')
    	cout<<"object code for "<<a[2]<<":::"<<object_code<<endl;
    if(a[2]=="BYTE"||a[2]=="WORD")
        lst<<a[0]<<"\t"<<extendTo(4,a[4])<<"  "<<curr_block_num<<"\t\t"<<a[1]<<"\t"<<a[2]<<"\t\t"<<a[3]<<endl;
    else
    {
        if(imm)      lst<<a[0]<<"\t"<<extendTo(4,a[4])<<"  "<<curr_block_num<<"\t\t"<<a[1]<<"\t\t"<<a[2]<<"\t\t#"<<a[3]<<"\t\t"<<object_code<<endl;
        else if(ind) lst<<a[0]<<"\t"<<extendTo(4,a[4])<<"  "<<curr_block_num<<"\t\t"<<a[1]<<"\t\t"<<a[2]<<"\t\t@"<<a[3]<<"\t\t"<<object_code<<endl;
        else         lst<<a[0]<<"\t"<<extendTo(4,a[4])<<"  "<<curr_block_num<<"\t\t"<<a[1]<<"\t\t"<<a[2]<<"\t\t"<<a[3]<<"\t\t"<<object_code<<endl;
    }
    if(text_s=="")
    {
        loc_ctr=toHex(toDec(BLOCK[curr_block].address)+toDec(a[4]));
        text_s="T^"+extendTo(6,loc_ctr);
        text_e="^"+object_code;
        text_length=object_code.length();
    }
    else if(text_length+object_code.length()>60)
    {
        obj<<text_s<<"^"<<extendTo(2,toHex(text_length/2))<<text_e<<endl;
        loc_ctr=toHex(toDec(BLOCK[curr_block].address)+toDec(a[4]));
        text_s="T^"+extendTo(6,loc_ctr);
        text_e="^"+object_code;
        text_length=object_code.length();
    }
    else
    {
        text_e+="^"+object_code;
        text_length+=object_code.length();
    }
    if(a[2]=="LDB")
    {
        base=toDec(SYMTAB[a[3]].address)+toDec(BLOCK[SYMTAB[a[3]].block].address);
    }
}

string gen_code(string a[])
{
    string ob1,ob2,ob3;
    hexa operand_addr,prgm_ctr;
    int format;
    if(a[2]=="BYTE")
    {
        int i;
        ob1="";
        if(a[3][0]=='X')
            for(i=2;i<a[3].length()-1;++i) ob1+=a[3][i];
        else //a[3][0]=='C'
            for(i=2;i<a[3].length()-1;++i)
                ob1+=toHex((int)a[3][i]);
        return ob1;
    }
    if(a[2]=="WORD")
    {
        ob1=toHex(atoi(a[3].c_str()));
        return ob1;
    }
    if(a[2]=="RSUB")
    {
        ob1="4F0000";
        return ob1;
    }
    if(a[2]=="+RSUB")
    {
        ob1="4F000000";
        return ob1;
    }
    if(a[2][0]=='+')
    {
        format=4;
        a[2]=a[2].substr(1);
    }
    else
        format=OPTAB[a[2]].format;
    if(format==1)
    {
        cout<<"Format 1"<<endl;
        ob1=OPTAB[a[2]].opcode;
        return ob1;
    }
    if(format==2)
    {
        cout<<"Format 2"<<endl;
        ob1=OPTAB[a[2]].opcode;
        if(a[3].length()==3)
        {
            ob2=toHex(reg_num(a[3][0]));
            if(isdigit(a[3][2]))  ob2=ob2+toHexDig(a[3][2]-1);
            else
            {
                ob2=ob2+toHexDig(reg_num(a[3][2]));
            }
        }
        else  //a[3].length==1
        {
            if(isdigit(a[3][0]))
            {
                ob2=toHex(atoi(a[3].c_str()))+"0";
                cout<<"isdigit! ob2: "<<ob2<<endl;
            }
            else
            {
                cout<<toHex(reg_num(a[3][0]))<<endl;
                ob2=toHex(reg_num(a[3][0]))+"0";
                cout<<"Not Isdigit! ob2: "<<ob2<<endl;
            }
        }
        cout<<"a[2]: "<<a[2]<<" ob1:"<<ob1<<"ob2:"<<ob2<<endl;
        return (ob1+extendTo(2,ob2));
    }
    if(format==3)
    {
        cout<<"Format 3"<<endl;
        cout<<a[2]<<endl;
        ob1=OPTAB[a[2]].opcode;
        if(a[3][0]=='#')
        {
            imm=true;
            cout<<"Immediate!"<<endl;
            ob1=toHex(toDec(ob1)+1);
            a[3]=a[3].substr(1);
            if(isdigit(a[3][0]))
            {
                ob2="0";
                ob3=toHex(atoi(a[3].c_str()));
                return extendTo(2,ob1)+ob2+extendTo(3,ob3);
            }
            //cout<<"ob1: "<<ob1<<endl;
        }
        else if(a[3][0]=='@')
        {
            ind=true;
            cout<<"Indirect!"<<endl;
            ob1=toHex(toDec(ob1)+2);
            a[3]=a[3].substr(1);
        }
        else
            ob1=toHex(toDec(ob1)+3);
        ob2="0";
        bool x=false;
        if(a[3][a[3].length()-2]==',')
        {
            x=true;
            ob2=toHex(toDec(ob2)+8);
            a[3]=a[3].substr(0,a[3].length()-2);
        }
        //cout<<"ob1:"<<ob1<<"ob2:"<<ob2<<endl;
        prgm_ctr=toHex(toDec(BLOCK[curr_block].address)+toDec(a[5]));
        operand_addr=toHex(toDec(SYMTAB[a[3]].address)+toDec(BLOCK[SYMTAB[a[3]].block].address));
        cout<<"prgm_ctr: "<<prgm_ctr<<" operand_addr: "<<operand_addr<<endl;
        if(x) a[3]+=",X";
        int disp=toDec(operand_addr)-toDec(prgm_ctr);
        cout<<"disp: "<<disp<<endl;
        if(disp>=-2048 && disp<2048)
        {
            ob2=toHex(toDec(ob2)+2);
            if(disp<0) disp+=4096;
            ob3=toHex(disp);
            return extendTo(2,ob1)+extendTo(1,ob2)+extendTo(3,ob3);
        }
        disp=toDec(operand_addr)-base;
        if(disp>=-2048 && disp<2048)
        {
            ob2=toHex(toDec(ob2)+4);
            if(disp<0) disp+=4096;
            ob3=toHex(disp);
            return extendTo(2,ob1)+extendTo(1,ob2)+extendTo(3,ob3);
        }
        //If still here, means overflow
        error_flag=1;
        error<<"Line "<<a[0]<<": Overflow detected"<<endl;
    }
    if(format==4)
    {
        ob1=OPTAB[a[2]].opcode;
        if(a[3][0]=='#')
        {
            imm=true;
            ob1=toHex(toDec(ob1)+1);
            a[3]=a[3].substr(1);
            if(isdigit(a[3][0]))
            {
                ob2="0";
                ob3=toHex(atoi(a[3].c_str()));
                a[2]="+"+a[2];
                return ob1+ob2+extendTo(5,ob3);
            }
        }
        else if(a[3][0]=='@')
        {
            ind=true;
            ob1=toHex(toDec(ob1)+2);
            a[3]=a[3].substr(1);
        }
        else
            ob1=toHex(toDec(ob1)+3);
        bool x=false;
        ob2="1";
        if(a[3][a[3].length()-2]==',')
        {
            x=true;
            ob2=toHex(toDec(ob2)+8);
            a[3]=a[3].substr(0,a[3].length()-2);
        }
        operand_addr=toHex(toDec(SYMTAB[a[3]].address)+toDec(BLOCK[SYMTAB[a[3]].block].address));
        if(x) a[3]+=",X";
        ob3=operand_addr;
        a[2]="+"+a[2];
        hexa loc_ctr=toHex(toDec(BLOCK[curr_block].address)+toDec(a[4])+1);
        mod<<"M^"<<extendTo(6,loc_ctr)<<"^05"<<endl;
        return extendTo(2,ob1)+extendTo(1,ob2)+extendTo(5,ob3);
    }
}

```

---
### Listing and Object Code

```assemble
Line	Loc   Block		Source Statement		Object Code
----------------------------------------------------------------

5	0000  0		FIBO		START		0
10	0000  0		FIRST		LDT		#1		750001
15	0003  0				LDS		#10		6D000A
20	0006  0				+JSUB		RDREC		4B100011
25	000A  0				+JSUB		WRREC		4B10002D
30	000E  0		LENGTH	RESW		1
35		 .
40		 . SUBROUTINE RDREC
45		 .
50	0011  0		RDREC		CLEAR		A		B400
55	0013  0		RLOOP		TD		INPUT		E32016
60	0016  0				JEQ		RLOOP		332FFA
65	0019  0				RD		INPUT		DB2010
70	001C  0				COMPR		A,T		A005
75	001E  0				JLT		RLOOP		3B2FF2
80	0021  0				COMPR		A,S		A004
85	0023  0				JGT		RLOOP		372FED
90	0026  0				STA		LENGTH		0F2FE5
95	0029  0				RSUB				4F0000
100	002C  0		INPUT	BYTE		X'F1'
105		 .
110		 .SUBROUTINE WDREC
115		 .
120	002D  0		WRREC		LDX		#0		050000
125	0030  0				LDS		#1		6D0001
130	0033  0				LDA		#0		010000
135	0036  0				LDT		LENGTH		772FD5
140	0039  0		WLOOP		TD		OUTPUT		E32019
145	003C  0				JEQ		WLOOP		332FFA
150	003F  0				WD		OUTPUT		DF2013
155	0042  0				ADDR		S,A		9040
160	0044  0				STA		VALUE1		0F200F
165	0047  0				STS		VALUE2		7F200F
170	004A  0				LDA		VALUE2		03200C
175	004D  0				LDS		VALUE1		6F2006
180	0050  0				TIXR		T		B850
185	0052  0				JLT		WLOOP		3B2FE4
190	0055  0		OUTPUT	BYTE		X'05'
195	0056  0		VALUE1	RESW		1
200	0059  0		VALUE2	RESW		1
205						END		FIRST
```
---
#### Object Code

```
H^FIBO  ^000000^00005C
T^000000^0E^750001^6D000A^4B100011^4B10002D
T^000011^1C^B400^E32016^332FFA^DB2010^A005^3B2FF2^A004^372FED^0F2FE5^4F0000^F1
T^00002D^1D^050000^6D0001^010000^772FD5^E32019^332FFA^DF2013^9040^0F200F^7F200F
T^00004A^0C^03200C^6F2006^B850^3B2FE4^05
M^000007^05
M^00000B^05
E^000000
```
