#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <string> 
#include <bitset>
#include "BigInt.h"


void BigInt::_remove_leading_zeros()
{
    while (this->m_data.size() > 1 && this->m_data.back() == 0) {
        this->m_data.pop_back();
    }

    if (this->m_data.size() == 1 && this->m_data[0] == 0) this->m_negative = false;
}
BigInt m_pow(const BigInt& fst, const BigInt& snd) {
    BigInt outputValue(1);
    for (BigInt i(0); i < snd; ++i) {
        outputValue *= fst;
    }
    return outputValue;
}


//////////////////////////////////////////////////////////////////////////////////
/*BIGINT CONSTRUCTOR*/
//////////////////////////////////////////////////////////////////////////////////

BigInt::BigInt() {
    m_data.push_back(0);
    m_negative = false;
}

BigInt::BigInt(int n) { //constructor from int
    if (n < 0) {
        m_negative = true;
        n = -n;
    }
    else {
        m_negative = false;
    }
    while (n > 0) {
        m_data.push_back(n % BASE);
        n /= BASE;
    }
}

BigInt::BigInt(char* str) { //Constructor from string
    if (str[0] == '-') {
        m_negative = true;
        str++;
    }
    else {
        m_negative = false;
    }
    for (int i = strlen(str) - 1; i >= 0; i--) {
        m_data.push_back(str[i] - '0');
    }
}

BigInt::BigInt(std::string str) {
    if (str[0] == '-') {
        m_negative = true;
        str.erase(0, 1);
    }
    else {
        m_negative = false;
    }
    for (int i = str.length() - 1; i >= 0; i--) {
        m_data.push_back(str[i] - '0');
    }
}

BigInt& BigInt::operator=(const BigInt& r) { //assignment operator. Possible to assign to itself
    this->m_data = r.m_data;
    return *this;
}

BigInt::BigInt(const BigInt& rhs) {
    m_data = rhs.m_data;
    m_negative = rhs.m_negative;
}


//////////////////////////////////////////////////////////////////////////////////
/*ARIPHMETIC OF BIGINT*/
//////////////////////////////////////////////////////////////////////////////////



BigInt& BigInt::operator++() { //prefix increment, return reference to self
    int carry = 1;
    for (auto& digit : m_data) {
        digit += carry;
        carry = digit / BASE;
        digit %= BASE;
    }
    if (carry > 0) {
        m_data.push_back(carry);
    }
    return *this;
}

const BigInt BigInt::operator++(int) {

    *this += 1;
    return *this;
}

BigInt& BigInt::operator--() {
    int carry = -1;
    for (auto& digit : m_data) {
        digit += carry;
        carry = digit / BASE;
        digit %= BASE;
    }
    if (carry < 0) {
        m_data.push_back(carry);
    }
    return *this;
}

const BigInt BigInt::operator--(int rhs) const {
    BigInt tmp(rhs);
    (*this)--;
    return tmp;
}

BigInt& BigInt::operator+=(const BigInt& rhs) {//
    if ((m_negative == rhs.m_negative) and (m_negative == true)) {
        BigInt tmp1(0);
        BigInt tmp2(0);
        tmp1.m_data = m_data;
        tmp2.m_data = rhs.m_data;
        tmp1 += tmp2;
        this->m_data = tmp1.m_data;
        this->m_negative = true;
    }
    if ((m_negative == rhs.m_negative) and (m_negative == false)) {
        int carry = 0;
        for (int i = 0; i < std::max(m_data.size(), rhs.m_data.size()); i++) {
            if (i < m_data.size()) {
                m_data[i] += carry;
                carry = m_data[i] / BASE;
                m_data[i] %= BASE;
            }
            else {
                m_data.push_back(carry);
                carry = 0;
            }
            if (i < rhs.m_data.size()) {
                m_data[i] += rhs.m_data[i];
                carry += m_data[i] / BASE;
                m_data[i] %= BASE;
            }
        }
        if (carry > 0) {
            m_data.push_back(carry);
        }
    }
    if ((m_negative == false) and (rhs.m_negative == true)) {
        bool sign;
        BigInt tmp1(rhs);
        tmp1.m_negative = false;
        BigInt tmp2(*this);
        tmp2.m_negative = false;
        if (tmp2 < tmp1) {
            sign = true;
            BigInt tmp3(minus(tmp1, tmp2));
            m_data = tmp3.m_data;
            m_negative = sign;
        }
        else {
            sign = false;
            tmp1 -= tmp2;
            m_data = tmp1.m_data;
            m_negative = sign;
        }
    }

    if ((m_negative == true) and (rhs.m_negative == false)) {
        BigInt tmpP1(*this);
        BigInt tmpP2(rhs);
        tmpP2 -= tmpP1;
        m_data = tmpP2.m_data;
        m_negative = tmpP2.m_negative;
    }
    return *this;

}

BigInt& BigInt::operator*=(const BigInt& rhs) {//
    bool sign;

    if (m_negative != rhs.m_negative) {
        m_negative = true;
    }
    else {
        m_negative = false;
    }
    BigInt tmp;
    tmp.m_data.resize(m_data.size() + rhs.m_data.size());
    for (size_t i = 0; i < m_data.size(); ++i)
    {
        int carry = 0;
        for (size_t j = 0; j < rhs.m_data.size() || carry > 0; ++j)
        {
            long long cur = tmp.m_data[i + j] + m_data[i] * 1ll * (j < rhs.m_data.size() ? rhs.m_data[j] : 0) + carry;
            tmp.m_data[i + j] = int(cur % BASE);
            carry = int(cur / BASE);
        }
    }
    while (tmp.m_data.size() > 1 && tmp.m_data.back() == 0)
    {
        tmp.m_data.pop_back();
    }
    m_data = tmp.m_data;
    return *this;
}

BigInt& BigInt::operator-=(const BigInt& rhs) {//
    BigInt result(0);
    if ((m_negative == rhs.m_negative) and (m_negative == true)) {
        BigInt tmp1(*this);
        BigInt tmp2(rhs);
        tmp1.m_negative = false;
        tmp2.m_negative = false;
        bool sign;
        if (tmp1 > tmp2) {
            sign = true;
        }
        else {
            sign = false;
        }

        tmp1 -= tmp2;
        this->m_data = tmp1.m_data;
        this->m_negative = sign;
        return *this;
    }
    if ((m_negative == false) and (rhs.m_negative == false)) {
        int carry = 0;
        if (*this < rhs) {
            BigInt tmp1(0);
            BigInt tmp2(0);
            tmp1.m_data = m_data;
            tmp2.m_data = rhs.m_data;
            tmp2 -= tmp1;
            this->m_data = tmp2.m_data;
            this->m_negative = true;
            return *this;
        }
        else {

            int carry = 0;
            for (auto i = 0; i < std::max(m_data.size(), rhs.m_data.size()); ++i) {
                int a = i < m_data.size() ? m_data[i] : 0;
                int b = i < rhs.m_data.size() ? rhs.m_data[i] : 0;
                int c = a - b - carry;
                if (c < 0) {
                    c += BASE;
                    carry = 1;
                }
                else {
                    carry = 0;
                }
                result.m_data.push_back(c);
            }
            while (result.m_data.size() > 1 && result.m_data.back() == 0) {
                result.m_data.pop_back();
            }
            m_data = result.m_data;
        }
        for (int i = 0; i < this->m_data.size(); ++i) {
            this->m_data[i] = this->m_data[i] % BASE;
        }
        return *this;
    }
    if ((m_negative == false) and (rhs.m_negative == true)) {
        BigInt tmpP1(*this);
        BigInt tmpP2(rhs);
        tmpP2.m_negative = false;
        tmpP1.m_negative = false;
        BigInt tmp3(plus(tmpP1, tmpP2));
        m_data = tmp3.m_data;
        m_negative = tmp3.m_negative;
        return *this;
    }
    if ((m_negative == true) and (rhs.m_negative == false)) {
        BigInt tmpP1(1);
        BigInt tmpP2(1);
        tmpP1.m_data = m_data;
        tmpP2.m_data = rhs.m_data;
        BigInt tmp3(plus(tmpP1, tmpP2));
        m_data = tmp3.m_data;
        m_negative = tmp3.m_negative;
    }

    for (int i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i] = this->m_data[i] % BASE;
    }
    return *this;
}

BigInt& BigInt::operator/=(const BigInt& rhs) {//
    bool sign;
    if (m_negative != rhs.m_negative) {
        sign = true;
    }
    else {
        sign = false;
    }
    BigInt tmp;
    tmp.m_data.resize(m_data.size());
    BigInt cur;
    for (int i = int(m_data.size()) - 1; i >= 0; --i)
    {
        cur *= BASE;
        cur += m_data[i];
        int x = 0, l = 0, r = BASE;
        while (l <= r)
        {
            int m = (l + r) / 2;
            BigInt t = rhs * BigInt(m);
            if (t <= cur)
            {
                x = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        tmp.m_data[i] = x;
        cur -= rhs * BigInt(x);
    }
    while (tmp.m_data.size() > 1 && tmp.m_data.back() == 0)
    {
        tmp.m_data.pop_back();
    }
    m_data = tmp.m_data;
    m_negative = sign;
    return *this;
}



BigInt& BigInt::operator%=(const BigInt& rhs) {//
    BigInt tmp;
    tmp.m_data.resize(m_data.size());
    BigInt cur;
    for (int i = int(m_data.size()) - 1; i >= 0; --i)
    {
        cur *= BASE;
        cur += m_data[i];
        int x = 0, l = 0, r = BASE;
        while (l <= r)
        {
            int m = (l + r) / 2;
            BigInt t = rhs * BigInt(m);
            if (t <= cur)
            {
                x = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        tmp.m_data[i] = x;
        cur -= rhs * BigInt(x);
    }
    while (tmp.m_data.size() > 1 && tmp.m_data.back() == 0)
    {
        tmp.m_data.pop_back();
    }
    m_data = cur.m_data;
    return *this;
}



BigInt BigInt::operator+() const {//
    return *this;
}

BigInt BigInt::operator-() const {//
    BigInt tmp(*this);
    tmp.m_negative = !tmp.m_negative;
    return tmp;
}


/////////////////////////////
BigInt::operator int() const {//
    int result = 0;
    for (int i = int(m_data.size()) - 1; i >= 0; --i) {
        result = result * BASE + m_data[i];
    }
    return result;
}


BigInt::operator std::string() const {//
    std::string result;
    if (m_negative) {
        result += "-";
    }
    for (int i = int(m_data.size()) - 1; i >= 0; --i) {
        result += char('0' + m_data[i]);
    }
    return result;
}
////////////////////////////////





BigInt operator/(const BigInt& lhs, const BigInt& rhs) {//
    BigInt tmp(lhs);
    tmp /= rhs;
    return tmp;
}



BigInt::~BigInt() {

}


BigInt operator%(const BigInt& lhs, const BigInt& rhs) {
    BigInt result(lhs);
    result %= rhs;
    return result;
}





BigInt BigInt::plus(const BigInt& lhs, const BigInt& rhs) {//
    BigInt tmp1(lhs);
    BigInt tmp2(rhs);
    int carry = 0;
    for (int i = 0; i < tmp1.m_data.size() || i < tmp2.m_data.size() || carry; ++i) {
        if (i == tmp1.m_data.size()) {
            tmp1.m_data.push_back(0);
        }
        tmp1.m_data[i] += carry + (i < tmp2.m_data.size() ? tmp2.m_data[i] : 0);
        carry = tmp1.m_data[i] >= BASE;
        if (carry) {
            tmp1.m_data[i] -= BASE;
        }
    }
    return tmp1;
}


BigInt operator*(const BigInt& lhs, const BigInt& rhs) {
    BigInt tmp(lhs);
    tmp *= rhs;
    return tmp;
}

BigInt operator+(const BigInt& lhs, const BigInt& rhs) {//
    BigInt tmp(lhs);
    tmp += rhs;
    return tmp;
}

BigInt operator-(const BigInt& lhs, const BigInt& rhs) {//
    BigInt tmp(lhs);
    tmp -= rhs;
    return tmp;
}


BigInt BigInt::minus(const BigInt& lhs, const BigInt& rhs) {//
    BigInt tmp11(lhs);
    BigInt tmp22(rhs);
    BigInt result(0);
    int carry = 0;
    if (*this < rhs) {
        BigInt tmp1(0);
        BigInt tmp2(0);
        tmp1.m_data = m_data;
        tmp2.m_data = rhs.m_data;
        tmp2 -= tmp1;
        this->m_data = tmp2.m_data;
        this->m_negative = true;
        return *this;
    }
    else {

        int carry = 0;
        for (auto i = 0; i < std::max(m_data.size(), rhs.m_data.size()); ++i) {
            int a = i < tmp11.m_data.size() ? tmp11.m_data[i] : 0;
            int b = i < rhs.m_data.size() ? rhs.m_data[i] : 0;
            int c = a - b - carry;
            if (c < 0) {
                c += BASE;
                carry = 1;
            }
            else {
                carry = 0;
            }
            result.m_data.push_back(c);
        }
        while (result.m_data.size() > 1 && result.m_data.back() == 0) {
            result.m_data.pop_back();
        }
    }
    for (int i = 0; i < this->m_data.size(); ++i) {
        this->m_data[i] = this->m_data[i] % BASE;
    }
    return result;
}


bool BigInt::operator==(const BigInt& rhs) const {//
    if (m_negative != rhs.m_negative) {
        return false;
    }
    for (int i = 0; i < m_data.size(); ++i) {
        if (m_data[i] != rhs.m_data[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt& rhs) const {//
    return !(m_data == rhs.m_data);
}

bool BigInt::operator<(const BigInt& rhs) const {//
    if (m_negative != rhs.m_negative) {
        return m_negative;
    }

    if (m_data.size() != rhs.m_data.size()) {
        return m_data.size() < rhs.m_data.size();
    }

    for (int i = int(m_data.size()) - 1; i >= 0; --i) {
        if (m_data[i] != rhs.m_data[i]) {
            return m_data[i] < rhs.m_data[i];
        }
    }
    return false;
}

bool BigInt::operator>(const BigInt& rhs) const {//
    return rhs < *this;
}


bool BigInt::operator<=(const BigInt& rhs) const {//
    return !(rhs < *this);
}

bool BigInt::operator>=(const BigInt& rhs) const {//
    return !(*this < rhs);
}


//////////////////////////////////////////////////////////////////////////////////
/*BINARY OPERATIONS*/
//////////////////////////////////////////////////////////////////////////////////


int divideByTwo(std::vector<unsigned>& a) {
    int carry = 0, b = 2;

    for (int i = a.size() - 1; i >= 0; --i) {
        long long cur = a[i] + carry * 1ll * 10;
        a[i] = static_cast<int>(cur / b);
        carry = static_cast<int>(cur % b);
    }

    while (a.size() > 1 && a.back() == 0)
        a.pop_back();

    return carry;
}

std::vector<int> toBin(BigInt& a) {
    int bit_count = 0;
    std::vector<unsigned> buf(a.m_data);
    std::vector<int> result_2_32;

    result_2_32.reserve(a.m_data.size() * 2);

    while (buf[0] >= 1) {
        int carry = divideByTwo(buf);
        //static_cast<int>();
        if (bit_count / 32 >= result_2_32.size()) {
            result_2_32.push_back(carry);
        }
        else {
            result_2_32[bit_count / 32] ^= (carry << (bit_count % 32));
        }

        bit_count++;
    }

    return result_2_32;
}

bool BigInt::odd() const {
    if (this->m_data.size() == 0) return false;
    return (this->m_data[0] & 1);
}

bool BigInt::even() const {
    return !this->odd();
}




BigInt operator&(const BigInt& fst, const BigInt& snd)
{
    std::vector<int> abin2_32 = toBin(const_cast<BigInt&>(fst));
    std::vector<int> bin_2_32 = toBin(const_cast<BigInt&>(snd));

    int min_size = std::min(abin2_32.size(), bin_2_32.size());

    BigInt outputValue;

    for (int i = 0; i < min_size; i++)
        outputValue.m_data.push_back((i < bin_2_32.size()) ? abin2_32[i] & bin_2_32[i] : 0);

    std::reverse(outputValue.m_data.begin(), outputValue.m_data.end());
    outputValue._remove_leading_zeros();

    return outputValue;
}


BigInt operator|(const BigInt& fst, const BigInt& snd) {
    BigInt outputValue;
    std::vector<int> fst_bin2_32 = toBin(const_cast<BigInt&>(fst));
    std::vector<int> snd_bin_2_32 = toBin(const_cast<BigInt&>(snd));

    int max_size = std::max(fst_bin2_32.size(), snd_bin_2_32.size());

    for (int i = 0; i < max_size; i++) {

        if (i < fst_bin2_32.size() && i >= snd_bin_2_32.size())
            outputValue.m_data.push_back(snd_bin_2_32[i] | 0);

        else if (i >= fst_bin2_32.size() && i < snd_bin_2_32.size())
            outputValue.m_data.push_back(snd_bin_2_32[i] | 0);

        else
            outputValue.m_data.push_back(fst_bin2_32[i] | snd_bin_2_32[i]);
    }

    //std::reverse(outputValue.m_data.begin(), outputValue.m_data.end());
    outputValue._remove_leading_zeros();
    //std::reverse(outputValue.m_data.begin(), outputValue.m_data.end());
    BigInt res(std::to_string(outputValue.m_data[1]));
    return res;
}



BigInt& BigInt::operator|=(const BigInt& another) {
    return *this = *this | another;
}
BigInt& BigInt::operator&=(const BigInt& another) {
    return *this = *this & another;
}
BigInt& BigInt::operator^=(const BigInt& another) {
    return *this = *this ^ another;
}

BigInt operator^(const BigInt& fst, const BigInt& snd) {
    BigInt outputValue(0), outputValue_2_30, _2_30Base("1073741824");

    BigInt& _a = const_cast<BigInt&>(fst);
    BigInt& _b = const_cast<BigInt&>(snd);

    //Convert to 2^30 base
    std::vector<int> a_2_30 = toBin(_a);
    std::vector<int> b_2_30 = toBin(_b);

    //Adding additional 0 or -1 if needed
    while (a_2_30.size() < b_2_30.size()) a_2_30.push_back((fst.m_negative) ? 0 : 0xFFFFFFFF);
    while (a_2_30.size() > b_2_30.size()) b_2_30.push_back((snd.m_negative) ? 0 : 0xFFFFFFFF);

    for (int i = 0; i < a_2_30.size(); i++)
        outputValue_2_30.m_data.push_back((a_2_30[i] ^ b_2_30[i]));

    //Remove leading zeroes
    outputValue_2_30._remove_leading_zeros();

    //Convert back to 10^9 base
    for (int i = 1; i < outputValue_2_30.m_data.size(); i++)
        outputValue += (BigInt(outputValue_2_30.m_data[i]) * m_pow(_2_30Base, BigInt(i - 1)));

    outputValue.m_negative = (fst.m_negative ^ snd.m_negative);

    return outputValue;
}

