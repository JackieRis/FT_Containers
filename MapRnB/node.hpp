/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 00:00:35 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/01/30 03:41:14 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include "../Utils/pair.hpp"
# include "../Iterators/iterator.hpp"

enum Color {
	RED = 1,
	BLACK = 2
};

namespace ft
{
	
    template<class pair>
    struct node
	{
		typedef	node<pair>*	node_ptr;
		
		Color		color;
		int			depth;
		node_ptr	left;
		node_ptr	right;
		node_ptr	parents;
		pair		data;
		int			depth;
		
		node(const pair& from): color(BLACK), data(from), left(NULL), right(NULL), parents(NULL)
		{
		
		}
		
		node(pair d, Color c, node l, node r, node p): data(d), color(c), left(l), right(r), parents(p)
		{
			
		}
		
		node(const node& from): left(from.left), right(from.right), parents(from.parents), data(from.data)
		{
			
		}
		
		
	};
};
#endif