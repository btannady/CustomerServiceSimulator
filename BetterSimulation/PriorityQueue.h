/*Programmer: Benedict Tannady*/
/*Programmer's ID: 1591141*/

#ifndef PriorityQueue_h
#define PriorityQueue_h

template <typename V>
class PriorityQueue
{
    V* values;
    int CAP;
    int siz;
    void capacity(int);
    V dummy;
    
public:
    
    /*default constructor*/
    PriorityQueue(int=2);
    
    /*copy constructor*/
    PriorityQueue(const PriorityQueue<V>&);
    
    /*destructor*/
    ~PriorityQueue() {delete [] values;}
    
    /*assignment operator*/
    PriorityQueue<V>& operator=(const PriorityQueue<V>&);
    
    /*push setter function*/
    void push(const V&);
    
    /*pop setter function*/
    void pop();
    
    /*top getter; returns the top value of the priority queue*/
    const V& top() const {return values[0];}
    
    /*size getter function*/
    int size() {return siz;}
    
    /*empty getter function*/
    bool empty() {return siz == 0 ? true : false;}
    
    /*clear setter function*/
    void clear() {siz = 0;}
    
};


//        leftChildIndex = 2 * index + 1;
//        rightChildIndex = 2 * index + 2;
//        parentIndex = (index + 1) / 2 - 1;

/*------------------------------------------------------------*/
/*Default constructor definition*/
template <typename V>
PriorityQueue<V>::PriorityQueue(int CAP)
{
    siz = 0;
    this->CAP = CAP;
    values = new V[CAP];
    
    for(int i = 0; i < CAP; i++){
        values[i] = V();
    }
}

/*------------------------------------------------------------*/
/*Copy constructor function definition*/
template <typename V>
PriorityQueue<V>::PriorityQueue(const PriorityQueue<V>& original){
    CAP = original.CAP; /*still just a copy*/
    siz = original.siz; /*still just a copy*/
    values = new V[CAP]; /*not a copy -- new object gets its own array*/
    
    for (int i = 0; i < CAP; i++) /*copy the contents of the array from the original...*/
        values[i] = original.values[i]; /*...to the copy*/
}

/*------------------------------------------------------------*/
/*Assignment operator function definition*/
template <typename V>
PriorityQueue<V>& PriorityQueue<V>::operator=(const PriorityQueue<V>& original)
{
    if (this != &original) /*of it's not a self copy...*/
    {
        /*do what the destructor does*/
        delete [] values;
        
        /*do what the copy constructor does*/
        CAP = original.CAP; /*still just a copy*/
        siz = original.siz; /*still just a copy*/
        values = new V[CAP]; /*not a copy -- new object gets its own array*/
        for (int i = 0; i < CAP; i++) /*copy the contents of the array from the original...*/
            values[i] = original.values[i]; /*...to the copy*/
    }
    return *this; /*return a self reference*/
}

/*------------------------------------------------------------*/
/*push function definition*/
template <typename V>
void PriorityQueue<V>::push(const V& thingy)
{
    if(siz == CAP)
    {
        CAP = CAP * 2;
    }
    
    /*copy new value into array index siz*/
    values[siz] = thingy;
    
    int index = siz;
    for( ; !(index == 0) ; )
    {
        if(index == 0)
        {
            break;
        }
        
        /*compute parent index of current index*/
        int parentIndex = ((index + 1) / 2 - 1);
        
        /*checks if value at array index is less than value at array parent index*/
        if(values[index] < values[parentIndex])
        {
            /*value at index is less than value at parent index*/
            break;
        }
        
        /*swap values at array current index and array parent index*/
        V temp = values[index];
        values[index] = values[parentIndex];
        values[parentIndex] = temp;
        
        index = parentIndex;
        
    }
    /*incrememnt siz*/
    siz++;
}

/*------------------------------------------------------------*/
/*pop function definition*/
template <typename V>
void PriorityQueue<V>::pop()
{
    int index = 0;
    V temp;
    
    for( ; !(index == siz) ; )
    {
        /*checks if there is no left child*/
        if((2 * index + 1) >= siz)
        {
            break;
        }
        
        /*checks if there is no right child*/
        if((2 * index + 2) >= siz)
        {
            values[index] = values[(2 * index + 1)];
            index = (2 * index + 1);
        }
        /*checks if value of the right child is less than the value of left child*/
        else if(values[(2 * index + 2)] < values[(2 * index + 1)])
        {
            values[index] = values[(2 * index + 1)];
            index = (2 * index + 1);
        }
        else
        {
            values[index] = values[(2 * index + 2)];
            index = (2 * index + 2);
        }
        
    }
    
    siz--;
    values[index] = values[siz];
    
    for( ; !(index == 0) ; )
    {
        if(values[index] < values[((index + 1) / 2 - 1)])
        {
            break;
        }
        
        /*swap the values at parent index and index*/
        temp = values[index];
        values[index] = values[((index + 1) / 2 - 1)];
        values[((index + 1) / 2 - 1)] = temp;
        
        index = ((index + 1) / 2 - 1);
    }
    
}

/*-----------------------------------------------------------------------*/

#endif




