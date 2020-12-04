#include <iostream>
#include <queue>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

int binary_to_decimal(string in)
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
class _code{
    public:
    char character;
    string code;
    _code(char c,string s){
        this->character=c;
        this->code=s;
    }
};
class _singlechar{
    public:
    char data;
    int freq;
    _singlechar(char data){
        this->data=data;
        this->freq=1;
    }
    void increment(){
        this->freq++;
    }
};
class _node{
    public:
    char data;
    int freq;
    _node* left;
    _node* right;
    _node(char data,int freq){
        this->data=data;
        this->freq=freq;
        this->left=NULL;
        this->right=NULL;
    }
};

struct compare{
    bool operator()(_node*l,_node*r){
        return(l->freq > r->freq);
    }
};

void printtree(_node* root,string code,vector<_code*> &coding){
    if(root==NULL){
        return;
    }
    if(root->data!='#'){
        //cout<<root->data<<" : "<< code <<endl;
        coding.push_back(new _code(root->data,code));
    }
    printtree(root->left, code+'0',coding);
    printtree(root->right,code+'1',coding);
}
void huffmantree(vector<_code*> &coding,vector<_singlechar*> &a,int size){
    //class _node{ char data; int freq; _node* left; _node* right;}
    _node* left,*right,*top;
    priority_queue<_node*, vector<_node*>, compare> q ;
    for(int i=0;i<size;i++){
        q.push(new _node(a[i]->data,a[i]->freq));
    }
   
    while(q.size()!=1){
        left=q.top();
        q.pop();
        right=q.top();
        q.pop();
        top=new _node('#',left->freq+right->freq);
        top->left=left;
        top->right=right;
        q.push(top);
    }
     printtree(q.top(),"",coding);

}
void ins(vector<_singlechar*> &a,char b){
    if(a.empty()){
        a.push_back(new _singlechar(b));
    }
    else{
        auto i=a.begin();
        int flag=0;
        while(i!=a.end()){
            if((*i)->data>=b){
                if((*i)->data==b){
                    ((*i)->freq)++;
                }
                else{
                    a.insert(i,new _singlechar(b));
                }
                flag=1;
                break;
            }
            i++;
        }
        if(flag==0){
            a.push_back(new _singlechar(b));
        }
    }
}
void compress(){
    //class _singlechar{public:char data;int freq;_singlechar(char data){this->data=data;this->freq=1;}void increment(){this->freq++;}}
    //vector to store unique characters along with their frequency 
    vector<_singlechar*> a;
    //string str
    //cin>>str;
    //int size = str.size();
    
    char c;
    ifstream read;
    read.open("input_string.txt");
    if(read.fail()){
        cout<<"couldn't open file"<<endl;
    }
    else{
        while(read.get(c)){
            ins(a,c);
        }
    }
    read.close();
    //class _code{public:char character;string code;_code(char c,string s){this->character=c;this->code=s;}};
    //vector to store characters along with their coding
    vector<_code*> coding;
    huffmantree(coding,a,a.size()); 
    /*
    for(auto i=coding.begin();i!=coding.end();i++){
        cout<<(*i)->character<<"writing"<<(*i)->code<<endl;
        }
    */
    //auto i=coding.begin();
    
    /*
    while(i!=coding.end()){
        write<<(*i)->character<<" "<<(*i)->code<<endl;
        i++;
    }
    write<<'#'<<endl;
    */
    //int j=0;
    //ifstream read;
    /*
    vector<bool> encoded_data;
    cout<<encoded_data.max_size()<<endl;
    read.open("input_string.txt");
    int count1=0,count2=0;
    while(read.get(c)){
        auto i=coding.begin();
        while(i!=coding.end()){
            if(c==(*i)->character){
                string temp = (*i)->code;
                int size = temp.size();
                int j=0;
                while(j<size){
                    if(temp[j]=='0'){
                        encoded_data.push_back(0);
                    }
                    else{
                        encoded_data.push_back(1);
                    }
                    j++;
                }
                break;
            }
            i++;
            count1++;
        }
    }
    cout<<encoded_data.size()<<endl;
    read.close();
    */
    ofstream out_file;
    ifstream in_file;
    in_file.open("input_string.txt",ios::in);
    out_file.open("output.bin",ios::binary|ios::out);
    string in ="",s="";
     //the first byte saves the size of the vector
    //in+=(char)coding.size();
    in+=coding.size();
    for(auto i=coding.begin();i!=coding.end();i++){
        in+=(int)(*i)->character;
        //set the codes with a fixed 128-bit string form[000¡­¡­1 + real code]
        //'1' indicates the start of huffman code
        s.assign(127-((*i)->code).size(),'0');
        s+='1';
        s.append((*i)->code);
        in+=(char)binary_to_decimal(s.substr(0,8));
        for (int i = 0; i < 15; i++)
		{//cut into 8-bit binary codes that can convert into saving char needed for binary file
			s = s.substr(8);
			in += (char)binary_to_decimal(s.substr(0, 8));
		}
    }
    s.clear();
    char b;
    in_file.get(b);
    while(!in_file.eof()){
        //convert char by char
        auto i=coding.begin();
        while((*i)->character!=b){
            i++;
        }
        s+=((*i)->code);
        while(s.size()>8){
            //chop into 8 bits
            in+=(char)binary_to_decimal(s.substr(0,8));
            s=s.substr(8);
        }
        in_file.get(b);
    }
    int count = 8-s.size();
    if(s.size()<8){
        s.append(count,'0');
    }
    in+=(char)binary_to_decimal(s);
    in+=(char)count;
    //cout<<in<<endl;
    //cout<<in.size()<<endl;
    out_file.write(in.c_str(),in.size());
    in_file.close();
    out_file.close();
    cout<<"Compression successful"<<endl;
    /*
    int Bit_Counter = 0;
	uint8_t Packed_Byte = 0;
    
	for(int i = 0; i < encoded_data.size(); ++i){
		if(encoded_data[i] == 1){
			Packed_Byte |= 1;
		}
		if(i < encoded_data.size()-1){
			Packed_Byte <<= 1;
		}
		++Bit_Counter;
		if(Bit_Counter == 8){
			write << Packed_Byte;
			Bit_Counter = 0;
            Packed_Byte = 0;
		}
	}
    write << Packed_Byte;
    write.close();
    */
}
char search(vector<_code*> &coding,string binary){
    auto i=coding.begin();
    while(i!=coding.end()){
        if((*i)->code==binary){
            break;
        }
        i++;
    }
    return (*i)->character;
}

void decode(){
    //class _code{ char character; string code }
    ifstream in_file;
    in_file.open("output.bin",ios::in|ios::binary);
    unsigned char size;
    in_file.read(reinterpret_cast<char*>(&size),1);

    //vector to store characters along with their decoding
    vector<_code*> decode;
    for(int i=0;i<size;i++){
        char a_code;
        unsigned char h_code_c[16];
        in_file.read(&a_code,1);
        
        in_file.read(reinterpret_cast<char*>(h_code_c),16);
        string h_code_s="";
        for(int i=0;i<16;i++){
            //obtain original 128 bit-binary string
            h_code_s+=decimal_to_binary(h_code_c[i]);
        }
        int j=0;
        while(h_code_s[j]=='0'){
            //delete the added '0000iii1' to get the real huffman code
            j++;
        }
        h_code_s=h_code_s.substr(j+1);
        //cout<<a_code<<"reading"<<h_code_s<<endl;
        decode.push_back(new _code(a_code,h_code_s));
    }
    in_file.close();
    in_file.open("output.bin",ios::in|ios::binary);
    fstream out_file;
    out_file.open("decoded_text.txt",ios::out);
    //unsigned char size;
    //get number of codings
    in_file.read(reinterpret_cast<char*>(&size),1);
    //jump to the last one byte to get the number of '0' append to the string at last
    in_file.seekg(-1,ios::end);
    char count0;
    in_file.read(&count0,1);
    //jump to the position where text starts
    in_file.seekg(1+17*size,ios::beg);
    vector<unsigned char> text;
    unsigned char textseg;
    in_file.read(reinterpret_cast<char*>(&textseg),1);
    while(!in_file.eof()){
        //get the text byte by byte using unsigned char
        text.push_back(textseg);
        in_file.read(reinterpret_cast<char*>(&textseg),1);
    }
    string path;
    string complete="";
    for(int i=0;i<text.size()-1;i++){
        //translate the huffman code
        path=decimal_to_binary(text[i]);
        if(i==text.size()-2){
            path = path.substr(0,8-count0);
        }
        complete=complete+path;
    }
    //cout<<complete<<endl;
    string temp="",to_write="";
    while(complete.size()>0){
        temp+=complete[0];
        if(complete.size()==1){
            complete="";
        }
        else{
            complete=complete.substr(1);
        }
        int flag=0;
        auto i=decode.begin();
        while(i!=decode.end()){
            if(temp==(*i)->code){
                flag=1;
                break;
            }
            i++;
        }
        if(flag==1){
            to_write+=(*i)->character;
            temp="";
        }
        
    }
    //cout<<to_write<<endl;
    out_file<<to_write;
    in_file.close();
    out_file.close();
    cout<<"Decompression successful"<<endl;

    /*
    char c;
    string str="",line;
    int size;

    ifstream read;
    read.open("output.txt");
    while(read){
        getline(read,line);
        //cout<<line<<endl;
        if(line=="#"){
            break;
        }
        str="";
        charac=line[0];
        size=line.size();
        for(int i=2;i<size;i++){
            str+=line[i];
        }
        decode.push_back(new _code(charac,str));   
    }
    string binary;

    ofstream write;
    write.open("decoded.txt");
    while(read){
        read>>binary;
        //cout<<letter<<" ";
        write<<search(decode,binary);
    }
    read.close();
    write.close();
    */
    /*
    for(auto i=decode.begin();i!=decode.end();i++){
        cout<<(*i)->character<<" "<<(*i)->code<<endl;
    }
    */
}

int main(){
    int choice=0;
    while(choice!=-1){
        cout<<"1 to compress"<<endl<<"2 to decode"<<endl<<"-1 to exit"<<endl;;
        cin>>choice;
        switch(choice){
            case 1:
            compress();
            break;
            case 2:
            decode();
            break;
            case -1:
            break;
            default:
            cout<<"Enter a choice"<<endl;
        }
    }
    return 0;
}