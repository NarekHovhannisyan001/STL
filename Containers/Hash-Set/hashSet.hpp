#ifndef MYSET_HPP
#define MYSET_HPP

#include "/Users/narek/Documents/PicsartAcademy/stdVector/Vector.h"

#include <forward_list>


template <class T>
class MySet {

public:

    MySet();
    ~MySet();


public:
    void insert(const T& val);
    void remove(const T& val);
    bool find(const T& val) const;
    double getLF() const;



private:
    template <class R>
    size_t hashFunction(const R& val,size_t size) const;
    void reHash();
    bool is_prime(size_t num);
    size_t next_prime(size_t num);

private:
    Vector<std::forward_list<T>> m_bucket;
    size_t m_size;

};




#include "hashSet.tpp"


#endif  //MYSET_HPP