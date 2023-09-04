/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:41:15 by vgejno            #+#    #+#             */
/*   Updated: 2023/09/04 20:13:01 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <exception>



class Btc {

	private:

		std::map<std::string, double> _dataBase;
		std::map<std::string, std::string> _dataInput;

		void parseInputFile( const std::string& fileInput );

	public:

		Btc( const std::string& fileCSV, const std::string& fileInput );
		~Btc();

		Btc( const Btc& other );
		Btc& operator=( const Btc& other );

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