// // #include <iostream>
// // #include <unistd.h>
// // #include <fstream>
// // using namespace std;
// //
// // class GenStack{
// // public:
// //   GenStack();//deffault constructor
// //   GenStack(int maxSize); //overloaded constructor
// //   ~GenStack(); //destructor
// //
// //   //functions
// //   void push(char data);//insert
// //   char pop();//delete
// //
// //   //helper functions
// //   bool isFull();
// //   bool isEmpty();
// //   char peek();
// //
// //   int m_size;//max size of myStack
// //   int top; //variable to keep track of indices representing the top of our stack
// //
// //
// //   char *myArray; //pointer to declare at runtime
// //
// //
// //
// //
// // };
//
//
//
// #include <iostream>
// #include <unistd.h>
// #include <fstream>
// using namespace std;
//
// template<typename T>
// class GenStack{
// public:
//   GenStack();//deffault constructor
//   GenStack(int maxSize); //overloaded constructor
//   ~GenStack(); //destructor
//
//   //functions
//   void push(T data);//insert
//   T pop();//delete
//
//   //helper functions
//   bool isFull();
//   bool isEmpty();
//   T peek();
//
//   int m_size;//max size of myStack
//   int top; //variable to keep track of indices representing the top of our stack
//
//
//   T *myArray; //pointer to declare at runtime
//
//
//
//
// };


#include <iostream>
#include <unistd.h>
#include <fstream>
using namespace std;

template<class T>
class GenStack{
  // int m_size;//max size of myStack
  // int top; //variable to keep track of indices representing the top of our stack
  // T *myArray; //pointer to declare at runtime


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


template <class T>
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

  myArray[++top] = data;
}

template<class T>
T GenStack<T>::pop(){
  //check if isEmpty before preceding to remove

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
void GenStack<T>::checkDelimiters(string fileName){
ifstream inFS;
int lineCount = 0;
string content;
int stackSize = 0;
GenStack<char> *myStack = new GenStack<char>(512);


inFS.open(fileName);

if(!inFS.is_open()){
  cout<<"couldn't open file. "<<endl;
}

while(!inFS.eof()){
  inFS>> content;
  if(!inFS.fail()){
    lineCount++;
    for(int i = 0;i<content.size();++i){
      if(content[i]=='{'  || content[i]=='['  ||content[i]=='(' ){
        myStack-> push(content[i]);
      }
      else if(content[i]=='}'){
        //peek and compare
        if(myStack->peek() =='{' ) {
          myStack->pop();

        }else{
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
while(myStack->isEmpty()==false){
  cout<< "missing delimiter for "<<myStack->peek()<<endl;
  myStack->pop();
}



inFS.close();
delete myStack;
}
