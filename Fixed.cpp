/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fixed.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: flintlouis <flintlouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/08 13:52:15 by flintlouis    #+#    #+#                 */
/*   Updated: 2021/01/18 19:40:38 by flintlouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cmath>
#include "Fixed.hpp"

/* Constructors */

Fixed::Fixed(void) : rawBits_(0) {}

Fixed::Fixed(int const n)    
{
	this->rawBits_ = n << this->precision_;	// n * 256 (in base 10 it would be like n * 1e8, example: $10.24 * 1e8 = 1024000000.0)
}

Fixed::Fixed(float const f)
{
	this->rawBits_ = roundf(f * (1 << this->precision_)); // Floats don't work with bitshifts
}

Fixed::Fixed(Fixed const & src)
{
	*this = src;
}

Fixed::~Fixed() {}

/* Operators */

Fixed &Fixed::operator=(Fixed const &rhs)
{
	this->rawBits_ = rhs.getRawBits();
	return *this;
}

Fixed &Fixed::operator=(int const n)
{
	this->rawBits_ = n << this->precision_;
	return *this;
}

Fixed &Fixed::operator=(float const f)
{
	this->rawBits_ = roundf(f * (1 << this->precision_));
	return *this;
}

Fixed &Fixed::operator++(void)
{
	this->rawBits_ += 1;
	return *this;
}

Fixed Fixed::operator++(int)
{
	Fixed tmp(*this);
	++(*this);
	return tmp;
}

Fixed &Fixed::operator--(void)
{
	this->rawBits_ -= 1;
	return *this;
}

Fixed Fixed::operator--(int)
{
	Fixed tmp(*this);
	--(*this);
	return tmp;
}

Fixed Fixed::operator+(Fixed const &rhs)
{
	Fixed tmp;
	tmp.setRawBits(this->rawBits_ + rhs.getRawBits());
	return tmp;
}

Fixed Fixed::operator-(Fixed const &rhs)
{
	Fixed tmp;
	tmp.setRawBits(this->rawBits_ - rhs.getRawBits());
	return tmp;
}

Fixed Fixed::operator*(Fixed const &rhs)
{
	Fixed tmp;
	tmp.setRawBits((this->rawBits_ * rhs.getRawBits()) >> this->precision_); // Divide by 256 because rawbits are already multiplied by 256
	return tmp;
}

Fixed Fixed::operator/(Fixed const &rhs)
{
	Fixed tmp;
	tmp.setRawBits((this->rawBits_ / rhs.getRawBits()) << this->precision_); // Times by 256 because rawbits have to be multiplied by 256
	return tmp;
}

bool Fixed::operator>(Fixed const &rhs) const
{
	return (this->rawBits_ > rhs.getRawBits());
}

bool Fixed::operator<(Fixed const &rhs) const
{
	return (this->rawBits_ < rhs.getRawBits());
}

bool Fixed::operator>=(Fixed const &rhs) const
{
	return (this->rawBits_ >= rhs.getRawBits());
}

bool Fixed::operator<=(Fixed const &rhs) const
{
	return (this->rawBits_ <= rhs.getRawBits());
}

bool Fixed::operator==(Fixed const &rhs) const
{
	return (this->rawBits_ == rhs.getRawBits());
}

bool Fixed::operator!=(Fixed const &rhs) const
{
	return (this->rawBits_ != rhs.getRawBits());
}

/* Member Methods */

int Fixed::getRawBits(void) const
{
	return this->rawBits_;
}

void Fixed::setRawBits(int const raw)
{
	this->rawBits_ = raw;
}

float Fixed::toFloat(void) const
{
	return (float)this->rawBits_ / (float)(1 << this->precision_);
}

int Fixed::toInt(void) const
{
	return (this->rawBits_ + (1 << (this->precision_ - 1))) >> this->precision_; // Add 0.5 to get the correrct rounding when going to int
}

std::ostream &operator<<(std::ostream &o, Fixed const &i)
{
	o << i.toFloat();
	return o;
}

Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	return a < b ? a : b;
}

Fixed const &Fixed::min(Fixed const &a, Fixed const &b)
{
	return a < b ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	return a > b ? a : b;
}

Fixed const &Fixed::max(Fixed const &a, Fixed const &b)
{
	return a > b ? a : b;
}
