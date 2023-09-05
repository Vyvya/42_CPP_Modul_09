/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:41:26 by vgejno            #+#    #+#             */
/*   Updated: 2023/09/05 20:50:06 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "Color.hpp"

enum ErrorState{
	
	ERROR,
	NO_DATE,
	NO_PIPE,
	NO_VALUE,
	NUM_NEG,
	NUM_SIZE
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

	parseInputFile( _dataBase, fileInput );
}

void Btc::parseInputFile( std::map<std::string, double> _dataBase, const std::string& fileInput ) {
	
	std::map<std::string, std::string> dataOutput;

	//init with default
	ErrorState errorState = ERROR;
	// std::cout << "reading input.txt 1" << std::endl;
	// (void)_dataBase;
	std::ifstream infileInput( fileInput );

	if( !infileInput.is_open() ) {
		
		throw Btc::ExceptionFile();
	}

	std::string strInput;
	std::string header;
	//skip header
	std::getline( infileInput, header );

	// std::cout << "reading input.txt 2" << std::endl;

	while( std::getline( infileInput, strInput ) ) {
		
		std::istringstream issInput(strInput);
		std::string dateInput;
		std::string valueStr;

		if( std::getline( issInput, dateInput, '|' )) {
			
			// std::cout << "reading input.txt 3" << std::endl;
			
			//date successfully extracted
			if( !dateInput.empty() ) {
				
				std::cout << "dateInput\t" << dateInput << std::endl;
				
				//Valid date
				if( issInput >> std::ws >> valueStr ) {

					double toDouble = convert( valueStr );
					std::cout << "toDouble: " << toDouble << std::endl;
					if( toDouble < 0 ) {
						
						errorState = NUM_NEG;
					} else if( toDouble > 1000 ) {
						
						errorState = NUM_SIZE;
					}
					
					double toValue = calculateValueOnDate( _dataBase, dateInput, toDouble );
					std::cout << "toValue: " << toValue << std::endl;
					_toValue = toValue;
					
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
        // std::cout << "DateInput: " << dateInput << " => " << " ValueInput: " << valueStr << std::endl;
        std::cout << "DateInput: " << dateInput << " => " << " ValueOutput: " << _toValue << std::endl << std::endl;
		
		
	}
	
	// for( std::map<std::string, std::string>::const_iterator it = dataOutput.begin(); it != dataOutput.end(); ++it ) {
			
	// 		std::cout << "DateInput: " << it->first <<  " => " << it->second <<std::endl;
	// }
	
	infileInput.close();
}

double Btc::convert( std::string literal ) {

	double toDouble;
	
		toDouble = std::stod( literal );
		std::cout << "Convert to double: " << toDouble << std::endl;
		return( toDouble );
}

double Btc::calculateValueOnDate( std::map<std::string, double> _dataBase, std::string dateInput, double toDouble) {
	
	std::cout << "received dateInput\t" << dateInput << "received dateInput size\t" << dateInput.size() << std::endl;
	

	if ( !findDate( _dataBase, dateInput )) {
		
		throw Btc::ExceptionFile();
	}
	

	std::map<std::string, double>::const_iterator it = _dataBase.find(dateInput);
	
	if(it != _dataBase.end() ) {
		std::cout << "Date: " << it->first <<  " Value: " << it->second <<std::endl;
		return (it->second * toDouble);
	}
	
	return 0;
}

bool Btc::findDate( std::map<std::string, double> _dataBase, std::string dateInput ) {

	(void)(void)(_dataBase);
	std::string trimDateInput = trim( dateInput );
	
	for (size_t i = 0; i < trimDateInput.size(); ++i) {
    	std::cout << "Character at index " << i << ": " << trimDateInput[i] << std::endl;
	}
	std::cout << "trimmed dateInput\t" << trimDateInput << " trimmed dateInput size\t" << trimDateInput.size() << std::endl;
	// dateInput.clear();
	
	if( isValidDate( trimDateInput ) == false ) {
		
		std::cout << "Error: bad input " << trimDateInput << std::endl;

	}
	
	std::map<std::string, double>::const_iterator it = _dataBase.find(trimDateInput);
	std::cout << "_dataBase\t" << it->first << "_dataBase size\t" << it->first.size() << std::endl;

	return 1;
}

bool Btc::isValidDate( const std::string&  trimDateInput  ) {
	
	std::cout << "1" << std::endl;
	if(  trimDateInput .length() != 10 ) {
		return false;
	}
	std::cout << "2" << std::endl;
	
	//split the date into components
	int year, month, day;
	std::cout << "isValidDate trimmed dateInput\t" << trimDateInput.c_str() << " trimmed dateInput size\t" << trimDateInput.size() << std::endl;
	std::istringstream iss(trimDateInput);
	char dash; // To store the '-' character
    if (iss >> year >> dash >> month >> dash >> day) {
        if (dash == '-') {
            // Date was successfully parsed
            std::cout << "Parsed date: Year=" << year << " Month=" << month << " Day=" << day << std::endl;
			if( year < 1000 || month < 1 || month > 12 || day < 1 || day > 31 ) {
				std::cerr << YL << "Date false: " << trimDateInput << std::endl;

				return false;
			}
        } else {
            std::cerr << "Invalid date format: " << trimDateInput << std::endl;
        }
    } else {
        std::cerr << "Failed to parse date: " << trimDateInput << std::endl;
    }
	
	std::cout << "4" << std::endl;
	
	return true;
}

// std::string Btc::trim( std::string& dateInput ) {

// 	// std::string::const_iterator it = dateInput.begin();
// 	// while( it != dateInput.end() && isspace( *it )) {
// 	// 	it++;
// 	// }
// 	// dateInput.resize(10);

// 	//trim leading white spaces
// 	size_t start = dateInput.find_first_not_of(" \t\r\n");
	
// 	std::cout << "resized dateInput\t" << dateInput << "resized dateInput size\t" << dateInput.size() << std::endl;

// 	return dateInput;
// }

std::string Btc::trim(std::string& dateInput) {
    // Trim leading whitespace
    size_t start = dateInput.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        // The string contains only whitespace, return an empty string
        dateInput.clear();
        return dateInput;
    }
    dateInput = dateInput.substr(start);

    // Trim trailing whitespace
    size_t end = dateInput.find_last_not_of(" \t\r\n");
    if (end != std::string::npos) {
        dateInput = dateInput.substr(0, end + 1);
    }

    return dateInput;
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