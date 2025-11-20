#include "practice.hpp"

bigint::bigint() {
	this->number = "0";
}
bigint::bigint(const std::string& number) {
	std::string value = number;
	if (value.empty())
		this->number = "0";
	else {
		normalize(value);
		this->number = value;
	}
}
bigint::bigint(int i) {
	std::ostringstream oss;
	oss << i;
	this->number = oss.str();
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
std::string bigint::getNumber() const {
	return this->number;
}

bigint bigint::operator+(const bigint& value) {
	std::string a = this->number;
	std::string b = value.number;
	std::string result = "";
	int carry = 0;
	int i = 0;

	std::reverse(a.begin(), a.end());
	std::reverse(b.begin(), b.end());
	while (i < a.size() || i < b.size() || carry) {
		int first = 0;
		if (i < a.size())
			first = a[i] - '0';
		int second = 0;
		if (i < b.size())
			second = b[i] - '0';
		int sum = first + second + carry;
		result = (char)('0' + sum % 10) + result;
		carry = sum / 10;
		i++;
	}
	return bigint(result);
}
bigint bigint::operator+(const int i) {
	return *this + bigint(i);
}
bigint& bigint::operator+=(const bigint& value) {
	*this = *this + value;
	return *this;
}
bool bigint::operator==(const bigint& value) {
	return (this->number == value.number);
}
bool bigint::operator!=(const bigint& value) {
	return (this->number != value.number);
}
bool bigint::operator<(const bigint& value) {
	if (this->number.size() != value.number.size())
		return (this->number.size() < value.number.size());
	return (this->number < value.number);
}
bool bigint::operator<=(bigint& value) {
	return (*this < value || *this == value);
}
bool bigint::operator>(bigint& value) {
	return (value < *this);
}
bool bigint::operator>=(bigint& value) {
	return (*this > value || *this == value);
}
bigint bigint::operator<<(const int i) {
	bigint result;
	std::string a = this->number;
	if (a == "0")
		return result;
	a.append(i, '0');
	result.number = a;
	return result;
}
bigint bigint::operator<<(const bigint& value) {
	int i = std::atoi(value.number.c_str());
	return (*this << i);
}
bigint bigint::operator>>(const int i) {
	bigint result(*this);
	int len = this->number.size() - i;
	if (len <= 0)
		result.number = "0";
	else
		result.number.erase(len);
	return result;
}
bigint bigint::operator>>(const bigint& value) {
	int i = std::atoi(value.number.c_str());
	return (*this >> i);
}
bigint& bigint::operator>>=(const int i) {
	*this = *this >> i;
	return *this;
}
bigint& bigint::operator>>=(const bigint& value) {
	int i = std::atoi(value.number.c_str());
	*this >>= i;
	return *this;
}
bigint& bigint::operator<<=(const int i) {
	*this = *this << i;
	return *this;
}
bigint& bigint::operator<<=(const bigint& value) {
	int i = std::atoi(value.number.c_str());
	*this <<= i;
	return *this;
}
bigint& bigint::operator++() {
	*this += 1;
	return *this;
}
bigint bigint::operator++(int) {
	bigint result(*this);
	*this += 1;
	return result;
}

void normalize(std::string& number) {
	size_t pos = number.find_first_not_of('0');
	if (pos == std::string::npos)
		number = "0";
	else
		number.erase(0, pos);
}
std::ostream& operator<<(std::ostream& o, const bigint& number) {
	std::string value = number.getNumber();
	normalize(value);
	o << value << std::endl;
	return o;
}