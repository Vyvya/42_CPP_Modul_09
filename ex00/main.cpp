/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:41:29 by vgejno            #+#    #+#             */
/*   Updated: 2023/09/07 22:55:37 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*CSV stands for Comma Separated Values, used to store tabular data*/

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "Color.hpp"

void readFile( char *file ) {

	std::ifstream infile( file );

	if( infile.is_open() ) {
		
		std::string str;
		while( infile.good() ) {
			
			std::getline( infile, str );
			std::cout << str << std::endl;
		}
	} else {
		
		std::cout << "Error: opening file" << std::endl;
	}

	infile.close();
	return ;
}

int main( int argc, char **argv ) {
	
	if( argc != 2) {
		
		std::cout << "Error: wrong number of args" << std::endl;
		return -1;
	}

	try {

		Btc btc( "data.csv", argv[1] );

	} catch (const Btc::ExceptionFile& e) {

		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}