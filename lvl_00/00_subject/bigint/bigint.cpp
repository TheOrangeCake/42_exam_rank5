/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoannguy <hoannguy@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 15:20:21 by hoannguy          #+#    #+#             */
/*   Updated: 2025/09/29 15:20:21 by hoannguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

bigint::bigint() {
	this->number = "0";
}
bigint::bigint(const std::string& num) {
	if (num.empty())
		this->number = "0";
	else {
		this->number = num;
	}
}
bigint::bigint(int i) {
	std::ostringstream s;
	s << i;
	this->number = s.str();
}
bigint::bigint(const bigint& copy) {
	this->number = copy.number;
}
bigint& bigint::operator=(const bigint& assign) {
	this->number = assign.number;
	return *this;
}
bigint::~bigint() {

}
std::string bigint::getNum() const {
	return this->number;
}

bigint bigint::operator+(const bigint& num) const {
	std::string a = this->number;
	std::string b = num.number;
	std::string result = "";
	int			carry = 0;
	int			i = 0;

	// read from the end
	std::reverse(a.begin(), a.end());
	std::reverse(b.begin(), b.end());
	// loop each character
	while (i < (int)a.size() || i < (int)b.size() || carry) {
		// get first number
		int first = 0;
		if (i < (int)a.size())
			first = a[i] - '0';
		// get second number
		int second = 0;
		if (i < (int)b.size())
			second = b[i] - '0';
		// calculate
		int sum = carry + first + second;
		result = char('0' + sum % 10) + result;
		carry = sum / 10;
		i++;
	}
	return bigint(result);
}
bigint& bigint::operator+=(const bigint& num) {
	*this = *this + num;
	return (*this);
}
bool bigint::operator==(const bigint& num) const {
	return (this->number == num.number);
}
bool bigint::operator!=(const bigint& num) const {
	return (this->number != num.number);
}
void normalize(std::string& number) {
	size_t	pos = number.find_first_not_of('0');
	if (pos == std::string::npos)
		number = "0";
	else
		number.erase(0, pos);
}
bool bigint::operator<(const bigint& num) const {
	std::string a = this->number;
	std::string b = num.number;

	normalize(a);
	normalize(b);
	// check if same size
	if (a.size() != b.size())
		return (a.size() < b.size());
	return a < b;
}
bool bigint::operator<=(const bigint& num) const {
	return (*this < num || *this == num);
}
bool bigint::operator>(const bigint& num) const {
	return (num < *this);
}
bool bigint::operator>=(const bigint& num) const {
	return (!(*this < num));
}
bigint bigint::operator<<(const int i) const{
	bigint result(*this);
	result.number.append(i, '0');
	return result;
}
bigint bigint::operator>>(const int i) const {
	bigint result(*this);
	int len = (int)this->number.size() - i;
	if (len <= 0)
		result.number = "0";
	else {
		result.number.erase(len);
	}
	return result;
}
bigint bigint::operator<<(const bigint& num) const {
	int number = std::atoi(num.number.c_str());
	return (*this << number);
}
bigint bigint::operator>>(const bigint& num) const {
	int number = std::atoi(num.number.c_str());
	return (*this >> number);
}

std::ostream& operator<<(std::ostream& o, const bigint& number) {
	std::string value = number.getNum();
	normalize(value);
	o << value << std::endl;
	return o;
}