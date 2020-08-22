#include<bits/stdc++.h>
using namespace std ;
template <typename t >
class node
{
public:
    string key ;
    t value ;
    node<t> * next;
    node(string key , t val)
    {
        this->key =key ;
        value =val ;
    }
};
template <typename t >
class hash_table
{
    int cs ;
    int ts ;
    node<t> ** buckets ;
    void rehash()
    {
        node<t> ** old_buckets = buckets ;
        int old_ts =ts ;
        ts =ts*2 ;
        cs =0 ;
        buckets = new node<t>*[ts] ;
        for(int i=0;i< ts;i++){
            buckets[i] =NULL ;
        }
        for(int i=0;i< old_ts;i++){
            node<t> *temp =old_buckets[i] ;
            while(temp!=NULL){
                insert(temp->key, temp->value) ;
                temp=temp->next ;
            }
            delete old_buckets[i] ;
        }
        delete []old_buckets ;
    }
    int hash_fn(string key)
    {
        int l =key.length() ;
        int ans =0 ;
        int p=1 ;
        for(int i=0;i< l;i++){
            ans+=key[l-1-i]*p ;
            p=p*37 ;
            p%= ts ;
            ans%=ts ;
        }
        return ans ;
    }
public:
    hash_table(int ds =7 )
    {
        cs  =0;
        ts =ds ;
        buckets =new node<t> *[ts] ;
        for(int i=0;i< ts;i++){
            buckets[i] =NULL ;
        }
    }
    void insert(string key , t value)
    {
        int i =hash_fn(key) ;
        node<t> * n = new node<t>(key, value) ;
        n->next =buckets[i] ;
        buckets[i] =n ;
        cs++ ;
        float load_factor =float(cs/ts) ;
        if(load_factor>0.7){
            cout<<"load factor is : " <<load_factor<<endl ;
            rehash() ;
        }
    }
    void print()
    {
        for(int i=0;i< ts;i++){
            node<t>* temp =buckets[i] ;
            cout<<"bucket "<<i<<" ->" ;
            while(temp!=NULL){
                cout<<" ( "<<temp->key<<" , "<<temp->value<<" ) " ;
                temp =temp->next ;
            }
            cout<<endl ;
        }
    }
    t* search(string key)
    {
        int i =hash_fn(key );
        node<t>* temp =buckets[i] ;
        while(temp!=NULL){
            if(temp->key == key){
                return &(temp->value) ;
            }
            temp =temp->next ;
        }
        return NULL ;
    }
};
int main()
{
    hash_table <int> h(11) ;
    h.insert("mango" , 100) ;
    h.insert("apple" , 200) ;
    h.insert("banana" , 400) ;
    h.insert("chiku" , 300) ;
    h.insert("orange" , 500) ;
    h.print() ;
    string fk ="mango" ;
    int * price = h.search(fk) ;
    cout<<*price ;
    return 0 ;

}

