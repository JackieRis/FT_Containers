/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:08:59 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/02/12 04:05:45 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector/vector.hpp"
#include "Stack/stack.hpp"
#include <iostream>
#include <sstream>

int main()
{
	ft::vector<int>				vecInt;
	
	std::cout << "Checking if vecInt is well set: " << std::endl;
	for (size_t i = 0; i < 10; i++)
	{
		vecInt.push_back(i * i * 2);
		std::cout << "index " << i << ": " << vecInt.at(i) << std::endl;
	}
	
	std::cout << std::endl;

	{
		std::cout << "Erasing from index 3 to index 7 include." << std::endl;
		
		ft::vector<int>::iterator	Iter = vecInt.begin();
		ft::vector<int>::iterator	It1 = vecInt.begin() + 3;
		ft::vector<int>::iterator	It2 = It1 + 5;

		vecInt.erase(It1, It2);
		for (size_t i = 0; Iter != vecInt.end(); ++Iter, ++i)
			std::cout << "index " << i << ": " << *Iter << std::endl;
	}
	
	std::cout << std::endl;
	
	{
		std::cout << "Inserting at index 2" << std::endl;

		ft::vector<int>::iterator	Iter = vecInt.begin();
		ft::vector<int>::iterator	It1 = vecInt.begin() + 3;
		
		vecInt.insert(It1, 10);
		vecInt.insert(It1 + 1, 5, 12);
		
		for (size_t i = 0; Iter != vecInt.end(); ++Iter, ++i)
			std::cout << "index " << i << ": " << *Iter << std::endl;
	}

	std::cout << std::endl;
	
	{

	}

	return (0);
}