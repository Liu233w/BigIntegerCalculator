#include "biginteger.h"
// 构造函数 ///////////////////////////////////////////
/*主要用来代替默认构造函数的作用
 *默认初始值为0
 */
BigInteger::BigInteger()
{
    vec.push_back(0);

    negative = false;
}
/*使用长整型来初始化的构造函数
 *支持负数输入
 */
BigInteger::BigInteger(long int s)
{
	/*如果s<0那就将内部判别正负的nagative设为ture，然后将s取相反数*/
    if (s < 0)
    {
        negative = true;

        s = -s;
    }
    else negative = false;

    int i;
	/*如果s为0的情况特殊处理*/
    if (s == 0) vec.push_back(0);
	/*因为使用vector来储存数据，一位一位来储存*/
    while (s)
    {
        i = s % 10;

        vec.push_back(i);

        s /= 10;
    }
}
/*使用字符串来初始化的构造函数*/
BigInteger::BigInteger(string str)
{
	/*如果字符串的第一个符号是-号，说明想要输入的是负数
	 *去掉-号，改变nagative为true
	 */
    if (str[0] == '-')
    {
        negative = true;

        str = str.substr(1, str.size() - 1);
    }
    else negative = false;
	/*因为是字符串输入，每个元素是char型，注意-'0'转化为int型*/
    for (int i = str.size() - 1; i >= 0; i--)
        vec.push_back(str[i] - '0');
}
/*使用大整数来初识化大整数*/
BigInteger::BigInteger(const BigInteger& a)
{
    vec = a.vec;

    negative = a.negative;
}
/*重载=符号，便于两个大整数的交换操作
 *因为是赋值，所以将右值设定为const的引用，这样保证不会被改变而且不会发生复制提高速度
 *使用this指针来返回值
 */
BigInteger BigInteger::operator = (const BigInteger& a)
{
    vec = a.vec;

    negative = a.negative;

    return *this;
}
// 重载流 /////////////////////////////////////////////
/*重载输出流，方便大整数的直接输出*/
ostream& operator << (ostream& out, const BigInteger& a)
{
    string str = "";
	/*judge的作用是如果是进行了加减操作就不必检验乘除操作的一个开关*/
    bool judge = false;
	/*进行加减操作后的正负*/
    if (a.vec[a.vec.size() - 1] + '0' == '-') 
        judge = true;
	/*判断乘除操作后的正负*/
    if (a.negative && !judge) //判断乘除的正负
        str += '-';
	/*将vector内的元素转化成为string来输出，因为逆向储存所以逆向输出*/
    for (int i = a.vec.size() - 1; i >= 0; i--)
    {
		/*因为是string，不要忘记+'0'*/
        str += (a.vec[i] + '0');
    }

    out << str;

    return out;
}
/*重载输入流，方便大整数的直接输入*/
istream& operator >> (istream& in, BigInteger& a)
{
    string str = "";

    in >> str;
	/*清空vector内的元素，因为默认构造函数会自动加上一个0*/
    a.vec.clear();

    for (int i = str.size() - 1; i >= 0; i--)
    {
		/*如果输入了负号，negative变为true，不把负号加入到vector中*/
        if (str[i] == '-')
        {
            a.negative = true;

            continue;
        }
        a.vec.push_back(str[i] - '0');
    }
    return in;
}
/*重载+=符号，来具体实现+的操作
 *+=的要求是左值可以改变，右值不能改变，所以右值设为const，并全部使用引用来避免复制赋值
 *原理是选出位数较大的来作为基数，然后位数小的再一位位加到基数上
 */
BigInteger operator+=(BigInteger& a, const BigInteger& b)
{
	/*建立暂时的容器来保证不会改变右值*/
    BigInteger temp;

    unsigned int maxt, mint, i;

    if (a.vec.size() > b.vec.size())
    {
        temp.vec = b.vec;

        mint = b.vec.size();

        maxt = a.vec.size();
    }
	/*如果基数不是a，就需要用temp来交换a，b的值*/
    else
    {
        mint = a.vec.size();

        maxt = b.vec.size();

        temp.vec = a.vec;

        a.vec = b.vec;
    }
	/*开始一位位来加法*/
    for (i = 0; i < mint - 1; i++)
    {
        a.vec[i] += temp.vec[i];
		/*如果这一位>9，就-10下一位加1*/
        if (a.vec[i] > 9)
        {
            a.vec[i] -= 10;

            a.vec[i + 1] += 1;
        }
    }
	/*较小的最后一位进行特殊操作*/
    a.vec[i] += temp.vec[i];
	
    if (a.vec[i] > 9)
    {
        a.vec[i] -= 10;
		/*特殊操作的目的在这里，如果ab等长那么就需要新增一位*/
        if (mint == maxt)
            a.vec.push_back(1);
        else
			/*不是等长那就直接在下一位加1*/
            a.vec[i + 1] += 1;
    }
	/*检查后面的位数有没有因为前面的进位而大于9的*/
    for (i = mint - 1; i < maxt - 1; i++) //减1怕ab位数相等的时候越界
    {
        if (a.vec[i] > 9)
        {
            a.vec[i] -= 10;

            a.vec[i + 1] += 1;
        }
    }
	/*最后一位特殊处理，如果大于>9,新增一位*/
    if (a.vec[i] > 9)
    {
        a.vec[i] -= 10;

        a.vec.push_back(1);
    }

    i = a.vec.size() - 1;
	/*去除无谓的前导0*/
    while (a.vec[i] == 0)
    {
        a.vec.pop_back();

        i--;
    }
    return a;
}
/*重载-=符号，来具体实现-的操作
*-=的要求是左值可以改变，右值不能改变，所以右值设为const，并全部使用引用来避免复制赋值
*原理是选出位数较大的或者数值较大来作为基数，然后位数小的再一位位与基数相减
*/
BigInteger operator-=(BigInteger& a, const BigInteger& b)
{
	/*因为相减可能得到负数，所以这是来判断结果是否为负*/
    bool judge;

    unsigned int i, mint, maxt;

    BigInteger temp;
	
    temp.vec.clear();

    if (a.vec.size() > b.vec.size())
    {
        mint = b.vec.size();

        maxt = a.vec.size();

        temp.vec = b.vec;
		/*a的位数如果大于0，那么结果肯定为正*/
        judge = false;
    }
    else if (a.vec.size() == b.vec.size())
    {
        for (i = a.vec.size() - 1; i >= 1; i--)
        {
			/*如果位数相等，从最大的位往下遍历，如果遇到b>a的情况，说明结果为负*，反之则为正*/
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
		/*如果之前的每一位都相等，最后一位也相等，返回0*/
        if (i == 0 && a.vec[0] == b.vec[0])
        {
            a.vec.clear();

            a.vec.push_back(0);

            return a;
        }
		/*如果最后一位不相等，判断与上面的情况相同*/
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
	/*如果位数比b少，那么结果明显为负*/
    else
    {
        mint = a.vec.size();

        maxt = b.vec.size();

        temp.vec = a.vec;

        a.vec = b.vec;

        judge = true;
    }
	/*开始一位位的相减*/
    for (i = 0; i < mint; i++)
    {
        a.vec[i] -= temp.vec[i];
		/*如果某一位相减的结果<0，那就上一位-1，来补这一位*/
        if (a.vec[i] < 0)
        {
            a.vec[i] += 10;

            a.vec[i + 1] -= 1;
        }
    }
	/*如果a的位数大于b的位数，才可以进行下面的操作，避免相等*/
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
	/*去掉前导0*/
    while (a.vec[i] == 0)
    {
        a.vec.pop_back();

        i--;
    }
	/*如果结果为负，加上负号，在输出时来判断*/
    if (judge)
        a.vec.push_back('-' - '0');

    return a;
}
/*重载+符号，具体实现用+=,-=的操作
*+的要求是左右值都不能改变，所以左/右值都设为const，并全部使用引用来避免复制赋值
*/
BigInteger operator+(const BigInteger& a, const BigInteger& b)
{
	/*使用两个临时容器来避免改变a,b的值*/
    BigInteger temp1, temp2;

    temp1.vec.clear();
    temp2.vec.clear();

    temp1 = a;
    temp2 = b;
	/*如果两个负数相加，等于绝对值相加后的结果取相反数*/
    if (a.negative && b.negative)
    {
        temp1.negative = false;
        temp2.negative = false;

        temp1 += temp2;

        temp1.vec.push_back('-' - '0');
    }
	/*如果a是负数，b是正数，相当于b-a，所以调用-=来实现*/
    else if (a.negative && !b.negative)
    {
        temp1.negative = false;

        temp2 -= temp1;

        temp1 = temp2;
    }
	/*如果a为正数，b为负数，相当于a-b，所以调用-=来实现*/
    else if (!a.negative && b.negative)
    {
        temp2.negative = false;

        temp1 -= temp2;
    }
	/*如果全是正数，那就是最正常的情况*/
    else temp1 += temp2;

    return temp1;
}
/*重载-符号，具体实现用+=,-=的操作
*-的要求是左右值都不能改变，所以左/右值都设为const，并全部使用引用来避免复制赋值
*/
BigInteger operator - (const BigInteger& a, const BigInteger& b)
{
	/*使用两个临时容器来避免改变a,b的值*/
    BigInteger temp1, temp2;

    temp1.vec.clear();
    temp2.vec.clear();

    temp1 = a;
    temp2 = b;
	/*如果a，b都是负数，相当于b-a，所以调用-=来实现*/
    if (a.negative && b.negative)
    {
        temp1.negative = false;
        temp2.negative = false;

        temp2 -= temp1;

        temp1 = temp2;
    }
	/*如果a是负数，b是正数，相当于绝对值相加后的结果取相反数，所以调用+=*/
    else if (a.negative && !b.negative)
    {
        temp1.negative = false;

        temp1 += temp2;

        temp1.vec.push_back('-' - '0');
    }
	/*如果a 是正数，把b是负数，相当于直接绝对值相加，调用+=*/
    else if (!a.negative && b.negative)
    {
        temp2.negative = false;

        temp1 += temp2;
    }
	/*如果都是正数就是最平常的情况*/
    else temp1 -= temp2;

    return temp1;
}
/*重载*符号
**的要求是左右值都不能改变，所以左/右值都设为const，并全部使用引用来避免复制赋值
*/
BigInteger operator * (const BigInteger& a, const BigInteger& b)
{
	/*用c来储存结果*/
    BigInteger c;

    c.vec.clear();

    unsigned int i, j, temp;
	/*c 的位数设定为a+b的位数，这是最大情况，保证不会溢出*/
    for (i = 0; i < (a.vec.size() + b.vec.size()); i++)
        c.vec.push_back(0);
	/*开始模拟竖式乘法，b的一位乘以a的每一位*/
    for (i = 0; i < a.vec.size(); i++)
    {
        for (j = 0; j < b.vec.size(); j++)
        {
			/*用temp来储存结果*/
            temp = c.vec[i + j] + a.vec[i] * b.vec[j];
			/*如果大于9了进位*/
            if (temp > 9)
            {
				/*如果不是最大的一位直接进一*/
                if ((i + j + 1)<(a.vec.size() + b.vec.size()))
                {
                    c.vec[i + j + 1] += temp / 10;

                    temp %= 10;
                }
				/*是最大的一位就要增长一位*/
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
	/*去掉前导0*/
    while (c.vec[i] == 0)
    {
        c.vec.pop_back();

        i--;
    }
	/*如果ab异号说明结果为负*/
    if ((a.negative && !b.negative) || (!a.negative && b.negative))
    {
        c.vec.push_back('-' - '0');

        c.negative = true;
    }
    else
        c.negative = false;

    return c;
}
/*重载/符号
* /的要求是左右值都不能改变，所以左/右值都设为const，并全部使用引用来避免复制赋值
*/
BigInteger operator / (const BigInteger& a, const BigInteger& b)
{
    int i, j = 1;
	/*引用一个函数来判断位数和大小*/
	/*如果b比a小，返回0*/
    if (SizeJudge(a, b) == -1)
    {
        return (BigInteger)0;
    }
	/*如果相等，返回1*/
    else if (SizeJudge(a, b) == 0)
    {
        return (BigInteger)1;
    }
	/*如果b为0，抛出错误*/
    if (b.vec.size() == 1 && b.vec[0] == 0)
    {
        throw logic_error("error");
    }
	/*i的作用是来表示ab之间的位数差距*/
    i = a.vec.size() - b.vec.size();
	/*使用i来初始化j，最大的结果是j*10^i */
    while (i)
    {
        j *= 10;

        i--;
    }

    BigInteger ans(j), temp, ok(1);

    temp = ans*b;
	/*一次来减j，直到见到相等为止的时候的j就是结果*/
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
	/*如果异号则结果为负*/
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
/*判断位数/数值大小的函数*/
int SizeJudge(const BigInteger a, const BigInteger b)
{
    int alen, blen, i;
    alen = a.vec.size();
    blen = b.vec.size();
	/*如果a大于b返回1*/
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
			/*如果a<b，返回-1*/
            else if (a.vec[i]<b.vec[i])
            {
                return -1;
            }
        }
		/*如果相等，返回0*/
        if (i == 0)
            return 0;
    }
    else
        return -1;
}
