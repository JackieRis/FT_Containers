/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 05:01:58 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/02/11 23:05:14 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "../Vector/vector.hpp"

namespace ft
{
	template<class T, class Containers = ft::vector<T> >
	class stack
	{
		public:
	typedef Containers							container_type;
	typedef typename container_type::value_type	value_type;
	typedef typename container_type::size_type	size_type;
	
		protected:
	container_type	c;
		
		public:
	explicit stack(const Containers &cont = Containers()):c(cont){}
	stack(const stack& from):c(from.c){}
	~stack() {}

	stack& operator=(const stack& from)
	{
		if (*this == from)
			return (*this);
		c = from.c;
		return (*this);
	}

	value_type&	top(){return (c.back());}
	const value_type& top()const{return (c.back());}
	void	push(const value_type& val){c.push_back(val);}
	void	pop(){c.pop_back();}
	bool	empty()const{return (c.empty());}
	size_type	size(){return (c.size());}

	template<class Type, class C>
	friend bool	operator==(const stack<Type, C> &l, const stack<Type, C> &r);
	template<class Type, class C>
	friend bool	operator<(const stack<Type, C> &l, const stack<Type, C> &r);
	};
	
	template<class T, class C>
	bool	operator==(const stack<T, C> &l, const stack<T, C> &r)
	{
		return (l.c == r.c);
	}
	template<class T, class C>
	bool	operator!=(const stack<T, C> &l, const stack<T, C> &r)
	{
		return (!(l == r));
	}
	template<class T, class C>
	bool	operator<(const stack<T, C> &l, const stack<T, C> &r)
	{
		return (l.c < r.c);
	}
	template<class T, class C>
	bool	operator<=(const stack<T, C> &l, const stack<T, C> &r)
	{
		return (!(r < l));
	}
	template<class T, class C>
	bool	operator>(const stack<T, C> &l, const stack<T, C> &r)
	{
		return (r < l);
	}
	template<class T, class C>
	bool	operator>=(const stack<T, C> &l, const stack<T, C> &r)
	{
		return (!(l < r));
	}
}

#endif