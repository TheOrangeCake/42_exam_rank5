#ifndef BIGINT_HPP
#define BIGINT_HPP
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

class bigint {
	private:
		std::string number;
	
	public:
		bigint();
		bigint(const std::string& num);
		bigint(int i);
		bigint(const bigint& copy);
		bigint& operator=(const bigint& assign);
		~bigint();

		std::string getNum() const;
		bigint operator+(const bigint& num) const;
		bigint& operator+=(const bigint& num);

		bool operator==(const bigint& num) const;
		bool operator!=(const bigint& num) const;
		bool operator<(const bigint& num) const;
		bool operator<=(const bigint& num) const;
		bool operator>(const bigint& num) const;
		bool operator>=(const bigint& num) const;

		bigint operator<<(const bigint& num) const;
		bigint operator>>(const bigint& num) const;
		bigint operator<<(const int i) const;
		bigint operator>>(const int i) const;
};

void normalize(std::string& number);
std::ostream& operator<<(std::ostream& o, const bigint& number);

#endif