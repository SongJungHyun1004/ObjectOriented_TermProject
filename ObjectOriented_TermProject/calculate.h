#pragma once
#include <stack>
#include <string>
#include "Strategy.h"
#include "priority.h"

using namespace std;

int calculate(string postfix)
{
	int len = postfix.length();
	stack<int> stack;
	string data = "";
	char ch;
	int priority;

	for (int i = 0; i < len; i++)
	{
		ch = postfix[i];
		priority = GetPriority(ch);
		if (priority == 1 || priority == 2) {
			int second = stack.top();
			stack.pop();
			int first = stack.top();
			stack.pop();
			if (ch == '/' && second == 0)
				return INT_MIN;
			Context* context = NULL;
			switch (ch)
			{
			case '+':
				context = new Context(new Add());
				break;
			case '-':
				context = new Context(new Substract());
				break;
			case '*':
				context = new Context(new Multiply());
				break;
			case '/':
				context = new Context(new Divide());
				break;
			}
			stack.push(context->execute_Calculation(first, second));
		}
		else {
			if (ch == ' ') {

			}
			else {
				data = ch;
				ch = postfix[++i];
				while (isdigit(ch)) {
					data += ch;
					ch = postfix[++i];
				}
				stack.push(stoi(data));
			}
		}
	}
	int result = stack.top();
	stack.pop();
	return result;
}