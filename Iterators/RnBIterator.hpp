/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RnBIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 01:11:58 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/01/30 01:12:38 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RNBITERATOR_HPP
# define RNBITERATOR_HPP

# include "../Utils/pair.hpp"
# include "iterator.hpp"
# include "../Utils/enableIf.hpp"
# include "../MapRnB/node.hpp"

namespace ft
{
	template<class T, typename Cont>
	struct AVLIterator
	{
		typedef ft::node<typename Cont::value_type>*			node_ptr;
		typedef typename iterator_traits<T>::difference_type	difference_type;
		typedef typename iterator_traits<T>::value_type			value_type;
		typedef typename iterator_traits<T>::pointer			pointer;
		typedef typename iterator_traits<T>::reference			reference;
		typedef typename std::bidirectional_iterator_tag		iterator_category;
		
		node_ptr	_p;
		node_ptr	_pEnd;

		AVLIterator(): _p(nullptr), _pEnd(nullptr) {}
		AVLIterator(node_ptr p, node_ptr pEnd): _p(p), _pEnd(pEnd)
		{
			if (!p)
				_p = _pEnd;
		}
		AVLIterator(const AVLIterator& from): _p(from._p), _pEnd(from._pEnd) {}
		template <class Iter>
		AVLIterator(const AVLIterator<Iter, typename enable_if<
                        !std::is_same<Iter, typename Cont::const_iterator::pointer>::value,
                        Cont>::type>& from): _p(from._p), _pEnd(from._pEnd) {}
		~AVLIterator(){}

		AVLIterator&	operator=(const AVLIterator& from)
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
		AVLIterator&	operator++()
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
		AVLIterator	operator++(int)
		{
			AVLIterator	tmp = *this;
			++(*this);
			return (tmp);
		}
		AVLIterator&	operator--()
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
		AVLIterator	operator--(int)
		{
			AVLIterator	tmp = *this;
			--(*this);
			return (tmp);
		}
	};
	
	template<class T, class Cont>
	bool	operator==(const AVLIterator<T,Cont>& lhs, const AVLIterator<T,Cont>& rhs)
	{
		return(lhs._p == rhs._p);
	}
	template<class T, class T2, class Cont>
	bool	operator==(const AVLIterator<T,Cont>&lhs, const AVLIterator<T2,Cont>& rhs)
	{
		return(lhs._p == rhs._p);
	}
	template<class T, class Cont>
	bool	operator!=(const AVLIterator<T,Cont>& lhs, const AVLIterator<T,Cont>& rhs)
	{
		return(lhs._p != rhs._p);
	}
	template<class T, class T2, class Cont>
	bool	operator!=(const AVLIterator<T,Cont>& lhs, const AVLIterator<T2,Cont>&rhs)
	{
		return(lhs._p != rhs._p);
	}
	
}

#endif