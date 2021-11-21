#include <iostream>
#include <string>
#include "convert.h"
#include "calculate.h"

using namespace std;

int main()
{
	string input;
	int quit = 0;
	cout << "���Ḧ ���ϸ� " << "q" << " �Է�" << endl;
	getline(cin, input);
	while (1) {
		while (input.empty()) {
			cout << "�ƹ��͵� �Է����� �ʾҽ��ϴ�. ���� �Է��� �ּ���." << endl;
			getline(cin, input);
		}
		if (input.compare("q") == 0) {
			break;
		}
		string postfix = Convert(input);
		while (postfix.compare("error") == 0) {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �ѹ� �Է��� �ּ���." << endl;
			getline(cin, input);
			while (input.empty()) {
				cout << "�ƹ��͵� �Է����� �ʾҽ��ϴ�. ���� �Է��� �ּ���." << endl;
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
			cout << "(0���� ���� �� �����ϴ�)�߸��� �Է��Դϴ�. �ٽ� �ѹ� �Է��� �ּ���." << endl;
		}
		else {
			//cout << postfix << endl;
			cout << answer << endl;
		}
		getline(cin, input);
	}
	return 0;
}