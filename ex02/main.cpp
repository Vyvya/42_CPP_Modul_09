#include "PmergeMe.hpp"

int main( int ac, char *av[] ) {

	if( ac != 2 ) {

		std::cout << "Error number of arguments " << std::endl;
	}

	PmergeMe mergeMe( av[1] );

	return 0;
}
