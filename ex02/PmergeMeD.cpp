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

	// timeval startTime, endTime;
	// gettimeofday(&startTime, NULL);
	// buildDeque(av);
	// gettimeofday(&endTime, NULL);

	timeval start, end;
	gettimeofday(&start, NULL);
	// unsync the I/O of C and C++.
    std::ios_base::sync_with_stdio(false);
	buildDeque(av);
	gettimeofday(&end, NULL);

	double elapsedTime;

	elapsedTime = (end.tv_sec - start.tv_sec) * 1e6;
    elapsedTime = (elapsedTime + (end.tv_usec - start.tv_usec)) * 1e-6;
	std::cout << GR << "Time to process a range of " << _deque.size() << " elements with std::deque: "
			<< std::fixed << std::setprecision(6) << elapsedTime << " us" << std::endl;
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

	std::cout << BL << "Ford Johnson Sort Deque" << std::endl;
	std::cout << BL << "Before:\t";
	printDeque( _deque );
	int straggler = 0;
	checkDequeStraggler( _deque, straggler );
	// std::cout << OR << "straggler: " << straggler << std::endl;

	fordJohnsonSortDeque( _deque, straggler );

	std::cout << OR << "After:\t";
	printDeque( _deque );
}

void PmergeMeD::printDeque( const std::deque<int>& _deque ) {

	for(  std::deque<int>::const_iterator it = _deque.begin(); it != _deque.end(); it++ ) {

		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

void PmergeMeD::checkDequeStraggler( std::deque<int>& _deque, int& straggler ) {

	if( _deque.size() <= 1 ) {
		return;
	}

	bool isStraggler = (_deque.size() % 2 == 1);
	// std::cout << "isStraggler: " << isStraggler << std::endl;

	// int straggler = 0;
	if( isStraggler ) {

		std::deque<int>::iterator its = _deque.end();
		--its;
		straggler = *its;
		_deque.pop_back();
		// std::cout << GR << "straggler: " << straggler << std::endl;
	}
}

void PmergeMeD::fordJohnsonSortDeque( std::deque<int>& _deque, int straggler ) {

	// int straggler = 0;
	// std::cout << "straggler: " << straggler << std::endl;

	if( _deque.size() <= 1 ) {
		return;
	}

	// bool isStraggler = (_deque.size() % 2 == 1);
	// // std::cout << "isStraggler: " << isStraggler << std::endl;

	// int straggler = 0;
	// if( isStraggler ) {

	// 	std::deque<int>::iterator its = _deque.end();
	// 	--its;
	// 	straggler = *its;
	// 	_deque.pop_back();
	// 	std::cout << "straggler: " << straggler << std::endl;
	// }
	// printDeque( _deque );

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

	fordJohnsonSortDeque( left, 0);
	fordJohnsonSortDeque( right, 0 );

	_deque.clear();
	merge( _deque, left, right, straggler );
}

void PmergeMeD::merge( std::deque<int>& _deque, std::deque<int>& leftIt, std::deque<int>& rightIt, int straggler ) {

    // std::deque<int>::iterator leftIt = left.begin();
    // std::deque<int>::iterator rightIt = right.begin();

	// std::cout << "straggler: " << straggler << std::endl;

	// Merge the sorted left and right halves back together
    while ( !leftIt.empty() && !rightIt.empty() ) {

        if ( leftIt.front() <= rightIt.front() ) {
            _deque.push_back( leftIt.front() );
            leftIt.pop_front();
        } else {
             _deque.push_back( rightIt.front() );
            rightIt.pop_front();
        }
    }

	// Append any remaining elements from both containers
    _deque.insert( _deque.end(), leftIt.begin(), leftIt.end() );
    _deque.insert( _deque.end(), rightIt.begin(), rightIt.end() );

	// Insert the straggler element back into the sorted deque
	if( straggler ) {

		// std::cout << "straggler: " << straggler << std::endl;

		std::deque<int>::iterator itEnd = _deque.end();
		for( std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); it++ ) {

			if( straggler < *it ) {

				_deque.insert( it, straggler );
				break;
			}

			if( straggler > *itEnd ) {

				_deque.push_back( straggler );
				break;
			}
		}
	}
}

void PmergeMeD::log( std::string msg ) {

	std::cout << "Error: " << msg << std::endl;
}

