#include <iostream>
#include <queue>
using namespace std;
class node{
    public:
    char data;
    int freq;
    node* left;
    node* right;
    node(char data,int freq){
        this->data=data;
        this->freq=freq;
        this->left=NULL;
        this->right=NULL;
    }
};

struct compare{
    bool operator()(node*l,node*r){
        return(l->freq > r->freq);
    }
};

void printtree(node* root,string code){
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
    node* left,*right,*top;
    priority_queue<node*, vector<node*>, compare> q ;
    for(int i=0;i<size;i++){
        q.push(new node(data[i],freq[i]));
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
        top=new node('#',left->freq+right->freq);
        top->left=left;
        top->right=right;
        q.push(top);
    }
    //cout<<"t3 "<<q.top()->freq<<endl;
    printtree(q.top(),"");

}

int main(){
   
   char arr[]={'a','b','c','d','e','f'};
   int freq[]={5,9,12,13,16,45};
   int size = sizeof(arr)/sizeof(arr[0]);
   huffmantree(arr,freq,size); 

   return 0;
}