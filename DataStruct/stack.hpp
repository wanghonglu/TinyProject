#ifndef __STACK__H
#define __STACK__H
#include<cstdint>
#include<cstdio>
#include<cassert>
#include<algorithm>
#include<stdexcept>

namespace datastruct{
template<typename T>
class StackBase{
public:
    virtual ~StackBase()=0;
    virtual bool    IsEmpty()const=0;
    virtual size_t  Size()const=0;
    virtual T Top()const =0;
    virtual void Pop()=0;
    virtual void Push( const T& )=0; 
};
//基类析构函数设置成纯虚函数,可以防止如果没有其他纯虚函数的时候,对基类实例化
//但是基类的析构函数必须有实现,因为子类析构的时候必须要能调用基类的析构函数
template<typename T>
StackBase<T>::~StackBase(){}
//数组描述
template<typename T>
class ArrayStack:public StackBase<T>{
public:
    
    static constexpr size_t  default_size=32;
    static constexpr size_t  realloclimit=1024;
    ArrayStack(size_t len );
    ArrayStack();
    ~ArrayStack();

    bool IsEmpty()const override;
    size_t Size()const override;
    T Top()const override;
    void Pop()override;
    void Push(const T& )override;
private:
    T         *ptr_ = nullptr;
    size_t    size_;
    size_t    capcity_;
};
template< typename T>
ArrayStack<T>::ArrayStack()
{
   ptr_ = new T[default_size]();
   assert( ptr_ );
   size_ =0;
   capcity_=default_size;  
}
template<typename T>
ArrayStack<T>::ArrayStack(size_t len )
{
    len = len<default_size?default_size:len;
    ptr_ = new T[len]();
    size_ = 0;
    capcity_=len;
}
template<typename T>
ArrayStack<T>::~ArrayStack()
{
    delete []ptr_;
    capcity_ = size_ = 0;
}
template<typename T>
bool ArrayStack<T>::IsEmpty()const
{
    return size_==0;
}
template<typename T>
size_t ArrayStack<T>::Size()const
{
    return size_;
}
template<typename T>
T ArrayStack<T>::Top()const
{
    if(IsEmpty())
        throw std::runtime_error("stack is empty");
    return ptr_[size_-1];
}
template<typename T>
void ArrayStack<T>::Pop()
{
    if(IsEmpty())
        throw std::runtime_error("stack is empty");
    size_--;
}
template<typename T>
void ArrayStack<T>::Push(const T& val )
{
    if( capcity_<size_+1 )
    {
        capcity_ = capcity_<realloclimit?capcity_*2:capcity_+realloclimit;
        T *tmp = new T[capcity_]();
        assert(tmp);
        std::copy( ptr_, ptr_+size_, tmp );
        delete []ptr_;
        ptr_ = tmp; 
    }
    ptr_[size_++]=val;
}
//链表描述
template<typename T>
class LinkedListStack:public StackBase<T>{
    public:
        LinkedListStack();
        ~LinkedListStack();
        bool    IsEmpty()const override;
        size_t  Size()const override;
        T       Top()const override;
        void    Pop()override;
        void    Push(const T& val )override;
         
    private:
        struct Node{
            T  val_;
            Node* next_ = nullptr;
        };
    Node*   head_;
    size_t  size_;
};
template<typename T>
LinkedListStack<T>::LinkedListStack()
{
    size_ =0;
    head_ = nullptr;
}
template<typename T>
LinkedListStack<T>::~LinkedListStack()
{
    size_ = 0;
    Node* del = head_;
    while( del )
    {
        Node *temp = del->next_;
        delete del;
        del = temp;
    }
    head_ = nullptr;
}
template<typename T>
bool LinkedListStack<T>::IsEmpty()const
{
    return size_ == 0 || head_ == nullptr;
}
template<typename T>
size_t LinkedListStack<T>::Size()const
{
    return size_;
}
template<typename T>
T LinkedListStack<T>::Top()const
{
    if( IsEmpty() )
        throw std::runtime_error("stack is empty");
    return head_->val_;
}
template<typename T>
void LinkedListStack<T>::Pop()
{
    if( IsEmpty() )
        throw std::runtime_error("stack is empty");
    Node* temp = head_;
    head_ = head_->next_;
    size_--;
    delete temp;
}
template<typename T>
void LinkedListStack<T>::Push( const T& val )
{
    Node* node = new Node();
    assert( node );
    node->val_=val;
    node->next_ = head_;
    head_ = node;
    size_++;
}
}//namespace datastrct end
#ifdef _UNIT_TEST_
#include<initializer_list>
void stack_test(int argc, char**argv ); 
#endif

#endif