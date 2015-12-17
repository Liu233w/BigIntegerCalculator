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

    while (s) //改动
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

BigInteger BigInteger::operator = (BigInteger a)
{
    vec = a.vec;

    negative = a.negative;

    return *this;
}

ostream& operator << (ostream& out, const BigInteger& a)
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

BigInteger operator+(BigInteger& a, BigInteger& b)
{
    BigInteger c, temp;

    c.vec.clear();
    temp.vec.clear();

    bool negative_judge;

    if (a.negative && b.negative)
        negative_judge = true;
    if (!a.negative && !b.negative)
        negative_judge = false;
    if (a.negative && !b.negative)
    {
        a.negative = false;

        return(b - a);
    }
    if (!a.negative && b.negative)
    {
        b.negative = false;

        return(a - b);
    }

    unsigned int i, mint, maxt;

    if (a.vec.size() > b.vec.size())
    {
        c.vec = a.vec;

        temp.vec = b.vec;

        mint = b.vec.size();

        maxt = a.vec.size();
    }
    else
    {
        c.vec = b.vec;

        temp.vec = a.vec;

        mint = a.vec.size();

        maxt = b.vec.size();
    }

    for (i = 0; i < mint - 1; i++)
    {
        c.vec[i] += temp.vec[i];

        if (c.vec[i] > 9)
        {
            c.vec[i] -= 10;

            c.vec[i + 1] += 1;
        }
    }

    c.vec[i] += temp.vec[i];

    if (c.vec[i] > 9)
    {
        c.vec[i] -= 10;

        if (mint == maxt)
            c.vec.push_back(1);
        else
            c.vec[i + 1] += 1;
    }

    for (i = mint; i < maxt - 1;i++)
    {
        if (c.vec[i] > 9)
        {
            c.vec[i] -= 10;

            c.vec[i + 1] += 1;
        }
    }

    if (c.vec[i] > 9)
    {
        c.vec[i] -= 10;

        c.vec.push_back(1);
    }

    i = c.vec.size() - 1;

    while (c.vec[i] == 0)
    {
        c.vec.pop_back();

        i--;
    }

    if (negative_judge)
        c.vec.push_back('-' - '0');

    return c;
}

BigInteger operator - (BigInteger& a, BigInteger& b)
{
    if (a.negative && b.negative)
    {
        a.negative = false;
        b.negative = false;

        return (b - a);
    }
    if (a.negative && !b.negative)
    {
        b.negative = true;

        return (a + b);
    }
    if (!a.negative && b.negative)
    {
        b.negative = false;

        return (a + b);
    }

    BigInteger c, temp;

    bool judge;

    c.vec.clear();
    temp.vec.clear();

    unsigned int i, mint, maxt;

    if (a.vec.size() > b.vec.size())
    {
        c.vec = a.vec;

        temp.vec = b.vec;

        mint = b.vec.size();

        maxt = a.vec.size();

        judge = false;
    }
    else if (a.vec.size() == b.vec.size())
    {
        for (i = a.vec.size() - 1; i >= 0; i--)
        {
            if (a.vec[i] < b.vec[i])
            {
                c.vec = b.vec;

                temp.vec = a.vec;

                mint = a.vec.size();

                maxt = b.vec.size();

                judge = true;

                break;
            }
            else if (a.vec[i] > b.vec[i])
            {
                c.vec = a.vec;

                temp.vec = b.vec;

                mint = b.vec.size();

                maxt = a.vec.size();

                judge = false;

                break;
            }
        }

        if (i == -1) return (BigInteger)0;
    }
    else
    {
        c.vec = b.vec;

        temp.vec = a.vec;

        mint = a.vec.size();

        maxt = b.vec.size();

        judge = true;
    }


    for (i = 0; i < mint; i++)
    {
        c.vec[i] -= temp.vec[i];

        if (c.vec[i] < 0)
        {
            c.vec[i] += 10;

            c.vec[i + 1] -= 1;
        }
    }

    if (maxt > mint)
        for (i = mint; i < maxt; i++)
        {
            if (c.vec[i] < 0)
            {
                c.vec[i] += 10;

                c.vec[i + 1] -= 1;
            }
        }

    if (judge)
        c.vec.push_back('-' - '0');

    i = c.vec.size() - 1;

    while (c.vec[i] == 0)
    {
        c.vec.pop_back();

        i--;
    }

    return c;
}

BigInteger operator * (BigInteger& a, BigInteger& b)
{
    BigInteger c;

    unsigned int i, j, temp;

    for (i = 0;i < (a.vec.size() + b.vec.size()); i++)
        c.vec.push_back(0);

    for (i = 0; i < a.vec.size(); i++)
    {
        for (j = 0; j < b.vec.size(); j++)
        {
            temp = c.vec[i + j] + a.vec[i] * b.vec[j];

            if (temp > 9)
            {
                if ((i + j + 1) < (a.vec.size() + b.vec.size()))
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

BigInteger operator / (BigInteger& a, BigInteger& b)
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

int SizeJudge(BigInteger a, BigInteger b)
{
    int alen, blen, i;
    alen = a.vec.size();
    blen = b.vec.size();
    if (alen > blen)
    {
        return 1;
    }
    else if (alen == blen)
    {
        for (i = alen - 1;i >= 0;i--)
        {
            if (a.vec[i] > b.vec[i])
            {
                return 1;
            }
            else if (a.vec[i] < b.vec[i])
            {
                return -1;
            }
        }
        if (i == 0)
            return 0;
    }
    else
    {
        return -1;
    }
}
