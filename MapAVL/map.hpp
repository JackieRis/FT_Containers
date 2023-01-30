/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:38:26 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/01/30 04:22:13 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "../Iterators/AVLIterator.hpp"
# include "../Utils/pair.hpp"
# include "../Iterators/reverse_iterator.hpp"
# include "../Utils/lexicographical_compare.hpp"
# include "../Utils/equal.hpp"
# include "nodeAVL.hpp"

namespace ft
{	
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	
	typedef typename ft::node<ft::pair<Key,T> >::node_ptr	node_ptr;
	
		public:
	typedef Key										key_type;
	typedef T										mapped_type;
	typedef ft::pair<key_type, mapped_type>			value_type;
	typedef Compare									key_compare;
	typedef Alloc									allocator_type;
	typedef	node<value_type>						node_type;

	class value_compare: public std::binary_function<value_type, value_type, bool>
	{
	private:
		friend class map<Key, T, Compare, Alloc>;
	protected:
		key_compare	comp;
		value_compare(key_compare c): comp(c) {}

	public:
		bool	operator()(const value_type& x, const value_type& y) const
		{return (comp(x.first, y.first));}
	};
		private:
	typedef typename Alloc::template rebind<value_type>::other	pair_alloc;
	typedef typename Alloc::template rebind<ft::node<ft::pair<Key,T> > >::other	node_alloc;
	typedef ft::pair<const key_type, mapped_type>	iter_value_type; // check if sus
		
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
	node_ptr 		endnode;
	size_t			node_count;
	
		private:
	
	//depth getter and calculators to help rebalancing the tree
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
			if (vc(val, n->left->data)) //vc compares both paire's key, true means unbalanced on left
				n = right_rotate(n);
			else
			{
				n->left = left_rotate(n->left);
				n = right_rotate(n);
			}
		}
		else if (balance < -1)//unbalanced on the right
		{
			if (vc(n->right->data, val))
				n = left_rotate(n);
			else
			{
				n->right = right_rotate(n->right);
				n = left_rotate(n);
			}
		}
	}

	void	remove_rebalance(node_ptr& n)
	{
		int	balance = get_balance(n);
		
		if (balance > 1)// wich side of the tree is unbalanced
		{
			if (get_balance(n->left) >= 0) //vc compares both paire's key, true means unbalanced on left
				n = right_rotate(n);
			else
			{
				n->left = left_rotate(n->left);
				n = right_rotate(n);
			}
		}
		else if (balance < -1)//unbalaced on the right
		{
			if (get_balance(n->right) <= 0)
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
		
		if (vc(val, node->data))
		{
			if (node->left)
				ret = rec_insert(val, node->left);
			else
			{
				node->left = create_node(val);
				node->left->parent = node;
				ret = ft::make_pair(iterator(node->left, endnode), true);
			}
		}
		else if(vc(node->data, val))
		{
			if (node->right)
				ret = rec_insert(val, node->right);
			else
			{
				node->right = create_node(val);
				node->right->parent = node;
				ret = ft::make_pair(iterator(node->right, endnode), true);
			}
		}
		else
			return (ft::make_pair(iterator(node, endnode), false));
		if (ret.second == false)
			return (ret);
		node->depth = calc_depth(node->left, node->right) + 1;
		insert_rebalance(node, val);
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
	node_ptr	get_last(node_ptr n)
	{
		node_ptr	tmp = n;
		if (!n)
			return (NULL);
		while (tmp->right)
			tmp = tmp->right;
		return (tmp);
	}

	void	updateEnd()
	{
		endnode->parent = get_last();
	}

	node_ptr dupNode(node_ptr n)
	{
		if (!n)
			return (nullptr);
		
		node_ptr ret = create_node(*n);
		
		try
		{
			ret->left = dupNode(n->left);
			if (ret->left)
				ret->left->parent = ret;
		}
		catch(...)
		{
			destroy_node(ret);
			throw;
		}
		
		try
		{
			ret->right = dupNode(n->right);
			if (ret->right)
				ret->right->parent = ret;
		}
		catch(...)
		{
			clearMap(ret->left);
			destroy_node(ret);
			throw;
		}

		return (ret);
	}

	void clearMap(node_ptr n)
	{
		if (!n)
			return ;
		
		clearMap(n->right);
		clearMap(n->left);
		destroy_node(n);
	}
	
	//recursive function to erase first then rebalance with the help of the recursive
	bool	rec_erase(node_ptr& n, const value_type& k)
	{
		bool	ret = false;

		if (!n)
			return (false);
		if (vc(k, n->data))
			ret = rec_erase(n->left, k);
		else if (vc(n->data, k))
			ret = rec_erase(n->right, k);
		else
		{
			node_ptr	tmp;
			
			if (!n->left || !n->right)
			{
				tmp = n->right;
				if (n->left)
					tmp = n->left;
				if (!tmp)
				{
					tmp = n;			//tmp gets parent's value
					n = nullptr;		// n sets to NULL so n parent has n as null
					destroy_node(tmp);	//then we can easily destroy our node
				}
				else
				{
					tmp->parent = n->parent; 	// tmp parent will get as parent n->parent
					destroy_node(n);			// we can now destroy n
					n = tmp;					// then because n is a reference to his parent's left or right, the parent will get n son at his left or right
				}
				ret = true;
			}
			else
			{
				tmp = get_last(n->left);		//we want to find the closest node before n
				std::swap(tmp->data, n->data);
				ret = rec_erase(n->left, k);
			}
		}
		if (!n)
			return (ret); 					//if no child, then no need to rebalance on this node
		
		n->depth = calc_depth(n->left, n->right) + 1;
		remove_rebalance(n);
		return (ret);
	}
		
		public:
	explicit map(const key_compare& comp = key_compare(), const Alloc& alloc = Alloc()): a(alloc), na(alloc), vc(comp), kc(comp), base(nullptr), endnode(create_node(node_type())), node_count(0) {}
	template<class inputIterator>
	map(inputIterator first, inputIterator last, const key_compare& comp = key_compare(), const Alloc& alloc = Alloc()): a(alloc), na(alloc), vc(comp), kc(comp), base(nullptr), endnode(create_node(node_type())), node_count(0)
	{
		insert(first, last);
	}
	map(const map& from): a(from.a), na(from.na), vc(from.vc), kc(from.kc), base(dupNode(from.base)), endnode(create_node(node_type())), node_count(from.node_count)
	{
		updateEnd();
	}
	~map()
	{
		destroy_node(endnode);
		clearMap(base);
	}

	allocator_type	get_allocator()const {return (Alloc(a));}

	iterator		begin()
	{
		node_ptr	tmp = base;
		if (!base)
			return (end());
		while (tmp->left)
			tmp = tmp->left;
		return (iterator(tmp, endnode));
	}
	const_iterator	begin() const
	{
		node_ptr	tmp = base;
		if (!base)
			return (end());
		while (tmp->left)
			tmp = tmp->left;
		return (const_iterator(tmp, endnode));
	}
	iterator		end()
	{
		return (iterator(endnode, endnode));
	}
	const_iterator	end() const
	{
		return (const_iterator(endnode, endnode));
	}

	reverse_iterator		rbegin()
	{
		return (reverse_iterator(end()));
	}
	const_reverse_iterator	rbegin() const
	{
		return (const_reverse_iterator(end()));
	}
	reverse_iterator		rend()
	{
		return (reverse_iterator(begin()));
	}
	const_reverse_iterator	rend() const
	{
		return (const_reverse_iterator(begin()));
	}

	size_type	size() const
	{
		return (node_count);
	}

	size_type	max_size() const
	{
		return (na.max_size());
	}

	void clear()
	{
		clearMap(base);
		base = nullptr;
		node_count = 0;
	}
	
	mapped_type &operator[](const key_type& k)
	{
		return ((*(insert(ft::make_pair(k, mapped_type())).first)).second);
	}

	iterator	find(const key_type& k)
	{
		value_type	f = ft::make_pair(k, mapped_type()); //f is key's pair
		node_ptr	tmp = base; //tmp is our base
		
		while (tmp)
		{
			if (vc(f, tmp->data)) // if element is on left->side 
				tmp = tmp->left;
			else if (vc(tmp->data, f)) // if element is on right->side
				tmp = tmp->right;
			else					// we found it
				return (iterator(tmp, endnode));
		}
		return (end());				//error 404 not found
	}
	const_iterator	find(const key_type& k) const
	{
		value_type	f = ft::make_pair(k, mapped_type()); //f is key's pair
		node_ptr	tmp = base; //tmp is our base
		
		while (tmp)
		{
			if (vc(f, tmp->data)) // if element is on left->side 
				tmp = tmp->left;
			else if (vc(tmp->data, f)) // if element is on right->side
				tmp = tmp->right;
			else					// we found it
				return (const_iterator(tmp, endnode));
		}
		return (end());				//error 404 not found
	}
	
	size_type	count(const key_type& k) const
	{
		return (find(k) != end());	
	}

	iterator	lower_bound(const key_type& k)
	{
		value_type	f = ft::make_pair(k, mapped_type());
		iterator	b = begin();
		iterator	e = end();

		while (b != e)
		{
			if (!vc(*b, f))
				return (b);
			++b;
		}
		return (e);
	}
	const_iterator	lower_bound(const key_type& k) const
	{
		value_type	f = ft::make_pair(k, mapped_type());
		const_iterator	b = begin();
		const_iterator	e = end();

		while (b != e)
		{
			if (!vc(*b, f))
				return (b);
			++b;
		}
		return (e);
	}
	iterator	upper_bound(const key_type& k)
	{
		value_type	f = ft::make_pair(k, mapped_type());
		iterator	b = begin();
		iterator	e = end();

		while (b != e)
		{
			if (vc(f, *b))
				return (b);
			++b;
		}
		return (e);
	}
	const_iterator	upper_bound(const key_type& k) const
	{
		value_type	f = ft::make_pair(k, mapped_type());
		const_iterator	b = begin();
		const_iterator	e = end();

		while (b != e)
		{
			if (vc(f, *b))
				return (b);
			++b;
		}
		return (e);
	}
	ft::pair<iterator, iterator>	equal_range(const key_type& k)
	{
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	}
	ft::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const
	{
		return (ft::make_pair(lower_bound(k), upper_bound(k)));
	}

	ft::pair<iterator, bool>	insert(const value_type& val)
	{
		ft::pair<iterator, bool> ret;
		if (!base)
		{
			base = create_node(val);
			node_count = 1;
			updateEnd();
			return (ft::make_pair(iterator(base, endnode), true));
		}
		ret = rec_insert(val, base);
		node_count += ret.second;
		updateEnd();
		return (ret);
	}
	iterator	insert(iterator pos, const value_type& val)
	{
		(void)pos;
		return (insert(val).first);
	}
	template<class inputIterator>
	void	insert(inputIterator first, inputIterator last)
	{
		for (; first != last; ++first)
			insert(*first);
	}
	
	void	erase(iterator position)
	{
		erase(position->first);
	}
	void	erase(iterator first, iterator last)
	{
		if (first == begin() && last == end()) //if we have to erase the whole tree, then clear will do it for us
		{
			clear();
			return ;
		}
		iterator tmp = first;
		iterator tmp2;
		for (; tmp != last;)
		{
			tmp2 = tmp;
			++tmp;
			erase(tmp2);
		}
	}
	size_type	erase(const key_type& k)
	{
		bool	ret = rec_erase(base, ft::make_pair(k, mapped_type()));
		
		node_count -= ret;
		if (ret)
			updateEnd();
		return (ret);
	}
	
	map&	operator=(const map& from)
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

	void swap(map& x)
	{
		std::swap(a, x.a);
		std::swap(na, x.na);
		std::swap(base, x.base);
		std::swap(endnode, x.endnode);
		std::swap(node_count, x.node_count);
		std::swap(vc, x.vc);
		std::swap(kc, x.kc);
	}

	bool empty() const
	{
		return (!node_count);
	}

	key_compare	key_comp() const
	{
		return (kc);
	}

	value_compare value_comp() const
	{
		return (vc);
	}
	
	};

	//*********************************************************************
	//operator
	template<class Key, class Val, class Comp, class Alloc>
	bool	operator==(const map<Key, Val, Comp, Alloc> &l, const map<Key, Val, Comp, Alloc> &r)
	{
		if (l.size() != r.size())
			return (false);
		return (ft::equal(l.begin(), l.end(), r.begin()));
	}
	
	template<class Key, class Val, class Comp, class Alloc>
	bool	operator<(const map<Key, Val, Comp, Alloc> &l, const map<Key, Val, Comp, Alloc> &r)
	{
		return (ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end()));//, l.value_comp()));
	}
	
	template<class Key, class Val, class Comp, class Alloc>
	bool	operator!=(const map<Key, Val, Comp, Alloc> &l, const map<Key, Val, Comp, Alloc> &r)
	{
		return (!(l == r));
	}

	template<class Key, class Val, class Comp, class Alloc>
	bool	operator>(const map<Key, Val, Comp, Alloc> &l, const map<Key, Val, Comp, Alloc> &r)
	{
		return (r < l);
	}
	
	template<class Key, class Val, class Comp, class Alloc>
	bool	operator<=(const map<Key, Val, Comp, Alloc> &l, const map<Key, Val, Comp, Alloc> &r)
	{
		return (!(r < l));
	}

	template<class Key, class Val, class Comp, class Alloc>
	bool	operator>=(const map<Key, Val, Comp, Alloc> &l, const map<Key, Val, Comp, Alloc> &r)
	{
		return (!(l < r));
	}
}

#endif