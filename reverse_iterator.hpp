/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 00:57:26 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/10/25 06:46:21 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP


# include "iterator.hpp"

namespace ft
{
	template <class Iter>
	class reverse_iterator
	{
			public:
		typedef Iter													iterator_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;

			protected:
		iterator_type	_current;
		
			public:

		reverse_iterator() {}
		
		reverse_iterator(iterator_type current): _current(current){}
		
		template<class U>
		reverse_iterator(const reverse_iterator<U>& from): _current(from.base()){}
		~reverse_iterator(){}
		
		reference	operator[](difference_type n) const
		{
			return (*(*this + n));
		}

		template<class U>
		reverse_iterator&	operator=(const reverse_iterator<U> &from)
		{
			_current = from.base();
			return (*this);
		}

		iterator_type	base()const
		{
			return (_current);
		}

		reference	operator*()
		{
			iterator_type tmp = _current;
			return (*--tmp);
		}
		pointer	operator->()
		{
			reference ref = operator*();
			return (&ref);
		}
		//**************************************************************************************
		//mathematik operators but reversed
		reverse_iterator&	operator++()
		{
			_current--;
			return (*this);
		}
		reverse_iterator	operator++(int)
		{
			reverse_iterator	tmp(*this);
			--_current;
			return (tmp);
		}
		reverse_iterator&	operator--()
		{
			_current++;
			return (*this);
		}
		reverse_iterator	operator--(int)
		{
			reverse_iterator	tmp(*this);
			++_current;
			return (tmp);
		}

		reverse_iterator	operator+(difference_type n)const
		{
			return (reverse_iterator(_current - n));
		}
		reverse_iterator	operator+=(difference_type n)
		{
			_current -= n;
			return (*this);
		}
		reverse_iterator	operator-(difference_type n)const
		{
			return (reverse_iterator(_current + n));
		}
		reverse_iterator	operator-=(difference_type n)
		{
			_current += n;
			return (*this);
		}
		
	};

		template<class Iter>
		reverse_iterator<Iter>	operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rit)
		{
			return (rit + n);
		}
		template<class Iter>
		typename reverse_iterator<Iter>::difference_type
		operator-(const reverse_iterator<Iter>& rit, const reverse_iterator<Iter>& rit2)
		{
			return (rit2.base() - rit.base());
		}
		template<class Iter, class Iter2>
		typename reverse_iterator<Iter>::difference_type
		operator-(const reverse_iterator<Iter>& rit, const reverse_iterator<Iter2>& rit2)
		{
			return (rit2.base() - rit.base());
		}

		//comparison operator
		template<class Iter>
		bool	operator==(const reverse_iterator<Iter>& l,const reverse_iterator<Iter>& r)
		{
			return (l.base() == r.base());
		}
		template<class Iter, class Iter2>
		bool	operator==(const reverse_iterator<Iter>& l,const reverse_iterator<Iter2>& r)
		{
			return (l.base() == r.base());
		}
		template<class Iter>
		bool	operator!=(const reverse_iterator<Iter>& l,const reverse_iterator<Iter>& r)
		{
			return (l.base() != r.base());
		}
		template<class Iter, class Iter2>
		bool	operator!=(const reverse_iterator<Iter>& l,const reverse_iterator<Iter2>& r)
		{
			return (l.base() != r.base());
		}
		template<class Iter>
		bool	operator<(const reverse_iterator<Iter>& l, const reverse_iterator<Iter>& r)
		{
			return (l.base() > r.base());
		}
		template<class Iter, class Iter2>
		bool	operator<(const reverse_iterator<Iter>& l, const reverse_iterator<Iter2>& r)
		{
			return (l.base() > r.base());
		}
		template<class Iter>
		bool	operator<=(const reverse_iterator<Iter>& l, const reverse_iterator<Iter>& r)
		{
			return (l.base() >= r.base());
		}
		template<class Iter, class Iter2>
		bool	operator<=(const reverse_iterator<Iter>& l, const reverse_iterator<Iter2>& r)
		{
			return (l.base() >= r.base());
		}
		template<class Iter>
		bool	operator>(const reverse_iterator<Iter>& l, const reverse_iterator<Iter>& r)
		{
			return (l.base() < r.base());
		}
		template<class Iter, class Iter2>
		bool	operator>(const reverse_iterator<Iter>& l, const reverse_iterator<Iter2>& r)
		{
			return (l.base() < r.base());
		}
		template<class Iter>
		bool	operator>=(const reverse_iterator<Iter>& l, const reverse_iterator<Iter>& r)
		{
			return (l.base() <= r.base());
		}
		template<class Iter, class Iter2>
		bool	operator>=(const reverse_iterator<Iter>& l, const reverse_iterator<Iter2>& r)
		{
			return (l.base() <= r.base());
		}
}


#endif