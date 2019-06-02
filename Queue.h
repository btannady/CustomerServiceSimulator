/*Programmer: Benedict Tannady*/
/*Programmer's ID: 1591141*/

#ifndef Queue_h
#define Queue_h

template <typename V>
class Queue
{
    
    struct Node
    {
        V value;
        Node* next;
    };
    
    Node* firstNode; //private data member
    Node* lastNode; // private data member
    int siz; // tracking the number of nodes
    V dummy;
    
public:
    
    Queue(); // may have a defaulted parameter
    
    Queue(const Queue<V>&); // copy constructor
    
    ~Queue(); // destructor
    
    Queue<V>& operator=(const Queue<V>&);
    
    void push(const V&);
    
    V& front(){
        if(firstNode)
        return (firstNode->value);
        return dummy;
    }; // return a mutable reference to the oldest node
    
    V& back(){
        if(lastNode)
        return (lastNode->value);
        return dummy;
    }; // return a mutable reference to the newest node
    
    void pop(); // remove the oldest node
    
    int size() const{
        return siz;
    }
    
    bool empty() const;
    
    void clear();
};
/*-----------------------------------------------------------------------*/
/*Main Constructor*/
template <typename V>
Queue<V>::Queue()
{
    siz = 0;
    firstNode = 0;
    lastNode = 0;
    dummy = V();
};
/*-----------------------------------------------------------------------*/
/*Destructor*/
template <typename V>
Queue<V>::~Queue()
{
    while (firstNode)
    {
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
    }
}
/*-----------------------------------------------------------------------*/
/*Copy Constructor*/
template <typename V>
Queue<V>::Queue(const Queue<V>& original)
{
    firstNode = 0;
    lastNode = 0;
    siz = original.siz;
    for (Node* p = original.firstNode; p; p = p->next)
    {
        Node* temp = new Node;
        temp->value = p->value;
        temp->next = 0;
        if (lastNode) lastNode->next = temp;
        else firstNode = temp;
        lastNode = temp;
    }
}
/*-----------------------------------------------------------------------*/
/*Assignment Operator*/
template <typename V>
Queue<V>& Queue<V>::operator=(const Queue<V>& original)
{
    if (this != &original)
    {
        // deallocate existing list
        while (firstNode)
        {
            Node* p = firstNode;
            firstNode = firstNode->next;
            delete p;
        }
        
        // build new queue
        lastNode = 0;
        for (Node* p = original.firstNode; p; p = p->next)
        {
            Node* temp = new Node;
            temp->value = p->value;
            temp->next = 0;
            if (lastNode) lastNode->next = temp;
            else firstNode = temp;
            lastNode = temp;
        }
        siz = original.siz;
    }
    return *this;
}

/*-----------------------------------------------------------------------*/
/*Push function*/
template <typename V>
void Queue<V>::push(const V& value)
{
    Node* temp = new Node;
    temp->value = value;
    temp->next = 0;
    if (lastNode) lastNode->next = temp;
    else firstNode = temp;
    lastNode = temp;
    ++siz;
} 

/*-----------------------------------------------------------------------*/
/*Pop function*/
template <typename V>
void Queue<V>::pop()
{
    if (firstNode)
    {
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
        --siz;
    }
    if(siz == 0){
        lastNode->next = 0;
    }
}
/*-----------------------------------------------------------------------*/
/*Clear function*/
template <typename V>
void Queue<V>::clear()
{
    while (firstNode)
    {
        Node* p = firstNode;
        firstNode = firstNode->next;
        delete p;
        --siz;
    }
}
/*-----------------------------------------------------------------------*/
/*Empty function*/
template <typename V>
bool Queue<V>::empty() const
{
    if(siz == 0){
        return true;
    }else{
        return false;
    }
}
/*-----------------------------------------------------------------------*/
#endif
