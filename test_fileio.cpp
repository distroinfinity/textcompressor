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
   read.open("C:\\My stuff\\work\\DS Project\\output.txt");
   while(read){
       getline(read,line);
       if(line=="#"){
           break;
       }
       cout<<line;
       cout<<endl;
   }
   while(read>>line){
       cout<<line<<" ";
   }
   read.close();
   return 0;
}