/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgejno <vgejno@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 22:41:26 by vgejno            #+#    #+#             */
/*   Updated: 2023/09/07 23:01:14 by vgejno           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <cmath>
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
	
	// std::cout << "Btc constructor called" << std::endl;
	std::ifstream infileCSV( fileCSV );

	if( !infileCSV.is_open() ) {
		throw Btc::ExceptionFile();
	}
	
	std::string str;
	while( std::getline( infileCSV, str ) ) {
		
		std::istringstream iss(str);
		std::string date;
		double value;

		if( std::getline( iss, date, ',') && iss >> value ) {
			
			_dataBase[date] = value;
		}
	}
	infileCSV.close();
	
	// try {

		bitcoinExchange( _dataBase, fileInput );

	// } catch (const Btc::ExceptionFile& e) {

	// 	std::cerr << "Error: " << e.what() << std::endl;
	// 	return 1;
	// }
}

void Btc::bitcoinExchange( std::map<std::string, double> _dataBase, const std::string& fileInput ) {
	
	//init with default
	ErrorState errorState = ERROR;

	std::ifstream infileInput( fileInput );

	if( !infileInput.is_open() ) {
		throw Btc::ExceptionFile();
	}

	std::string strInput;
	std::string header;
	
	//skip header
	std::getline( infileInput, header );
	
	while( std::getline( infileInput, strInput ) ) {
		
		std::istringstream issInput(strInput);
		std::string dateInput;
		std::string valueStr;

		if( std::getline( issInput, dateInput, '|' )) {
			
			//date successfully extracted
			if( !dateInput.empty() ) {
				
				// std::cout << "dateInput\t" << dateInput << std::endl;

				std::string trimDateInput = trim( dateInput );

				// std::cout << "trimDateInput\t" << trimDateInput << std::endl;
				
				if ( !findDate( trimDateInput )) { //_dataBase, 
					std::cout << "Error: not a positive number." << std::endl;
					
					// throw Btc::ExceptionReadFile();
					// break;
				}
				// std::cout << "dateInput\t" << dateInput << std::endl;
				//Valid date
				if( issInput >> std::ws >> valueStr ) {

					double toDouble = convert( valueStr );
					// std::cout << "toDouble: " << toDouble << std::endl;
					if( toDouble < 0 ) {
						
						errorState = NUM_NEG;
						std::cout << "Error: not a positive number." << std::endl;
						// break;
						
					} else if( toDouble > 1000 ) {
						
						errorState = NUM_SIZE;
						std::cout << "Error: too large a number." << std::endl;
						// break;
					}
					
					double toValue = calculateValueOnDate( _dataBase, trimDateInput, toDouble );
					if( !toValue) {
						// break;
					}
					// std::cout << "toValue: " << toValue << std::endl;
					_toValue = toValue;
       				std::cout << "DateInput: " << trimDateInput << " => " << " ValueOutput: " << _toValue << std::endl;
					// break;
					
				} else {
					//invalid value
					errorState = NO_VALUE;
					std::cout << "Error: no value." << std::endl;
					// break;
				}
			} else {
				//missing date
				errorState = NO_DATE;
				std::cout << "Error: no value." << std::endl;
				// break;
			}
		} else {
			//missing pipe
			errorState = NO_PIPE;
			std::cout << "Error: format." << std::endl;
			// break;
		}
        // std::cout << "DateInput: " << dateInput << " => " << " ValueOutput: " << _toValue << std::endl << std::endl;
	}
	infileInput.close();
}

double Btc::convert( std::string literal ) {

	double toDouble;
	
		toDouble = std::stod( literal );
		// std::cout << "Convert to double: " << toDouble << std::endl;
		return( toDouble );
}

double Btc::calculateValueOnDate( std::map<std::string, double> _dataBase, std::string trimDateInput, double toDouble) {
	
	// std::cout << "received dateInput\t" << dateInput << "received dateInput size\t" << dateInput.size() << std::endl;
	
	// std::string trimDateInput = trim( dateInput );
	
	// for (size_t i = 0; i < trimDateInput.size(); ++i) {
    // 	std::cout << "Character at index " << i << ": " << trimDateInput[i] << std::endl;
	// }
	// std::cout << "trimmed dateInput\t" << trimDateInput << " trimmed dateInput size\t" << trimDateInput.size() << std::endl;

	// if ( !findDate( trimDateInput )) { //_dataBase, 
		
	// 	throw Btc::ExceptionReadFile();
	// 	return 0;
	// }
	
	std::map<std::string, double>::key_compare keyCompare = _dataBase.key_comp();

	std::map<std::string, double>::const_iterator nearestBefore = _dataBase.end();
	std::map<std::string, double>::const_iterator nearestAfter = _dataBase.end();


	for( std::map<std::string, double>::const_iterator it = _dataBase.begin(); it != _dataBase.end(); it++ ) {
		
		bool before = keyCompare( it->first, trimDateInput );
		bool after = keyCompare( trimDateInput, it->first);
		
		if( !before && !after ) {
			
			//exact match
			nearestBefore = it;
			nearestAfter = it;
			break;
		
		} else if( before ) {
		
			//date in the map is before DateInput
			nearestBefore = it;
		} else if( after ) {
		
			//date in the map is after DateInput
			nearestAfter = it;
			break; //no need to continue
		}
	}
	
	if( nearestBefore == _dataBase.end() && nearestAfter == _dataBase.end() ) {

		//no valid date found in map
		// throw Btc::ExceptionFile();
		return 0;
	}

	//determine the nearest date
	if( nearestBefore == _dataBase.end() ) {
		
		// No date before dateInput, use nearestAfter
		// std::cout << "Nearest Date: " << nearestAfter->first << std::endl;
		return nearestAfter->second * toDouble;
		
	} else if( nearestAfter == _dataBase.end() ) {
		
		// No date after dateInput, use nearestBefore
		// std::cout << "Nearest Date: " << nearestBefore->first << std::endl;
		return nearestBefore->second * toDouble;
		
	} else {
		
		// Both before and after dates are available, choose the closest one
		int beforeDiff = calculateDateInt( nearestBefore->first, trimDateInput );
		int afterDiff = calculateDateInt( nearestAfter->first, trimDateInput );

		if( beforeDiff <= afterDiff ) {
			
			// std::cout << "Nearest Date: " << nearestBefore->first << std::endl;
			return nearestBefore->second * toDouble;
			
		} else {

			// std::cout << "Nearest Date: " << nearestAfter->first << std::endl;
			return nearestAfter->second * toDouble;
		}
	}
}

int Btc::calculateDateInt( const std::string& date1, const std::string& date2 ) {

	std::istringstream iss1(date1);
	std::istringstream iss2(date2);
	int year1 = 0, month1 = 0, day1 = 0;
	int year2 = 0, month2 = 0, day2 = 0;

	char dash = '\0'; // To store the '-' character
    if (!iss1 >> year1 >> dash >> month1 >> dash >> day1) {
        // std::cout << "Parsed date: Year1=" << year1 << " Month1=" << month1 << " Day1=" << day1 << std::endl;
		// continue;	
		return  -1;	
	// } else {
    //     // std::cerr << "Failed to parse date: " << date1 << std::endl;
    }

	if (iss2 >> year2 >> dash >> month2 >> dash >> day2) {
        // std::cout << "Parsed date: Year2=" << year2 << " Month2=" << month2 << " Day2=" << day2 << std::endl;
		// continue;	
		return  -1;
	// } else {
    //     // std::cerr << "Failed to parse date: " << date2 << std::endl;
    }

	//caalculate absolut difference in days (ignoring leap years for simplicity)
	int days1 = year1 * 365 + month1 * 30 + day1;
	int days2 = year2 * 365 + month2 * 30 + day2;

	return std::abs( days1 - days2);
}	

bool Btc::findDate( std::string trimDateInput ) { // std::map<std::string, double> _dataBase

	if( isValidDate( trimDateInput ) == false ) {
		
		std::cout << "Error: bad input " << trimDateInput << std::endl;
		return false;
	}

	// std::map<std::string, double>::const_iterator it = _dataBase.find(trimDateInput);
	// std::cout << "_dataBase\t" << it->first << "_dataBase size\t" << it->first.size() << std::endl;

	return true;
}

bool Btc::isValidDate( const std::string& trimDateInput ) {
	
	if(  trimDateInput .length() != 10 ) {
		return false;
	}
	
	//split the date into components
	int year, month, day;
	std::istringstream iss(trimDateInput);

	char dash; // To store the '-' character
    if (iss >> year >> dash >> month >> dash >> day) {
        // std::cout << "Parsed date: Year=" << year << " Month=" << month << " Day=" << day << std::endl;
        if (dash == '-') {
            // Date was successfully parsed
			if( year < 1582 || month < 1 || month > 12 || day < 1 || day > 31 ) {
				std::cerr << YL << "Date false: " << trimDateInput << std::endl;
				return false;
			}
			if( day == 31 && ( month == 2 || month == 4 || month == 6 || month == 9 || month == 11) ) {
				std::cerr << YL << "Date false: " << trimDateInput << std::endl;

				return false;
			}
			if( day == 30 && month == 2 ) {
				std::cerr << YL << "Date false: " << trimDateInput << std::endl;

				return false;
			}
			if( (month == 2 && day == 29) && (year % 4 != 0 || year % 100 == 0 ) ) {
				std::cerr << YL << "Date false: " << trimDateInput << std::endl;

				return false;
			}
        } else {
            // std::cerr << "Invalid date format: " << trimDateInput << std::endl;
			return false;
        }
    } else {
        // std::cerr << "Failed to parse date: " << trimDateInput << std::endl;
		return false;
    }
	
	std::string formatedYear = formatWidthDate( year, 4 );
	std::string formatedMonth = formatWidthDate( month, 2 );
	std::string formatedDay = formatWidthDate( day, 2 );

	// std::cout << YL << "Parsed date: Year=" << formatedYear << 
	// 	" Month=" << formatedMonth << " Day=" << formatedDay << std::endl;

	return true;
}

std::string Btc::formatWidthDate( int value, int width ) {

	std::string formatted = std::to_string( value );
	
	while( static_cast<int>(formatted.length()) < width ) {
		formatted = "0" + formatted;
	}
	return formatted;
}

std::string Btc::trim( std::string& dateInput ) {
	
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

std::map<std::string, double> Btc::getMap() const {
	
	return this->_dataBase;
}

Btc::~Btc() {

	// std::cout << "Btc destructor called" << std::endl;
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
	
	return "could not open file.";
}

const char* Btc::ExceptionReadFile::what() const throw() {
	
	return "Invalid line format";
}

std::ostream& operator<<(std:: ostream& os, const Btc& rhs ) {
	
	std::map<std::string, double> btcMap = rhs.getMap();
	std::map<std::string, double>::const_iterator it;
	
	for( it = btcMap.begin(); it != btcMap.end(); ++it ) {
		os << it->first << it->second << std::endl;
	}
	return os;
}
