#include <iostream>
#include <string>
#include "convert.h"
#include "calculate.h"

using namespace std;

int main()
{
	string input;
	getline(cin, input);
	while (input.empty()) {
		cout << "아무것도 입력하지 않았습니다. 식을 입력해 주세요." << endl;
		getline(cin, input);
	}
	string postfix = Convert(input);
	while (postfix.compare("error") == 0) {
		cout << "잘못된 입력입니다. 다시 한번 입력해 주세요." << endl;
		getline(cin, input);
		while (input.empty()) {
			cout << "아무것도 입력하지 않았습니다. 식을 입력해 주세요." << endl;
			getline(cin, input);
		}
		postfix = Convert(input);
	}
	//cout << postfix << endl;
	cout << calculate(postfix) << endl;
	return 0;
}