// Reverse Polish Notation.cpp : Defines the entry point for the console application.
// 栈的应用--四则运算表达式
// 后缀表达式以及中缀表达式

#include "stdafx.h"
#include <stack>
#include <queue>

queue<string> suffixExpr;

//	创建后缀表达式
void CreateSuffixExpr(char* buf, size_t len);
//	计算后缀表达式
int CalcSuffixExpr(void);

int main()
{
	char szBuf[100];
	while (cin>>szBuf)
	{
		CreateSuffixExpr(szBuf, strlen(szBuf));
		/*while (!suffixExpr.empty())
		{
			cout << suffixExpr.front() << " ";
			suffixExpr.pop();
		}
		cout << endl;*/
		cout << "ret = " << CalcSuffixExpr() << endl;
	}
    return 0;
}

/**
 *  中缀表达式->后缀表达式
 *  规则：从左到右遍历中缀表达式的每个数字和符号，若是数字就输出，即成为后缀表达式的一部分；
 *  若是符号，则判断其与栈顶符号的优先级，是右括号或优先级低于栈顶符号（乘除优先加减）
 *  则栈顶元素依次出栈并输出，并将当前符号进栈，一直到最终输出后缀表达式为止。
 */
void CreateSuffixExpr(char* buf, size_t len)
{
	stack<char> s;
	char* tmp = buf;
	int cur = 0;
	while (cur < len)
	{
		if (tmp[0] == '(')
		{
			//	优先级最高，入栈
			s.push(tmp[0]);
			tmp++;
		}
		else if (tmp[0] == ')')
		{
			//	右括号，在栈中查找匹配的左括号，然后查找中间的符号出栈，进行后缀表达式的入栈
			while (!s.empty() && s.top() != '(')
			{
				string str{ s.top() };
				suffixExpr.push(str);
				s.pop();
			}
			s.pop();	//	弹出左括号
			tmp++;
		}
		else if (tmp[0] == '*' || tmp[0] == '/')
		{
			//	比+-优先级高
			while (!s.empty() && (s.top() == '*' || s.top() == '/'))
			{
				string str{ s.top() };
				suffixExpr.push(str);
				s.pop();
			}
			s.push(tmp[0]);
			tmp++;
		}
		else if (tmp[0] == '-' || tmp[0] == '+')
		{
			//	比栈顶符号优先级低，进行栈顶符号至'（'或者栈中符号优先级不低于此符号为止，而后此符号进入栈顶位置
			while (!s.empty() && s.top() != '(')
			{
				string str{ s.top() };
				suffixExpr.push(str);
				s.pop();
			}
			s.push(tmp[0]);
			tmp++;
		}
		else
		{
			//	若是数字，则入栈
			int i = atoi(tmp);
			char sz[10];
			itoa(i, sz, 10);
			suffixExpr.push(sz);
			tmp += strlen(sz);
			if (strlen(sz) > 1)
			{
				cur += strlen(sz);
				continue;
			}
		}
		++cur;
	}

	while (!s.empty())
	{
		string str{ s.top() };
		suffixExpr.push(str);
		s.pop();
	}
}

/**
 *  后缀表达式计算
 *  规则：从左到右遍历表达式的每个数字和符号遇到数字就进栈，遇到符号，就将处于
 *  栈顶两个数字出栈，进行运算，运算结果进栈，一直到最终获得结果。
 */
int CalcSuffixExpr(void)
{
	int ret = 0;
	stack<int> stack;
	while (!suffixExpr.empty())
	{
		string s = suffixExpr.front();
		suffixExpr.pop();
		if (s == "+" || s == "-" || s == "*" || s == "/")
		{
			if (!stack.empty())
			{
				int i = stack.top();
				stack.pop();
				int j = stack.top();
				stack.pop();
				if (s == "+")
				{
					ret = i + j;
				}
				else if (s == "-")
				{
					ret = j - i;
				}
				else if (s == "*")
				{
					ret = j * i;
				}
				else
				{
					ret = j / i;
				}
				stack.push(ret);
			}
		}
		else
		{
			stack.push(atoi(s.c_str()));
		}
	}

	return ret;
}
