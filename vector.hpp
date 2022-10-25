/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:17:35 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/10/25 07:23:46 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include <limits.h>
# include <stdexcept>
# include "iterator.hpp"
# include "isIntegral.hpp"
# include "enableIf.hpp"
# include "equal.hpp"
# include "lexicographical_compare.hpp"
# include "reverse_iterator.hpp"

namespace   ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
	public:
		typedef	Alloc	allocator_type;
		typedef ft::iterator<T*, vector>	iterator;
		typedef ft::iterator<const T*, vector>	const_iterator;
		typedef ft::reverse_iterator<iterator>	reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef typename Alloc::size_type	size_type;
		typedef typename Alloc::value_type	value_type;
		typedef typename Alloc::reference	reference;
		typedef typename Alloc::const_reference	const_reference;
    private:
		Alloc	a;
        T		*_array;
        size_t	_cap;
		size_t	_last;
	
		void	newalloc(size_t n)
		{
			T	*tmp =  a.allocate(n);
			size_t		i = 0;

			for (;i < _last; i++)
				a.construct(&tmp[i], _array[i]);
			for (i = 0;i < _last; i++)
				a.destroy(&_array[i]);
			
			a.deallocate(_array, _cap);
			_array = tmp;
			_cap = n;
		}
		void	moveArray(iterator position)
		{
			iterator	it = end();
			for (; it > position; it--)
				*it = *(it - 1);
			_last += 1;
		}
		void	moveArray(iterator position, size_t n)
		{
			iterator	it = end() + (n - 1);
			
			for (; it > position; it--)
				*it = *(it - n);
			_last += n;
		}
		void	revMoveArray(iterator position)
		{
			iterator	it = position;
			for (; it < end() - 1; ++it)
				*it = *(it + 1);
			_last -= 1;
		}
		void	revMoveArray(iterator position, size_t n)
		{
			iterator	it = position;
			
			for (; it < end() - n; ++it)
				*it = *(it + n);
			_last -= n;
		}

    public:
        vector(const allocator_type &alloc = allocator_type()): a(alloc), _array(a.allocate(0)), _cap(0), _last(0)
		{}
        vector(size_t n, const T& val = T(), const allocator_type &alloc = allocator_type()):a(alloc), _array(a.allocate(n)), _cap(n), _last(n)
        {
            for (size_t i = 0; i < n; i++)
        		a.construct(&_array[i], val);
        }
        vector(const vector& from):a(from.a), _array(a.allocate(from._last)), _cap(from._cap), _last(from._last)
		{
			for (size_t i = 0; i < _last; i++)
				_array[i] = from._array[i];
		}
		template<class inputIt>
		vector(typename enable_if<!is_integral<inputIt>::value,inputIt>::type first, inputIt last, const allocator_type& alloc = allocator_type()): a(alloc)
		{
			size_t n = ft::distance(first, last);
			_array = a.allocate(n);
			_cap = n;
			for (; first != last; ++first)
				push_back(*first);
		}
        ~vector()
		{
			for (size_t i = 0;i < _cap; i++)
				a.destroy(&_array[i]);
			
			a.deallocate(_array, _cap);
		}
		

		//push_back to add an element at the end of the array
		void	push_back(const value_type& val)
		{
			if (_last == _cap)
			{
				if (_cap == 0)
					newalloc(2);
				else
					newalloc(_cap * 2);
			}
			_array[_last] = val;
			_last++;
		}
		void	pop_back()
		{
			_last--;
			a.destroy(&_array[_last]);
		}


		//begin and end
		iterator	begin(){return (iterator(_array));}
		const_iterator	begin()const{return (const_iterator(_array));}
		iterator	end(){return (iterator(_array + _last));}
		const_iterator	end()const{return (const_iterator(_array + _last));}

		reverse_iterator	rbegin(){return (reverse_iterator(_array + _last));}
		const_reverse_iterator	rbegin()const{return (const_reverse_iterator(_array + _last));}
		reverse_iterator	rend(){return (reverse_iterator(_array));}
		const_reverse_iterator	rend()const{return (const_reverse_iterator(_array));}
		
		//****************************************************************
		//capacity
		size_t	size()const{return(_last);}
		size_type	max_size()const
		{
			return(a.max_size());
		}
		
		size_type	capacity()const{return(_cap);}
		bool	empty()const{return (_last == 0);}
		//reserve more memory
		void	reserve(size_type n)
		{
			if (n <= _cap)
				return ;
			newalloc(n);
		}
		//resize container and fill it with value_type 
		void	resize(size_type n, value_type val = value_type())
		{
			if (n == _cap)
				return ;
			else if (n > _cap)
			{
				size_t	i = 0;
				newalloc(n);
				for (i = _last; i < _cap; i++)
					a.construct(&_array[i], val);
				_last = i;
			}
			else if (n <= _last)
			{
				for (size_type i = n; i < _last; i++)
					a.destroy(&_array[i]);
				_last = n;
			}
			else
			{
				size_type i = _last;
				for (; i < n; i++)
					a.construct(&_array[i], val);
				_last = i;
			}
		}
		
        vector&  operator=(const vector& from)
        {
            if (this == &from)
                return (*this);
            a = from.a;
			_cap = from._cap;
			_last = from._last;
			_array = a.allocate(_cap);
			for (size_t i = 0; i < _last; i++)
				a.construct(&_array[i], from._array[i]);
			return (*this);
        }
		template<class inputIt>
		void	assign(typename enable_if<!is_integral<inputIt>::value,inputIt>::type first, inputIt last)
		{
			clear();
			size_t dist = ft::distance(first, last);
			if (dist > _cap)
				newalloc(dist);
			for (; first != last; ++first)
			{
				a.construct(&_array[_last],*first);
				_last++;
			}
		}

		void	assign(size_type count, const T& value)
		{
			clear();
			if (count > _cap)
				newalloc(count);
			for (size_t i = 0; i < count; i++)
				push_back(value);
		}
		//**************************************************************************
		//element access
		T&	operator[](size_t n)
		{
			return (_array[n]);
		}
		const T&	operator[](size_t n)const
		{
			return (_array[n]);
		}
		reference	at(size_type n)
		{
			if (n >= _last)
				throw std::out_of_range("not in vector range");
			return (_array[n]);
		}
		const_reference	at(size_type n)const
		{
			if (n >= _last)
				throw std::out_of_range("not in vector range");
			return (_array[n]);
		}
		reference	front(){return (_array[0]);}
		const_reference	front()const {return (_array[0]);}
		reference	back(){return (_array[_last - 1]);}
		const_reference	back()const {return (_array[_last - 1]);}
		
		//*************************************************************************
		//modifiers
		iterator	insert(iterator position, const value_type& val)
		{
			if (position == end())
			{
				push_back(val);
				return (end() - 1);
			}
			size_t tmp = (size_t)(&*position - _array);
			if (_last >= _cap)
				newalloc(_cap * 2);
			iterator	it(_array + tmp);
			moveArray(it);
			*it = val;
			return (it);
		}
		iterator	insert(iterator position, size_type n, const value_type& val)
		{
			size_t tmp = ft::distance(begin(), position);
			if (position == end() - 1)
			{
				if (_cap <= (_last + n - 1))
					newalloc(_cap + n);
				for (size_t i = 0; i < n; i++)
					push_back(val);
				return (end() - n);
			}
			if (_cap < _last + n)
				newalloc(_cap + n);
			iterator	it(begin() + tmp);
			moveArray(it, n);
			for (iterator it2(it); it2 < it + n; ++it2)
				*it2 = val;
			return (it);
		}
		template<class inputIterator>
		void	insert(	iterator position,
						inputIterator first,
						typename enable_if<!is_integral<inputIterator>::value, inputIterator>::type last)
		{
			size_t tmp = ft::distance(begin(), position);
			size_t dist = ft::distance(first, last);
			if (position == end() - 1)
			{
				if (_cap < (_last + dist))
					newalloc(_cap + dist);
				iterator it(begin() + tmp);
				for (; first != last; ++first)
					*it = *first;
				_last += dist;
			}
		}
		iterator	erase(iterator position)
		{
			size_t tmp = ft::distance(begin(), position);
			if (position == end() - 1)
			{
				a.destroy(&_array[_last]);
				_last -= 1;
				return (end());
			}
			a.destroy(&_array[tmp]);
			revMoveArray(position);
			return (position);
		}
		iterator	erase(iterator first, iterator last)
		{
			size_t	tmp = ft::distance(begin(), first);
			size_t	n = ft::distance(first, last);
			
			if (last == end() - 1)
			{
				for (size_t i = tmp; i < _last; i++)
					a.destroy(&_array[i]);
				_last -= n;
				return (end());
			}
			iterator	it(begin() + tmp);
			for (; it < last; ++it)
				a.destroy(&*it);
			it = begin() + tmp;
			revMoveArray(it, n);
			return (it);
		}
		void	swap(vector& x)
		{
			std::swap(_array, x._array);
			std::swap(a, x.a);
			std::swap(_last, x._last);
			std::swap(_cap, x._cap);
		}
		void	clear()
		{
			for (size_t i = 0; i < _last; i++)
				a.destroy(&_array[i]);
			_last = 0;
		}

		//*********************************************************************
		//Allocator
		allocator_type	get_allocator()const {return (Alloc(a));}
    };
		//*********************************************************************
		//operator
		template<class T, class Alloc>
		bool	operator==(const vector<T, Alloc> &l, const vector<T, Alloc> &r)
		{
			if (l.size() != r.size())
				return (false);
			return (ft::equal(l.begin(), l.end(), r.begin()));
		}
		
		template<class T, class Alloc>
		bool	operator<(const vector<T, Alloc> &l, const vector<T, Alloc> &r)
		{
			return (ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end()));
		}
		
		template<class T, class Alloc>
		bool	operator!=(const vector<T, Alloc> &l, const vector<T, Alloc> &r)
		{
			return (!(l == r));
		}

		template<class T, class Alloc>
		bool	operator>(const vector<T, Alloc> &l, const vector<T, Alloc> &r)
		{
			return (r < l);
		}
		
		template<class T, class Alloc>
		bool	operator<=(const vector<T, Alloc> &l, const vector<T, Alloc> &r)
		{
			return (!(r < l));
		}

		template<class T, class Alloc>
		bool	operator>=(const vector<T, Alloc> &l, const vector<T, Alloc> &r)
		{
			return (!(l < r));
		}
}
#endif