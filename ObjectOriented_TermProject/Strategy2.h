#pragma once
class Strategy2 {
public:
	virtual int convert(std::string data) = 0;
};

class Binary : public Strategy2 {
public:
	int convert(std::string data) {
		return stoi(data, 0, 2);
	}
};

class HexaDecimal : public Strategy2 {
public:
	int convert(std::string data) {
		return stoi(data, 0, 16);
	}
};

class Context2 {
private:
	Strategy2* strategy;
public:
	Context2(Strategy2* strategy) {
		this->strategy = strategy;
	}
public:
	int execute_Convert(std::string data) {
		return strategy->convert(data);
	}
};