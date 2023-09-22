#include "PmergeMe.hpp"
#include "Color.hpp"
#include <stdlib.h>
#include <utility>
#include <ctime>
#include <iomanip>
#include <sys/time.h>

PmergeMe::PmergeMe( std::string av ) {

	// std::cout << "PmergeMe constructor called" << std::endl;
	// std::cout << av << std::endl;
	// std::cout << std::endl;

	timeval startTime, endTime;
gettimeofday(&startTime, NULL);
buildList(av);
gettimeofday(&endTime, NULL);

double elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000000.0 + (endTime.tv_usec - startTime.tv_usec);

// Apply the manipulators for formatting
std::cout << GR << "Time to process a range of " << _list.size() << " elements with std::deque: "
          << std::fixed << std::setprecision(5) << elapsedTime << " us" << std::endl;
std::cout << RES << std::endl;



	// timeval startTime, endTime;
	// gettimeofday(&startTime, NULL);
	// buildList(av);
	// gettimeofday(&endTime, NULL);

	// long long elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000000LL + (endTime.tv_usec - startTime.tv_usec);
	clock_t startTime = clock(); // Timer<milliseconds, steady_clock>
	buildList( av );
	clock_t endTime = clock(); // Timer<milliseconds, steady_clock>
	double elapsedTimeClock = static_cast<double>(endTime - startTime) * 1e6 / CLOCKS_PER_SEC;
	std::cout << GR << "Time to process a range of\t" << _list.size() << " elements with std::list : \t" << std::fixed << std::setprecision(5) << elapsedTime << " us" << std::endl;
	std::cout << RES << std::endl;
}

PmergeMe::~PmergeMe() {

	// std::cout << "PmergeMe destructor called" << std::endl;
}

bool PmergeMe::isDigit(const std::string& numStr) {

    std::string::const_iterator it = numStr.begin();
    while (it != numStr.end() && std::isdigit(*it))
		++it;
    return !numStr.empty() && it == numStr.end();
}

void PmergeMe::buildList(std::string av) {

	std::istringstream iss(av);
	std::string num_str;
	int num;

	while (iss >> num_str) {

		if (!isDigit(num_str)) {
			log("Not a digit");
			return;
		}

		num = std::stoi(num_str);
		_list.push_back( num );

	}

	std::cout << BL << "Before:\t";
	printList( _list );
	fordJohnsonSortList( _list );

	std::cout << OR << "After:\t";
	printList( _list );
}

void PmergeMe::printList( const std::list<int>& _list ) {

	for( std::list<int>::const_iterator it = _list.begin(); it != _list.end(); it++ ) {

		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::fordJohnsonSortList( std::list<int>& _list ) {

	if( _list.size() <= 1 ) {
		return;
	}

	std::list<int> left;
	std::list<int> right;
	int middle = _list.size() / 2;
	int i = 0;

	for( std::list<int>::iterator it = _list.begin(); it != _list.end(); it++ ) {

		if( i < middle ) {

			left.push_back( *it );
		} else {

			right.push_back( *it );
		}
		++i;
	}

	fordJohnsonSortList( left );
	fordJohnsonSortList( right );

	_list.clear();
	merge( _list, left, right );
}

void PmergeMe::merge( std::list<int>& _list, std::list<int>& left, std::list<int>& right ) {

    std::list<int>::iterator leftIt = left.begin();
    std::list<int>::iterator rightIt = right.begin();

    while ( leftIt != left.end() && rightIt != right.end() ) {

        if ( *leftIt <= *rightIt) {
            _list.push_back( *leftIt );
            leftIt++;
        } else {
             _list.push_back( *rightIt );
            rightIt++;
        }
    }

    while( leftIt != left.end() ) {

		_list.push_back(( *leftIt ));
		++leftIt;
	}

	 while( rightIt != right.end() ) {

		_list.push_back(( *rightIt ));
		++rightIt;
	}
}

void PmergeMe::log( std::string msg ) {

	std::cout << "Error: " << msg << std::endl;
}

