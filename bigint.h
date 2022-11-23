#pragma once
#include <string>
#include <deque>
#include <vector>

class BigInt {

public:
    BigInt();
    BigInt(int);
    BigInt(char*);
    BigInt(std::string); // бросать исключение std::invalid_argument при ошибке
    BigInt(const BigInt&);
    ~BigInt();

    BigInt& operator=(const BigInt&);  //возможно присваивание самому себе!

    BigInt operator~() const;

    BigInt& operator++();
    const BigInt operator++(int);
    BigInt& operator--();
    const BigInt operator--(int) const;

    BigInt& operator+=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator%=(const BigInt&);

    BigInt& operator^=(const BigInt&);
    BigInt& operator&=(const BigInt&);
    BigInt& operator|=(const BigInt&);

    BigInt operator+() const;  // unary +
    BigInt operator-() const;  // unary -

    bool operator==(const BigInt&) const;
    bool operator==(const int&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;

    operator int() const;
    operator std::string() const;

    size_t size() const;  // size in bytes

    friend BigInt operator+(const BigInt&, const BigInt&);
    friend BigInt operator-(const BigInt&, const BigInt&);
    friend BigInt operator*(const BigInt&, const BigInt&);
    friend BigInt operator/(const BigInt&, const BigInt&);
    friend BigInt operator%(const BigInt&, const BigInt&);

    //доделать:
    friend BigInt operator^(const BigInt&, const BigInt&); //xor!!!!!!!
    friend BigInt operator&(const BigInt&, const BigInt&); //and!!!!!!!
    friend BigInt operator|(const BigInt&, const BigInt&); //or!!!!!!!



    //void toDecimal(std::vector<bool>&);
    bool even() const;
    bool odd() const;
    
    void _remove_leading_zeros();
    BigInt m_pow(const BigInt&, const BigInt&);

    std::vector<unsigned> m_data;
private:
    bool is_negative;
    bool m_negative;
    enum { BASE = 10 }; //Base - система исчисления
    BigInt plus(const BigInt& lhs, const BigInt& rhs);
    BigInt minus(const BigInt& lhs, const BigInt& rhs);
};



//std::ostream& operator<<(std::ostream& o, const BigInt& i);


