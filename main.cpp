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
int main(){
    //class _singlechar{ char data; int freq }
    //vector to store unique characters along with their frequency 
    vector<_singlechar*> a;
    string str;
    cin>>str;
    int size = str.size();
    a.push_back(new _singlechar(str[0]));
    for(int i=1;i<size;i++){
        ins(a,str[i]);
    }
    //class _code{ char character; string code }
    //vector to store characters along with their encoding
    vector<_code*> coding;
    huffmantree(coding,a,a.size()); 
    /*
    for(auto i=coding.begin();i!=coding.end();i++){
        cout<<(*i)->character<<" "<<(*i)->code<<endl;
        }
    */
    cout<<"Please wait while we compress your file."<<endl;
    auto i=coding.begin();
    ofstream write;
    write.open("output.txt");
    while(i!=coding.end()){
        write<<(*i)->character<<" "<<(*i)->code<<endl;
        i++;
    }
    write<<'#'<<endl;
    int j=0;
    while(j<size){
        auto i=coding.begin();
        while(i!=coding.end()){
            if(str[j]==(*i)->character){
                write<<(*i)->code<<" ";
                break;
            }
            i++;
        }
        j++;
    }
    write.close();
    cout<<"File compression successful"<<endl;
    return 0;
}