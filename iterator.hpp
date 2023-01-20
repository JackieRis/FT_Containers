/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:47:14 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/10/27 01:08:20 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iterator>

namespace ft
{
	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};
	template <class T>
	struct iterator_traits<T*>
	{
		typedef typename std::ptrdiff_t						difference_type;
		typedef  T									value_type;
		typedef  T*									pointer;
		typedef  T&									reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef typename std::ptrdiff_t						difference_type;
		typedef  const T							value_type;
		typedef  const T*							pointer;
		typedef  const T&							reference;
		typedef typename std::random_access_iterator_tag	iterator_category;
	};

	template<class T, class Cont>
	class iterator
	{
		public:

		typedef typename iterator_traits<T>::difference_type	difference_type;
		typedef typename iterator_traits<T>::value_type			value_type;
		typedef typename iterator_traits<T>::pointer			pointer;
		typedef typename iterator_traits<T>::reference			reference;
		typedef typename std::random_access_iterator_tag		iterator_category;
	protected:
		pointer	_pVal;
	public:


		iterator(){}
		iterator(pointer pVal): _pVal(pVal){}
		iterator(const iterator& from){_pVal = from._pVal;}
		template<typename Iter>
		iterator(const iterator<Iter, Cont>& from): _pVal(&*from){}

		~iterator(){}

		//********************************************************************************
		//mathematik operators
		iterator	operator+(difference_type n)const
		{
			return (iterator(this->_pVal + n));
		}
		iterator&	operator+=(difference_type n)
		{
			this->_pVal += n;
			return (*this);
		}
		iterator	operator-(difference_type n)const
		{
			return (iterator(this->_pVal - n));
		}
		iterator&	operator-=(difference_type n)
		{
			this->_pVal -= n;
			return (*this);
		}
		
		//comparison operator
		//friend bool	operator<(const iterator<T,Cont>& lhs, const iterator<T,Cont>& rhs);
		//friend bool	operator==(const iterator<T,Cont>& lhs, const iterator<T,Cont>& rhs);

		//operator ++
		iterator	operator++(int)
		{
			iterator	tmp= *this;
			++(*this);
			return (tmp);
		}
		iterator&	operator++()
		{
			_pVal++;
			return (*this);
		}
		//operator --
		iterator	operator--(int)
		{
			iterator	tmp = *this;
			--(*this);
			return (tmp);
		}
		iterator&	operator--()
		{
			_pVal--;
			return (*this);
		}
		iterator&	operator=(const iterator& from)
		{
			if (*this == from)
				return (*this);
			this->_pVal = from._pVal;
			return (*this);
		}

		reference	operator*()const
		{
			return (*_pVal);
		}
		pointer	operator->()const
		{
			return (_pVal);
		}
		
		reference	operator[](const size_t n)const
		{return (static_cast<reference>(this->_pVal[n]));}
	};
	template<class T, class Cont>
	bool	operator==(const iterator<T,Cont>& lhs, const iterator<T,Cont>& rhs)
	{
		return(&*lhs == &*rhs);
	}
	template<class T, class T2, class Cont>
	bool	operator==(const iterator<T,Cont>&lhs, const iterator<T2,Cont>& rhs)
	{
		return (&*lhs == &*rhs);
	}
	template<class T, class Cont>
	bool	operator!=(const iterator<T,Cont>& lhs, const iterator<T,Cont>& rhs)
	{
		return (!(lhs == rhs));
	}
	template<class T, class T2, class Cont>
	bool	operator!=(const iterator<T,Cont>& lhs, const iterator<T2,Cont>&rhs)
	{
		return (&*lhs != &*rhs);
	}
	template<class T, class Cont>
	bool	operator<(const iterator<T,Cont>& lhs, const iterator<T,Cont>& rhs)
	{
		return (&*lhs < &*rhs);
	}
	template<class T, class T2, class Cont>
	bool	operator<(const iterator<T,Cont>& lhs, const iterator<T2,Cont>& rhs)
	{
		return (&*lhs < &*rhs);
	}
	template<class T, class Cont>
	bool	operator<=(const iterator<T,Cont>& lhs, const iterator<T,Cont>& rhs)
	{
		return (!(rhs < lhs));
	}
	template<class T, class T2, class Cont>
	bool	operator<=(const iterator<T,Cont>& lhs, const iterator<T2,Cont>& rhs)
	{
		return (&*lhs <= &*rhs);
	}
	template<class T, class Cont>
	bool	operator>(const iterator<T,Cont>& lhs, const iterator<T,Cont>& rhs)
	{
		return (rhs < lhs);
	}
	template<class T, class T2, class Cont>
	bool	operator>(const iterator<T,Cont>& lhs, const iterator<T2,Cont>& rhs)
	{
		return (&*lhs > &*rhs);
	}
	template<class T, class Cont>
	bool	operator>=(const iterator<T,Cont>& lhs, const iterator<T,Cont>& rhs)
	{
		return (!(lhs < rhs));
	}
	template<class T, class T2, class Cont>
	bool	operator>=(const iterator<T,Cont>& lhs, const iterator<T2,Cont>& rhs)
	{
		return (&*lhs >= &*rhs);
	}

	template<class Iter, class Cont>
	iterator<Iter, Cont>
	operator+(typename iterator<Iter, Cont>::difference_type n, const iterator<Iter, Cont>& r)
	{
		return (r + n);
	}

	template<class Iter, class Cont>
	typename iterator<Iter, Cont>::difference_type
	operator-(const iterator<Iter, Cont>& l, const iterator<Iter, Cont>& r)
	{
		return (&*l - &*r);
	}
	
	template<class Iter1, class Iter2, class Cont>
	typename iterator<Iter1, Cont>::difference_type
	operator-(const iterator<Iter1, Cont>& l, const iterator<Iter2, Cont>& r)
	{
		return (&*l - &*r);
	}

	template<class inputIterator>
	typename iterator_traits<inputIterator>::difference_type
	distance_ext(inputIterator first, inputIterator last, std::random_access_iterator_tag)
	{
		return (last - first);
	}

	template<class inputIterator>
	typename iterator_traits<inputIterator>::difference_type
	distance_ext(inputIterator first, inputIterator last, std::input_iterator_tag)
	{
		typename inputIterator::difference_type n = 0;

		for (; first != last; first++)
			n++;
		return (n);
	}

	template<class inputIterator>
	typename iterator_traits<inputIterator>::difference_type
	distance(inputIterator first, inputIterator last)
	{
		return (distance_ext(first, last, typename inputIterator::iterator_category()));
	}
}

#endif