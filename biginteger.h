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

	// 构造函数 /////////////////////////////////
	BigInteger();
	BigInteger(long int s);
	BigInteger(string str);
	BigInteger(const BigInteger& a);

	// 重载运算符//////////////////////////////
	BigInteger operator = (const BigInteger &a);

	friend ostream& operator << (ostream& out, BigInteger& a);
	friend istream& operator >> (istream& in, BigInteger& a);

	friend BigInteger operator + (const BigInteger& a, const BigInteger& b);
	friend BigInteger operator - (const BigInteger& a, const BigInteger& b);
	friend BigInteger operator * (const BigInteger& a, const BigInteger& b);
	friend BigInteger operator / (const BigInteger& a, const BigInteger& b);

	friend BigInteger operator += (BigInteger& a, const BigInteger& b);
	friend BigInteger operator -= (BigInteger& a, const BigInteger& b);

	friend int SizeJudge(BigInteger a, BigInteger b);
};

BigInteger operator + (const BigInteger& a,const BigInteger& b);
BigInteger operator - (const BigInteger& a,const BigInteger& b);
BigInteger operator * (const BigInteger& a,const BigInteger& b);
BigInteger operator / (const BigInteger& a,const BigInteger& b);

ostream& operator << (ostream& out, const BigInteger& a);
istream& operator >> (istream& in, BigInteger& a);

BigInteger operator += (BigInteger& a, const BigInteger& b);
BigInteger operator -= (BigInteger& a, const BigInteger& b);

int SizeJudge(BigInteger a, BigInteger b);

#endif // BIGINTEGER_H
