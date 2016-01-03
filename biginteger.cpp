#include "biginteger.h"

BigInteger::BigInteger()
{
	vec.push_back(0);

	negative = false;
}

BigInteger::BigInteger(long int s)
{
	if (s < 0)
	{
		negative = true;

		s = -s;
	}
	else negative = false;

	int i;

	if (s == 0) vec.push_back(0);

	while (s)
	{
		i = s % 10;

		vec.push_back(i);

		s /= 10;
	}
}

BigInteger::BigInteger(string str)
{
	if (str[0] == '-')
	{
		negative = true;

		str = str.substr(1, str.size() - 1);
	}
	else negative = false;

	for (int i = str.size() - 1; i >= 0; i--)
		vec.push_back(str[i] - '0');

}

BigInteger::BigInteger(const BigInteger& a)
{
	vec = a.vec;

	negative = a.negative;
}

BigInteger BigInteger::operator = (const BigInteger& a)
{
	vec = a.vec;

	negative = a.negative;

	return *this;
}
// 重载流 ///////////////////////////////////
ostream& operator << (ostream& out, BigInteger& a)
{
	string str = "";

	bool judge = false;

	if (a.vec[a.vec.size() - 1] + '0' == '-') //判断加减的正负
		judge = true;

	if (a.negative && !judge) //判断乘除的正负
		str += '-';

	for (int i = a.vec.size() - 1; i >= 0; i--)
	{
		str += (a.vec[i] + '0');
	}

	out << str;

	return out;
}

istream& operator >> (istream& in, BigInteger& a)
{
	string str = "";

	in >> str;

	a.vec.clear();

	for (int i = str.size() - 1; i >= 0; i--)
	{
		if (str[i] == '-')
		{
			a.negative = true;

			continue;
		}
		a.vec.push_back(str[i] - '0');
	}

	return in;
}

BigInteger operator+=(BigInteger& a, const BigInteger& b)
{
	BigInteger temp;

	unsigned int maxt, mint, i;

	if (a.vec.size() > b.vec.size())
	{
		temp.vec = b.vec;

		mint = b.vec.size();

		maxt = a.vec.size();
	}
	else
	{
		mint = a.vec.size();

		maxt = b.vec.size();

		temp.vec = a.vec;

		a.vec = b.vec;
	}

	for (i = 0; i < mint - 1; i++)
	{
		a.vec[i] += temp.vec[i];

		if (a.vec[i] > 9)
		{
			a.vec[i] -= 10;

			a.vec[i + 1] += 1;
		}
	}

	a.vec[i] += temp.vec[i];

	if (a.vec[i] > 9)
	{
		a.vec[i] -= 10;

		if (mint == maxt)
			a.vec.push_back(1);
		else
			a.vec[i + 1] += 1;
	}

	for (i = mint - 1; i < maxt - 1; i++) //减1怕相等的时候越界
	{
		if (a.vec[i] > 9)
		{
			a.vec[i] -= 10;

			a.vec[i + 1] += 1;
		}
	}

	if (a.vec[i] > 9)
	{
		a.vec[i] -= 10;

		a.vec.push_back(1);
	}

	i = a.vec.size() - 1;

	while (a.vec[i] == 0)
	{
		a.vec.pop_back();

		i--;
	}
	return a;
}
// += 检查完成 ///////////////////////////////
BigInteger operator-=(BigInteger& a, const BigInteger& b)
{
	bool judge;

	unsigned int i, mint, maxt;

	BigInteger temp, zero(0);

	temp.vec.clear();

	if (a.vec.size() > b.vec.size())
	{
		mint = b.vec.size();

		maxt = a.vec.size();

		temp.vec = b.vec;

		judge = false;
	}
	else if (a.vec.size() == b.vec.size())
	{
		for (i = a.vec.size() - 1; i >= 1; i--)
		{
			if (a.vec[i] < b.vec[i])
			{
				mint = a.vec.size();

				maxt = b.vec.size();

				temp.vec = a.vec;

				a.vec = b.vec;

				judge = true;

				break;
			}
			else if (a.vec[i] > b.vec[i])
			{
				mint = b.vec.size();

				maxt = a.vec.size();

				temp.vec = b.vec;

				judge = false;

				break;
			}
		}
		if (i == 0 && a.vec[0] == b.vec[0])
		{
			a.vec.clear();

			a.vec.push_back(0);

			return a;
		}
		else if (i == 0 && a.vec[0] > b.vec[0])
		{
			mint = b.vec.size();

			maxt = a.vec.size();

			temp.vec = b.vec;

			judge = false;
		}
		else if (i == 0 && a.vec[0] < b.vec[0])
		{
			mint = a.vec.size();

			maxt = b.vec.size();

			temp.vec = a.vec;

			a.vec = b.vec;

			judge = true;
		}
	}
	else
	{
		mint = a.vec.size();

		maxt = b.vec.size();

		temp.vec = a.vec;

		a.vec = b.vec;

		judge = true;
	}


	for (i = 0; i < mint; i++)
	{
		a.vec[i] -= temp.vec[i];

		if (a.vec[i] < 0)
		{
			a.vec[i] += 10;

			a.vec[i + 1] -= 1;
		}
	}

	if (maxt > mint)
		for (i = mint; i < maxt; i++)
		{
			if (a.vec[i] < 0)
			{
				a.vec[i] += 10;

				a.vec[i + 1] -= 1;
			}
		}

	i = a.vec.size() - 1;

	while (a.vec[i] == 0)
	{
		a.vec.pop_back();

		i--;
	}

	if (judge)
		a.vec.push_back('-' - '0');

	return a;
}
// -=检查完毕 /////////////////////////////////

BigInteger operator+(const BigInteger& a, const BigInteger& b)
{
	BigInteger temp1, temp2;

	temp1.vec.clear();
	temp2.vec.clear();

	temp1 = a;
	temp2 = b;

	if (a.negative && b.negative)
	{
		temp1.negative = false;
		temp2.negative = false;

		temp1 += temp2;

		temp1.vec.push_back('-' - '0');
	}
	else if (a.negative && !b.negative)
	{
		temp1.negative = false;

		temp2 -= temp1;

		temp1 = temp2;
	}
	else if (!a.negative && b.negative)
	{
		temp2.negative = false;

		temp1 -= temp2;
	}
	else temp1 += temp2;

	return temp1;
}
// +检查完毕 ///////////////////////////////////////

BigInteger operator - (const BigInteger& a, const BigInteger& b)
{

	BigInteger temp1, temp2;

	temp1.vec.clear();
	temp2.vec.clear();

	temp1 = a;
	temp2 = b;

	if (a.negative && b.negative)
	{
		temp1.negative = false;
		temp2.negative = false;

		temp2 -= temp1;

		temp1 = temp2;
	}
	else if (a.negative && !b.negative)
	{
		temp1.negative = false;

		temp1 += temp2;

		temp1.vec.push_back('-' - '0');
	}
	else if (!a.negative && b.negative)
	{
		temp2.negative = false;

		temp1 += temp2;
	}
	else temp1 -= temp2;

	return temp1;
}
// -检查完毕 /////////////////////////////////////
BigInteger operator * (const BigInteger& a, const BigInteger& b)
{
	BigInteger c;

	c.vec.clear();

	unsigned int i, j, temp;

	for (i = 0; i < (a.vec.size() + b.vec.size()); i++)
		c.vec.push_back(0);

	for (i = 0; i < a.vec.size(); i++)
	{
		for (j = 0; j < b.vec.size(); j++)
		{
			temp = c.vec[i + j] + a.vec[i] * b.vec[j];

			if (temp > 9)
			{
				if ((i + j + 1)<(a.vec.size() + b.vec.size()))
				{
					c.vec[i + j + 1] += temp / 10;

					temp %= 10;
				}
				else
				{
					c.vec.push_back(temp / 10);

					temp %= 10;
				}
			}
			c.vec[i + j] = temp;
		}
	}
	i = c.vec.size() - 1;

	while (c.vec[i] == 0)
	{
		c.vec.pop_back();

		i--;
	}

	if ((a.negative && !b.negative) || (!a.negative && b.negative))
	{
		c.vec.push_back('-' - '0');

		c.negative = true;
	}
	else
		c.negative = false;

	return c;
}
// *检查完毕 ////////////////////////////////////

BigInteger operator / (const BigInteger& a, const BigInteger& b)
{
	int i, j = 1;

	if (SizeJudge(a, b) == -1)
	{
		return (BigInteger)0;
	}
	else if (SizeJudge(a, b) == 0)
	{
		return (BigInteger)1;
	}

	if (b.vec.size() == 1 && b.vec[0] == 0)
	{
		BigInteger err("error");

		return err;
	}

	i = a.vec.size() - b.vec.size();

	while (i)
	{
		j *= 10;

		i--;
	}

	BigInteger ans(j), temp, ok(1);

	temp = ans*b;

	if (SizeJudge(a, temp) == 1)
		while (SizeJudge(a, temp) == 1)
		{
			ans = ans + ok;

			temp = ans*b;
		}
	else if (SizeJudge(a, temp) == -1)
		while (SizeJudge(a, temp) == -1)
		{
			ans = ans - ok;

			temp = ans*b;
		}

	if ((a.negative && !b.negative) || (!a.negative && b.negative))
	{
		char sign = '-';

		ans.vec.push_back(sign - '0');

		ans.negative = 1;
	}
	else
		ans.negative = 0;

	return ans;
}

int SizeJudge(const BigInteger a, const BigInteger b)
{
	int alen, blen, i;
	alen = a.vec.size();
	blen = b.vec.size();

	if (alen>blen)
	{
		return 1;
	}
	else if (alen == blen)
	{
		for (i = alen - 1; i >= 0; i--)
		{
			if (a.vec[i]>b.vec[i])
			{
				return 1;
			}
			else if (a.vec[i]<b.vec[i])
			{
				return -1;
			}
		}
		if (i == 0)
			return 0;
	}
	else
		return -1;
}