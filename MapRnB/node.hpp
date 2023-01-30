/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 00:00:35 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/01/30 06:57:25 by tnguyen-         ###   ########.fr       */
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
		typedef	node*	node_ptr;
		typedef node&	node_ref;
		
		Color		color;
		bool		isSentinel;
		node_ptr	left;
		node_ptr	right;
		node_ptr	parents;
		pair		data;

		
		node(const pair& from): color(BLACK), data(from), left(NULL), right(NULL), parents(NULL)
		{
		
		}
		
		node(pair d, bool b,Color c, node l, node r, node p): data(d), isSentinel(b), color(c), left(l), right(r), parents(p)
		{
			
		}
		
		node(const node& from): left(from.left), right(from.right), parents(from.parents), data(from.data)
		{
			
		}
	};
};
#endif