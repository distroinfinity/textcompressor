#include <iostream>
#include <queue>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

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
        cout<<(*i)->character<<" "<<(*i)->code<<endl;
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
    vector<bool> encoded_data;
    read.open("input_string.txt");
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
        }
    }
    cout<<encoded_data.size()<<endl;
    read.close();
    ofstream write;
    write.open("output.bin",ios::binary|ios::out);
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
		}
	}
    write << Packed_Byte;
    write.close();
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
    //vector to store characters along with their decoding
    vector<_code*> decode;
    char charac;
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
            cout<<"test1"<<endl;
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