#include "PmergeMeD.hpp"
#include "PmergeMe.hpp"

#include "Color.hpp"
#include <stdlib.h>
#include <utility>
#include <ctime>
#include <iomanip>
#include <sys/time.h>

PmergeMeD::PmergeMeD( std::string av ) {

	// std::cout << "PmergeMe constructor called" << std::endl;
	// std::cout << av << std::endl;
	// std::cout << std::endl;


// ...

	timeval startTime, endTime;
	gettimeofday(&startTime, NULL);
	buildDeque(av);
	gettimeofday(&endTime, NULL);

	double elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000000LL + (endTime.tv_usec - startTime.tv_usec);
	std::cout << GR << "Time to process a range of " << _deque.size() << " elements with std::deque: "
			<< std::fixed << std::setprecision(5) << elapsedTime << " us" << std::endl;
	std::cout << RES << std::endl;

}

PmergeMeD::~PmergeMeD() {

	// std::cout << "PmergeMe destructor called" << std::endl;
}

bool PmergeMeD::isDigit(const std::string& numStr) {

    std::string::const_iterator it = numStr.begin();
    while (it != numStr.end() && std::isdigit(*it))
		++it;
    return !numStr.empty() && it == numStr.end();
}

void PmergeMeD::buildDeque(std::string av) {

	std::istringstream iss(av);
	std::string num_str;
	int num;

	while (iss >> num_str) {

		if (!isDigit(num_str)) {
			log("Not a digit");
			return;
		}

		num = std::stoi(num_str);
		_deque.push_back( num );

	}

	std::cout << BL << "Before:\t";
	printDeque( _deque );
	// mergeSort( _list );

	std::cout << OR << "After:\t";
	printDeque( _deque );
}

void PmergeMeD::printDeque( const std::deque<int>& _deque ) {

	for( std::deque<int>::const_iterator it = _deque.begin(); it != _deque.end(); it++ ) {

		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMeD::fordJohnsonSortDeque( std::deque<int>& _deque ) {

	if( _deque.size() <= 1 ) {
		return;
	}

	if( (_deque.size() % 2) == 1 ) {

		std::deque<int>::iterator its = _deque.end();
		int straggler = *its;
		std::cout << "straggler: " << straggler << std::endl;
	}

	std::deque<int> left;
	std::deque<int> right;
	int middle = _deque.size() / 2;
	int i = 0;

	for( std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); it++ ) {

		if( i < middle ) {

			left.push_back( *it );
		} else {

			right.push_back( *it );
		}
		++i;
	}

	fordJohnsonSortDeque( left );
	fordJohnsonSortDeque( right );

	_deque.clear();
}
// 	merge( _list, left, right );
// }

// void PmergeMe::merge( std::list<int>& _list, std::list<int>& left, std::list<int>& right ) {

//     std::list<int>::iterator leftIt = left.begin();
//     std::list<int>::iterator rightIt = right.begin();

//     while ( leftIt != left.end() && rightIt != right.end() ) {

//         if ( *leftIt <= *rightIt) {
//             _list.push_back( *leftIt );
//             leftIt++;
//         } else {
//              _list.push_back( *rightIt );
//             rightIt++;
//         }
//     }

//     while( leftIt != left.end() ) {

// 		_list.push_back(( *leftIt ));
// 		++leftIt;
// 	}

// 	 while( rightIt != right.end() ) {

// 		_list.push_back(( *rightIt ));
// 		++rightIt;
// 	}
// }

void PmergeMeD::log( std::string msg ) {

	std::cout << "Error: " << msg << std::endl;
}

