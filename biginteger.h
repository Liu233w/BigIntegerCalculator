#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include<iostream>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

class BigInteger
{
public:

    vector<int> vec;

    bool negative;

    BigInteger();
    BigInteger(long int s);
    BigInteger(string str);
    BigInteger(const BigInteger& a);

    BigInteger operator = (BigInteger a);

    friend ostream& operator << (ostream& out, const BigInteger& a);
    friend istream& operator >> (istream& in, BigInteger& a);

    friend BigInteger operator + (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator - (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator * (const BigInteger& a, const BigInteger& b);
    friend BigInteger operator / (const BigInteger& a, const BigInteger& b);

    friend int SizeJudge(BigInteger a, BigInteger b);


};

BigInteger operator + (BigInteger& a, BigInteger& b);
BigInteger operator - (BigInteger& a, BigInteger& b);
BigInteger operator * (BigInteger& a, BigInteger& b);
BigInteger operator / (BigInteger& a, BigInteger& b);

ostream& operator << (ostream& out, const BigInteger& a);
istream& operator >> (istream& in, BigInteger& a);


#endif // BIGINTEGER_H
