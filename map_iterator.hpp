/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:26:15 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/10/20 04:16:11 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "iterator.hpp"
# include "map.hpp"

namespace ft
{
	template<class T, typename Cont>
	struct map_iterator
	{
		typedef ft::node<typename Cont::value_type>*			node_ptr;
		typedef typename iterator_traits<T>::difference_type	difference_type;
		typedef typename iterator_traits<T>::value_type			value_type;
		typedef typename iterator_traits<T>::pointer			pointer;
		typedef typename iterator_traits<T>::reference			reference;
		typedef typename std::bidirectional_iterator_tag		iterator_category;
		
		node_ptr	_p;

		map_iterator();
		map_iterator(node p): _p(p){}
		map_iterator(const map_iterator& from): _p(from._p);
		~iterator(){}

		map_iterator&	operator=(const map_iterator& from)
		{
			if (*this == from)
				return (*this);
			_p = from._p;
			return (*this);
		}
		
		//fun part, operators for map
		map_iterator&	operator++()
		{
			node_ptr	tmp = _p;
			node_ptr	current = _p;
			if (_p->right)
			{
				tmp = _p->right;
				while (tmp->left)
					tmp = tmp->left;
				_p = tmp;
			}
			else
			{
				tmp = _p->parent;
				while (tmp && tmp->right == current)
				{
					current = tmp;
					tmp = tmp->parent;
				}
				if (!tmp)
					;//end
				else
					_p = tmp;
			}
			return (*this);
		}
		map_iterator	operator++(int)
		{
			map_iterator	tmp = *this;
			++(*this);
			return (tmp);
		}
		map_iterator&	operator--()
		{
			node_ptr	tmp;
			node_ptr	current;
			
			if (_p->left)
			{
				tmp = _p->left;
				while (tmp->right)
					tmp = tmp->right;
				_p = tmp;
			}
			else
			{
				tmp = _p->parent;
				while (tmp && tmp->left == current)
				{
					current = tmp;
					tmp = tmp->parent;
				}
				if (!tmp)
					;//begin
				else
					_p = tmp;
			}
			return (*this);
		}
		map_iterator	operator--(int)
		{
			map_iterator	tmp = *this;
			--(*this);
			return (tmp);
		}
	};
	
	
}

#endif