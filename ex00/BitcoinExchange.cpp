/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:41:26 by vgejno            #+#    #+#             */
/*   Updated: 2023/09/01 23:59:17 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <string>

Btc::Btc( char * fileCSV ) {
	
	std::ifstream infileCSV( fileCSV );

	if( !infileCSV.is_open() ) {
		
		throw Btc::Exception();
	}
	} else {
		
	}
	std::string str;
		while( infileCSV.good() ) {
			
			std::getline( infileCSV, str );
			std::cout << str << std::endl;
}

Btc::~Btc() {

	
}
		
Btc::Btc( const Btc& other ) {

	
}
Btc& Btc::operator=( const Btc& other ) {

	
}

std::ostream& operator<<(std:: ostream& os, const Btc& rhs ) {
	
	
}