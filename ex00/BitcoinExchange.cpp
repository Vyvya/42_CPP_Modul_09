/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:41:26 by vgejno            #+#    #+#             */
/*   Updated: 2023/09/04 20:22:08 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

enum ErrorState{
	
	ERROR,
	NO_DATE,
	NO_PIPE,
	NO_VALUE
};


Btc::Btc( const std::string& fileCSV, const std::string& fileInput ) {
	
	std::cout << "Btc constructor called" << std::endl;
	std::ifstream infileCSV( fileCSV );

	if( !infileCSV.is_open() ) {
		
		throw Btc::ExceptionFile();
	}
	
	std::string str;
	while( std::getline( infileCSV, str ) ) {
		
		std::istringstream iss(str);
		std::string date;
		double value;
		// _dataBase.insert();
		if( std::getline( iss, date, ',') && iss >> value ) {
			
			_dataBase[date] = value;
		}
		
		// for( std::map<std::string, double>::const_iterator it = _dataBase.begin(); it != _dataBase.end(); ++it ) {
			
		// 	std::cout << "Date: " << it->first <<  " Value: " << it->second <<std::endl;
		// }
	}
	infileCSV.close();

	parseInputFile( fileInput );
}

void Btc::parseInputFile( const std::string& fileInput ) {
	
	//init with default
	ErrorState errorState = ERROR;
	std::cout << "reading input.txt 1" << std::endl;
	
	std::ifstream infileInput( fileInput );

	if( !infileInput.is_open() ) {
		
		throw Btc::ExceptionFile();
	}

	std::string strInput;
	std::string header;
	//skip header
	std::getline( infileInput, header );

	std::cout << "reading input.txt 2" << std::endl;

	while( std::getline( infileInput, strInput ) ) {
		
		std::istringstream issInput(strInput);
		std::string dateInput;
		std::string valueInput;

		if( std::getline( issInput, dateInput, '|' )) {

			//date successfully extracted
			if( !dateInput.empty() ) {
				
				//Valid date
				if( issInput >> std::ws >> valueInput ) {
					
					//Value was successfulle extracted
					// std::string valueStr = std::to_string(valueInput);
					// _dataInput[dateInput] = std::stod(valueStr);
					_dataInput[dateInput] = valueInput;

				} else {
					
					//invalid value
					errorState = NO_VALUE;
				}
			} else {

				//missing date
				errorState = NO_DATE;
			}
		} else {
			
			//missing pipe
			errorState = NO_PIPE;
		}

		// Debugging output to check values
        // std::cout << "DateInput: " << dateInput << " ValueInput: " << valueInput << std::endl;
		
		
	}
	for( std::map<std::string, std::string>::const_iterator it = _dataInput.begin(); it != _dataInput.end(); ++it ) {
			
			std::cout << "DateInput: " << it->first <<  " ValueInput: " << it->second <<std::endl;
		}
	infileInput.close();
}

Btc::~Btc() {

	std::cout << "Btc destructor called" << std::endl;
}
		
Btc::Btc( const Btc& other ) : _dataBase(other._dataBase) {

}
Btc& Btc::operator=( const Btc& other ) {

	if( this != &other) {
		
		_dataBase = other._dataBase;
		
	} else {
		
		throw Btc::ExceptionReadFile();
	}
	
	return *this;
}

const char* Btc::ExceptionFile::what() const throw() {
	
	return "Error: file";
}

const char* Btc::ExceptionReadFile::what() const throw() {
	
	return "Error: Invalid line format";
}

std::ostream& operator<<(std:: ostream& os, const Btc& rhs ) {
	
	(void)os;
	(void)rhs;
	return os;
}