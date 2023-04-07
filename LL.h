#include <iostream>

using namespace std; 
template <typename T>
class LL 
{
    //contents of each node
    struct node 
    {
        T data;
        node* prev;
        node* next;
    };
    //iterator class to allow access of each node in main
   public:
    class Iterator 
    {
       public:
        friend class LL;
        Iterator();
        Iterator(node*);
        T operator*() const;
        Iterator operator++(int);
        Iterator operator++();
        Iterator operator--(int);
        Iterator operator--();
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;

       private:
        node* current;
    };

    LL();
    LL(const LL<T>&);
    const LL<T>& operator=(const LL<T>&);
    ~LL();
    void headInsert(const T&);
    void tailInsert(const T&);
    void headRemove();
    //void print(); 
    bool isEmpty() const;
    std::size_t size() const;
    Iterator begin() const;
    Iterator end() const;

   private:
    node * portal;
};

//iterator class implementation
template <typename T>
LL<T>::Iterator::Iterator() //cons sets currecnt to null
{
    current = nullptr; 
}

template <typename T>
LL<T>::Iterator::Iterator(node* ptr) //sets curr == ptr
{
    current = ptr; 
}

template <typename T>
T LL<T>::Iterator::operator*() const 
{
    return current->data; 
}

template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator++(int) //postfix
{   //move to the right one use "this object" post 
   this->current = this->current->next; 
   return this->current; 
}

template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator++() //prefix 
{   //move to the right and return the object prev pointed to 
    this->current = this->current->next;
    return this->current->prev;
}

template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator--(int) //postfix
{   //move to the left one use "this object" post 
    this->current = this->current->prev; 
    return this->current; 
}

template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator--() //prefix
{   //move to the left and return the object prev pointed to 
    this->current = this->current->prev; 
    return this->current->next; 
}

template <typename T>
bool LL<T>::Iterator::operator==(const Iterator& rhs) const 
{
    //reutn if object eq to derefranced iterator
    return this->current == rhs.current; 
}

template <typename T>
bool LL<T>::Iterator::operator!=(const Iterator& rhs) const 
{
    //reutn if object not eq to derefranced iterator
   return this->current != rhs.current; 
}

//Linked list class implementation
template <typename T>
LL<T>::LL() 
{
    //set to next and prev 
    // portal->prev = portal->next = portal;
    portal = new node; 
    portal->prev = portal; //tail 
    portal->next = portal; //head 
}

//copy constructor
template <typename T>
LL<T>::LL(const LL<T>& copy) 
{
    // deep copy the "copy" obj into derefranced *this object (current)
    // set head and tail to nullptr 

    this->portal = new node; 
    portal->next = portal; //head 
    portal->prev = portal; //tail 

    // one way tto solve it 
    // node* work = copy.portal->next;
    // //if not eq to null, insert at tail end/cnt copy
    // while (work != copy.portal) 
    // {   
    //     this->tailInsert(work->data); 
    //     work = work->next;  
    // }

    //second way to solve it 
    //declare a new iterator to assigne start of ll  
    LL<T>::Iterator temp; 
    temp = copy.begin(); //tmep set to head  
    //if not eq to null, insert at tail end/cnt copy
    while (temp != copy.portal) 
    {   
        this->tailInsert(temp.current->data);
        temp++;  
    }

}

template <typename T>
const LL<T>& LL<T>::operator=(const LL<T>& rhs) 
{
    // check current line is empty 
    // if not deallocate list 
    // is rhs is empy 
    // if not tail isnert data to rhs using a loop 
    node* ptr = portal->next; 
    if(ptr != portal)  //if not empty to while loop 
    {
        while(portal->next != portal) //not self assigned
        {
           this->headRemove();            //delete ptr 
        }
    }
    portal->next = portal;
    portal->prev = portal;
    
    //one way to solve in 
    // node* curr = rhs.portal->next;
    // while (curr != rhs.portal) 
    // {     
    //     this->tailInsert(curr->data); 
    //     curr = curr->next;  
    // }

    //second way to solve it
    LL<T>::Iterator curr; 
    curr = rhs.begin(); 
    while (curr != rhs.portal) 
    {     
        this->tailInsert(curr.current->data); 
        curr++;  
    }
    
    return *this; 
}

//destructor
template <typename T>
LL<T>::~LL() 
{
    node* ptr = portal->next; //ptr is head 
    while(ptr != portal)      //not head 
    {
        node* next = ptr->next; //next link 
        delete ptr; 
        ptr = next;  
    }
    delete portal; 
}

//head insert
template <typename T>
void LL<T>::headInsert(const T& item) 
{
    node* temp = new node();
    temp->data = item;  //obj set to temp to add at head
    if(portal->next == portal) //if only portal and no other ll
    {
        temp->prev = portal; //prev to portal link
        temp->next = portal; //next to portal link
        portal->prev = temp; //portal prev to temp
        portal->next = temp; //portal next to temp
    }
    else 
    {
        //set temp to hold portal head
        node* head_node = portal->next; 
        head_node->prev = temp; //link old port link to temp
        portal->next = temp;    //now temp link to next head
        temp->next = head_node; //tmep head to portal head
        temp->prev = portal;    //portal to temp prev
    }
}

//tail insert
template <typename T>
void LL<T>::tailInsert(const T& item) 
{
    node* temp = new node(); 
    temp->data = item; 
    
    if(portal->next == portal)  //only one new link 
    {
        temp->prev = portal; //prev to portal link 
        temp->next = portal; //next to portal link 
        portal->prev = temp; //portal prev to temp 
        portal->next = temp; //portal next to temp
    }
    else
    {   //new node holds prev link to portal 
        node* prev_node = portal->prev; 
        portal->prev = temp;    //temp link to prev
        temp->prev = prev_node; //temp link to prev link of portal
        temp->next = portal;    //portal to temp
        prev_node->next = temp; //portal old link to tmep
    }
}

template <typename T>
void LL<T>::headRemove()
{
    //if not empty, there will be a ll 
    if(!isEmpty())
    {
        node* temp = portal->next;  //temp set to head 
        portal->next = temp->next;  //link to portal next
        temp->next->prev = portal;  //prev link to portal 
        temp->prev = nullptr;       //clear out temp link 
        temp->next = nullptr;       
        delete temp;                //finally delete 
        
    }
} 

template <typename T>
bool LL<T>::isEmpty() const
{
    //if head(portal->next) == portal, no other ll  
    return portal->next == portal; 
}

template <typename T>
std::size_t LL<T>::size() const
{
    // set cnt and temp to head 
    //if not portal, inc cnt and move to next ll 
    std::size_t count =0;
    node* temp = portal->next;
    while (temp != portal)
    {
        count++;
        temp = temp->next; 
    }
    return count;  
}

template <typename T>
typename LL<T>::Iterator LL<T>::begin() const 
{
    // returns an Itereator object whoss current filed contains this->head
    //return this->portal->next;
    return Iterator(portal->next);  
}

template <typename T>
typename LL<T>::Iterator LL<T>::end() const 
{
    // returns an Itereator object whoss current filed contains this->portal//end
    // return this->portal->prev; //should be the tail right? 
    return Iterator(portal); 
}

// template <typename T> 
// void LL<T>::print()
// {
    
//     node* temp = portal->next;

//         int size=0;
//         while(size!=7){
//             if(temp==portal){
//                 std::cout<<"- ";
//                 size++;
//                 temp = temp->next;
//                 continue;
//             }
//             std:: cout <<""<< temp->data << " ";
//             temp = temp->next;
//             size++;
//         }

//     std::cout << std::endl;
// }