#ifndef VECT2_HPP
#define VECT2_HPP
#include <iostream>

class vect2 {
	private:
		int x;
		int y;
	
	public:
		vect2();
		vect2(int x, int y);
		vect2(const vect2& copy);
		vect2& operator=(const vect2& assign);
		~vect2();

		int getX() const;
		int getY() const;
		int operator[](const int i) const;
		int& operator[](const int i);
		vect2 operator*(const int i);
		vect2 operator+(const int i);
		vect2 operator*(const vect2& v);
		vect2 operator+(const vect2& v);
		vect2& operator+=(const int i);
		vect2& operator+=(const vect2& v);
		vect2& operator*=(const int i);
		vect2& operator*=(const vect2& v);
		vect2& operator-=(const int i);
		vect2& operator-=(const vect2& v);
		vect2 operator--(int);
		vect2 operator++(int); 
		vect2& operator--();
		vect2& operator++();
		bool operator==(const vect2& v) const;
		bool operator!=(const vect2& v) const;
};

vect2 operator+(const int i, const vect2& v);
vect2 operator*(const int i, const vect2& v);
std::ostream& operator<<(std::ostream& o, const vect2& v);

#endif