/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enableIf.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:19:43 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/10/17 19:21:42 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLEIF_HPP
# define ENABLEIF_HPP

namespace ft
{
	template <bool Cond, class T = void>
	struct enable_if
	{
		
	};
	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
}

#endif