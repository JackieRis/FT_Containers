/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodeAVL.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 01:01:14 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/01/30 01:08:21 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODEAVL_HPP
# define NODEAVL_HPP

# include "../Utils/pair.hpp"
# include "../Utils/enableIf.hpp"
# include "../Iterators/iterator.hpp"

namespace ft 
{
template<class pair>
	struct node
	{
		typedef	node<pair>*	node_ptr;
	
		node_ptr	left;
		node_ptr	right;
		node_ptr	parent;
		pair		data;
		int			depth;
	
		//default constructor, set all value to 0 and depth to 1
		node(): left(nullptr), right(nullptr), parent(nullptr), data(), depth(1){}
		node(const pair& from): left(nullptr), right(nullptr), parent(nullptr), data(from), depth(1){}
		node(const node& from): left(from.left), right(from.right), parent(from.parent), data(from.data), depth(from.depth){}
	};
};
#endif