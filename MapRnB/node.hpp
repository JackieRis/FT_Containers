/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 00:00:35 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/01/30 00:35:18 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include "../utils/pair.hpp"
# include "../utils/enableIf.hpp"
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
		Color   color;
		node    left;
		node    right;
		node    parents;
		pair    data;
		
		node(const pair& from): color(BLACK), data(from), left(NULL), right(NULL), parents(NULL)
		{
		
		}
		
		node(pair d, Color c, Node l, Node r, Node p): data(d), color(c), left(l), right(r), parents(p)
		{
			
		}
		
		node(const Node& from): left(from.left), right(from.right), parents(fron.parents), data(from.data)
		{
			
		}
	};
};
#endif