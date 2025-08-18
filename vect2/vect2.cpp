#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {}
vect2::vect2(int x, int y) : x(x), y(y) {}
vect2::vect2(const vect2 &copy)
{
    this->x = copy.x;
    this->y = copy.y;
}

int vect2::get_x()const
{
    return (this->x);
}
int vect2::get_y()const
{
    return (this->y);
}

std::ostream& operator<<(std::ostream &os, const vect2 &s)
{
    os << "{" << s.get_x() << ", " << s.get_y() << "}";
    return os;
}

vect2& vect2::operator=(const vect2 &src)
{
    this->x = src.x;
    this->y = src.y;
    return *this;
}

int vect2::operator[](int n) const
{
    if (n == 0)
        return this->x;
    else if (n == 1)
        return this->y;
}

int& vect2::operator[](int n)
{
    if (n == 0)
        return this->x;
    else if (n == 1)
        return this->y;
}

vect2& vect2::operator++()
{
    this->x++;
    this->y++;
    return (*this);
}

vect2 vect2::operator++(int)
{
    vect2 tmp(*this);
    this->x++;
    this->y++;
    return (tmp);
}

vect2& vect2::operator--()
{
    this->x--;
    this->y--;
    return (*this);
}

vect2 vect2::operator--(int)
{
    vect2 tmp(*this);
    this->x--;
    this->y--;
    return (tmp);
}

vect2 vect2::operator+(const vect2 &src) const
{
    int sum_x = this->x + src.x;
    int sum_y = this->y + src.y;
    return vect2(sum_x, sum_y);
}

vect2& vect2::operator+=(const vect2 &src)
{
    *this = *this + src;
    return (*this);
}

vect2 vect2::operator-(const vect2 &src) const
{
    int sum_x = this->x - src.x;
    int sum_y = this->y - src.y;
    return vect2(sum_x, sum_y);
}

vect2& vect2::operator-=(const vect2 &src)
{
    *this = *this - src;
    return (*this);
}

bool vect2::operator==(const vect2 &src) const
{
    if (this->x == src.x && this->y == src.y)
        return true;
    return false;
}

bool vect2::operator!=(const vect2 &src) const
{
    return !(*this == src);
}

vect2 vect2::operator*(int n) const
{
    return vect2(this->x * n, this->y * n);
}

vect2 operator*(int n, const vect2 &v)
{
    return (v * n);
}

vect2& vect2::operator*=(int n)
{
    *this = *this * n;
    return (*this);
}

vect2 vect2::operator-() const
{
    return vect2(-this->x, -this->y);
}