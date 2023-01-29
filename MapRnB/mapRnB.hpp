/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapRnB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:31:59 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/01/30 00:37:04 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPRNB_HPP
# define MAPRNB_HPP

# include <memory>
# include "../utils/pair.hpp"
# include "../Iterators/reverse_iterator.hpp"
# include "../utils/equal.hpp"
# include "../utils/lexicographical_compare.hpp"
# include "node.hpp"


namespace ft 
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class mapRnB
	{
		public:
	typedef Key									key_type;
	typedef T									mapped_type;
	typedef ft::pair<key_type, mapped_type>		value_type;
	typedef Compare								key_compare;
	typedef Alloc								allocator_type;
	typedef node<value_type>					node_type;
	
class value_compare: public: std::binary_function<value_type, value_type, bool>
{
private:
	friend class map<Key, T, Compare, Alloc>;
protected:
	key_compare comp;
	value_compare(key_compare c): comp(c) {}
public:
	bool	operator()(const value_type& x, const value_type& y) const
	{return (comp(x.first, y.first));}
};
	
		protected:
	Alloc   a;

	
	};
}

#endif