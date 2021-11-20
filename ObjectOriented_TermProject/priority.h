#pragma once
int GetPriority(char op)
{
	switch (op)
	{
	case '*':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	case '(':
		return 0;
	case ')':
		return -1;
	default:
		return -2;
	}
}