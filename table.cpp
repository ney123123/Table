//
//  boolTableEqual.h
//  as2
//
//  Created by kam keung pun on 22/7/2022.
//
#include "mylist.h"
#include <iostream>

using namespace std;

template <class TYPE>
class Table{
public:
    Table(){}
    virtual bool update(const std::string& key, const TYPE& value)=0;
    virtual bool remove(const std::string& key)=0;
    virtual bool find(const std::string& key, TYPE& value)=0;
    virtual int numRecords() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int capacity() const = 0;
    virtual ~Table(){}
};

template <class TYPE>
class SimpleTable:public Table<TYPE>{

    struct Record{
        TYPE data_;
        std::string key_;
        Record(const std::string& key, const TYPE& data){
            key_=key;
            data_=data;
        }

    };

    Record** records_;   //the table
    int capacity_;       //capacity of the array


public:
    SimpleTable(int capacity);
    SimpleTable(const SimpleTable& rhs);
    SimpleTable(SimpleTable&& rhs);
    virtual bool update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const SimpleTable& operator=(const SimpleTable& rhs);
    virtual const SimpleTable& operator=(SimpleTable&& rhs);
    virtual ~SimpleTable();
    virtual bool isEmpty() const{return numRecords()==0;}
    virtual int numRecords() const;
    virtual int capacity() const {return capacity_;}
    void show();

};
//-------
template <class TYPE>
class ChainingTable:public Table<TYPE>{
    

     //the table
    int capacity_;       //capacity of the array
public:
    struct Record{
        TYPE data_;
        Record* next_ = nullptr;
        std::string key_ ;
        Record(const std::string& key, const TYPE& data=TYPE{}){
            key_=key;
            data_=data;
        }
        
        Record(){
            
        }
        bool operator==(const Record&b){
            return !key_.compare( b.key_);
        }
       

    };
    //friend bool operator==(const Record& b);
    DList<Record>* records_ = nullptr;
    ChainingTable(int maxExpected);
    ChainingTable(const ChainingTable& other);
    ChainingTable(ChainingTable&& other);
    double loadFactor() const;
    void deleNode(Record* a);
    
    virtual bool update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const ChainingTable& operator=(const ChainingTable& other);
    virtual const ChainingTable& operator=(ChainingTable&& other);
    virtual ~ChainingTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};


template <class TYPE>
class LPTable:public Table<TYPE>{
    struct Record{
        TYPE data_;
        std::string key_;
        // del is for identify if it is a removed record and not a null record;
        bool del = false;
        
        Record(const std::string& key, const TYPE& data){
            key_=key;
            data_=data;
        }
        Record(Record& a){
            key_=a.key_;
            data_=a.data_;
            del = a.del;
        }
    };
    Record** records_;   //the table
    int capacity_;       //capacity of the array
public:
    LPTable(int maxExpected);
    LPTable(const LPTable& other);
    LPTable(LPTable&& other);
    double loadFactor() const;
    virtual bool update(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const LPTable& operator=(const LPTable& other);
    virtual const LPTable& operator=(LPTable&& other);
    virtual ~LPTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const{
    int rc=0;
    for(int i=0;records_[i]!=nullptr;i++){
        rc++;
    }
    return rc;
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity): Table<TYPE>(){
    records_=new Record*[capacity+1];
    capacity_=capacity;
    for(int i=0;i<capacity_+1;i++){
        records_[i]=nullptr;
    }
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs){
    records_=new Record*[rhs.capacity_];
    capacity_=rhs.capacity_;
    for(int i=0;i<capacity_+1;i++){
        records_[i]=nullptr;
    }
    for(int i=0;i<rhs.numRecords();i++){
        update(rhs.records_[i]->key_,rhs.records_[i]->data_);
    }
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs){
    capacity_=rhs.capacity_;
    records_=rhs.records_;
    rhs.records_=nullptr;
    rhs.capacity_=0;
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const std::string& key, const TYPE& value){
    int idx=-1;
    int sz=numRecords();
    bool rc=true;
    for(int i=0;i<sz;i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx==-1){
        if(sz < capacity_){
            records_[numRecords()]=new Record(key,value);
            
            for(int i=numRecords()-1;i>0 && records_[i]->key_ < records_[i-1]->key_;i--){
               // std::cout <<"records_["<<i<<"]->key_=" << records_[i]->key_ << ",records_["<<i-1<<"]->key_=" << records_[i-1]->key_ << std::endl;
                Record* tmp=records_[i];
                records_[i]=records_[i-1];
                records_[i-1]=tmp;
            }
        }
        else{
            rc=false;
        }
    }
    else{
        records_[idx]->data_=value;
    }
    return rc;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key){
    int idx=-1;
    
    for(int i=0;records_[i]!=nullptr;i++){
        
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx!=-1){
        delete records_[idx];
        
        for(int i=idx;i<numRecords()-1;i++){
            records_[i]=records_[i+1];
        }
        records_[numRecords()-1]=nullptr;
        return true;
    }
    else{
        return false;
    }
}
template <class TYPE>
void SimpleTable<TYPE>::show(){
    if(records_){
        int sz=numRecords();
    for(int i=0;i<sz;i++){
        std::cout << records_[i]->key_ <<"," << records_[i]->data_ << std::endl;
    }
    }
}
template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value){
    int idx=-1;
    for(int i=0;i<numRecords();i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx==-1)
        return false;
    else{
        value=records_[idx]->data_;
        return true;
    }
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs){
    if(this!=&rhs){
        if(records_){
            while(numRecords() != 0){
                remove(records_[0]->key_);
            }
            delete [] records_;
        }
        records_=new Record*[rhs.capacity_+1];
        capacity_=rhs.capacity_;
        for(int i=0;i<capacity_;i++){
            records_[i]=nullptr;
        }
        for(int i=0;i<rhs.numRecords();i++){
            update(rhs.records_[i]->key_,rhs.records_[i]->data_);
        }

    }
    return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs){
    if(records_){
        while(numRecords() != 0){
            remove(records_[0]->key_);
        }
        delete [] records_;
    }
    records_=rhs.records_;
    capacity_=rhs.capacity_;
    rhs.records_=nullptr;
    rhs.capacity_=0;

    return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
    if(records_){
        int sz=numRecords();
        for(int i=0;i<sz;i++){
            remove(records_[0]->key_);
        }
        delete [] records_;
    }
}
//---------
//create a empty DList<Record>[] in size of capacity;
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity): Table<TYPE>(){
    records_=new DList<Record>[capacity];
    capacity_=capacity;
    for(int i =0; i< capacity_; i++){
       // records_[i] = nullptr;
    }
    
}
//create a new DList<Record>[] and copy it one by one from the target's DList<Record>[]
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other){
    
   
    records_=new DList<Record>[other.capacity_];
    capacity_ = other.capacity_;
    for(int i =0; i< capacity_; i++){

        if(!other.records_[i].empty())
        records_[i] = DList<ChainingTable<TYPE>::Record>(other.records_[i]);
    }
    
}
//create a new DList<Record>[] and move it one by one from the target's DList<Record>[]
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other){
    records_=new DList<Record>[other.capacity_];
    capacity_ = other.capacity_;
    for(int i =0; i< capacity_; i++){
        if(!other.records_[i].empty() && other.records_[i].front_ != nullptr)
        records_[i] = std::move(other.records_[i]);
    }
    other.capacity_=0;
}

//according to the key, find if the records exist in the table, if yes, change its data_ to value.if not ,create a new record by the key and value ,and insert it into the chain of [idx].
template <class TYPE>
bool ChainingTable<TYPE>::update(const std::string& key, const TYPE& value){
    hash<string> hashFunction;
    size_t idx = hashFunction(key);
    idx = idx%capacity_;
    if(records_[idx].empty()){
     records_[idx].insert(records_[idx].begin(),Record(key,value));
        
        return true;
    }
   typename DList<Record>::iterator it = records_[idx].search(Record(key,value));
        if(it != records_[idx].end() ){
           
            records_[idx].modify(it,Record(key,value));
            
            return true;
        }
        else {
            records_[idx].insert(records_[idx].begin(),Record(key,value));
            
            return true;
            
        }
            
    return true;
}
//According the key, find if the record with this key exist in the table. if yes, erase it from the chain. and return true, otherwise return false.
template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string& key){hash<string> hashFunction;
    size_t idx = hashFunction(key);
    idx = idx%capacity_;
    if(  records_[idx].empty() || records_[idx].front_ == nullptr ){
        return false;
    }
    typename DList<Record>::iterator it = records_[idx].search(Record(key));
    if(it == records_[idx].end())
        return false;
 records_[idx].erase(it);
 return true;
 
}



// by according the key, find if it exist in the List, then value = the data(by referenece) of the record of the key. and return true. Otherwise return false and do nothing on the value.
template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value){
    hash<string> hashFunction;
    size_t idx = hashFunction(key);
    idx = idx%capacity_;
    if(records_[idx].empty()){
        return false;
    }
    typename DList<Record>::iterator it = records_[idx].search(Record(key,value));
    if(it == records_[idx].end())
        return false;
    
    Record tem2 = *it;
    value = tem2.data_;
    return true;
}

// first clear and delete the records_[], then create a new DList<Record>[] and copy it one by one from the target's DList<Record>[]
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other){
    if(records_ != nullptr ){
    
    delete []records_;}
    records_=new DList<Record>[other.capacity_];
    capacity_ = other.capacity_;
    for(int i =0; i< capacity_; i++){
        if(!other.records_[i].empty() )
        records_[i] = DList<ChainingTable<TYPE>::Record>(other.records_[i]);
    }
    return *this;

}

// first clear and delete the records_[], then create a new DList<Record>[] and move it one by one from the target's DList<Record>[]
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other){
    
    if(records_ != nullptr )
    {delete [] records_;}
    records_=new DList<Record>[other.capacity_];
    capacity_ = other.capacity_;
    
    for(int i =0; i< capacity_; i++){
        if(!other.records_[i].empty())
        records_[i] = std::move(other.records_[i]);
    }
    
    other.capacity_=0;
    return *this;

}



//delete records_[];
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable(){
  if(records_){
        
                delete [] records_;
    }
}

// return true if there is not Record in this table
template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const {

    return numRecords() == 0;
}


// return the total number of the size of each List exist in this Table
template <class TYPE>
int ChainingTable<TYPE>::numRecords() const {
    int i = 0;
    
    int sum=0;
    for(i=0;i<capacity_;i++){
        if(!records_[i].empty())
        sum+= records_[i].size();
    }

    return sum;
    
}
template <class TYPE>
int ChainingTable<TYPE>::capacity() const {
    return capacity_;
}

template <class TYPE>
double ChainingTable<TYPE>::loadFactor() const {
    return 0;
}

//--------
//create a new Record[] in size of capacity
template <class TYPE>
LPTable<TYPE>::LPTable(int capacity): Table<TYPE>(){
    records_=new Record*[capacity];
    capacity_=capacity;
    for(int i=0;i<capacity_+1;i++){
        records_[i]=nullptr;
    }
}

// create a new records_[] and copy it one by one from the target's Records
template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other){
    capacity_ = other.capacity_;
    records_=new Record*[capacity_];
    for(int i = 0; i < capacity_;i++){
        records_[i]=nullptr;
        if(other.records_[i]!= nullptr)
        {records_[i] = new Record(*other.records_[i]);}
    }
}
// move everything from the target.
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other){
    capacity_=other.capacity_;
    records_=other.records_;
    other.records_=nullptr;
    other.capacity_=0;
}



template <class TYPE>
bool LPTable<TYPE>::update(const std::string& key, const TYPE& value){
  if(numRecords() == capacity_-1)
        return false;
    
    hash<string> hashFunction;
    size_t idx = hashFunction(key);
    idx = idx%capacity_;
    int originalIdx = idx;
    //loop until availible space for put the record, or find the exist one
    while(records_[idx]!= nullptr){
        //if the space is a reocrd removed before, delete it and create a new one and put it into.
        if(records_[idx]->del){
            delete records_[idx];
            records_[idx] = nullptr;
            records_[idx] = new Record(key,value);
            return true;
        }
        //if we find the match one and it is not removed, return the value by reference.
        if(!key.compare(records_[idx]->key_) && !records_[idx]->del){
            records_[idx]->data_ = value;
            return true;
        }
        idx++;
        idx = idx%capacity_;
        // if we have checked the loop completely, which mean that no space and no match, return false
        if(idx == originalIdx ){
            return false;
        }
    }
   // we find the null space, create a new one and put it into.
    records_[idx] = new Record(key,value);
   return true;
    
}

template <class TYPE>
bool LPTable<TYPE>::remove(const std::string& key){
    hash<string> hashFunction;
    size_t idx = hashFunction(key);
    idx = idx%capacity_;
   int originalIdx = idx;
    //loop until find the exist match one
   
    while(records_[idx]!= nullptr){
        if(records_[idx]->del){
            if(!key.compare(records_[idx]->key_))
                return false;
            idx++;
            idx = idx%capacity_;
            continue;
        }
        //if we find the match one, and it is not removed. we set the del to false but not delete it.
        if(!key.compare(records_[idx]->key_)){
            
             records_[idx]->del = true;
            return true;
        }
        idx++;
        idx = idx%capacity_;
        // if we have checked the loop completely, which mean that no match, return false
        if(idx == originalIdx ){
            return false;
        }
    }
    
    
    return false;
}


template <class TYPE>
bool LPTable<TYPE>::find(const std::string& key, TYPE& value){
    hash<string> hashFunction;
    size_t idx = hashFunction(key);
    idx = idx%capacity_;
    int originalIdx = idx;
    //loop until availible space for put the record, or find the exist one
    while(records_[idx]!= nullptr){
        //if we find the match one, and it is not removed. we return the value by reference and return true;
        if(!key.compare(records_[idx]->key_)&& !records_[idx]->del){
            value = records_[idx]->data_;
            return true;
        }
        idx++;
        idx = idx%capacity_;
        // if we have checked the loop completely, which mean that no match, return false
        if(idx == originalIdx ){
            return false;
        }
    }
    
    
    return false;
}

// first clear and delete the records_[], then create a new Record[] and copy it one by one from the target's Record[]
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other){
    for(int i=0;i<capacity_;i++){
        if(records_[i]!=nullptr)
            delete records_[i];
        
    }
    delete [] records_;
    capacity_ = other.capacity_;
    records_ = new Record*[capacity_];
    for(int i=0;i<capacity_;i++){
        records_[i] = nullptr;
        if(other.records_[i] != nullptr)
        records_[i] = new Record(*other.records_[i]);
    }
    return *this;
}

//first clear and delete the records_[], then create a new Record[] and move it one by one from the target's Record[]
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other){
    for(int i=0;i<capacity_;i++){
        if(records_[i]!=nullptr)
            delete records_[i];
        
    }
    delete [] records_;
    capacity_=other.capacity_;
    records_=other.records_;
    other.records_=nullptr;
    other.capacity_=0;
    return *this;
}
//delete every Record and delete records_[]
template <class TYPE>
LPTable<TYPE>::~LPTable(){
    for(int i=0;i<capacity_;i++){
        if(records_[i]!=nullptr)
            delete records_[i];
    }
    delete [] records_;
}

template <class TYPE>
bool LPTable<TYPE>::isEmpty() const {
    return numRecords() == 0;
}
//count if the record is not null and not removed
template <class TYPE>
int LPTable<TYPE>::numRecords() const {
    int rc=0;
    for(int i=0;i<capacity_;i++){
        if(records_[i]!=nullptr && !records_[i]->del)
            rc++;
        
    } return rc;
}
template <class TYPE>
int LPTable<TYPE>::capacity() const {
    return capacity_;
}
template <class TYPE>
double LPTable<TYPE>::loadFactor() const {
    return 0;
}
