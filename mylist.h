
/********************************************************************/
/*                                                                  */
/*  A1 Part 2: DList starter file                                   */
/*                                                                  */
/*  Author1 Name: <name here>                                       */
/*      - class/function list/main author or main checker           */
/*  Author2 Name: <name here>                                       */
/*      - class/function list/main author or main checker           */
/*                                                                  */
/********************************************************************/

#ifndef mylist_h
#define mylist_h
#include <iostream>
//#include "boolTableEqual.h"


using namespace std;
template <typename T>
class DList{
    struct Node{
        T data_;
        Node* next_;
        Node* prev_;
        Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
            data_=data;
            next_=next;
            prev_=prev;
        }
    };
public:
    Node* front_;
    Node* back_;

public:
    class const_iterator{
    protected:
    public:
        Node* curr_;
        const_iterator();
        const_iterator(Node* n);
        const_iterator& operator++();
        const_iterator operator++(int);
        
        const_iterator& operator--();
        const_iterator operator--(int);
        bool operator==(const_iterator rhs);
        bool operator!=(const_iterator rhs);
        
        const T& operator*()const;
    };
    class iterator:public const_iterator{
    public:
        iterator();
        iterator(Node* n);
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        T& operator*();
        const T& operator*()const;
    };
    DList();
    ~DList();
    void show(){
        Node* tem = front_;
        while (tem)
        {
         std::cout << " tem->data_ = " << tem->data_ << std::endl;
            tem = tem->next_;
        }
    }
    DList(const DList& rhs);
    DList& operator=(const DList& rhs);
    DList(DList&& rhs);
    DList& operator=(DList&& rhs);
    iterator insert(iterator it, const T& data);
   
    iterator search(const T& data);
    iterator erase(iterator it);
    void modify(iterator it, T data);
    void sort(iterator first, iterator last);
    bool empty() const;
    int size() const;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
};


template <typename T>
typename DList<T>::const_iterator DList<T>::const_iterator::operator++(int){
   // std::cout << "enterB!\n";
    if(this->curr_->next_!= nullptr){
      //  std::cout << "enter1!\n";
    const_iterator tem  = const_iterator(*this);
    
    this->curr_ = this->curr_->next_;
    
    return tem;
    }
    else if (curr_ == nullptr){
        return const_iterator(nullptr);
    }
    else{
       // std::cout << "enter2!\n";
        //std::cout << "else\n";
        Node* tem = new Node();
        
        
        this->curr_->next_ = tem;
        tem->next_ = nullptr;
        tem->prev_ = this->curr_;
        //this->curr_ = nullptr;
        
        return const_iterator(*this);
    }
    
    
}
template <typename T>
typename DList<T>::const_iterator& DList<T>::const_iterator::operator--(){curr_ = curr_->prev_;
    return *this;
}
template <typename T>
typename DList<T>::const_iterator DList<T>::const_iterator::operator--(int){const_iterator tem  = const_iterator(*this);
    this->curr_ = this->curr_->prev_;
        
    return tem;}
template <typename T>
bool DList<T>::const_iterator::operator==(const_iterator rhs){
    if(curr_ == nullptr && rhs.curr_ != nullptr){return false;}
else if(curr_ == nullptr && rhs.curr_ == nullptr){
    return true;
}
else if ( curr_->prev_ == rhs.curr_->prev_ && curr_->next_ == nullptr && rhs.curr_->next_ == nullptr ){
    return true;
}
return
    curr_->data_ == rhs.curr_->data_;
    
}

template <typename T>
DList<T>::const_iterator::const_iterator(){curr_=nullptr;}

template <typename T>
DList<T>::const_iterator::const_iterator(Node* n){
    curr_=n;
}
template <typename T>
typename DList<T>::const_iterator& DList<T>::const_iterator::operator++(){
   // std::cout << "enterA!\n";
    if(this->curr_->next_!= nullptr){
    
    const_iterator *tem  = new const_iterator(this->curr_->next_);
    
    this->curr_ = this->curr_->next_;
    
    return *tem;
    }
    else{
        
        Node* tem = new Node();
        
        
        this->curr_->next_ = tem;
        tem->next_ = nullptr;
        tem->prev_ = this->curr_;
       // this->curr_ = nullptr;
        const_iterator *t = new const_iterator(tem);
        return *t;
    }
    
}

 template <typename T>
bool DList<T>::const_iterator::operator!=(const_iterator rhs){
    if(rhs.curr_ == nullptr){
      //  std::cout << "asd\n";
    }
    if(curr_ == nullptr && rhs.curr_ != nullptr){return true;}
else if(curr_ == nullptr && rhs.curr_ == nullptr){
    return false;
}
else if ( curr_->prev_ == rhs.curr_->prev_ && curr_->next_ == nullptr && rhs.curr_->next_ == nullptr ){
    return false;
}
return !(curr_->data_ == rhs.curr_->data_);}
template <typename T>
const T& DList<T>::const_iterator::operator*()const{return curr_->data_ ;}



//----
template <typename T>
DList<T>::iterator::iterator(){this->curr_= nullptr;}
template <typename T>
DList<T>::iterator::iterator(Node* n){
    this->curr_=n;
}
template <typename T>
typename DList<T>::iterator& DList<T>::iterator::operator++(){
    //std::cout << "enter!\n";
    if(this->curr_->next_!= nullptr){
    
    iterator *tem  = new iterator(this->curr_->next_);
    
    this->curr_ = this->curr_->next_;
    
    return *tem;
    }
    else{
        
        Node* tem = new Node();
        
        
        this->curr_->next_ = tem;
        tem->next_ = nullptr;
        tem->prev_ = this->curr_;
        iterator *t = new iterator(tem);
        return *t;
    }
    
}
template <typename T>
typename DList<T>::iterator DList<T>::iterator::operator++(int){
   // std::cout << "\nenter " << this->curr_->data_ << std::endl;
    Node* tem2 = new Node();
    //std::cout << "++ done!\n";
    if(this->curr_->next_!= nullptr ){
        
    iterator tem  = iterator(*this);
    
    this->curr_ = this->curr_->next_;
    
    return tem;
    }
    else{
    //std::cout << "enter else\n";
        //Node* tem = new Node();
        
        
        
        iterator tem3 = iterator(*this);
        tem2->next_ = nullptr;
        tem2->prev_ = this->curr_;
        //this->curr_->next_ = tem2;
        *this = tem2;
        return tem3;
        
    }
    
    
    
    
}
template <typename T>
typename DList<T>::iterator& DList<T>::iterator::operator--(){
    //std::cout << "enterA: " << this->curr_->data_ << std::endl;
    this->curr_ = this->curr_->prev_;
    return *this;
    
    
}
template <typename T>
typename DList<T>::iterator DList<T>::iterator::operator--(int){
   // std::cout << "enterB: " << this->curr_->data_ << std::endl;
    
    if(this->curr_->prev_!= nullptr){
    
    iterator tem  = iterator(*this);
    this->curr_ = this->curr_->prev_;
        
    return tem;
    }
    else{
        //std::cout << "else\n";
        Node* tem = new Node();
        
        
        this->curr_->prev_ = tem;
        tem->prev_ = nullptr;
        tem->next_ = this->curr_;
        
        return iterator(*this);
    }
    
    
}
template <typename T>
T& DList<T>::iterator::operator*(){return this->curr_->data_ ;}
template <typename T>
const T& DList<T>::iterator::operator*()const{return this->curr_->data_ ;}


//---/
template <typename T>
typename DList<T>::iterator DList<T>::begin(){return iterator(front_);}
template <typename T>
typename DList<T>::iterator DList<T>::end(){if(back_ == nullptr){
    return iterator(nullptr);
}
    Node* tem = new Node();
    
    //tem.data_ = 0;
    //back_->next_ = tem;
    tem->next_ = nullptr;
    tem->prev_ = back_;
    
    return iterator(tem);
    
}
template <typename T>
typename DList<T>::const_iterator DList<T>::cbegin() const{ return const_iterator(front_);    }
template <typename T>
typename DList<T>::const_iterator DList<T>::cend() const{
    if(back_ == nullptr){
        //std::cout << "enter\n";
    return const_iterator(nullptr);
    
    
    
}
Node* tem = new Node();


tem->next_ = nullptr;
tem->prev_ = back_;

return const_iterator(tem);}

//--
template <typename T>
DList<T>::DList(){
    front_=nullptr;
            back_=nullptr;
}


template <typename T>
DList<T>::~DList(){
    Node* tem = front_;
   // cout << "enter Des of list\n";
   
                while (tem )
                {
                   /* if(tem->next_ == nullptr){
                        delete tem;
                        break;
                    }*/
                    Node* nextNode = tem->next_;
                    //std::cout << "delete tem->data_ = " << tem->data_ << std::endl;
                    if( tem != end().curr_ && tem != nullptr && tem->next_ != tem && nextNode != nullptr ){
                        
                        delete tem;
                        
                    }
                    
                    tem = nextNode;
                }

}
template <typename T>
DList<T>::DList(const DList& rhs){
    /*Node *Otem = front_;
    
    while(Otem && Otem->next_){
        
        Node *Otem2 =Otem->next_;
        delete Otem;
        Otem = Otem2;
     }*/
    
    Node * tem = rhs.front_;
       Node * tem2 =new Node(tem->data_);
    tem->prev_ = nullptr;
       front_ = tem2;
       while(tem && tem->next_){
           tem2->next_ = new Node( tem->next_->data_);
           tem2->next_->prev_ = tem2;
           tem2 = tem2->next_;
           tem = tem->next_;
        }
       this->back_ = tem;
}
template <typename T>
DList<T>& DList<T>::operator=(const DList& rhs){
    
  //  std::cout << "enter Dcopy ass"<< std::endl;
    if(this == &rhs){
        
        return *this;
    }
    while(begin() != end())
        
    {this->erase(begin());}

    Node * tem = rhs.front_;
       Node * tem2 =new Node(tem->data_);
       front_ = tem2;
       
       
       while(tem && tem->next_){
           
           tem2->next_ = new Node( tem->next_->data_);
           tem2->next_->prev_ = tem2;
           tem2 = tem2->next_;
           tem = tem->next_;
           
           
           
       }
       
       
       this->back_ = tem;
   // DList *temD = new DList(rhs);
    
    return *this;
    
    
}
template <typename T>
void DList<T>::modify(iterator it, T data){
    it.curr_->data_ = data;
}
template <typename T>

DList<T>::DList(DList&& rhs){
  //  std::cout << "enter move con"<< std::endl;
    front_ = nullptr;
    back_ = nullptr;
    this->front_ = rhs.front_;
    this->back_ = rhs.back_;
    
    rhs.front_ = nullptr;
    rhs.back_ = nullptr;

}

template <typename T>
DList<T>& DList<T>::operator=(DList&& rhs){
   // std::cout << "enter move ass"<< std::endl;
    //Node* tem = this->front_;
    //int k = 0;
   while(begin() != end())
        
    {
        //std::cout << "k=" << k << std::endl;
        //k++;
        this->erase(begin());
        
    }
    this->front_ = rhs.front_;
    this->back_ = rhs.back_;
    rhs.front_ = nullptr;
    rhs.back_ = nullptr;
    
    return *this;
}


template <typename T>
typename DList<T>::iterator DList<T>::insert(iterator it, const T& data){
    Node* temNode =new Node(data);
    
    //std::cout << data << std::endl;
    
    if(it.curr_ == nullptr){
       // std::cout << "a\n";
        front_ = temNode;
        back_ = temNode;
        it.curr_ = temNode;
        it.curr_->prev_ = nullptr;
    }
    else if (it == front_){
        //std::cout << "c\n";
        front_->prev_ = temNode;
        temNode->next_ = front_;
        front_ = temNode;
        it.curr_ = temNode;
    }
    else if (it == end()){
        
        //std::cout << "b\n";
        back_->next_ = temNode;
        temNode->prev_ = back_;
        back_ = temNode;
        it.curr_ = temNode;
    }
    
    else if(it.curr_->prev_ !=nullptr  ){
        //std::cout << "d\n";
        temNode->prev_ = it.curr_->prev_;
        temNode->next_ = it.curr_;
        it.curr_->prev_->next_ = temNode;
        it.curr_->prev_ = temNode;
        it.curr_ = temNode;
        
        
    }
    
    
    
        
        
    
        
    
    
                
    return it;
}


template <typename T>
typename DList<T>::iterator DList<T>::search(const T& data){
    Node* tem = front_;
    
    while(tem){
       // std::cout << "decltype(tem ) is " << type_name<decltype(tem->data_)>() << '\n';
        //std::cout << "decltype(data) is " << type_name<decltype(data)>() << '\n';
        
      //  cout <<"data->key_=" << data->key_ << endl;
       // cout <<"tem->data_->key__=" << tem->data_->key_ << endl;
        if(!data.key_.compare(tem->data_.key_)){
          // if(tem->data_ == data){
            
            DList<T>::iterator it = DList<T>::iterator(tem);
            return it;
        }
        tem = tem->next_;
        
    }
    return end();
}

/*template <>
DList<ChainingTable<int>::Record*>::iterator DList<ChainingTable<int>::Record*>::search(const ChainingTable<int>::Record*& data){
    Node* tem = front_;
    while(tem){
       // std::cout << "decltype(tem ) is " << type_name<decltype(tem->data_)>() << '\n';
       // std::cout << "decltype(data) is " << type_name<decltype(data)>() << '\n';
        //cout <<"data->key_=" << data->key_ << endl;
       // if(data->key_ == tem->data_->key_){
        if(tem->data_.key_ == data.key_){
            
            DList<ChainingTable<int>::Record>::iterator it = DList<ChainingTable<int>::Record>::iterator(tem);
            return it;
        }
        tem = tem->next_;
    }
    return end();
}*/


template <typename T>
typename DList<T>::iterator DList<T>::erase(iterator it){
    
    if(it.curr_->next_ == nullptr && it == begin()){
        
        it.curr_->prev_ = nullptr;
       delete it.curr_;
        //delete front_;
       back_ = nullptr;
       front_ = nullptr;
        
        
       return end();
   }
    if(it.curr_->next_ == nullptr){
        string a = it.curr_->data_.key_;
        
        Node * tem = it.curr_->prev_;
        delete it.curr_;
        tem->next_ = nullptr;
        //it.curr_ = tem;
        back_ = tem;
        
        
        return end();
    }
    else if(it == begin()){
        
        Node * tem = it.curr_->next_;
        delete it.curr_;
        tem->prev_ = nullptr;
        it.curr_ = tem;
        front_ = it.curr_;
        return begin();
    }
    
    else{
        
        Node * tem = it.curr_->next_;
        it.curr_->next_->prev_ = it.curr_->prev_;
        it.curr_->prev_->next_ = it.curr_->next_;
        delete it.curr_;
        it.curr_ = tem;
        return it;
    }
    


}

template <typename T>
void DList<T>::sort(iterator first, iterator last){
    iterator it = first;
    int size = 0;
    
    
    while(true)
    {
        
        
        //std::cout << "it=" << *it << std::endl;
        size++;
        if(it == back_ || it.curr_->next_ == last.curr_)
            break;
        it++;
        
        
    }
    T *tem = new T[size];
    it = first;
    for(int i = 0; i< size ; i++){
        
        tem[i] = *it;
        it++;
    }
    
    T *a = tem;
        T *b = new T[size];
        for (int j = 1; j < size; j += j) {
            for (int x = 0; x < size; x += j + j) {
                int low = x, mid = std::min(x + j, size), high = std::min(x + j + j, size);
                int k = low;
                int b1 = low, end1 = mid;
                int b2 = mid, end2 = high;
                while (b1 < end1 && b2 < end2)
                    b[k++] = a[b1] < a[b2] ? a[b1++] : a[b2++];
                while (b1 < end1)
                    b[k++] = a[b1++];
                while (b2 < end2)
                    b[k++] = a[b2++];
            }
            T *temp = a;
            a = b;
            b = temp;
        }
        if (a != tem) {
            for (int i = 0; i < size; i++)
                b[i] = a[i];
            b = a;
        }
        delete[] b;
    
    int i = 0;
    it = first;
    while(true)
    {
        
        
        //std::cout << "it=" << *it << std::endl;
        it.curr_->data_ = tem[i];
        
        it++;
        i++;
        if(i >= size)
            break;
        
        
    }
     i = 0;
    it = first;
    while(true)
    {
        
        
        //std::cout << "it=" << *it << std::endl;
        //it.curr_->data_ = tem[i];
        if(it == back_ || it == last)
            break;
        it++;
        i++;
        
        
    }
    
    
    
    

}
template <typename T>
bool DList<T>::empty() const{
    return  this->front_ == nullptr? true : false;
}
template <typename T>
int DList<T>::size() const{
    Node* tem = front_;
    //DList<T>::iterator it =begin();
    int size = 0;
   // Node* tem2
    while(tem //&& tem != cend().curr_
          ){
        size++;
       // if(tem->next_ != nullptr){
        tem = tem->next_;
       /* }
        else{
            break;
        }*/
    }
    return size;
}
#endif
