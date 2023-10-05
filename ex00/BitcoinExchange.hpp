/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:41:15 by vgejno            #+#    #+#             */
/*   Updated: 2023/09/24 17:39:43 by vgejno           ###   ########.fr       */
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
		double _toValue;

	public:

		Btc( const std::string& fileCSV, const std::string& fileInput );
		~Btc();

		Btc( const Btc& other );
		Btc& operator=( const Btc& other );

		std::map<std::string, double> getMap() const;
		void bitcoinExchange( std::map<std::string, double> _dataBase, const std::string& fileInput );
		double convert( std::string literal );
		double calculateValueOnDate( std::map<std::string, double> _dataBase, std::string trimDateInput, double toDouble);
		bool findDate( std::string trimDateInput );
		std::string trim( std::string& dateInput );
		bool isValidDate( const std::string& dateInput );
		std::string formatWidthDate( int value, int width );
		int calculateDateInt( const std::string& date1, const std::string& date2 );
		
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