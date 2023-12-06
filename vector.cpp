#include "vector.h"
#include <stdexcept>
#include <iostream>
#include <initializer_list>
#include <algorithm>


Custom_vector::Custom_vector():m_size{0}, m_capacity{0}, m_arr{nullptr} {};

Custom_vector::Custom_vector(int size) {
    m_size = size;
    m_capacity = m_size * 2;
    m_arr = new int[m_capacity];

    for (int i = 0; i < m_size; ++i) 
    {
        m_arr[i] = 0;
    }
};

 Custom_vector::Custom_vector(std::initializer_list<int> values) 
    : m_size(values.size()), m_capacity(values.size() * 2), m_arr(new int[m_capacity]) 
{
    std::copy(values.begin(), values.end(), m_arr);
};

Custom_vector::Custom_vector(const Custom_vector& other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_arr = new int[m_capacity];

    for(int i = 0; i < m_size; ++i)
    {
        m_arr[i] = other.m_arr[i];
    }
};

Custom_vector::Custom_vector(Custom_vector&& other) noexcept
: m_size{other.m_size}, 
  m_capacity{other.m_capacity}, 
  m_arr{other.m_arr}
{
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_arr = nullptr;
};

Custom_vector::~Custom_vector()
{
    delete[] m_arr;
};


void Custom_vector::push_back(int value) 
{
    if (m_size >= m_capacity) 
    {
        m_capacity *= 2;
        int* tmp = new int[m_capacity];

        for (int i = 0; i < m_size; ++i) 
        {
            tmp[i] = m_arr[i];
        }

        delete[] m_arr;
        m_arr = tmp;
    }

    m_arr[m_size] = value;
    ++m_size;
};

void Custom_vector::pop_back() 
{
    if (m_size > 0) 
    {
        --m_size;

        if (m_size < m_capacity / 4 && m_capacity > 4) 
        {
            m_capacity /= 2;
            int* tmp = new int[m_capacity];

            for (int i = 0; i < m_size; ++i) 
            {
                tmp[i] = m_arr[i];
            }

            delete[] m_arr;
            m_arr = tmp;
        }
    }
};


void Custom_vector::push_front(int value) {
    
    if (m_size >= m_capacity) 
    {
        m_capacity *= 2;
        int* tmp = new int[m_capacity];

        for (int i = 0; i < m_size; ++i) 
        {
            tmp[i + 1] = m_arr[i];
        }

        delete[] m_arr;
        m_arr = tmp;
    } 
    else 
    {
        for (int i = m_size; i > 0; --i) 
        {
            m_arr[i] = m_arr[i - 1];
        }
    }

    m_arr[0] = value;
    ++m_size;
};

void Custom_vector::pop_front()
{
    if(m_size > 0)
    {
        if(m_size < m_capacity / 4 && m_capacity > 4)
        {
            m_capacity /= 2;
            int* tmp = new int[m_capacity];

            for(int i = 0; i < m_size; ++i)
            {
                tmp[i] = m_arr[i + 1];
            }

            delete[] m_arr;
            m_arr = tmp;
            --m_size;
        }
    }
};

int Custom_vector::front() const
{
    if(m_size > 0)
    {
        return m_arr[0];

    }

    throw std::out_of_range("Index out of bounds, no element");
};

int Custom_vector::back() const
{
    if(m_size > 0)
    {
        return m_arr[m_size - 1];
    }

    throw std::out_of_range("Index out of bounds, no element");
};

void Custom_vector::swap(Custom_vector& other)
{
    
   int* tmp = new int[m_capacity];
   int current_size = m_size;
   int current_capacity = m_capacity;

   for(int i = 0; i < m_size; ++i)
   {
        tmp[i] = m_arr[i];
   }

   delete[] m_arr;
    m_arr = new int[other.m_capacity];
    m_size = other.m_size;
    m_capacity = other.m_capacity;

    for(int i = 0; i < m_size; ++i)
    {
        m_arr[i] = other.m_arr[i];
    }

    other.m_arr = tmp;
    other.m_size = current_size;
    other.m_capacity = current_capacity;
    
};

int Custom_vector::size() const
{
    return m_size;
};

void Custom_vector::clear()
{
    delete[] m_arr;
    m_arr = nullptr;
    m_size = 0;
    m_capacity = 0;
    
};

int* Custom_vector::data() const
{
    return m_arr;
};

bool Custom_vector::empty() const
{
    if(m_size == 0)
    {
        return true;
    }

    return false;
};

int Custom_vector::at(int index) const
{
    if(index < m_size)
    {
        return m_arr[index];
    }
    throw std::out_of_range("Index out of bounds");
};

void Custom_vector::traverse(void(*operation)(int)) const
{
    for(int i = 0; i < m_size; ++i)
    {
        operation(m_arr[i]);
    }
};


void Custom_vector::traverse(void(*operation)(int&))
{
    for(int i = 0; i < m_size; ++i)
    {
        operation(m_arr[i]);
    }
};

void Custom_vector::insert(int index, int element)
{
    if(index > m_size)
    {
        std::out_of_range("Index out of bounds");
        return;
    }

    if(m_size == m_capacity)
    {
        m_capacity*= 2;
        int* tmp = new int[m_capacity];

        for(int i = 0; i < m_size; ++i)
        {
            tmp[i] = m_arr[i];
        }

        delete[] m_arr;
        m_arr = tmp;
        tmp = nullptr;
    }

    for(int i = m_size; i > index; --i)
    {
        m_arr[i] = m_arr[i -1];
    }

    m_arr[index] = element;
    ++m_size;
}

Custom_vector& Custom_vector::operator=(const Custom_vector& other)
{
    if(this != &other)
    {
        delete[] m_arr;

        m_size = other.m_size;
        m_capacity = other.m_capacity;

        m_arr = new int[m_capacity];
 
        for(int i = 0; i < m_size; ++i)
        {
            m_arr[i] = other.m_arr[i];
        }

    }
    return *this;
};

Custom_vector& Custom_vector::operator=(Custom_vector&& other) noexcept
{
    if(this != &other)
    {
        delete m_arr;

        m_arr = other.m_arr;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_arr = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    return *this;
};


const int& Custom_vector::operator[](int index) const
{
    if(index < m_size)
    {
        return m_arr[index];
    }
    else
    {
        throw std::out_of_range("Index out of bounds");
    }
};

int& Custom_vector::operator[](int index) 
{
    if(index < m_size)
    {
        return m_arr[index];
    }
    else
    {
        throw std::out_of_range("Index out of bounds");
    }
};

bool Custom_vector::operator==(const Custom_vector& other) const
{
    if(m_size != other.m_size)
    {
        return false;
    }
    else
    {
        for(int i = 0; i < m_size; ++i)
        {
            if(m_arr[i] != other.m_arr[i])
            {
                return false;
            }
        }
    }

    return true;
};

std::ostream& operator<<(std::ostream& os, const Custom_vector& vector) {
    os << "[";
    for (int i = 0; i < vector.m_size; ++i) {
        os << vector.m_arr[i];
        if (i < vector.m_size - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
};

std::istream& operator>>(std::istream& is, Custom_vector& vector)
{
    int value;
    while(is >> value)
    {
        vector.push_back(value);
    }
    return is;
};


Custom_vector Custom_vector::operator+(const Custom_vector& other) const
{
    int current_m_size = std::max(m_size, other.m_size);

    Custom_vector joined;
    joined.m_size = current_m_size;
    joined.m_capacity = current_m_size * 2;

    joined.m_arr = new int[joined.m_capacity];

    if(!joined.m_arr)
    {
        throw std::bad_alloc();
    }

    for(int i = 0; i < current_m_size; ++i)
    {
        int this_value = 0;
        if(i < m_size)
        {
            this_value = m_arr[i];
        }

        int other_value = 0;
        if(i < other.m_size)
        {
            other_value = other.m_arr[i];
        }

        joined.m_arr[i] = this_value + other_value;
    }

    return joined;
};

Custom_vector Custom_vector::operator-(const Custom_vector& other) const
{
    int curren_m_size = std::max(m_size, other.m_size);

    Custom_vector subtracted;
    subtracted.m_size = curren_m_size;
    subtracted.m_capacity = curren_m_size * 2;

    subtracted.m_arr = new int[subtracted.m_capacity];

    if(!subtracted.m_arr)
    {
        throw std::bad_alloc();
    }

    for(int i = 0; i < curren_m_size; ++i)
    {
        int this_value = 0;
        if(i < m_size)
        {
            this_value = m_arr[i];
        }

        int other_value = 0;
        if(i < other.m_size)
        {
            other_value = other.m_arr[i];
        }

        subtracted.m_arr[i] = this_value - other_value;
    }

    return subtracted;
};

Custom_vector Custom_vector::operator*(const Custom_vector& other) const
{
    int current_m_size = std::max(m_size, other.m_size);

    Custom_vector multiplied;
    multiplied.m_size = current_m_size;
    multiplied.m_capacity = current_m_size * 2;

    multiplied.m_arr = new int[multiplied.m_capacity];

    if(!multiplied.m_arr)
    {
        throw std::bad_alloc();
    }

    for(int i = 0; i < current_m_size; ++i)
    {
        int this_value = 0;
        if(i < m_size)
        {
            this_value = m_arr[i];
        }

        int other_value = 0;
        if(i < other.m_size)
        {
            other_value = other.m_arr[i];
        }

        multiplied.m_arr[i] = this_value * other_value;
    }

    return multiplied;
};

Custom_vector Custom_vector::operator/(const Custom_vector& other) const
{
    Custom_vector divided;
    int current_m_size = std::max(m_size, other.m_size);
    divided.m_size = current_m_size;
    divided.m_capacity = current_m_size * 2;

    divided.m_arr = new int[divided.m_capacity];

    for(int i = 0; i < current_m_size; ++i)
    {
        int this_value = (i < m_size) ? m_arr[i] : 0;
        int other_value = (i < other.m_size) ? other.m_arr[i] : 1; 

        divided.m_arr[i] = this_value / other_value;
    }

    return divided;
}
Custom_vector Custom_vector::operator%(int divider) const
{
    Custom_vector remainder;
    remainder.m_size = m_size;
    remainder.m_capacity = m_capacity;

    remainder.m_arr = new int[m_capacity];

    for(int i = 0; i < m_size; ++i)
    {
        remainder.m_arr[i] = m_arr[i] % divider;
    }

    return remainder;
};

Custom_vector& Custom_vector::operator%=(int divider) 
{

    for(int i = 0; i < m_size; ++i)
    {
        m_arr[i] = m_arr[i] % divider;
    }

    return *this;
};

Custom_vector& Custom_vector::operator/=(int divider) 
{
    if(divider == 0)
    {
        throw std::runtime_error("Division by zero!");
    }
    for(int i = 0; i < m_size; ++i)
    {
        m_arr[i] = m_arr[i] / divider;
    }

    return *this;
};

Custom_vector& Custom_vector::operator*=(int multiplier)
{
    for(int i = 0; i < m_size; ++i)
    {
        m_arr[i] = m_arr[i] * multiplier;
    }

    return *this;
};

Custom_vector& Custom_vector::operator+=(int adder)
{
    for(int i = 0; i < m_size; ++i)
    {
        m_arr[i] = m_arr[i] + adder;
    }

    return *this;
};

Custom_vector& Custom_vector::operator-=(int subtractor)
{
    for(int i = 0; i <m_size; ++i)
    {
        m_arr[i] = m_arr[i] - subtractor;
    }
    return *this;
};

Custom_vector& Custom_vector::operator++()
{
    for(int i = 0; i < m_size; ++i)
    {
        ++m_arr[i];
    }
    return *this;
};

Custom_vector& Custom_vector::operator--()
{ 
    for(int i = 0; i < m_size; ++i)
    {
        --m_arr[i];
    }
    return*this;
};


Custom_vector Custom_vector::operator++(int) 
{   
    Custom_vector tmp(*this);
    ++(*this);
    return tmp;

};      

Custom_vector Custom_vector::operator--(int)
{
    Custom_vector tmp(*this);
    --(*this);
    return tmp;
};

Custom_vector Custom_vector::operator|(const Custom_vector& other) const
{
    int current_size = std::max(m_size, other.m_size);
    Custom_vector result;
    result.m_size = current_size;
    result.m_capacity = current_size * 2;
    result.m_arr = new int[result.m_capacity];

    for(int i = 0; i < current_size; ++i)
    {
        result.m_arr[i] = m_arr[i] | other.m_arr[i];
    }

    return result;
};

Custom_vector Custom_vector::operator&(const Custom_vector& other) const
{
    int current_size = std::max(m_size, other.m_size);
    Custom_vector result;
    result.m_size = current_size;
    result.m_capacity = current_size * 2;
    result.m_arr = new int[result.m_capacity];

    for(int i = 0; i < current_size; ++i)
    {
        result.m_arr[i] = m_arr[i] & other.m_arr[i];
    }
    
    return result;
};

Custom_vector Custom_vector::operator^(const Custom_vector& other) const
{
    int current_size  = std::max(m_size, other.m_size);
    Custom_vector result;
    result.m_size = current_size;
    result.m_capacity = current_size * 2;
    result.m_arr = new int[result.m_capacity];

    for(int i = 0; i < current_size; ++i)
    {
        result.m_arr[i] = m_arr[i] ^ other.m_arr[i];    
    }
    return result;
};

Custom_vector Custom_vector::operator~() const
{
    Custom_vector result;
    result.m_size = m_size;
    result.m_capacity = m_capacity;
    result.m_arr = new int[m_capacity];

    for(int i = 0; i < m_size; ++i)
    {
        result.m_arr[i] = ~m_arr[i];
    }
    return result;
};

