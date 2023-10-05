#include "RPN.hpp"

RPN::RPN( std::string arg ) {

	// std::cout << "RNP constructor called" << std::endl;
	_operations[0] = "+";
	_operations[1] = "-";
	_operations[2] = "*";
	_operations[3] = "/";

	buildStack( arg );
}

void RPN::buildStack( std::string arg ) {

	std::istringstream iss( arg );
	std::string token;

	while( getline(iss, token, ' ')) {

		if( isOperator(token)) {

			if( performOperation( _rpn, token ) == -1 ) {

				return;
			}
		} else {

			double num;
			std::istringstream numIss(token);

			if( numIss >> num ) {

				_rpn.push_back( num );

			} else {

				std::cout << "Error Invalid input" << std::endl;
				return;
			}
		}
	}

	if( _rpn.size() != 1 ) {

		std::cout << "Error Invalid input combination" << std::endl;
		return;

	} else {

		double res = _rpn.front();
		_rpn.pop_back();
		std::cout << res << std::endl;
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

	for( int i = 0; i < 4; i++ ) {

		if( token == _operations[i] ) {

			return true;
		}
	}
	return false;
}

double RPN::performOperation( std::vector<double> &rpn, std::string token ) {

	if (rpn.size() < 2) {

        std::cout << "Error: Not enough operands for operator " << token << std::endl;
        return -1;
    }

	double lnum = rpn.back();
	rpn.pop_back();

	double rnum = rpn.back();
	rpn.pop_back();

	if( token == "+" ) {

		rpn.push_back( lnum + rnum );

	} else if( token == "-" ) {

		rpn.push_back( rnum - lnum );

	} else if( token == "*" ) {

		rpn.push_back( lnum * rnum );

	} else if( token == "/" ) {

		if( lnum == 0 ) {
			std::cout << "Error division by 0" << std::endl;
			return -1;

		} else {

			rpn.push_back( rnum / lnum );
		}

	} else {

		std::cout << "Error unknown operator" << std::endl;
		return -1;
	}
	return 0;
}

RPN::~RPN() {

	// std::cout << "RPN destructor called" << std::endl;
}
