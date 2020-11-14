#ifndef LSL_H
#define LSL_H
#include <iostream>
#include <stdexcept>
#include <memory> //allows smart pointers

using namespace std;

template<typename T>
class LSL
{
private:
    struct NodeLSL
    {
        T data;
        shared_ptr<NodeLSL> next;
        //Constructor
        //elem : Element to be added to the list
        //n : pointer to the next node
        //example: NodeLSL(33);
        //example: NodeLSL(33, nextNode);
        NodeLSL(const T& elem, shared_ptr<NodeLSL> n = nullptr)
        {
            data = elem;
            next = n;
        }
    };

    size_t listSize;
    shared_ptr<NodeLSL> listFront;
    shared_ptr<NodeLSL> listBack;

public:
    LSL()
    {
        listSize = 0;
        listFront = nullptr;
        listBack = nullptr;
    }

    bool empty() const;
    size_t size() const;
    void push_front(const T& element);
    void push_back(const T& element);
    const T& front() const;
    const T& back() const;
    void pop_front();
    void pop_back();
    void insert(size_t position, const T& element);
    void erase(size_t position);
    void clear();
    void remove(const T& value);
    T& operator [] (size_t position);
};

template<typename T>
bool LSL<T>::empty() const
{
    return listSize == 0;
}

template<typename T>
size_t LSL<T>::size() const
{
    return listSize;
}

template<typename T>
void LSL<T>::push_front(const T& element)
{
    if (empty())
    {
        listFront = make_shared<NodeLSL>(element);
        listBack = listFront;
    }
    else
    {
        shared_ptr<NodeLSL> temp = make_shared<NodeLSL>(element, listFront);
        listFront = temp;
    }

    ++listSize;
}

template<typename T>
void LSL<T>::push_back(const T& element)
{
    if (empty())
    {
        listBack = make_shared<NodeLSL>(element);
        listFront = listBack;
    }
    else
    {
        shared_ptr<NodeLSL> temp = make_shared<NodeLSL>(element);
        listBack->next = temp;
        listBack = temp;
    }

    ++listSize;
}

template<typename T>
const T& LSL<T>::front() const
{
    if (empty())
    {
        throw runtime_error("Trying front() from empty list");
    }

    return listFront->data;
}

template<typename T>
const T& LSL<T>::back() const
{
    if (empty())
    {
        throw runtime_error("Trying back() from empty list");
    }

    return listBack->data;
}

template<typename T>
void LSL<T>::pop_front()
{
    if (empty())
    {
        throw runtime_error("Trying pop_front() from empty list");
    }
    if (size() == 1)
    {
        listFront = nullptr;
        listBack = nullptr;
    }
    else
    {
        listFront = listFront->next;
    }
    --listSize;
}

template<typename T>
void LSL<T>::pop_back()
{
    if (empty())
    {
        throw runtime_error("Trying pop_back() from empty list");
    }
    if (size() == 1)
    {
        listFront = nullptr;
        listBack = nullptr;
    }
    else
    {
        shared_ptr<NodeLSL> temp = listFront;
        while (temp->next != listBack)
        {
            temp = temp->next;
        }
        temp->next = nullptr;
        listBack = temp;
    }
     --listSize;
}

template<typename T>
void LSL<T>::insert(size_t position, const T& element)
{
    if (empty())
    {
        throw runtime_error("Trying insert() in empty list");
    }
    if (position > size())
    {
        throw out_of_range("Trying insert() in non valid position");
    }
    if (position == 0)
    {
        push_front(element);
    }
    else if (position == size())
    {
        push_back(element);
    }
    else
    {
        shared_ptr<NodeLSL> temp = listFront;
        for (size_t i(0); i < position-1; ++i)
        {
            temp = temp->next;
        }
        shared_ptr<NodeLSL> newNode = make_shared<NodeLSL>(element, temp->next);
        temp->next = newNode;
        ++listSize;
    }
}

template<typename T>
void LSL<T>::erase(size_t position)
{
    if (empty())
    {
        throw runtime_error("Trying erase() from empty list");
    }
    if (position >= size())
    {
        throw out_of_range("Trying erase() in non valid position");
    }
    if (position == 0)
    {
        pop_front();
    }
    else if (position == size()-1)
    {
        pop_back();
    }
    else
    {
        shared_ptr<NodeLSL> temp = listFront;
        for (size_t i(0); i < position-1; ++i)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        --listSize;
    }
}

template<typename T>
void LSL<T>::clear()
{
    while (!empty())
    {
        pop_front();
    }
}

template<typename T>
void LSL<T>::remove(const T& value)
{
    if (empty())
    {
        throw runtime_error("Trying remove() from empty list");
    }

    T data;
    size_t i(0);
    shared_ptr<NodeLSL> temp = listFront;

    while(temp != nullptr)
    {
        data = temp->data;
        temp = temp->next;
        if (data == value)
        {
            erase(i);
            --i;
        }
        ++i;
    }
}

template<typename T>
T& LSL<T>::operator[](size_t position)
{
    if (empty())
    {
        throw runtime_error("Trying [] from empty list");
    }
    if (position >= size())
    {
        throw out_of_range("Trying [] in non valid position");
    }

    shared_ptr<NodeLSL> temp = listFront;
    for (size_t i(0); i < position; ++i)
    {
        temp = temp->next;
    }
    return temp->data;
}
#endif // LSL_H
