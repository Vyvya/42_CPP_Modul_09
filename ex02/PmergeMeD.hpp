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
		void fordJohnsonSortDeque( std::deque<int>& _deque );
		void merge( std::list<int>& _list, std::list<int>& left, std::list<int>& right);

};


#endif

