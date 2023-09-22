#include "PmergeMe.hpp"
#include "PmergeMeD.hpp"
#include "Color.hpp"

int main( int ac, char **av ) {

	// for( int i = 0; av[i]; i++ ) {

	// 	std::cout << BL << av[i] << " ";
	// }

	std::cout << std::endl;
	if( ac != 2 ) {

		std::cout << "Error: Incorrect number of arguments. Usage: " << av[0] << " <space-separated list of numbers>" << std::endl;
		return 1;
	}

	std::string avc = av[1];
	PmergeMe mergeMe( av[1] );
	PmergeMeD mergeMeD( avc );

	return 0;
}
