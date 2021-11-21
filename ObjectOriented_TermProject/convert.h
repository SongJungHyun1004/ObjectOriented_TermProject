#pragma once
#include <string>
#include <stack>
#include "Strategy2.h"
#include "priority.h"

using namespace std;

string toDecimal(string data) {
	int len = data.length();
	char type = data[0];
	data = data.substr(1);
	Context2* context = NULL;
	if (type == 'b') {
		context = new Context2(new Binary());
	}
	if (type == 'x') {
		context = new Context2(new HexaDecimal());
	}
	int dec = context->execute_Convert(data);
	data = to_string(dec);
	return data;
}

string Convert(string expression)
{
	string result = "";
	stack<char> stack;
	int len = expression.length();
	char ch;
	string data;
	int priority;
	int open = 0;
	int close = 0;
	int error = 0;

	for (int i = 0; i < len; i++)
	{
		ch = expression[i];
		priority = GetPriority(ch);

		if (priority == 2 || priority == 1) { // 연산자
			if (i == 0) {// 연산자로 시작된 식
				error = 1;
				break;
			}
			ch = expression[++i];
			priority = GetPriority(ch);
			if (priority == 2 || priority == 1 || ch == ')' || ch == NULL) {// 연속된 연산자나, 연산자 뒤에 닫는 괄호가 있거나, 연산자로 끝나는 식
				error = 1;
				break;
			}
			i--;
			ch = expression[--i];
			if (ch == '(') {// 연산자 앞에 여는 괄호가 있는 식
				error = 1;
				break;
			}
			ch = expression[++i];
			priority = GetPriority(ch);
			while (!stack.empty() && GetPriority(stack.top()) >= priority) {
				result += stack.top();
				result += " ";
				stack.pop();
			}
			stack.push(ch);
		}
		else if (priority == 0) { // 여는 괄호
			open++;
			ch = expression[++i];
			if (ch == ')') {// 여는 괄호 뒤에 바로 닫는 괄호가 있는 식
				error = 1;
				break;
			}
			ch = expression[--i];
			if (i != 0) {
				ch = expression[--i];
				if (isdigit(ch)) {// 여는 괄호 앞에 숫자가 있는 식
					error = 1;
					break;
				}
				ch = expression[++i];
			}
			stack.push(ch);
		}
		else if (priority == -1) { // 닫는 괄호
			close++;
			ch = expression[++i];
			if (isdigit(ch)) {// 닫는 괄호 뒤에 숫자가 있는 식
				error = 1;
				break;
			}
			i--;
			if (close > open) {// 닫는 괄호가 여는 괄호보다 먼저 오는 식
				error = 1;
				break;
			}
			while (!stack.empty() && stack.top() != '(') {
				result += stack.top();
				result += " ";
				stack.pop();
			}
			stack.pop();
		}
		else { // 숫자
			data = ch;
			if (ch == '0') {// 0으로 시작하는 숫자 처리
				ch = expression[++i];
				if (ch == 'b') {// 0b로 시작하는 2진수
					data = ch;
					ch = expression[++i];
					if (ch != '0' && ch != '1') {// 0b 다음 0이나 1이 아닐 경우
						error = 1;
						break;
					}
					while (ch == '0' || ch == '1') {
						data += ch;
						ch = expression[++i];
					}
					if (isdigit(ch)) {//0이나 1이 아닌 다른 숫자가 올 경우
						error = 1;
						break;
					}
					i--;
					data = toDecimal(data);
				}
				else if (ch == 'x') {// 0x로 시작하는 16진수
					data = ch;
					ch = expression[++i];
					if (!(isdigit(ch) || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'))) {// 0x 다음 숫자나 a~f가 아닐 경우
						error = 1;
						break;
					}
					while (isdigit(ch) || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F')) {
						data += ch;
						ch = expression[++i];
					}
					i--;
					data = toDecimal(data);
				}
				else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ')' || ch == NULL) {// 숫자 0
					i--;
				}
				else {// 0다음 올 수 없는 문자가 있을 경우
					error = 1;
					break;
				}
			}
			else if (ch != '0' && isdigit(ch)) {// 0이 아닌 숫자
				ch = expression[++i];
				while (isdigit(ch)) {
					data += ch;
					ch = expression[++i];
				}
				i--;
			}
			else {// 연산자도, 괄호도, 숫자도 아닌 문자
				error = 1;
				break;
			}
			result += data + " ";
		}
	}
	if (open != close || error == 1) {// 괄호 짝이 안 맞거나 error변수가 1인 경우
		while (!stack.empty())
			stack.pop();
		result = "error ";
	}
	while (!stack.empty()) {
		result += stack.top();
		result += " ";
		stack.pop();
	}
	result.erase(result.end() - 1);// 맨 뒤 공백자르기
	return result;
}