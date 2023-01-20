/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:26:15 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/10/27 04:51:29 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "pair.hpp"
# include "iterator.hpp"
# include "enableIf.hpp"

namespace ft
{
	template<class pair>
	struct node
	{
		typedef	node<pair>*	node_ptr;
	
		node_ptr	left;
		node_ptr	right;
		node_ptr	parent;
		pair		data;
		int			depth;
	
		//default constructor, set all value to 0 and depth to 1
		node(): left(nullptr), right(nullptr), parent(nullptr), data(), depth(1){}
		node(const pair& from): left(nullptr), right(nullptr), parent(nullptr), data(from), depth(1){}
		node(const node& from): left(from.left), right(from.right), parent(from.parent), data(from.data), depth(from.depth){}
	};
	
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
		node_ptr	_pEnd;

		map_iterator(): _p(nullptr), _pEnd(nullptr) {}
		map_iterator(node_ptr p, node_ptr pEnd): _p(p), _pEnd(pEnd)
		{
			if (!p)
				_p = _pEnd;
		}
		map_iterator(const map_iterator& from): _p(from._p), _pEnd(from._pEnd) {}
		template <class Iter>
		map_iterator(const map_iterator<Iter, typename enable_if<
                        !std::is_same<Iter, typename Cont::const_iterator::pointer>::value,
                        Cont>::type>& from): _p(from._p), _pEnd(from._pEnd) {}
		~map_iterator(){}

		map_iterator&	operator=(const map_iterator& from)
		{
			if (this == &from)
				return (*this);
			_p = from._p;
			_pEnd = from._pEnd;
			return (*this);
		}

		reference	operator*() const
		{
			return (_p->data);
		}
		
		pointer	operator->() const
		{
			return (&_p->data);
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
					_p = _pEnd;//end
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
			node_ptr	tmp = _p;
			node_ptr	current = tmp;

			
			if (_p == _pEnd)
			{
				_p = _pEnd->parent;
				return (*this);
			}

			if (tmp->left)
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
					;//_p = _p; //begin fix ?
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
	
	template<class T, class Cont>
	bool	operator==(const map_iterator<T,Cont>& lhs, const map_iterator<T,Cont>& rhs)
	{
		return(lhs._p == rhs._p);
	}
	template<class T, class T2, class Cont>
	bool	operator==(const map_iterator<T,Cont>&lhs, const map_iterator<T2,Cont>& rhs)
	{
		return(lhs._p == rhs._p);
	}
	template<class T, class Cont>
	bool	operator!=(const map_iterator<T,Cont>& lhs, const map_iterator<T,Cont>& rhs)
	{
		return(lhs._p != rhs._p);
	}
	template<class T, class T2, class Cont>
	bool	operator!=(const map_iterator<T,Cont>& lhs, const map_iterator<T2,Cont>&rhs)
	{
		return(lhs._p != rhs._p);
	}
	
}

#endif