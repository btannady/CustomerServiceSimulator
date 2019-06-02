/*Programmer: Benedict Tannady*/
/*Programmer's ID: 1591141*/

#include <cstdlib> /*min()*/

#ifndef DynamicArray_h
#define DynamicArray_h

template <typename V>
class DynamicArray{
    
    V* values;
    int cap;
    V dummy;
    
public:
    
    /*default constructor; default capacity is 2*/
    DynamicArray(int = 2);
    
    /*copy constructor*/
    DynamicArray(const DynamicArray<V>&);
    
    /*destructor*/
    ~DynamicArray(){
        delete [] values;
    }
    
    /*assignment operator*/
    DynamicArray<V>& operator=(const DynamicArray<V>&);
    
    /*square bracket setter function; returns class data member by reference, extends array cap if index is out of range*/
    V& operator[](int index);
    
    /*square bracket getter function; takes index (0-cap), returns element located in index*/
    V operator[](int index) const;
    
    /*capacity setter function*/
    void capacity(int);
    
    /*capacity getter function; returns cap, the data structure's capacity*/
    int capacity() const{
        return cap;
    };
    
};

/*------------------------------------------------------------*/
/*constructor definition*/
template <typename V>
DynamicArray<V>::DynamicArray(int cap){
    dummy = V();
    this->cap = cap;
    values = new V[cap];
}

/*------------------------------------------------------------*/
/*copy constructor definition*/
template <typename V>
DynamicArray<V>::DynamicArray(const DynamicArray<V>& original)
{
    cap = original.cap; /*still just a copy*/
    values = new V[cap]; /*not a copy -- new object gets its own array*/
    
    for (int i = 0; i < cap; i++) /*copy the contents of the array from the original...*/
        values[i] = original.values[i]; /*...to the copy*/
    dummy = original.dummy; /*not really necessary because who cares what dummy contains?*/
}

/*------------------------------------------------------------*/
/*assignment operator function definition*/
template <typename V>
DynamicArray<V>& DynamicArray<V>::operator=(const DynamicArray<V>& original)
{
    if (this != &original) /*of it's not a self copy...*/
    {
        /*do what the destructor does*/
        delete [] values;
        
        /*do what the copy constructor does*/
        cap = original.cap; /*still just a copy*/
        values = new V[cap]; /*not a copy -- new object gets its own array*/
        for (int i = 0; i < cap; i++) /*copy the contents of the array from the original...*/
            values[i] = original.values[i]; /*...to the copy*/
        dummy = original.dummy; /*not really necessary because who cares what dummy contains?*/
    }
    return *this; /*return a self reference*/
}

/*------------------------------------------------------------*/
/*capacity setter function definition*/
template <typename V>
void DynamicArray<V>::capacity(int cap)
{
    /*allocate a new array with the new capacity*/
    V* temp = new V[cap];
    
    /*get the lesser of the new and old capacities*/
    int limit = min(cap, this->cap); /*requires the C++ "algorithm" library*/
    
    /*copy the contents*/
    for (int i = 0; i < limit; i++)
        temp[i] = values[i];
    
    /*set added values to their defaults*/
    for (int i = limit; i < cap; i++)
        temp[i] = V();
    
    /*deallocate original array*/
    delete [] values;
    
    /*switch newly allocated array into the object*/
    values = temp;
    
    /*update the capacity*/
    this->cap = cap;
}

/*------------------------------------------------------------*/
/*square bracket setter function definition*/
template <typename V>
V& DynamicArray<V>::operator[](int index){
    if (index < 0){
        return dummy;
    }
    if (index >= cap){
        capacity(2 * index);
    }
    return values[index];
};

/*------------------------------------------------------------*/
/*square bracket getter function definition*/
template <typename V>
V DynamicArray<V>::operator[](int index) const{
    if(index < 0 || index >= cap){
        return V();
    }
    return values[index];
};

/*------------------------------------------------------------*/


#endif


