#include <bitset> 
#include <string> 
#include <iostream> 
#include<fstream>
#include <bitset>
#include<stdio.h>
using namespace std;
int main() 
{ 
  std::string bit_string = "110010"; 
  std::bitset<8> b1(bit_string);             // [0, 0, 1, 1, 0, 0, 1, 0] 
  //bitset<8> * a=&b1;
  // string from position 2 till end 
  std::bitset<8> b2(bit_string, 2);      // [0, 0, 0, 0, 0, 0, 1, 0] 
  
  // string from position 2 till next 3 positions 
  std::bitset<8> b3(bit_string, 2, 3);   // [0, 0, 0, 0, 0, 0, 0, 1] 
  //std::cout << b1 << '\n' << b2 << '\n' << b3 << '\n'; 
  
  ofstream write;
  write.open("testbin.bin",ios::binary | ios::out);
  //write.write(false,sizeof(bool));
  uint8_t t=00000000;
  char a ='i';
  string b= "0001";
  write<<a<<b;
  write<<t;
  //cout<<t;
  //int *a=&e;
  //int *b=&e;
  //FILE *p;
  //p=fopen("testbin.bin","wb");
  //fwrite(a,sizeof(bitset<8>),sizeof(a),p);
  //fwrite(b,1,sizeof(a),p); 
  write.close();

  return 0; 
}  