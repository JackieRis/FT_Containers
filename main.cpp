/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:08:59 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/02/15 23:15:19 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector/vector.hpp"
#include "Stack/stack.hpp"
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

	std::cout << RED << "Construct our vector" << RESET << std::endl;
	std::cout << BLUE << "Checking if vecInt is well set" << RESET << std::endl;
	for (size_t i = 0; i < 10; i++)
	{
		vecInt.push_back(i * i * 2);
		std::cout << "index " << i << ": " << vecInt.at(i) << std::endl;
	}

	std::cout << std::endl;
	std::cout << RED << "max_size() result: " << RESET << std::endl;
	std::cout << vecInt.max_size() << std::endl;
	std::cout << std::endl;

	{
		std::cout << RED << "erase()" << RESET << std::endl;
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
		std::cout << RED << "insert()" << RESET << std::endl;
		std::cout << BLUE << "Inserting at index 2" << RESET << std::endl;

		ft::vector<int>::iterator	Iter = vecInt.begin();
		ft::vector<int>::iterator	It1 = vecInt.begin() + 3;
		
		vecInt.insert(It1, 10);
		vecInt.insert(It1 + 1, 5, 12);
		
		for (size_t i = 0; Iter != vecInt.end(); ++Iter, ++i)
			std::cout << "index " << i << ": " << *Iter << std::endl;
	}
	
	std::cout << std::endl;

	std::cout << RED << "size()" << RESET << std::endl;
	std::cout << BLUE << "size() result: " << RESET << std::endl;
	std::cout << vecInt.size() << std::endl;

	std::cout << std::endl;
	
	std::cout << RED << "front() and back()" << RESET << std::endl;
	std::cout << BLUE << "Front value: " << RESET << vecInt.front() << std::endl;
	std::cout << BLUE << "Back value: " << RESET << vecInt.back() << std::endl;
	
	std::cout << std::endl;
	
	std::cout << RED << "Copy constructor" << RESET << std::endl;
	std::cout << BLUE << "Vector's copy constructor called for baguette from vecInt" << RESET << std::endl;
	ft::vector<int>		baguette(vecInt);
	
	{
		std::cout << RED << "pop_back()" << RESET << std::endl;
		std::cout << BLUE << "Deleting all elements with pop_back function" << RESET << std::endl;

		for (size_t i = 0; i < 11; ++i)
			vecInt.pop_back();

		std::cout << RED << "empty() result: " << RESET << std::endl;
		std::cout << vecInt.empty() << std::endl;
		std::cout << RED << "capacity() result: " << RESET << std::endl;
		std::cout << vecInt.capacity() << std::endl;
		std::cout << RED << "resize()" << RESET << std::endl;
		std::cout << BLUE << "Resizing our vector to 10 with default value " << RESET << std::endl;
		vecInt.resize(10);
		std::cout << RED << "size() result: " << RESET << std::endl;
		std::cout << vecInt.size() << std::endl;
		
	}

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

		std::cout << std::endl;

	{
		std::cout << RED << "reserve()" << RESET << std::endl;
		
		std::cout << BLUE << "Old vecInt capacity: " << RESET << vecInt.capacity() << std::endl;
		vecInt.reserve(15);
		std::cout << BLUE << "Try to reserve a capacity of 15, should do nothing because n is smaller than our cap" << RESET << std::endl;
		std::cout << BLUE << "capacity() returns: " << RESET << vecInt.capacity() << std::endl;
		vecInt.reserve(50);
		std::cout << BLUE << "reserve(50) result: " << RESET << vecInt.capacity() << std::endl;
		
	}

	return (0);
}