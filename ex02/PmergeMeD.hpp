#ifndef PMERGEMED_HPP
# define PMERGEMED_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <exception>
#include <list>
#include <deque>
#include <utility>

class PmergeMeD {

	private:

		// std::list<std::pair<int, int> > _pairList;
		std::deque<int> _deque;


	public:

		PmergeMeD( std::string av );
		~PmergeMeD();

		void log( std::string msg );
		void buildDeque( std::string av );
		void printDeque(const std::deque<int>& _deque);
		bool isDigit(const std::string& numStr);
		void checkDequeStraggler( std::deque<int>& _deque, int& straggler );
		void fordJohnsonSortDeque( std::deque<int>& _deque, int straggler );
		void merge( std::deque<int>& _deque, std::deque<int>& left, std::deque<int>& right, int straggler );

};


#endif

