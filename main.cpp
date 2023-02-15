/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:08:59 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/02/15 22:34:01 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector/vector.hpp"
#include "Stack/stack.hpp"
#include <stdio.h>
#include <iostream>
#include <sstream>

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"		/* Reset */
#define BLUE    "\033[34m"      /* Blue */
#define CYAN    "\033[36m"      /* Cyan */
#define RED     "\033[31m" 


int main()
{
	ft::vector<int>				vecInt;
	
	printf("Checking if vecInt is well set: \n");
	for (size_t i = 0; i < 10; i++)
	{
		vecInt.push_back(i * i * 2);
		std::cout << "index " << i << ": " << vecInt.at(i) << std::endl;
	}
	
	std::cout << std::endl;
	std::cout << "Checking max_size() result: " << std::endl;
	std::cout << vecInt.max_size() << std::endl;
	std::cout << std::endl;

	{
		std::cout << RED << "ERASE" << RESET << std::endl;
		std::cout << BLUE << "Erasing from index 3 to index 7 include." << RESET << std::endl;
		
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

	std::cout << "size() result: " << std::endl;
	std::cout << vecInt.size() << std::endl;

	std::cout << std::endl;
	
	std::cout << "Front value: " << vecInt.front() << std::endl;
	std::cout << "Back value: " << vecInt.back() << std::endl;
	
	std::cout << std::endl;
	
	std::cout << "Vector's copy constructor called for baguette from vecInt" << std::endl;
	ft::vector<int>		baguette(vecInt);
	
	{
		std::cout << BLUE << "Deleting all elements with pop_back function" << RESET << std::endl;
		
		ft::vector<int>::iterator	Iter = vecInt.begin();

		for (size_t i = 0; i < 11; ++i)
			vecInt.pop_back();

		std::cout << BLUE << "empty() result: " << RESET << std::endl;
		std::cout << vecInt.empty() << std::endl;
		std::cout << BLUE << "capacity() result: " << RESET << std::endl;
		std::cout << vecInt.capacity() << std::endl;
		std::cout << BLUE << "Resizing our vector to 10 with default value " << RESET << std::endl;
		vecInt.resize(10);
		std::cout << BLUE << "size() result: " << RESET << std::endl;
		std::cout << vecInt.size() << std::endl;
		
	}
	
	std::cout << std::endl;

	{
		std::cout << BLUE << "Vector content: " << RESET << std::endl;
		ft::vector<int>::iterator	Iter = vecInt.begin();

		for (size_t i = 0; Iter != vecInt.end(); ++Iter, ++i)
			std::cout << "index " << i << ": " << *Iter << std::endl;
	}

	std::cout << std::endl;

	{
		std::cout << RED << "CLEAR()" << RESET << std::endl;
		vecInt.clear();

		std::cout << BLUE << "Vector content: " << RESET << std::endl;
		ft::vector<int>::iterator	Iter = vecInt.begin();

		for (size_t i = 0; Iter != vecInt.end(); ++Iter, ++i)
			std::cout << "index " << i << ": " << *Iter << std::endl;
		std::cout << BLUE << "empty() test: " << RESET << vecInt.empty() << std::endl;
	}
	
	std::cout << std::endl;

	{
		std::cout << RED << "SWAP()" << RESET << std::endl;
		ft::vector<int>				tmp;
		ft::vector<int>::iterator	beg = tmp.begin();
		
		std::cout << BLUE << "filling our tmp array with 20 value of 42" << RESET << std::endl;
		tmp.insert(beg, 20, 42);
		std::cout << BLUE << "empty() test on vector tmp: " << RESET << tmp.empty() << std::endl;
		std::cout << BLUE << "Swap tmp and vecInt" << RESET << std::endl;
		vecInt.swap(tmp);
		ft::vector<int>::iterator	Iter = vecInt.begin();
		for (size_t i = 0; Iter != vecInt.end(); ++Iter, ++i)
			std::cout << "index " << i << ": " << *Iter << std::endl;
	}
	
	std::cout << std::endl;

	{
		std::cout << RED << "ASSIGN()" << RESET << std::endl;
		std::cout << BLUE << "Assign all values from baguette to vecInt" << RESET << std::endl;
		
		vecInt.assign(baguette.begin(), baguette.end());
		ft::vector<int>::iterator	Iter = vecInt.begin();
		for (size_t i = 0; Iter != vecInt.end(); ++Iter, ++i)
			std::cout << "index " << i << ": " << *Iter << std::endl;
	}

	return (0);
}