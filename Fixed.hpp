/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fixed.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: flintlouis <flintlouis@student.codam.nl      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/08 13:52:12 by flintlouis    #+#    #+#                 */
/*   Updated: 2021/01/11 12:30:12 by flintlouis    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
	public:
		Fixed(void);
		Fixed(int const n);
		Fixed(float const f);
		Fixed(Fixed const & src);
		~Fixed();

		Fixed &operator=(Fixed const &rhs);
		Fixed &operator=(int const n);
		Fixed &operator=(float const f);

		Fixed &operator++(void); //pre increment
		Fixed &operator--(void); //pre decrement

		Fixed operator++(int); //post increment
		Fixed operator--(int); //post decrement

		Fixed operator+(Fixed const &rhs);
		Fixed operator-(Fixed const &rhs);
		Fixed operator*(Fixed const &rhs);
		Fixed operator/(Fixed const &rhs);
		
		bool operator>(Fixed const &rhs) const;
		bool operator<(Fixed const &rhs) const;
		bool operator>=(Fixed const &rhs) const;
		bool operator<=(Fixed const &rhs) const;
		bool operator==(Fixed const &rhs) const;
		bool operator!=(Fixed const &rhs) const;

		int getRawBits(void) const;
		void setRawBits(int const raw);
		
		float toFloat(void) const;
		int toInt(void) const;
		
		static Fixed &min(Fixed &a, Fixed &b);
		static Fixed const &min(Fixed const &a, Fixed const &b);
		static Fixed &max(Fixed &a, Fixed &b);
		static Fixed const &max(Fixed const &a, Fixed const &b);

	private:
		int rawBits_;
		static int const precision_ = 8;
};

std::ostream &operator<<(std::ostream &o, Fixed const &i);

#endif
