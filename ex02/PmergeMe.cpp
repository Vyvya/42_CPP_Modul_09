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

	timeval start, end;
	gettimeofday(&start, NULL);
	// unsync the I/O of C and C++.
    std::ios_base::sync_with_stdio(false);
	buildList(av);
	gettimeofday(&end, NULL);

	// double elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000000.0 + (endTime.tv_usec - startTime.tv_usec);
	double elapsedTime;

	elapsedTime = (end.tv_sec - start.tv_sec) * 1e6;
    elapsedTime = (elapsedTime + (end.tv_usec - start.tv_usec)) * 1e-6;

	std::cout << GR << "Time to process a range of " << _list.size() << " elements with std::deque: "
			<< std::fixed << std::setprecision(6) << elapsedTime << " s" << std::endl;
	std::cout << RES << std::endl;



	// timeval startTime, endTime;
	// gettimeofday(&startTime, NULL);
	// buildList(av);
	// gettimeofday(&endTime, NULL);

	// long long elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000000LL + (endTime.tv_usec - startTime.tv_usec);
	// clock_t startTimeClock = clock(); // Timer<milliseconds, steady_clock>
	// buildList( av );
	// clock_t endTimeClock = clock(); // Timer<milliseconds, steady_clock>
	// double elapsedTimeClock = static_cast<double>(endTimeClock - startTimeClock) * 1e6 / CLOCKS_PER_SEC;
	// std::cout << GR << "Time to process a range of\t" << _list.size() << " elements with std::list : \t" << std::fixed << std::setprecision(5) << elapsedTimeClock << " us" << std::endl;
	// std::cout << RES << std::endl;
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

	std::cout << BL << "Ford Johnson Sort List" << std::endl;
	std::cout << BL << "Before:\t";
	printList( _list );

	int straggler = 0;
	checkListStraggler( _list, straggler );
	fordJohnsonSortList( _list, straggler );

	std::cout << OR << "After:\t";
	printList( _list );
}

void PmergeMe::printList( const std::list<int>& _list ) {

	for( std::list<int>::const_iterator it = _list.begin(); it != _list.end(); it++ ) {

		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

void PmergeMe::checkListStraggler( std::list<int>& _list, int& straggler ) {

	// if( _list.size() <= 1 ) {
	// 	return;
	// }

	bool isStraggler = (_list.size() % 2 == 1);
	// std::cout << "isStraggler: " << isStraggler << std::endl;

	// int straggler = 0;
	if( isStraggler ) {

		std::list<int>::iterator its = _list.end();
		--its;
		straggler = *its;
		_list.pop_back();
		// std::cout << GR << "straggler: " << straggler << std::endl;
	}
}

void PmergeMe::fordJohnsonSortList( std::list<int>& _list, int straggler ) {

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

	fordJohnsonSortList( left, 0 );
	fordJohnsonSortList( right, 0 );

	_list.clear();
	merge( _list, left, right, straggler );
}

void PmergeMe::merge( std::list<int>& _list, std::list<int>& left, std::list<int>& right, int straggler ) {

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
	// printList( _list );

    while( leftIt != left.end() ) {

		_list.push_back(( *leftIt ));
		++leftIt;
	}

	 while( rightIt != right.end() ) {

		_list.push_back(( *rightIt ));
		++rightIt;
	}

	// Insert the straggler element back into the sorted deque
	if( straggler ) {

		// std::cout << "1straggler: " << straggler << std::endl;

		std::list<int>::iterator itEnd = _list.end();
		for( std::list<int>::iterator it = _list.begin(); it != _list.end(); it++ ) {

			if( straggler < *it ) {

				_list.insert( it, straggler );
				break;
			}

			if( straggler > *itEnd ) {

				_list.push_back( straggler );
				break;
			}
		}
	}
}

void PmergeMe::log( std::string msg ) {

	std::cout << "Error: " << msg << std::endl;
}

