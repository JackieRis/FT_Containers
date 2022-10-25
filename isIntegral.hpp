/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isIntegral.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:07:29 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/10/17 19:19:02 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISINTEGRAL_HPP
# define ISINTEGRAL_HPP

# include <type_traits>
# ifndef FT_IS_INTEGRAL
# define FT_IS_INTEGRAL(type) template <> struct is_integral<type> : public std::true_type {};
#endif

namespace ft 
{

	template <class T>
	struct is_integral : public std::false_type {};

	FT_IS_INTEGRAL(bool);
	FT_IS_INTEGRAL(char);
	FT_IS_INTEGRAL(char16_t);
	FT_IS_INTEGRAL(char32_t);
	FT_IS_INTEGRAL(wchar_t);
	FT_IS_INTEGRAL(signed char);
	FT_IS_INTEGRAL(short int);
	FT_IS_INTEGRAL(int);
	FT_IS_INTEGRAL(long int);
	FT_IS_INTEGRAL(long long int);
	FT_IS_INTEGRAL(unsigned char);
	FT_IS_INTEGRAL(unsigned short int);
	FT_IS_INTEGRAL(unsigned int);
	FT_IS_INTEGRAL(unsigned long int);
	FT_IS_INTEGRAL(unsigned long long int);

}

# undef FT_IS_INTEGRAL

#endif