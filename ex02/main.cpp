#include "PmergeMe.hpp"
#include "Color.hpp"

int main( int ac, char **av ) {

	if( ac != 2 ) {

		std::cout << "Error: Incorrect number of arguments. Usage: " << av[0] << " <space-separated list of numbers>" << std::endl;
		return 1;
	}

	// (void)ac;

	std::string avc = av[1];
	PmergeMe mergeMe( av[1] );

	return 0;
}
