/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:41:15 by vgejno            #+#    #+#             */
/*   Updated: 2023/09/05 20:08:30 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <exception>
#include "Color.hpp"


class Btc {

	private:

		std::map<std::string, double> _dataBase;
		// std::map<std::string, std::string> _dataInput;
		double _toValue;

	public:

		Btc( const std::string& fileCSV, const std::string& fileInput );
		~Btc();

		Btc( const Btc& other );
		Btc& operator=( const Btc& other );

		void parseInputFile( std::map<std::string, double> _dataBase, const std::string& fileInput );
		double convert( std::string literal );
		double calculateValueOnDate( std::map<std::string, double> _dataBase, std::string dateInput, double toDouble);
		bool findDate( std::map<std::string, double> _dataBase, std::string dateInput );
		std::string trim( std::string& dateInput );
		bool isValidDate( const std::string& dateInput );
		
		class ExceptionFile : public std::exception {

			public:
				virtual const char *what() const throw();
		};

		class ExceptionReadFile : public std::exception {

			public:
				virtual const char *what() const throw();
		};
	
};

std::ostream& operator<<(std:: ostream& os, const Btc& rhs );

#endif