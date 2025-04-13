#include "EA_v1.h"

using namespace std;


Polynomial d_dx(Polynomial a) {
	return a.derivate("x");
}

Polynomial d_dy(Polynomial a) {
	return a.derivate("y");
}

Polynomial d_dz(Polynomial a) {
	return a.derivate("z");
}

Polynomial i_dx(Polynomial a) {
	return a.integrate("x");
}

Polynomial i_dy(Polynomial a) {
	return a.integrate("y");
}

Polynomial i_dz(Polynomial a) {
	return a.integrate("z");
}


char STACK_FUNC_SYMBOL = '#'; // 

string POSTFIX_OPERAND_STRING = "v"; // var
string POSTFIX_OPERATOR_STRING = "o";
string POSTFIX_FUNCTION_STRING = "f";
string POSTFIX_SEPARATOR_STRING = "|";
string POSTFIX_CONST_STRING = "c";

std::vector<std::string> EA_v1::getCachedPostfix() {
	return cachedPostfix;
}


std::vector<std::string> EA_v1::getCachedPurePostfix() {
	vector<std::string> env;
	std::string item;
	for (auto i : cachedPostfix) {
		item = i;
		item.erase(0, 2);
		env.push_back(item);
	}
	return env;
}

long int convertStrToInt(string strNum) {
	long num = 0;
	long pow = 10;
	char sign = 1;
	size_t i = 0;

	if (strNum[0] == '-')
	{
		sign = -1;
		i = 1;
	}
	for (; i < strNum.length(); i++) {
		num *= pow;
		num += (strNum[i] - '0');
	}
	return num * sign;
}

EA_v1::EA_v1() {
	cachedPostfix.clear();
	functionList = { { "d_dx", d_dx }, { "d_dy", d_dy }, { "d_dz", d_dz },
	{ "i_dx", i_dx }, { "i_dy", i_dy }, { "i_dz", i_dz } }; // <name, ptr_to_func> 
}

Tptr EA_v1::funcCheck(const string& func) {
	Tptr functionPtr = functionList[func];
	if (functionPtr == nullptr)
		throw (string("Expression Analyzer can't identify function") + func);
	return functionPtr;
}

std::vector<std::string> EA_v1::getPostfix(const std::string& expression, std::set<std::string>& outRequestedPolynomials) {
	map<char, int> priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3}, {STACK_FUNC_SYMBOL, 4} };
	stack<string> funcStack;

	int bracketBalance = 0;
	char stackItem;
	stack<char> st;
	string postfixItem;
	vector <string> postfix = {};
	int state = 1;
	for (char item : expression) {
		if (bracketBalance < 0)
			throw(string("Closing bracket withut an open one"));
		switch (item) {
		case ' ':
			break;
		case '(':
			switch (state) {
			case 1:
				bracketBalance++;
				state = 1;
				st.push(item);
				break;
			case 3:
				state = 1;
				bracketBalance++;
				st.push(item);
				break;
			case 2: {
				bracketBalance++;
				state = 1;
				Tptr funcPtr = funcCheck(postfixItem);
				if (funcPtr) {
					st.push(STACK_FUNC_SYMBOL);
					st.push(item);
					funcStack.push(postfixItem);
				}
				else
					throw(string("No such function as ") + postfixItem);
				break;
			}
			default:
				throw(string("Incorrect state before ") + item);
				break;
			}
			break;

		case ')':
			bracketBalance--;
			if (bracketBalance < 0)
				throw(string("Closing bracket withut an open one"));
			switch (state) {
			case 2:
				outRequestedPolynomials.insert(postfixItem);
				postfix.push_back(string(POSTFIX_OPERAND_STRING) + string(POSTFIX_SEPARATOR_STRING) + postfixItem);
				break;
			case 4:
				break;
			case 6:
				postfix.push_back(string(POSTFIX_CONST_STRING) + string(POSTFIX_SEPARATOR_STRING) + postfixItem);
				break;
			default:
				throw(string("Incorrect state before ") + item);
				break;
			}
			state = 4;

			stackItem = st.top();
			st.pop();
			while (stackItem != '(') {
				if (stackItem == STACK_FUNC_SYMBOL) {
					postfix.push_back(string(POSTFIX_FUNCTION_STRING) + string(POSTFIX_SEPARATOR_STRING) + funcStack.top());
					funcStack.pop();
				}
				else {
					postfixItem = string(POSTFIX_OPERATOR_STRING) + string(POSTFIX_SEPARATOR_STRING) + stackItem;
					postfix.push_back(postfixItem);
				}
				stackItem = st.top();
				st.pop();
			}
			break;

		case '*': case '+': case '-':
			switch (state) {
			case 2:
				outRequestedPolynomials.insert(postfixItem);
				postfix.push_back(string(POSTFIX_OPERAND_STRING) + string(POSTFIX_SEPARATOR_STRING) + postfixItem);
				state = 3;
				break;
			case 4:
				state = 3;
				break;
			case 6:
				postfix.push_back(string(POSTFIX_CONST_STRING) + string(POSTFIX_SEPARATOR_STRING) + postfixItem);
				state = 3;
				break;
			case 1:
				if (item != '-')
					throw(string("Incorrect state before ") + item);
				postfixItem = string("-1");
				postfix.push_back(string(POSTFIX_CONST_STRING) + string(POSTFIX_SEPARATOR_STRING) + postfixItem);
				item = '*';
				state = 3;
				break;
			default:
				throw(string("Incorrect state before ") + item);
				break;
			}

			while (!st.empty()) {
				stackItem = st.top();
				st.pop();
				if (priority[item] <= priority[stackItem]) {
					if (stackItem == STACK_FUNC_SYMBOL) {
						postfix.push_back(string(POSTFIX_FUNCTION_STRING) + string(POSTFIX_SEPARATOR_STRING) + funcStack.top());
						funcStack.pop();
					}
					else {
						postfixItem = stackItem;
						postfix.push_back(string(POSTFIX_OPERATOR_STRING) + string(POSTFIX_SEPARATOR_STRING) + postfixItem);
					}
				}
				else {
					st.push(stackItem);
					break;
				}
			}
			st.push(item);
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			switch (state) {
			case 1: case 3:
				state = 6;
				postfixItem = item;
				break;
			case 6:
				postfixItem += item;
				break;
			default:
				throw(string("incorrect sate before letter") + item + string("in word") + postfixItem + item);
			}
			break;


		default:
			if (!((('a' <= item) && (item <= 'z')) || (('A' <= item) && (item <= 'Z')) || (item == '_')))
				throw (string("Names can only contain letters fron a to z and '_' symbol"));

			switch (state) {
			case 1: case 3:
				state = 2;
				postfixItem = item;
				break;
			case 2:
				postfixItem += item;
				break;
			default:
				throw(string("incorrect sate before letter") + item + string("in word") + postfixItem + item);
			}
		}
	}
	if (bracketBalance != 0)
		throw(string("Bad brackets detected"));
	switch (state) {
	case 2:
		outRequestedPolynomials.insert(postfixItem);
		postfix.push_back(string(POSTFIX_OPERAND_STRING) + string(POSTFIX_SEPARATOR_STRING) + postfixItem);
		break;
	case 4:
		break;
	case 6:
		postfix.push_back(string(POSTFIX_CONST_STRING) + string(POSTFIX_SEPARATOR_STRING) + postfixItem);
		break;
	default:
		throw(string("Incorrect state at the end"));
		break;
	}
	while (!st.empty()) {
		stackItem = st.top();
		st.pop();
		if (stackItem == STACK_FUNC_SYMBOL) {
			postfix.push_back(string(POSTFIX_FUNCTION_STRING) + string(POSTFIX_SEPARATOR_STRING) + funcStack.top());
			funcStack.pop();
		}
		else {
			postfixItem = string(POSTFIX_OPERATOR_STRING) + string(POSTFIX_SEPARATOR_STRING) + stackItem;
			postfix.push_back(postfixItem);
		}
	}
	return postfix;
}

void EA_v1::analyzeExpression(const std::string& expression, std::set<std::string>& outRequestedPolynomials) {
	cachedPostfix = getPostfix(expression, outRequestedPolynomials);
}

Polynomial EA_v1::calculateSummaryPolynomial(const std::map<std::string, const Polynomial&> polynomials) {
	stack<Polynomial> operandsStack;
	for (string item : cachedPostfix) {
		char type = item[0];
		string itemName = item;
		itemName.erase(0, 2);

		switch (type) {
		case 'v': {
			auto handle = polynomials.find(itemName);
			if (handle == polynomials.end()) {
				throw(string("No polynmial ") + itemName + string(" in plynmials map"));
			}
			operandsStack.push(handle->second);
			//Polynomial handle = polynomials[itemName];
			//operandsStack.push(handle);
			break;
		}
		case 'c': {
			Polynomial handle(convertStrToInt(itemName));
			operandsStack.push(handle);
			break;
		}
		case 'o': {
			Polynomial operandRight = operandsStack.top();
			operandsStack.pop();
			Polynomial operandLeft = operandsStack.top();
			operandsStack.pop();
			char operatorSign = itemName[0];
			switch (operatorSign) {
			case '+':
				operandsStack.push(operandLeft + operandRight);
				break;
			case '-':
				operandsStack.push(operandLeft - operandRight);
				break;
			case '*':
				operandsStack.push(operandLeft * operandRight);
				break;
			default:
				throw(string("Error: Postfix form has undefined operator"));
			}
			break;
		}
		case 'f': {
			Polynomial arg = operandsStack.top();
			operandsStack.pop();
			Tptr funcPtr = funcCheck(itemName);
			if (funcPtr == nullptr)
				throw (string("Error: Postfix form has undefined function"));
			operandsStack.push(funcPtr(arg));
			break;
		}
		default:
			throw (string("Error: Postfix form has undefined element"));
			break;
		}
	}
	return operandsStack.top();
}



