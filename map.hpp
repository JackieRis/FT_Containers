/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:38:26 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/10/25 04:27:06 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "pair.hpp"
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template<class pair>
	struct node
	{
		typedef	node<pair>*	node_ptr;
	
		node_ptdr	left;
		node_ptr	right;
		node_ptr	parent;
		pair		data;
		int			depth;
	
		//default constructor, set all value to 0 and depth to 1
		node(): left(nullptr), right(nullptr), parent(nullptr), data(), depth(1){}
		node(const pair& from): left(nullptr), right(nullptr), parent(nullptr), data(from), depth(1){}
		node(const node& from): left(from.left), right(from.right), parent(from.parent), data(from.data), depth(from.depth){}
	};
	
	
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T>> >
	class map
	{
	
	typedef typename Alloc::template rebind<Node<pair<Key,T> > >::other	node_alloc;
	typedef typename ft::node<pair<Key,T> >::node_ptr	node_ptr;
	
		public:
	typedef T										mapped_type;
	typedef Key										key_type;
	typedef ft::pair<Key,T>							value_type;
	typedef Compare									key_compare;
	typedef	node<value_type>						node_type;
	typedef ft::map_iterator<const T*>				const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	class value_compare: public std::binary_function<value_type, value_type, bool>
	{
	private:
		friend class map<Key, T, Compare, Alloc>
	protected:
		key_compare	comp;
		value_compare(key_compare c): comp(c){}

	public:
		bool	operator()(const value_type& x, const value_type& y)const {return (comp(x.first,y.first));}
	};
		
		protected:
	node_ptr		base;
	node_ptr 		end;
	Alloc			a;
	node_alloc		na;
	size_t			node_count;
	value_compare	vc;
	key_compare		kc;
	
		private:
	typedef ft::map_iterator<T*>					iterator;

	//depth getter and calucators to help rebalancing the tree
	int	get_depth(node_ptr n)
	{
		if (n)
			return (n->depth);
		return (0);
	}
	int	calc_depth(node_ptr l, node_ptr r)
	{
		int	tmpl = get_depth(l);
		int tmpr = get_depth(r);
		if (tmpl > tmpr)
			return (tmpl);
		return (tmpr);
	}
	int	get_balance(node_ptr n) // if the return is positive, left is unbalanced, else if neg, right is unblanced, 0 is balanced
	{
		if (!n)
			return (0);
		return (get_depth(n->left) - get_depth(n->right));
	}
	
	node_ptr	left_rotate(node_ptr n)
	{
		node_ptr	r = n->right;
		node_ptr	rl = r->left;
		
		r->left = n;
		n->right = rl;
		n->depth = calc_depth(n->left, n->right) + 1;
		n->depth = calc_depth(r->left, r->right) + 1;
		r->parent = n->parent;
		n->parent = r;
		if (rl)
			rl->parent = n;
		return (r);
	}
	node_ptr	right_rotate(node_ptr n)
	{
		node_ptr	l = n->left;
		node_ptr	lr = l->right;
		
		l->right = n;
		n->left = lr;
		n->depth = calc_depth(n->left, n->right) + 1;
		l->depth = calc_depth(l->left, l->right) + 1;
		l->parent = n->parent;
		n->parent = l;
		if (lr)
			lr->parent = n;
		return (l);
	}

	void	insert_rebalance(node_ptr& n, const value_type& val)
	{
		int	balance = get_balance(n);
		
		if (balance > 1)// wich side of the tree is unbalanced
		{
			if (vc(val,n->left->data)) //vc compares both paire's key, true means unbalanced on left
				n = right_rotate(n);
			else
			{
				n->left = left_rotate(n->left);
				n = right_rotate(n);
			}
		}
		else if (balance < -1)//unbalaced on the right
		{
			if (vc(n->right->data))
				n = left_rotate(n);
			else
			{
				n->right = right_rotate(n->right);
				n = left_rotate(n);
			}
		}
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
			na.deallocate(p, 1);
			throw;
		}
		return (p);
	}

	void	destroy_node(node_ptr x)
	{
		na.destroy(x);
		na.deallocate(x, 1);
	}
	ft::pair<iterator, bool>	rec_insert(const value_type& val, node_ptr& node)
	{
		ft::pair<iterator, bool>	ret;
		
		if (vc(val.first, node->data.first))
		{
			if (node->left)
				ret = rec_insert(val, node->left);
			else
			{
				node->left = create_node(val);
				node->left->parent = node;
				ret = make_pair(iterator(node->left, true))
			}
		}
		else if(vc(node->data.first, val.first))
		{
			if (node->right)
				ret = rec_insert(val, node->right);
			else
			{
				node->right = create_node(val);
				node->right->parent = node;
				ret = make_pair(iterator(node->right, true));
			}
		}
		else
			return (make_pair(iterator(node), false));
		if (pair->second == false)
			return (ret);
		node->depth = calc_depth(node->left, node->right) + 1;
		node = insert_rebalance(n, val); 
		return (ret);
	}
	
	node_ptr	get_last()
	{
		node_ptr	tmp = base;
		if (!base)
			return (NULL);
		while (tmp->right)
			tmp = tmp->right;
		return (tmp);
	}
	void	updateBegEnd()
	{
		end->parent = get_last();
	}
		
		public:
	map();
	explicit map(const Compare& comp=std::less<Key>, const Allocator& alloc = Allocator()): vc(comp), kc(comp), na(alloc), a(alloc){}
	template<class inputIterator>
	map(inputIterator first, inputIterator last, const Compare& comp=std::less<Key>, const Allocator& alloc = Allocator()): vc(comp), kc(comp), a(alloc), na(alloc)
	{
		end = create_node(node_type());
		insert(first, last);
		
	}
	map(const map& from): vc(from.vc), kc(from.kc), a(from.a), na(from.na), node_count(from.node_count)
	{
		
	}
	~map()
	{
		destroy_node(end);
	}

	iterator		begin()
	{
		node_ptr	tmp = base;
		if (!base)
			;//return end
		while (tmp->left)
			tmp = tmp->left;
		return (iterator(tmp));
	}
	const_iterator	begin()const
	{
		node_ptr	tmp = base;
		if (!base)
			;//return end
		while (tmp->left)
			tmp = tmp->left;
		return (const_iterator(tmp));
	}
	iterator		end()
	{
		
	}
	const_iterator	end()const {}
	
	ft::pair<iterator, bool>	insert(const value_type& val)
	{
		ft::pair<iterator, bool> ret;
		if (!base)
		{
			base = create_node(val);
			node_count = 1;
			return (ft::make_pair(iterator(base), true));
		}
		ret = rec_insert(val, base);
		node_count += ret.second;
		updateBegEnd();
		return (ret);
	}
	iterator	insert(iterator pos, const value_type& val)
	{
		return (insert(val).first);
	}
	template<class inputIterator>
	void	insert(inputIterator first, inputIterator last)
	{
		for (; first < last; ++first)
			insert(*first);
	}
	
	map&	operator=(const map& from)
	{
		if (*this == from)
			return (*this);
		base = from.base;
		a = from.a;
		return (*this);
	}
	};
}

#endif