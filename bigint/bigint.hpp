#ifndef BIGINT_HPP
# define BIGINT_HPP
# include <sstream>
# include <string>
# include <vector>
# include <iostream>
# include <algorithm>

class bigint{

    private:
        std::string number;
    
    public:
        bigint();
        bigint(unsigned long long num);
        bigint(const std::string &s);
        bigint(const bigint &copy);
        const std::string get_num() const;
        bool operator>(const bigint &src) const;
        bool operator<(const bigint &src) const;
        bool operator<=(const bigint &src) const;
        bool operator>=(const bigint &src) const;
        bool operator==(const bigint &src) const;
        bool operator!=(const bigint &src) const;
        bigint operator+(const bigint &src) const;
        bigint& operator+=(const bigint &src);
        bigint operator-(const bigint &src) const;
        bigint& operator-=(const bigint &src);
        bigint& operator++();
        bigint operator++(int);
        bigint& operator--();
        bigint operator--(int);
        bigint operator<<(int n)const;
        bigint& operator<<=(int n);
        bigint operator>>(int n)const;
        bigint& operator>>=(int n);


};

std::ostream& operator<<(std::ostream &os, const bigint &n);

#endif