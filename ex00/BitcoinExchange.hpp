/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:41:15 by vgejno            #+#    #+#             */
/*   Updated: 2023/09/01 23:23:27 by vgejno           ###   ########.fr       */
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

		std::map<std::string, int> dataBase;

	public:

		Btc();
		~Btc();

		Btc( const Btc& other );
		Btc& operator=( const Btc& other );

		class Exception : public std::exception {

			public:
		} 
	
};

std::ostream& operator<<(std:: ostream& os, const Btc& rhs ) {
	
	
}

#endif