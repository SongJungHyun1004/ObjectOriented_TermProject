#include <iostream>
#include <string>
#include "convert.h"
#include "calculate.h"

using namespace std;

int main()
{
	string input;
	int quit = 0;
	cout << "종료를 원하면 " << "q" << " 입력" << endl;
	getline(cin, input);
	while (1) {
		while (input.empty()) {
			cout << "아무것도 입력하지 않았습니다. 식을 입력해 주세요." << endl;
			getline(cin, input);
		}
		if (input.compare("q") == 0) {
			break;
		}
		string postfix = Convert(input);
		while (postfix.compare("error") == 0) {
			cout << "잘못된 입력입니다. 다시 한번 입력해 주세요." << endl;
			getline(cin, input);
			while (input.empty()) {
				cout << "아무것도 입력하지 않았습니다. 식을 입력해 주세요." << endl;
				getline(cin, input);
			}
			if (input.compare("q") == 0) {
				quit = 1;
				break;
			}
			postfix = Convert(input);
		}
		if (quit)
			break;
		int answer = calculate(postfix);
		if (answer == INT_MIN) {
			cout << "(0으로 나눌 수 없습니다)잘못된 입력입니다. 다시 한번 입력해 주세요." << endl;
		}
		else {
			//cout << postfix << endl;
			cout << answer << endl;
		}
		getline(cin, input);
	}
	return 0;
}