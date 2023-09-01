/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:41:15 by vgejno            #+#    #+#             */
/*   Updated: 2023/09/01 23:59:30 by vgejno           ###   ########.fr       */
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

		std::map<const std::string, int> _dataBase;

	public:

		Btc( std::string fileCSV );
		~Btc();

		Btc( const Btc& other );
		Btc& operator=( const Btc& other );

		class Exception : public std::exception {

			public:
				const char *what() const throw();
		};
	
};

std::ostream& operator<<(std:: ostream& os, const Btc& rhs );

#endif