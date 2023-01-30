/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapRnB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:31:59 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/01/30 03:27:13 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPRNB_HPP
# define MAPRNB_HPP

# include <memory>
# include "../Iterators/reverse_iterator.hpp"
# include "../Iterators/RnBIterator.hpp"
# include "../Utils/pair.hpp"
# include "../Utils/equal.hpp"
# include "../Utils/lexicographical_compare.hpp"
# include "node.hpp"


namespace ft 
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class mapRnB
	{
	typedef typename ft::node<ft::pair<Key,T> >::node_ptr node_ptr;

		public:
	typedef Key									key_type;
	typedef T									mapped_type;
	typedef ft::pair<key_type, mapped_type>		value_type;
	typedef Compare								key_compare;
	typedef Alloc								allocator_type;
	typedef node<value_type>					node_type;
	
	class value_compare: public std::binary_function<value_type, value_type, bool>
	{
	private:
		friend class mapRnB<Key, T, Compare, Alloc>;
		
	protected:
		key_compare comp;
		value_compare(key_compare c): comp(c) {}
		
	public:
		bool	operator()(const value_type& x, const value_type& y) const
		{return (comp(x.first, y.first));}
	};
	
	private:
		typedef typename Alloc::template rebind<value_type>::other	pair_alloc;
		typedef typename Alloc::template rebind<ft::node<ft::pair<Key,T> > >::other node_alloc;
		typedef ft::pair<const key_type, mapped_type>	iter_value_type;
	
	public:
		typedef typename pair_alloc::pointer				pointer;
		typedef typename pair_alloc::const_pointer			const_pointer;
		typedef typename pair_alloc::reference				reference;
		typedef typename pair_alloc::const_reference		const_reference;
		typedef typename pair_alloc::difference_type		difference_type;
		typedef typename pair_alloc::size_type				size_type;
		typedef ft::map_iterator<value_type *, map>			iterator;
		typedef ft::map_iterator<const value_type *, map>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	protected:
		Alloc			a;
		node_alloc		na;
		value_compare	vc;
		key_compare		kc;
		node_ptr		base;
		node_ptr		endnode;
		size_t			node_count;
		
	private:

		int	get_depth(node_ptr n)
		{
			if (n)
				return (n->depth);
			return (0);
		}
		void	left_rotate(node_ptr n)
		{
			node_ptr	y = n->right;
			n->right = y->left;
			
		}
		void	right_rotate(node_ptr n)
		{}
	};
}

#endif