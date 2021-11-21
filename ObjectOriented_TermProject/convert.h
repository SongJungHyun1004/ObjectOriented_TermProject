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

		if (priority == 2 || priority == 1) { // ������
			if (i == 0) {// �����ڷ� ���۵� ��
				error = 1;
				break;
			}
			ch = expression[++i];
			priority = GetPriority(ch);
			if (priority == 2 || priority == 1 || ch == ')' || ch == NULL) {// ���ӵ� �����ڳ�, ������ �ڿ� �ݴ� ��ȣ�� �ְų�, �����ڷ� ������ ��
				error = 1;
				break;
			}
			i--;
			ch = expression[--i];
			if (ch == '(') {// ������ �տ� ���� ��ȣ�� �ִ� ��
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
		else if (priority == 0) { // ���� ��ȣ
			open++;
			ch = expression[++i];
			if (ch == ')') {// ���� ��ȣ �ڿ� �ٷ� �ݴ� ��ȣ�� �ִ� ��
				error = 1;
				break;
			}
			ch = expression[--i];
			if (i != 0) {
				ch = expression[--i];
				if (isdigit(ch)) {// ���� ��ȣ �տ� ���ڰ� �ִ� ��
					error = 1;
					break;
				}
				ch = expression[++i];
			}
			stack.push(ch);
		}
		else if (priority == -1) { // �ݴ� ��ȣ
			close++;
			ch = expression[++i];
			if (isdigit(ch)) {// �ݴ� ��ȣ �ڿ� ���ڰ� �ִ� ��
				error = 1;
				break;
			}
			i--;
			if (close > open) {// �ݴ� ��ȣ�� ���� ��ȣ���� ���� ���� ��
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
		else { // ����
			data = ch;
			if (ch == '0') {// 0���� �����ϴ� ���� ó��
				ch = expression[++i];
				if (ch == 'b') {// 0b�� �����ϴ� 2����
					data = ch;
					ch = expression[++i];
					if (ch != '0' && ch != '1') {// 0b ���� 0�̳� 1�� �ƴ� ���
						error = 1;
						break;
					}
					while (ch == '0' || ch == '1') {
						data += ch;
						ch = expression[++i];
					}
					if (isdigit(ch)) {//0�̳� 1�� �ƴ� �ٸ� ���ڰ� �� ���
						error = 1;
						break;
					}
					i--;
					data = toDecimal(data);
				}
				else if (ch == 'x') {// 0x�� �����ϴ� 16����
					data = ch;
					ch = expression[++i];
					if (!(isdigit(ch) || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'))) {// 0x ���� ���ڳ� a~f�� �ƴ� ���
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
				else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ')' || ch == NULL) {// ���� 0
					i--;
				}
				else {// 0���� �� �� ���� ���ڰ� ���� ���
					error = 1;
					break;
				}
			}
			else if (ch != '0' && isdigit(ch)) {// 0�� �ƴ� ����
				ch = expression[++i];
				while (isdigit(ch)) {
					data += ch;
					ch = expression[++i];
				}
				i--;
			}
			else {// �����ڵ�, ��ȣ��, ���ڵ� �ƴ� ����
				error = 1;
				break;
			}
			result += data + " ";
		}
	}
	if (open != close || error == 1) {// ��ȣ ¦�� �� �°ų� error������ 1�� ���
		while (!stack.empty())
			stack.pop();
		result = "error ";
	}
	while (!stack.empty()) {
		result += stack.top();
		result += " ";
		stack.pop();
	}
	result.erase(result.end() - 1);// �� �� �����ڸ���
	return result;
}