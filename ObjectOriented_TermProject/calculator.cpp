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
		cout << "�ƹ��͵� �Է����� �ʾҽ��ϴ�. ���� �Է��� �ּ���." << endl;
		getline(cin, input);
	}
	string postfix = Convert(input);
	while (postfix.compare("error") == 0) {
		cout << "�߸��� �Է��Դϴ�. �ٽ� �ѹ� �Է��� �ּ���." << endl;
		getline(cin, input);
		while (input.empty()) {
			cout << "�ƹ��͵� �Է����� �ʾҽ��ϴ�. ���� �Է��� �ּ���." << endl;
			getline(cin, input);
		}
		postfix = Convert(input);
	}
	//cout << postfix << endl;
	cout << calculate(postfix) << endl;
	return 0;
}