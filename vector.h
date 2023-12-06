#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>

class Custom_vector
{
    public:
        Custom_vector();
        explicit Custom_vector(int size);
        Custom_vector(std::initializer_list<int> values);
        Custom_vector(const Custom_vector& other);
        Custom_vector(Custom_vector&& other) noexcept;
        ~Custom_vector();
        void push_back(int value);
        void pop_back();
        void push_front(int value);  
        void pop_front();            
        int front() const;                
        int back() const;               
        void swap(Custom_vector& other);                
        int size() const;             
        void clear();   
        int* data() const;                
        bool empty() const;
        int at(int index) const;
        void traverse(void(*operation)(int&)); 
        void traverse(void(*operation)(int)) const;           
        void insert(int index, int element);
        const int& operator[](int index) const;
        bool operator==(const Custom_vector& other) const;
        int& operator[](int index);
        Custom_vector& operator=(const Custom_vector& other);
        Custom_vector& operator=(Custom_vector&& other) noexcept;
        Custom_vector operator+(const Custom_vector& other) const;
        Custom_vector operator-(const Custom_vector& other) const;
        Custom_vector operator*(const Custom_vector& other) const;
        Custom_vector operator/(const Custom_vector& other) const; 
        Custom_vector operator%(int divider) const; 
        Custom_vector& operator%=(int divider);
        Custom_vector& operator/=(int divider);
        Custom_vector& operator*=(int multiplier);
        Custom_vector& operator+=(int adder);
        Custom_vector& operator-=(int subtractor);
        Custom_vector& operator++();
        Custom_vector& operator--();
        Custom_vector operator++(int);    
        Custom_vector operator--(int);
        Custom_vector operator|(const Custom_vector& other) const;    
        Custom_vector operator&(const Custom_vector& other) const;
        Custom_vector operator^(const Custom_vector& other) const;
        Custom_vector operator~() const;
        friend std::ostream& operator<<(std::ostream& os, const Custom_vector& vector);
        friend std::istream& operator>>(std::istream& is, Custom_vector& vector);
    private:
        int m_size;
        int m_capacity;
        int* m_arr;
};
#endif



