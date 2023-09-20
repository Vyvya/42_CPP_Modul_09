#include "RPN.hpp"
#include <string>
#include <iostream>

int main( int ac, char **av ) {

	if( ac != 2 ) {

		std::cerr << "Error: wrong number of arguments" << std::endl;
		return 0;
	}

	RPN stack( av[1] );

	return 0;
}
