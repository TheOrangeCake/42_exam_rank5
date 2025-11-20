#include "vect2.hpp"

vect2::vect2() {
	this->x = 0;
	this->y = 0;
}
vect2::vect2(int x, int y) {
	this->x = x;
	this->y = y;
}
vect2::vect2(const vect2& assign) {
	this->x = assign.x;
	this->y = assign.y;
}
vect2& vect2::operator=(const vect2& copy) {
	this->x = copy.x;
	this->y = copy.y;
	return *this;
}
vect2::~vect2() {

}
int vect2::getX() const {
	return this->x;
}
int vect2::getY() const {
	return this->y;
}
int vect2::operator[](const int i) const {
	if (i == 0)
		return this->x;
	else
		return this->y;
}
int& vect2::operator[](const int i) {
	if (i == 0)
		return this->x;
	else
		return this->y;
}
vect2 vect2::operator*(const int i) {
	vect2 v(this->x * i, this->y * i);
	return v;
}
vect2 vect2::operator+(const int i) {
	vect2 v(this->x + i, this->y + i);
	return v;
}
vect2 vect2::operator*(const vect2& v) {
	vect2 ve(this->x * v.x, this->y * v.y);
	return ve;
}
vect2 vect2::operator+(const vect2& v) {
	vect2 ve(this->x + v.x, this->y + v.y);
	return ve;
}
vect2& vect2::operator+=(const int i) {
	this->x += i;
	this->y += i;
	return *this;
}
vect2& vect2::operator+=(const vect2& v) {
	this->x += v.x;
	this->y += v.y;
	return *this;
}
vect2& vect2::operator*=(const int i) {
	this->x *= i;
	this->y *= i;
	return *this;
}
vect2& vect2::operator*=(const vect2& v) {
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}
vect2& vect2::operator-=(const int i) {
	this->x -= i;
	this->y -= i;
	return *this;
}
vect2& vect2::operator-=(const vect2& v) {
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}
vect2 vect2::operator--(int) {
	vect2 v(this->x, this->y);
	this->x--;
	this->y--;
	return v;
}
vect2 vect2::operator++(int) {
	vect2 v(this->x, this->y);
	this->x++;
	this->y++;
	return v;
}
vect2& vect2::operator--() {
	this->x--;
	this->y--;
	return *this;
}
vect2& vect2::operator++() {
	this->x++;
	this->y++;
	return *this;
}
bool vect2::operator==(const vect2& v) const {
	return (this->x == v.x && this->y == v.y);
}
bool vect2::operator!=(const vect2& v) const {
	return (this->x != v.x || this->y != v.y);
}
vect2 operator*(const int i, const vect2& v) {
	vect2 vector(i * v.getX(), i * v.getY());
	return vector;
}
vect2 operator+(const int i, const vect2& v) {
	vect2 vector(i + v.getX(), i + v.getY());
	return vector;
}
std::ostream& operator<<(std::ostream& o, const vect2& v) {
	o << "{" << v[0] << ", " << v[1] << "}" << std::endl;
	return o;
}