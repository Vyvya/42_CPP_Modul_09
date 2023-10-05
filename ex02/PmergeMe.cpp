#include "PmergeMe.hpp"
#include "Color.hpp"
#include <stdlib.h>
#include <utility>
#include <ctime>
#include <iomanip>
#include <sys/time.h>

PmergeMe::PmergeMe( std::string av ) {

	timeval start, end;

	//list
	gettimeofday(&start, NULL);
	// unsync the I/O of C and C++.
    std::ios_base::sync_with_stdio(false);
	buildList(av);
	gettimeofday(&end, NULL);

	double elapsedTime;

	elapsedTime = (end.tv_sec - start.tv_sec) * 1e6;
    elapsedTime = (elapsedTime + (end.tv_usec - start.tv_usec)) * 1e-6;

	std::cout << GR << "Time to process a range of " << _list.size() << " elements with std::deque: "
			<< std::fixed << std::setprecision(6) << elapsedTime << " us" << std::endl;
	std::cout << RES << std::endl;

	//deque
	timeval startD, endD;
	gettimeofday(&startD, NULL);
    std::ios_base::sync_with_stdio(false);
	buildDeque(av);
	gettimeofday(&endD, NULL);

	double elapsedTimeD;

	elapsedTimeD = (endD.tv_sec - startD.tv_sec) * 1e6;
    elapsedTimeD = (elapsedTimeD + (endD.tv_usec - startD.tv_usec)) * 1e-6;
	std::cout << GR << "Time to process a range of " << _deque.size() << " elements with std::deque: "
			<< std::fixed << std::setprecision(6) << elapsedTimeD << " us" << std::endl;
	std::cout << RES << std::endl;

}

PmergeMe::~PmergeMe() {

	// std::cout << "PmergeMe destructor called" << std::endl;
}

//list

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

	bool isStraggler = (_list.size() % 2 == 1);

	if( isStraggler ) {

		std::list<int>::iterator its = _list.end();
		--its;
		straggler = *its;
		_list.pop_back();
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
	mergeList( _list, left, right, straggler );
}

void PmergeMe::mergeList( std::list<int>& _list, std::list<int>& left, std::list<int>& right, int straggler ) {

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

	if( straggler ) {

		std::list<int>::iterator itEnd = _list.end();
		--itEnd;

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

//deque

void PmergeMe::buildDeque(std::string av) {

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
	fordJohnsonSortDeque( _deque, straggler );

	std::cout << OR << "After:\t";
	printDeque( _deque );
}

void PmergeMe::printDeque( const std::deque<int>& _deque ) {

	for(  std::deque<int>::const_iterator it = _deque.begin(); it != _deque.end(); it++ ) {

		std::cout << " " << *it;
	}
	std::cout << std::endl;
}

void PmergeMe::checkDequeStraggler( std::deque<int>& _deque, int& straggler ) {

	if( _deque.size() <= 1 ) {
		return;
	}

	bool isStraggler = (_deque.size() % 2 == 1);

	if( isStraggler ) {

		std::deque<int>::iterator its = _deque.end();
		--its;
		straggler = *its;
		_deque.pop_back();
	}
}

void PmergeMe::fordJohnsonSortDeque( std::deque<int>& _deque, int straggler ) {

	if( _deque.size() <= 1 ) {
		return;
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

	fordJohnsonSortDeque( left, 0);
	fordJohnsonSortDeque( right, 0 );

	_deque.clear();
	mergeDeque( _deque, left, right, straggler );
}

void PmergeMe::mergeDeque( std::deque<int>& _deque, std::deque<int>& leftIt, std::deque<int>& rightIt, int straggler ) {

    while ( !leftIt.empty() && !rightIt.empty() ) {

        if ( leftIt.front() <= rightIt.front() ) {
            _deque.push_back( leftIt.front() );
            leftIt.pop_front();
        } else {
             _deque.push_back( rightIt.front() );
            rightIt.pop_front();
        }
    }

	// Add any remaining elements from both containers
    _deque.insert( _deque.end(), leftIt.begin(), leftIt.end() );
    _deque.insert( _deque.end(), rightIt.begin(), rightIt.end() );

	// Insert the straggler element back into the sorted deque
	if( straggler ) {

		std::deque<int>::iterator itEnd = _deque.end();
		--itEnd;

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

void PmergeMe::log( std::string msg ) {

	std::cout << "Error: " << msg << std::endl;
}
