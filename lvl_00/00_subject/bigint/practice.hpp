#ifndef PRACTICE_HPP
#define PRACTICE_HPP
#include <string>
#include <algorithm>
#include <sstream>
#include <ostream>

class bigint {
	private:
		std::string number;
	
	public:
		bigint();
		bigint(const std::string& number);
		bigint(int i);
		bigint(const bigint& copy);
		bigint& operator=(const bigint& assign);
		~bigint();

		std::string	getNumber() const;
		bigint		operator+(const int i);
		bigint		operator+(const bigint& value);
		bigint&		operator+=(const bigint& value);

		bool operator==(const bigint& value);
		bool operator!=(const bigint& value);
		bool operator<(const bigint& value);
		bool operator<=(bigint& value);
		bool operator>(bigint& value);
		bool operator>=(bigint& value);

		bigint operator<<(const bigint& value);
		bigint operator<<(const int i);
		bigint operator>>(const bigint& value);
		bigint operator>>(int i);

		bigint& operator>>=(const bigint& value);
		bigint& operator>>=(const int i);
		bigint& operator<<=(const bigint& value);
		bigint& operator<<=(const int i);

		bigint& operator++();
		bigint operator++(int);
};

void normalize(std::string& number);
std::ostream& operator<<(std::ostream& o, const bigint& number);


#endif