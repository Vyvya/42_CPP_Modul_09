#include "PmergeMe.hpp"
#include "Color.hpp"
#include <stdlib.h>
#include <utility>
#include <ctime>
#include <iomanip>

PmergeMe::PmergeMe( std::string av ) {

	// std::cout << "PmergeMe constructor called" << std::endl;
	std::cout << av << std::endl;
	std::cout << std::endl;

	clock_t startTime = clock(); // Timer<milliseconds, steady_clock>
	buildList( av );
	clock_t endTime = clock(); // Timer<milliseconds, steady_clock>
	double elapsedTime = static_cast<double>(endTime - startTime) * 1e6 / CLOCKS_PER_SEC;
	std::cout << std::fixed << std::setprecision(5) << elapsedTime << " us" << std::endl;
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

	std::cout << "Before:\t";
	printList( _list );
	mergeSort( _list );

	std::cout << "After:\t";
	printList( _list );
}	

void PmergeMe::printList( const std::list<int>& _list ) {

	for( std::list<int>::const_iterator it = _list.begin(); it != _list.end(); it++ ) {

		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::mergeSort( std::list<int>& _list ) {

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

	mergeSort( left );
	mergeSort( right );

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

