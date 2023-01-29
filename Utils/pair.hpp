/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:15:44 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/10/27 06:15:25 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template<class T1, class T2>
	struct	pair
	{
		typedef T1	first_type;
		first_type	first;
		typedef T2	second_type;
		second_type	second;

		//constructors && destructors
		pair(): first(first_type()), second(second_type()){}
		template <class U, class V>
		pair(const pair<U,V>& from): first(from.first), second(from.second){}
		pair(const first_type& f, const second_type& s): first(f), second(s){}
		~pair(){};
		
		//operators
		pair& operator=(const pair& from)
		{
			if (this == &from)
				return (*this);
			first = from.first;
			second = from.second;
			return (*this);
		}

		template <class TA, class TB>
		friend bool	operator==(const pair<TA,TB>& lhs, const pair<TA,TB>& rhs);
		template <class TA, class TB>
		friend bool	operator<(const pair<TA,TB>& lhs, const pair<TA,TB>& rhs);
	};
	//********************************************************************************************************
	//make_pair
	template<class T1, class T2>
	pair<T1,T2>	make_pair(T1 x, T2 y)
	{
		return (pair<T1,T2>(x,y));
	}

	template<class T1, class T2>
	bool	operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){return (lhs.first == rhs.first && lhs.second == rhs.second);}
	
	template<class T1, class T2>
	bool	operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){return (!(lhs == rhs));}

	template<class T1, class T2>
	bool	operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){return ((lhs.first < rhs.first) || (!(lhs.first < rhs.first) && lhs.second < rhs.second));}

	template<class T1, class T2>
	bool	operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){return (!(rhs < lhs));}

	template<class T1, class T2>
	bool	operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){return (rhs < lhs);}

	template<class T1, class T2>
	bool	operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){return (!(lhs < rhs));}
	
}

#endif