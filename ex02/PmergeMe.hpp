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

		// std::list<std::pair<int, int> > _pairList;
		std::list<int> _list;


	public:

		PmergeMe( std::string av );
		~PmergeMe();

		void log( std::string msg );
		void buildList( std::string av );
		void printList(const std::list<int>& _list);
		bool isDigit(const std::string& numStr);
		void checkListStraggler( std::list<int>& _list, int& straggler );
		void fordJohnsonSortList( std::list<int>& _list, int straggler );
		void merge( std::list<int>& _list, std::list<int>& left, std::list<int>& right, int straggler );

};


#endif

