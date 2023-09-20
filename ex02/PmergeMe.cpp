#include "PmergeMe.hpp"
#include "Color.hpp"
#include <stdlib.h>
#include <utility>

PmergeMe::PmergeMe( std::string av ) {

	std::cout << "PmergeMe constructor called" << std::endl;
	std::cout << av << std::endl;
	std::cout << std::endl;


	buildPairs( av );

}

PmergeMe::~PmergeMe() {}

void PmergeMe::buildPairs(std::string av) {
	std::istringstream iss(av);
	std::string num1_str, num2_str;

	while ( iss >> num1_str ) {

		int num1 = std::stoi( num1_str );

		if ( iss >> num2_str ) {

			int num2 = std::stoi( num2_str );

			if( num1 > num2 ) {

				swapNum( &num1, &num2 );
			}
			_pairList.push_back(std::make_pair( num1, num2 ));
			std::cout << R << num1 << " " << num2 << std::endl;

		} else {

			_unpairList.push_back( num1 );
			std::cout << num1 << std::endl;

			// Clear the stream state and ignore any remaining characters on the current line
			iss.clear();
			iss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

	}
	std::cout << std::endl;

	// swapPairs( &_pairList, &_unpairList );
	sortPairs( _pairList, _unpairList );
}

void PmergeMe::swapNum( int* num1, int* num2 ) {

	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

// void PmergeMe::swapPairs( std::list<std::pair<int, int> > _pairList, std::list<int> _unpairList ) {

// 	(void)_unpairList;

// 	std::list<std::pair<int, int> >::iterator it = _pairList.begin();
// 	std::list<std::pair<int, int> >::iterator itf;
// 	std::list<std::pair<int, int> >::iterator its = _pairList.begin();

// 	// swapPairs( )
// 	for( itf = _pairList.begin(); itf!= _pairList.end(); itf++ ) {

// 		for( its = it++; its!= _pairList.end(); its++ ) {

// 			if( (*itf).first > (*its).first ) {

// 				swapNum( &(*itf).first, &(*its).first );
// 			}
// 			if( (*itf).second > (*its).second ) {

// 				swapNum( &(*itf).second, &(*its).second );
// 			}
// 		}
// 	}
// }

void PmergeMe::sortPairs( std::list<std::pair<int, int> > _pairList, std::list<int> _unpairList ) {

	(void)_unpairList;

	std::list<std::pair<int, int> >::iterator it = _pairList.begin();
	std::list<std::pair<int, int> >::iterator itf;
	std::list<std::pair<int, int> >::iterator its = _pairList.begin();


	std::list<std::pair<int, int> >::iterator it1;
	std::list<std::pair<int, int> >::iterator it2;

	// swapPairs( )
	for( itf = _pairList.begin(); itf!= _pairList.end(); itf++ ) {

		for( its = it++; its!= _pairList.end(); its++ ) {

			if( (*itf).first > (*its).first ) {

				swapNum( &(*itf).first, &(*its).first );
			}
			if( (*itf).second > (*its).second ) {

				swapNum( &(*itf).second, &(*its).second );
			}
		}
		std::cout << YL << (*itf).first << " " << (*itf).second << std::endl;

	}

	std::cout << std::endl;

	std::list<int> mergeList1;
	std::list<int> mergeList2;

	int temp1;
	int temp2;

	for( it2 = _pairList.begin(); it2 != _pairList.end(); it2++ ) {

		std::cout << OR << (*it2).first << " " << (*it2).second << std::endl;

		temp1 = (*it2).first;
		temp2 = (*it2).second;

		std::cout << VL << "temp1: " << temp1 << std::endl;
		std::cout << VL << "temp2: " << temp2 << std::endl;

		mergeList1.push_back( temp1 );

		std::cout << GR << "mergeList1: ";
		for( std::list<int>::iterator itpr = mergeList1.begin(); itpr != mergeList1.end(); itpr++ ) {

			std::cout << GR << *itpr << " ";

		}

		std::cout << std::endl;

		mergeNum( temp2, mergeList1 );
		// if( it2 != _pairList.end() ) {

		// 	std::list<std::pair<int, int> >::iterator it3 = it2++;
		// 	if( (*it3).first > temp2 ) {

			mergeList1.push_back( temp2 );
		// sortPairs( _pairList, _unpairList );

			// }

		// }
		// _pairList.pop_back();
	}
	std::cout << std::endl;
	std::cout << GR << "final mergeList1: ";
	for( std::list<int>::iterator itpr = mergeList1.begin(); itpr != mergeList1.end(); itpr++ ) {

		std::cout << GR << *itpr << " ";

	}
	std::cout << std::endl;

}

void PmergeMe::mergeNum( int num, std::list<int> mergeList1 ) {

	// std::list<int>::iterator it = mergeList1.begin();
	std::list<int>::iterator itf;
	// std::list<int>::iterator its = mergeList1.begin();

	std::cout << BL << "num: " << num << std::endl;

	// swapPairs( )
	for( itf = mergeList1.begin(); itf!= mergeList1.end(); itf++ ) {

			std::cout << R << "*itf: " << *itf << std::endl;

			if( *itf > num ) {

				swapNum( &(*itf), &num );
				std::cout << VL << "swaped num: " << num << std::endl;

				return;
			}

		}
}

void PmergeMe::log( std::string msg ) {

	std::cout << "Error: " << msg << std::endl;
}
