#include <bits/stdc++.h>
using namespace std;

string commandExecute(const char* command){
  FILE* f=popen(command,"r");
  if(!f) return NULL;
  char buffer[128];
  string result="";
  while(!feof(f)){
    if(fgets(buffer,128,f)!=NULL){
      result+=buffer;
    }
  }
  return result;
}
int main(void){
  bool exit=false;
  string code;
  //system("cd SearchFolder\npwd");
  while(!exit){
    cout<<"$ ";
    getline(cin,code);

    if(code[0]=='c' && code[1]=='d'){
      code=code+"\npwd";
    }
    const char* cmd=code.c_str();
    //system(cmd);
    cout<<commandExecute(cmd)<<endl;
    if(strcmp(cmd,"exit")==0) exit=true;
  }
}
