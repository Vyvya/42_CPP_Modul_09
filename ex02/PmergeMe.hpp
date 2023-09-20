#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <exception>
#include <list>
#include <deque>
#include <utility>

class PmergeMe {

	private:

		std::list<std::pair<int, int> > _pairList;
		std::list<int> _unpairList;


	public:

		PmergeMe( std::string av );
		~PmergeMe();

		void log( std::string msg );
		void buildPairs( std::string av );
		int parsePairs(std::string& numStr);
		bool isDigit(const std::string& numStr);
		// void swapPairs( std::list<std::pair<int, int> > _pairList, std::list<int> _unpairList );
		void sortPairs( std::list<std::pair<int, int> >& _pairList, std::list<int>& _unpairList );
		void mergeNum( int num, std::list<int> mergeList1 );
		void swapNum( int* num1, int* num2 );
};


#endif

