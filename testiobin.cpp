#include <bitset> 
#include <string> 
#include <iostream> 
#include<fstream>
#include <bitset>
#include<stdio.h>
using namespace std;

int binary_to_decimal(string& in)
{
	int result = 0;
	for (int i = 0; i < in.size(); i++)
		result = result * 2 + in[i] - '0';
	return result;
}

string decimal_to_binary(int in)
{
	string temp = "";
	string result = "";
	while (in)
	{
		temp += ('0' + in % 2);
		in /= 2;
	}
	result.append(8 - temp.size(), '0');													//append '0' ahead to let the result become fixed length of 8
	for (int i = temp.size() - 1; i >= 0; i--)												
	{
		result += temp[i];
	}
	return result;
}

int main() 
{ /*
  ofstream write;
  write.open("testbin.bin",ios::binary|ios::out);
  char a='i';
  write.write(&a,sizeof(char));
  write.close();
  */
string a="manu";
a+=1;
cout<<a;
 /*
 ifstream read;
  read.open("output.bin",ios::binary | ios::in);
   char textseg;
	read.read(reinterpret_cast(&textseg), 1);
  string temp = decimal_to_binary(textseg);
  cout<<temp<<endl;

  read.close();
 */ 
  return 0; 
}  