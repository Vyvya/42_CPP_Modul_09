#include "PmergeMe.hpp"

int main( int ac, char *av[] ) {

	if( ac != 2 ) {

		std::cout << "Error number of arguments. Usage: <space-separeted list of numbers" << std::endl;
	}

	PmergeMe mergeMe( av[1] );

	return 0;
}
