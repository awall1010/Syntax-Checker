#include <iostream>
#include <unistd.h>
#include <fstream>
using namespace std;

template<class T>
class GenStack{

public:
  GenStack();//deffault constructor
  GenStack(int maxSize); //overloaded constructor
  ~GenStack(); //destructor
  //functions
  void push(T data);//insert
  T pop();//delete
  //helper functions
  bool isFull();
  bool isEmpty();
  T peek();
  void checkDelimiters(string fileName);
  int m_size;//max size of myStack
  int top; //variable to keep track of indices representing the top of our stack
  T *myArray; //pointer to declare at runtime

};


template <class T> //deffault
GenStack<T>::GenStack(){
  myArray = new T[128];
  m_size = 128;
  top = -1;

}

//overloaded constructor
template<class T>
GenStack<T>::GenStack(int maxSize){
  myArray = new T[maxSize];
  m_size = maxSize;
  top = -1;

}

template<class T>
void GenStack<T>::push(T data){
  //check if full before inserting
  if(isFull()==true){ //if full create new
    T* tempArray= new T[++m_size];
    tempArray = myArray;
    myArray = new T[++m_size];
    for(int i = 0;i<(m_size-1);++i){
      myArray[i]=tempArray[i];
    }
    delete tempArray;
  }
  myArray[++top] = data;
}

template<class T>
T GenStack<T>::pop(){

  return myArray[top--];
}


template<class T>
T GenStack<T>::peek(){
  return myArray[top];
}

template<class T>
bool GenStack<T>::isFull(){

  return (top == m_size-1);
}

template<class T>
bool GenStack<T>::isEmpty(){
  return (top==-1);
}

template<class T>
GenStack<T>::~GenStack(){
  delete myArray;
}

template<class T>
void GenStack<T>::checkDelimiters(string fileName){ //check delimiters
ifstream inFS;
int lineCount = 0;
string content;
int stackSize = 0;
GenStack<char> *myStack = new GenStack<char>(128); //initialize


inFS.open(fileName);

if(!inFS.is_open()){
  cout<<"couldn't open file. "<<endl;
}

while(!inFS.eof()){
  inFS>> content;
  if(!inFS.fail()){
    lineCount++;
    for(int i = 0;i<content.size();++i){
      if(content[i]=='{'  || content[i]=='['  ||content[i]=='(' ){ //add to stack if open
        myStack-> push(content[i]);
      }
      else if(content[i]=='}'){ //check if closing delimiter
        //peek and compare
        if(myStack->peek() =='{' ) { //if it closes pop it off
          myStack->pop();

        }else{ //tell it what its missing
          cout<<"Expecting delimiter of type '{' on line: "<<lineCount<<endl;
          }
      }
      else if(content[i]==']'){
        if(myStack->peek() =='['){
          myStack->pop();
        }
        else{
          cout<<"Expecting delimiter of type '[' on line: "<<lineCount<<endl;
        }
      }
      else if(content[i]==')'){
        if( myStack->peek() =='('){
          myStack->pop();
        }
        else{
          cout<<"Expecting delimiter of type '(' on line: "<<lineCount<<endl;
        }
      }
  }
}
}
while(myStack->isEmpty()==false){ //tell every delimiter not dealt with
  cout<< "missing delimiter for "<<myStack->peek()<<endl;
  myStack->pop();
}

inFS.close();
delete myStack;
}
