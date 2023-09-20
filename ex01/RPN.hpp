#ifndef RPN_HPP
# define RPN_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <exception>

class RPN {

	private:

		std::vector<double> _rpn;
		std::string _operations[4];

	public:

		RPN( std::string arg );
		~RPN();

		std::vector<double> getRPN() const;
		std::string getOperations() const;
		void buildStack( std::string arg  );
		bool isOperator( const std::string arg );
		double performOperation( std::vector<double> &rpn, std::string arg );

};

#endif
