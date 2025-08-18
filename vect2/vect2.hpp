#ifndef VECT2_HPP
# define VECT2_HPP

#include <iostream>

class vect2
{
    private:
        int x;
        int y;
    public:
        vect2();
        vect2(int x, int y);
        vect2(const vect2 &copy);
        int get_x()const;
        int get_y()const;
        vect2& operator=(const vect2 &src);
        int operator[](int n) const;
        int& operator[](int n);
        vect2& operator++();
        vect2 operator++(int);
        vect2& operator--();
        vect2 operator--(int);
        vect2 operator+(const vect2 &src) const;
        vect2& operator+=(const vect2 &src);
        vect2 operator-(const vect2 &src) const;
        vect2& operator-=(const vect2 &src);
        bool operator==(const vect2 &src) const;
        bool operator!=(const vect2 &src) const;
        vect2 operator*(int n) const;
        vect2& operator*=(int n);
        vect2 operator-() const;
};

std::ostream& operator<<(std::ostream &os, const vect2 &s);
vect2 operator*(int n, const vect2 &v);

# endif