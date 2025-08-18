#include "bigint.hpp"

bigint::bigint()
{
    number = "0";
}

bigint::bigint(unsigned long long num)
{
    std::ostringstream oss;
    oss << num;
    number = oss.str();
}

bigint::bigint(const std::string &s)
{
    // remove space
    size_t start = 0;
    while (start < s.size() && s[start] == ' ')
        ++start;
    size_t end = s.size();
    while(end > 0 && s[end - 1] == ' ')
        --end;
    std::string clean = s.substr(start, end - start);

    size_t pos = clean.find_first_not_of('0');
    if (pos == std::string::npos)
        number = "0"; // ca veut dire c'est zero si par exemple ("00000")
    else
        number = clean.substr(pos); // c'est genre 5 si ("0005")
}

bigint::bigint(const bigint &copy)
{
    this->number = copy.number;
}

const std::string bigint::get_num() const
{
    return (this->number);
}

std::ostream& operator<<(std::ostream &os, const bigint &n)
{
    os << n.get_num();
    return os;
}

bool bigint::operator>(const bigint &src) const
{
    std::string a = this->number;
    std::string b = src.number;

    if (a.size() != b.size())
        return (a.size() > b.size());

    for (int i = 0; i < a.size() ; i++)
    {
        if (a[i] != b[i])
            return (a[i] > b[i]);
    }
    return false;
}

bool bigint::operator<(const bigint &src) const
{
    std::string a = this->number;
    std::string b = src.number;

    if (a.size() != b.size())
        return (a.size() < b.size());
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            return (a[i] < b[i]);
    }
    return false;
}

bool bigint::operator<=(const bigint &src) const
{
    return !(*this > src);
}

bool bigint::operator>=(const bigint &src) const
{
    return !(*this < src);
}

bool bigint::operator==(const bigint &src) const
{
    std::string a = this->number;
    std::string b = src.number;
    if (a.size() != b.size())
        return false;
    for (int i = 0; i < a.size() ; i++)
    {
        if(a[i] != b[i])
            return false;
    }
    return true;
}

bool bigint::operator!=(const bigint &src) const
{
    return !(*this == src);
}

bigint bigint::operator+(const bigint &src) const
{
    std::string a = this->number;
    std::string b = src.number;
    std::string res;
    int carry = 0;

    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    
    size_t n = std::max(a.size(), b.size());
    for (int i = 0; i < n || carry; i++)
    {
        int digit_a = i < a.size() ? a[i] - '0' : 0;
        int digit_b = i < b.size() ? b[i] - '0' : 0;
        int sum = digit_a + digit_b + carry;
        res.push_back((sum % 10 ) + '0'); 
        carry = sum / 10;
    }

    std::reverse(res.begin(), res.end());
    return (bigint(res));
}

bigint& bigint::operator+=(const bigint &other)
{
    *this = *this + other;
    return (*this);
}


bigint bigint::operator-(const bigint &src) const
{
    std::string a = this->number;
    std::string b = src.number;
    if (src > *this)
        return bigint("0");
    
    std::string res;
    int borrow = 0;

    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    
    size_t n = std::max(a.size(), b.size());
    for (int i = 0; i < n ; i++)
    {
        int digit_a = a[i] - '0' - borrow;
        int digit_b = i < b.size() ? b[i] - '0' : 0;
        int sous = 0;
        if (digit_a < digit_b)
        {
            sous = 10 + digit_a - digit_b;
            borrow = 1;
        }
        else
            sous = digit_a - digit_b;
        res.push_back(sous + '0'); 
    }

    std::reverse(res.begin(), res.end());
    return (bigint(res));
}

bigint& bigint::operator-=(const bigint &src)
{
    *this = *this - src;
    return *this;
}

bigint& bigint::operator++()
{
    *this += 1;
    return *this;
}
bigint bigint::operator++(int)
{
    bigint tmp(*this);
    *this += 1;
    return tmp;
}

bigint& bigint::operator--()
{
    *this -= 1;
    return *this;
}
bigint bigint::operator--(int)
{
    bigint tmp(*this);
    *this -= 1;
    return tmp;
}

bigint bigint::operator<<(int n)const
{
    std::string new_str;
    new_str = this->number;
    for (int i = 0; i < n; i++)
    {
        new_str.push_back('0');
    }
    return bigint(new_str);
}

bigint& bigint::operator<<=(int n)
{
    *this = *this << n;
    return *this;
}

bigint bigint::operator>>(int n) const
{
    std::string new_str;
    new_str = this->number;
    if (n >= new_str.size())
        return bigint("0");
    for (int i = 0; i < n ; i++)
    {
        new_str.pop_back();
    }
    return (bigint(new_str));
}

bigint& bigint::operator>>=(int n)
{
    *this = *this >> n;
    return *this;
}