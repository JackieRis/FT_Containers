/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:51:37 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/10/25 07:34:51 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPICAL_COMPARE_HPP
# define LEXICOGRAPICAL_COMPARE_HPP

namespace ft
{
	template<class inputIterator1, class inputIterator2>
	bool	lexicographical_compare(inputIterator1 first1, inputIterator1 last1,
		inputIterator2 first2, inputIterator2 last2)
	{
		for (;(first1 != last1) && (first2 != last2);)
		{
			if (*first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
			++first1;
			++first2;
		}
		return ((first1 == last1) && (first2 != last2));
	}
	
	template<class inputIterator1, class inputIterator2, class compare>
	bool	lexicographical_compare(inputIterator1 first1, inputIterator1 last1,
		inputIterator2 first2, inputIterator2 last2, compare comp)
	{
		for (;(first1 != last1) && (first2 != last2);)
		{
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
			++first1;
			++first2;
		}
		return ((first1 == last1) && (first2 != last2));
	}
}

#endif