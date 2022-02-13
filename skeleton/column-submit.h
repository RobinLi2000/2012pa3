// column-submit.h

#ifndef COLUMN_SUBMIT_H_
#define COLUMN_SUBMIT_H_

#include <string>
#include <iostream>

/// TODO: Add the definitions of inline global functions below

template <>
inline std::string Column<int>::as_string_at(int index) const {
    return std::to_string(this->operator[](index));
}

template <>
inline std::string Column<bool>::as_string_at(int index) const {
    if (this->operator[](index) == true)
    return "true";
    else
    return "false";
}

template <>
inline std::string Column<std::string>::as_string_at(int index) const {
    return this->operator[](index);
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Column<T>& column) {
    return (column.operator<<(os));
}

/// TODO: Add the missing function definitions of the Column template below

template <typename T>
void Column<T>::reserve_capacity(int new_capacity) {
    if (new_capacity > capacity_)
    {
        T *new_list = new T[new_capacity];
        for (int i=0; i<new_capacity; i++)
        {
            new_list[i] = default_value_;
        }
        for (int i=0; i < size_; i++)
        {
            new_list[i] = data_[i];
        }
        delete [] data_;
        data_ = new_list;
        new_list = nullptr;
        delete [] new_list;
        capacity_ = new_capacity;      
    }
}

template <typename T>
void Column<T>::expand_size(int new_size) {
    if (new_size > size_ && new_size <= capacity_)
    {
        for (int i=size_; i<new_size; i++)
        {
            data_[i]=default_value_;
        }
        size_ = new_size;
    }
    if (new_size > capacity_)
    {
        Column::reserve_capacity(new_size);
        for (int i=size_; i<new_size; i++)
        {
            data_[i] = default_value_;
        }
        size_ = new_size;
    }
}

template <typename T>
void Column<T>::append(const Column<T>& other) {
    if (other.get_size() <= (capacity_ - size_))
    {
        for (int i=0; i<other.get_size(); i++)
        {
            data_[i+size_] = other.data_[i];
        }
        size_ += other.get_size();
    }
    else
    {
        int current_size = size_ + other.get_size();
        reserve_capacity(current_size);
        //expand_size(current_size);
        for (int i=0; i<other.get_size(); i++)
        {
            data_[i+size_] = other.data_[i];
        }  
        size_ = current_size;  
    }
    
}

template <typename T>
const Column<T>& Column<T>::operator=(const Column<T>& other) {
    int a = other.get_size();
    T *newlist = new T[a];
    for (int i=0; i<other.get_size(); i++)
    {
        newlist[i]=other.at(i);
    }
    //this->data_ = nullptr;
    //delete [] this->data_;
    delete [] data_;
    this->capacity_ = other.get_capacity();
    this->data_ = newlist;
    this->set_name(other.get_name());
    this->size_ = other.get_size();
    this->default_value_ = other.default_value_;
    newlist = nullptr;
    delete [] newlist;
    return *this;
}

template <typename T>
Column<T> Column<T>::operator+(const Column<T>& other) const {
    Column<T> result(this->default_value_, size_, size_, "NULL");
   //int new_cap = this->get_capacity();
    for (int i=0; i<other.get_size(); i++)
    {
        result.at(i) = this->at(i) + other.at(i);
    }
    return result;
}

template <typename T>
const Column<T>& Column<T>::operator+=(const Column<T>& other) {
    for (int i=0; i<size_; i++)
    {
        this->at(i) = this->at(i)+other.at(i);
    }
    //this->capacity_ = other.get_capacity();
    return *this;    
}

template <typename T>
Column<bool> Column<T>::operator==(const Column<T>& other) const {
    Column<bool> result(false, size_, size_, "NULL");
    for (int i=0; i<size_; i++)
    {
        if (this->at(i) == other.at(i))
        result.at(i)=true;
        else
        result.at(i)=false;
    }
    return result;
}

template <typename T>
Column<bool> Column<T>::operator<(const Column<T>& other) const {
    Column<bool> result(false, size_, size_, "NULL");
    for (int i=0; i<size_; i++)
    {
        if (this->at(i) < other.at(i))
        result.at(i)=true;
        else
        result.at(i)=false;
    }
    return result;
}

template <typename T>
Column<bool> Column<T>::operator==(const T& other) const {
    Column<bool> result(false, size_, size_, "NULL");
    for (int i=0; i<size_; i++)
    {
        if (this->data_[i] == other)
        result.at(i) = true;
        else 
        result.at(i) = false;
    }
    return result;
}

template <typename T>
Column<bool> Column<T>::operator<(const T& other) const {
    Column<bool> result(false, size_, size_, "NULL");
    for (int i=0; i<size_; i++)
    {
        if (this->data_[i] < other)
        result.at(i) = true;
        else 
        result.at(i) = false;
    }
    return result;
}

template <typename T>
Column<bool> Column<T>::operator!() const {
    Column<bool> result(default_value_, size_, size_, "NULL");
    for(int i=0; i<size_; i++)
    {
        if (this->data_[i] == true)
        result.at(i) = false;
        else 
        result.at(i) = true;
    }
    return result;
}

template <typename T>
Column<bool> Column<T>::operator&&(const Column<T>& other) const {
    Column<bool> result(default_value_, size_, size_, "NULL");
    for (int i=0; i<size_; i++)
    {
        if (this->data_[i] == true && other.at(i) == true)
        result.at(i) = true;
        else 
        result.at(i) = false;
    }
    return result;
}


template <typename T>
T Column<T>::operator[](int index) const {
    if (index>=0)
    return this->data_[index];
    else 
    return this->data_[size_+index];
}

// hardest one

template <typename T>
T& Column<T>::operator[](int index) {
    if (index>=0)
    return this->data_[index];
    else 
    return this->data_[size_+index];
}
/*
template <typename T>
Column<T>::Column(const Column<T>& other, const Column<bool>& selector) {
    int result_size=0;
    for (int i=0; i<other.get_size(); i++)
    {
        if (selector.at(i) == true)
        result_size++;
    }
    other.re
    for (int i=0; i<result_size; i++)
    {
        other.data_[i]=default_value_;
    }
    other.name_="NULL";
}

template <typename T>
Column<T> Column<T>::operator[](const Column<bool>& selector) const {
    Column<T> result(*this, selector);
    int j=0;
    for (int i=0; i<size_; i++)
    {
        if (selector.at(i)==true)
        {
            result.at(j)=this->at(i);
            j++;
        }
    }

    return result;
}
*/

template <typename T>
Column<T>::Column(const Column<T> &other, const Column<bool> &selector)
{
    *this = *other[selector]; 
}

template <typename T>
Column<T> Column<T>::operator[](const Column<bool> &selector) const
{
    int result_size = 0;
    for (int i = 0; i < selector.get_size(); i++)
    {
        if (selector [i]== true)
        {
            result_size++;
        }
    }
     
    Column<T> result(default_value_, result_size, result_size, "NULL");
    int j = 0;
    for (int i = 0; i < size_; i++)
    {
        if (selector.at(i) == true)
        {
            result.data_[j] = data_[i];
            j++;
        }
    }
    return result;
}
#endif  // COLUMN_SUBMIT_H_
