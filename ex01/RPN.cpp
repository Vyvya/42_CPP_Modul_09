#include "RPN.hpp"

RPN::RPN( std::string arg ) {

	std::cout << "RNP constructor called" << std::endl;
	_operations[0] = "+";
	_operations[1] = "-";
	_operations[2] = "*";
	_operations[3] = "/";

	buildStack( arg );
}

void RPN::buildStack( std::string arg ) {

	// std::cout << "RPN::buildStack: " << std::endl;

	std::istringstream iss( arg );
	std::string token;
	// std::string operations[4];
	while( getline(iss, token, ' ')) {

		if( isOperator(token)) {

			// std::cout << "oper: " << token << std::endl;
			performOperation( _rpn, token );
		} else { // if there is a numeric value

			double num;
			std::istringstream numIss(token);

			if( numIss >> num ) {

				_rpn.push_back( num );
				// std::cout << "num: " << num << std::endl;
			} else {

				std::cout << "Error Invalid input" << std::endl;
				return;
			}
		}
	}

	for( std::vector<double>::iterator it = _rpn.begin(); it < _rpn.end(); it++ ) {

		std::cout << "num: " << *it << std::endl;
	}

	if( _rpn.size() != 1 ) {

		std::cout << _rpn.size() << "Error Invalid input combination" << std::endl;
		return;

	} else {

		double res = _rpn.front();
		_rpn.pop_back();
		std::cout << "Result: " << res << std::endl;
	}
}

std::vector<double> RPN::getRPN( void ) const {

	return this->_rpn;
}

std::string RPN::getOperations() const {

	std::string allOperators;

	for( int i = 0; i < 4; i++ ) {
		allOperators = _operations[i];
	}
	return allOperators;
}

bool RPN::isOperator( const std::string token ) {

	std::cout << "arg: " << token << std::endl;

	for( int i = 0; i < 4; i++ ) {

		// std::cout << "1" << std::endl;

		if( token == _operations[i] ) {
			// std::cout << "2" << std::endl;
			return true;
		}
	}
	return false;
}

double RPN::performOperation( std::vector<double> &rpn, std::string token ) {

	std::cout << "RPN::performOperation: " << std::endl;

	if (rpn.size() < 2) {
        std::cout << "Error: Not enough operands for operator " << token << std::endl;
        return -1;
    }

	double lnum = rpn.back();
	std::cout << "lnum: " << lnum << std::endl;
	rpn.pop_back();

	double rnum = rpn.back();
	std::cout << "rnum: " << rnum << std::endl;
	rpn.pop_back();

	if( token == "+" ) {
		std::cout << "rnum + lnum: " << rnum + lnum << std::endl;

		rpn.push_back( lnum + rnum );

	} else if( token == "-" ) {
		std::cout << "rnum - lnum: " << rnum - lnum << std::endl;

		rpn.push_back( rnum - lnum );

	} else if( token == "*" ) {
		std::cout << "rnum * lnum: " << rnum * lnum << std::endl;

		rpn.push_back( lnum * rnum );

	} else if( token == "/" ) {

		if( rnum == 0 ) {
			std::cout << "Error division by 0" << std::endl;
			return -1;

		} else {
			std::cout << "rnum / lnum: " << rnum / lnum << std::endl;

			rpn.push_back( rnum / lnum );
		}
	} else {

		std::cout << "Error unknown operator" << std::endl;
		return -1;
	}
	return 0;
}

RPN::~RPN() {

	std::cout << "RPN destructor called" << std::endl;
}
