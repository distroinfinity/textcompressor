#include <iostream>
#include <queue>
#include<vector>
using namespace std;
class _singlechar{
    public:
    char data;
    int freq;
    _singlechar(char data){
        this->data=data;
        this->freq=0;
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

void printtree(_node* root,string code){
    //cout<<code<<" t4"<<endl;
    if(root==NULL){
        return;
    }
    //cout<<"t5"<<endl;
    if(root->data!='#'){
        cout<<root->data<<" : "<< code <<endl;
    }
    //cout<<"t6"<<endl;
    printtree(root->left, code+'0');
    printtree(root->right,code+'1');
}

void huffmantree(char data[],int freq[],int size){
    //cout<<"t1"<<endl;
    _node* left,*right,*top;
    priority_queue<_node*, vector<_node*>, compare> q ;
    for(int i=0;i<size;i++){
        q.push(new _node(data[i],freq[i]));
    }
    /*
    for(int i=0;i<size;i++){
        cout<<q.top()->data<<" "<<q.top()->freq;
        q.pop();
    }
    */
    //cout<<"t2"<<endl;
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
    //cout<<"t3 "<<q.top()->freq<<endl;
    printtree(q.top(),"");

}
void ins(vector<_singlechar*> &a,char b){
    auto i=(a.begin()+1);
    cout<<(*i)->data;
    while(i!=a.end()){
        if((*i)->data>b){
            break;
        }
        i++;
    }
    if((*(i-1))->data==b){
        (*(i-1))->freq++;
    }
    else{
        a.insert(i,new _singlechar(b));
    }
    /*
    for(auto i=a.begin();i!=a.end();i++){
       cout<<(*i)->data<<" : "<<(*i)->freq<<endl;
    }
    */
   

}
int main(){
   vector<_singlechar*> a;
   //vector<int> b;
   //b.insert(b.begin(),1);
   string str;
   cin>>str;
   int size = str.size();
   a.push_back(new _singlechar(str[0]));
   for(int i=1;i<size;i++){
       ins(a,str[i]);
   }
   for(auto i=a.begin();i!=a.end();i++){
       cout<<(*i)->data<<" : "<<(*i)->freq<<endl;
   }
   /*
   char arr[]={'a','b','c','d','e','f'};
   int freq[]={5,9,12,13,16,45};
   huffmantree(arr,freq,size); 
*/
   return 0;
}