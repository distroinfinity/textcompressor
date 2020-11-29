#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int main(){
    string line;
    /*
    ofstream write;
    
    write.open("writing.txt");
    while(write){
        getline(cin,line);
        if(line=="-1"){
            break;
        }
    write<<line<<endl;
    }
    write.close();
    */
   ifstream read;
   read.open("writing.txt");
   while(read){
       getline(read,line);
       cout<<line;
       cout<<endl;
   }
   read.close();
   return 0;
}