class Strategy {
public:
	virtual int doOperation(int num1, int num2) = 0;
};

class Add : public Strategy {
public:
	int doOperation(int num1, int num2) {
		return num1 + num2;
	}
};

class Substract : public Strategy {
public:
	int doOperation(int num1, int num2) {
		return num1 - num2;
	}
};

class Multiply : public Strategy {
public:
	int doOperation(int num1, int num2) {
		return num1 * num2;
	}
};

class Divide : public Strategy {
public:
	int doOperation(int num1, int num2) {
		return num1 / num2;
	}
};

class Context {
private:
	Strategy* strategy;
public:
	Context(Strategy* strategy) {
		this->strategy = strategy;
	}
public:
	int execute_Calculation(int num1, int num2) {
		return strategy->doOperation(num1, num2);
	}
};