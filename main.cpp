#include "GenStack.h"

int main(int argc, char const *argv[]) {
  if(argc<2){ //make sure valid command line parameters
    cout<<"invalid command line parameters."<<endl;
    return 1;

  }
string fName;
fName = argv[1];

GenStack<char> *checkStack = new GenStack<char>(128);
checkStack->checkDelimiters(fName);

bool anotherFile = true;
char firstChoice;
while(anotherFile){
  cout<<endl;
  cout<<"would you like to check another file?"<<endl;
  cout<<"enter Y for yes anything else for no"<<endl;
  // cout<<endl;
  cin>>firstChoice;
  firstChoice=toupper(firstChoice);

  if(firstChoice=='Y'){
    cout<<"enter the file name: "<<endl;
    string nextFile;
    cin>>nextFile;
    cout<<endl;
    checkStack->checkDelimiters(nextFile);
  }
  else{
    anotherFile = false;
  }


}

return 0;
}
