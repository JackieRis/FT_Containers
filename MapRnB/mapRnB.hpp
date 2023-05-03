/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapRnB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:31:59 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/05/03 18:31:27 by tnguyen-         ###   ########.fr       */
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
		typedef ft::RnBIterator<value_type *, mapRnB>			iterator;
		typedef ft::RnBIterator<const value_type *, mapRnB>	const_iterator;
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
		template<class pair>
		node_ptr	createSentinel()
		{
			node_ptr	sentinel = a.allocate(1);
			a.construct(sentinel, node<pair>(0,true,BLACK,NULL,NULL,NULL));
		}
		
		node_ptr	get_node()
		{
			return (na.allocate(1));
		}

		node_ptr	create_node(const node_type& x)
		{
			node_ptr	p = get_node();
			
			try
			{
				na.construct(p, x);
			}
			catch(...)
			{
				na.deallocate(p,1);
				throw ;
			}
			return (p);
		}
		
		void	destroy_node(node_ptr x)
		{
			na.destroy(x);
			na.deallocate(x,1);
		}
		
		void	clearMap(node_ptr n)
		{
			if (!n)
				return ;
			clearMap(n->right);
			clearMap(n->left);
			destroy_node(n);
		}
		
		void	left_rotate(node_ptr n)
		{
			node_ptr	y = n->right;
			n->right = y->left;
			if (y->left->isSentinel == false)
				y->left->parent = n;
			y->parent = n->parent;
			if (n->parent == NULL)
				base = y;
			else
			{
				if (n->parent->left == n)
					n->parent->left = y;
				else
					n->parent->right = y;
			}
			y->left = n;
			n->parent = y;
		}
		void	right_rotate(node_ptr n)
		{
			node_ptr	y = n->left;
			n->left = y->right;
			if (y->right->isSentinel == true)
				y->right->parent = n;
			y->parent = n->parent;
			if (n->parent == NULL)
				base = y;
			else
			{
				if (n->parent->right == n)
					n->parent->right = y;
				else
					n->parent->left = y;
			}
			y->right = n;
			n->parent = y;
		}
		

		void	recInsert(node_ptr root, node_ptr n)
		{
			if (root != NULL)
			{
				if (n->data.first < root->data.first)
				{
					if (base->left != NULL)
					{	
						recInsert(base->left, n);
						return ;
					}	
					else
						base->left = n;
				}
				else
				{
					if (base->right != NULL)
					{	
						recInsert(base->right, n);
						return ;
					}
					else
						base->right = n;
				}
			}
			n->parent = base;
			n->left = NULL;
			n->right = NULL;
			n->color = RED;
		}
		
	public:
	

		/*##################################################################################*/
		/*                              Members functions                                   */
		/*##################################################################################*/
		
		explicit mapRnB(const key_compare& comp = key_compare(), const Alloc& alloc = Alloc()): a(alloc), na(alloc), vc(comp), kc(comp), base(nullptr), endnode(create_node(node_type())), node_count(0) {}
		template<class inputIterator>
		mapRnB(inputIterator first, inputIterator last, const key_compare& comp = key_compare(), const Alloc& alloc = Alloc()): a(alloc), na(alloc), vc(comp), kc(comp), base(nullptr), endnode(create_node(node_type())), node_count(0)
		{
			insert(first, last);
		}
		mapRnB(const mapRnB& from): a(from.a), na(from.na), vc(from.vc), kc(from.kc), base(dupNode(from.base)), endnode(create_node(node_type())), node_count(from.node_count)
		{
			updateEnd();
		}
		~mapRnB()
		{
			destroy_node(endnode);
			clearmap(base);
		}
	
		allocator_type	get_allocator() const {return (Alloc(a));}
	
		mapRnB&	operator=(const mapRnB& from)
		{
			if (this == &from)
				return (*this);
			clear();
			a = from.a;
			na = from.na;
			kc = from.kc;
			vc = from.vc;
			if (from.base)
			{
				base = dupNode(from.base);
				node_count = from.node_count;
				updateEnd();
			}
			return (*this);
		}

		/*##################################################################################*/
		/*                                    Modifiers                                     */
		/*##################################################################################*/

		void clear()
		{
			clearMap(base);
			base = nullptr;
			node_count = 0;
		}

		/*##################################################################################*/
		/*                                      lookup                                      */
		/*##################################################################################*/

		size_type	count(const Key& key) const
		{
			return (find(key) != end());
		}

		iterator	find(const key_type& k)
		{
			value_type	f = ft::make_pair(k, mapped_type());	//f is key's pair
			node_ptr	tmp = base;								//tmp is our base
			
			while (tmp)
			{
				if (tmp->data.first == k)
				{
					if (tmp->color == -1)
						return NULL;
					return (iterator(tmp, endnode));
				}
				else if (vc(f, tmp->data))							// if element is on left->side 
					tmp = tmp->left;
				else if (vc(tmp->data, f))						// if element is on right->side
					tmp = tmp->right;
				else											// we found it
					return (iterator(tmp, endnode));
			}
			return (end());										//error 404 not found
		}

		iterator	lower_bound(const Key& key)
		{
			iterator	it = begin();
			iterator	itEnd = end();

			while (it != itEnd)
			{
				if (!kc(it->first, key))
					return (it);
				++it;
			}
		}
		const_iterator	lower_bound(const Key& key) const
		{
			const_iterator	it = begin();
			const_iterator	itEnd = end();

			while (it != itEnd)
			{
				if (!kc(it->first, key))
					return (it);
				++it;
			}
		}

		iterator	upper_bound(const Key& key)
		{
			iterator	it = begin();
			iterator	itEnd = end();

			while (it != itEnd)
			{
				if (kc(key, it->first))
					return (it);
				++it;
			}
			return (it);
		}
		const_iterator	upper_bound(const Key& key) const
		{
			const_iterator	it = begin();
			const_iterator	itEnd = end();

			while (it != itEnd)
			{
				if (kc(key, it->first))
					return (it);
				++it;
			}
			return (it);
		}
	};
}

#endif