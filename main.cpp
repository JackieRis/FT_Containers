/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:08:59 by tnguyen-          #+#    #+#             */
/*   Updated: 2023/02/21 08:57:52 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vector/vector.hpp"
#include "Stack/stack.hpp"
#include "Map/map.hpp"
#include <iostream>
#include <sstream>

//the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
#define RESET   "\033[0m"		/* Reset */
#define BLUE    "\033[34m"      /* Blue */
#define CYAN    "\033[36m"      /* Cyan */
#define RED     "\033[31m" 
#define GREEN   "\033[32m"

int main()
{
	ft::vector<int>				vecInt;
	ft::vector<int>::const_iterator	CIt = vecInt.begin();	

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
	
	std::cout << std::endl;

	{
		ft::vector<int>::iterator	Iter = vecInt.end();
		
		if (CIt != Iter)
			std::cout << GREEN << "Congrats you can compare Iterators with const_iterators" << RESET << std::endl;
		else
			std::cout << RED << "CRASH" << RESET << std::endl;
	}
	
	{
		ft::vector<int>	baguette;
		baguette.push_back(42);
		baguette.push_back(42);
		baguette.push_back(42);
		baguette.push_back(42);
		baguette.push_back(42);
		std::cout << baguette.capacity() << std::endl;
	}
	
	std::cout << std::endl;
	
	{
		std::cout << BLUE << "Check if you well allocate your vector on basic constructor" << RESET << std::endl;
		ft::vector<int>	test;
		
		std::cout << test[0] << std::endl;
	}

	std::cout << std::endl;
	
		/*##################################################################################*/
		//                                 MAP TESTS
		/*##################################################################################*/

	std::cout << RED << "MAP TESTS" << RESET << std::endl;
	std::cout << std::endl;

	{
		std::cout << RED << "CONSTRUCTORS" << RESET << std::endl;
		ft::map<int, std::string>	Users;
		std::cout << GREEN << "Default constructor" << RESET << std::endl;

		Users.insert(ft::make_pair(0, "toto"));
		Users.insert(ft::make_pair(404, "Error"));
		Users.insert(ft::make_pair(42, "42"));
		Users.insert(ft::make_pair(1, "tata"));
		Users.insert(ft::make_pair(-15, "negative"));
		Users.insert(ft::make_pair(2147483647, "Int max"));
		Users.insert(ft::make_pair(-2147483648, "Int min"));
		
		ft::map<int, std::string>::iterator	Beg = Users.begin();
		ft::map<int, std::string>::iterator	End = Users.end();
		for (; Beg != End; ++Beg)
			std::cout << BLUE << "Users: " << RESET << Beg->first << " | " << Beg->second << std::endl;
		
		std::cout << std::endl;
		
		ft::map<int, std::string>	Users2(Users);
		std::cout << GREEN << "Copy constructor" << RESET << std::endl;
		ft::map<int, std::string>::iterator	Beg2 = Users2.begin();
		ft::map<int, std::string>::iterator	End2 = Users2.end();
		for (; Beg2 != End2; ++Beg2)
			std::cout << BLUE << "Users2: " << RESET << Beg2->first << " | " << Beg2->second << std::endl;
		
		Beg2 = Users2.begin();
		Beg2++;
		Beg2++;
		
		std::cout << std::endl;
		std::cout << GREEN << "Iterator constructor" << RESET << std::endl;
		ft::map<int, std::string>	Users3(Beg2, End2);
		ft::map<int, std::string>::iterator	Beg3 = Users3.begin();
		ft::map<int, std::string>::iterator	End3 = Users3.end();
		
		for (; Beg3 != End3; ++Beg3)
			std::cout << BLUE << "Users3: " << RESET << Beg3->first << " | " << Beg3->second << std::endl;
		
		std::cout << std::endl;

		std::cout << GREEN << "Operator= test" << RESET << std::endl;
		Users3 = Users2;
		Beg3 = Users3.begin();
		End3 = Users3.end();
		for (; Beg3 != End3; ++Beg3)
			std::cout << BLUE << "Users3: " << RESET << Beg3->first << " | " << Beg3->second << std::endl;
			
		std::cout << std::endl;
		std::cout << GREEN << "Get_allocator test" << RESET << std::endl;
		ft::map<int, std::string>::allocator_type	alloc = Users3.get_allocator();
		std::cout << GREEN << "No crash, you passed the test" << RESET << std::endl;
		
		std::cout << std::endl;
		std::cout << RED << "Element access" << RESET << std::endl;
		
		std::cout << std::endl;
		std::cout << GREEN << "Operator[] test" << RESET << std::endl;
		std::cout << BLUE << Users3[42] << RESET << std::endl;

		std::cout << std::endl;
		std::cout << GREEN << "Operator[] test" << RESET << std::endl;
		Users3[42] = "42bis";
		std::cout << BLUE << Users3[42] << RESET << std::endl;
		
		std::cout << std::endl;
		
		/*##################################################################################*/
		//                                 ITERATORS TESTS
		/*##################################################################################*/
		
		std::cout << RED << "Iterators" << RESET << std::endl;
		
		std::cout << std::endl;

		std::cout << GREEN << "Begin test" << RESET << std::endl;
		ft::map<int, std::string>::iterator	Begin = Users3.begin();
		std::cout << BLUE << "Begin: " << RESET << Begin->first << " | " << Begin->second << std::endl;
		
		std::cout << std::endl;
		
		std::cout << GREEN << "End test" << RESET << std::endl;
		ft::map<int, std::string>::iterator	End4 = Users3.end();
		End4--;
		std::cout << BLUE << "End: " << RESET << End4->first << " | " << End4->second << std::endl;
		
		std::cout << std::endl;

		std::cout << GREEN << "Rbegin test" << RESET << std::endl;
		ft::map<int, std::string>::reverse_iterator	RBegin = Users3.rbegin();
		std::cout << BLUE << "RBegin: " << RESET << RBegin->first << " | " << RBegin->second << std::endl;
		
		std::cout << std::endl;

		std::cout << GREEN << "Rend test" << RESET << std::endl;
		ft::map<int, std::string>::reverse_iterator	REnd = Users3.rend();
		REnd--;
		std::cout << BLUE << "REnd: " << RESET << REnd->first << " | " << REnd->second << std::endl;
	}
	
	{
		/*##################################################################################*/
		//                                 Capacity TESTS
		/*##################################################################################*/
		
		std::cout << std::endl;
		
		std::cout << RED << "Capacity" << RESET << std::endl;
		
		std::cout << std::endl;

		std::cout << GREEN << "Empty test" << RESET << std::endl;
		ft::map<int, std::string>	Users;
		std::cout << BLUE << "Empty: " << RESET << Users.empty() << std::endl;
		
		std::cout << std::endl;

		std::cout << GREEN << "Size test" << RESET << std::endl;
		
		Users.insert(ft::make_pair(0, "toto"));
		Users.insert(ft::make_pair(404, "Error"));
		Users.insert(ft::make_pair(42, "42"));
		Users.insert(ft::make_pair(1, "tata"));
		Users.insert(ft::make_pair(-15, "negative"));
		Users.insert(ft::make_pair(2147483647, "Int max"));
		Users.insert(ft::make_pair(-2147483648, "Int min"));

		std::cout << BLUE << "Size: " << RESET << Users.size() << std::endl;
		
		std::cout << std::endl;
		
		std::cout << GREEN << "Max_size test" << RESET << std::endl;
		std::cout << BLUE << "Max_size: " << RESET << Users.max_size() << std::endl;
	}
	
	{
		/*##################################################################################*/
		//                                Modifiers TESTS
		/*##################################################################################*/
		
		std::cout << std::endl;
		
		std::cout << RED << "Modifiers" << RESET << std::endl;
		
		std::cout << std::endl;
		
		std::cout << GREEN << "Insert test" << RESET << std::endl;
		
		ft::map<int, std::string>	Users;
		Users.insert(ft::make_pair(0, "toto"));
		Users.insert(ft::make_pair(404, "Error"));
		Users.insert(ft::make_pair(42, "42"));
		Users.insert(ft::make_pair(1, "tata"));
		Users.insert(ft::make_pair(-15, "negative"));
		Users.insert(ft::make_pair(2147483647, "Int max"));
		Users.insert(ft::make_pair(-2147483648, "Int min"));

		for (size_t i = 30; i < 40; i++)
			Users.insert(ft::make_pair(i, "baguette"));
		
		ft::map<int, std::string>::iterator	Beg = Users.begin();
		ft::map<int, std::string>::iterator	End = Users.end();
		for (; Beg != End; ++Beg)
			std::cout << BLUE << "Users: " << RESET << Beg->first << " | " << Beg->second << std::endl;
			
		std::cout << std::endl;

		std::cout << GREEN << "Erase test" << RESET << std::endl;
		Users.erase(Users.begin());
		Beg = Users.begin();
		Beg++;
		Users.erase(Beg, Users.end());
		
		Beg = Users.begin();
		for (; Beg != End; ++Beg)
			std::cout << BLUE << "Users: " << RESET << Beg->first << " | " << Beg->second << std::endl;
			
		std::cout << std::endl;

		std::cout << GREEN << "Swap test" << RESET << std::endl;
		ft::map<int, std::string>	Users2;
		Users2.insert(ft::make_pair(0, "toto"));
		Users2.insert(ft::make_pair(404, "Error"));
		Users2.insert(ft::make_pair(42, "42"));
		Users2.insert(ft::make_pair(1, "tata"));
		Users2.insert(ft::make_pair(-15, "negative"));
		Users2.insert(ft::make_pair(2147483647, "Int max"));
		Users2.insert(ft::make_pair(-2147483648, "Int min"));

		Users.swap(Users2);

		Beg = Users.begin();
		End = Users.end();
		for (; Beg != End; ++Beg)
			std::cout << BLUE << "Users: " << RESET << Beg->first << " | " << Beg->second << std::endl;
			
		std::cout << std::endl;
		
		Beg = Users2.begin();
		End = Users2.end();
		
		for (; Beg != End; ++Beg)
			std::cout << BLUE << "Users2: " << RESET << Beg->first << " | " << Beg->second << std::endl;
			
		std::cout << std::endl;
		
		std::cout << GREEN << "Clear test" << RESET << std::endl;
		Users.clear();
		Users2.clear();

		if (Users.empty() && Users2.empty())
			std::cout << BLUE << "Users and Users2 are empty" << RESET << std::endl;
		else
			std::cout << RED << "Users and Users2 are not empty" << RESET << std::endl;
	}
	
	{
		/*##################################################################################*/
		//                                Observers TESTS
		/*##################################################################################*/
		
		std::cout << std::endl;
		
		std::cout << RED << "Observers" << RESET << std::endl;

		std::cout << std::endl;
		
		std::cout << GREEN << "Key_comp test" << RESET << std::endl;
		ft::map<int, std::string>	Users;
		Users.insert(ft::make_pair(0, "toto"));
		Users.insert(ft::make_pair(404, "Error"));
		Users.insert(ft::make_pair(42, "42"));
		Users.insert(ft::make_pair(1, "tata"));
		Users.insert(ft::make_pair(-15, "negative"));
		Users.insert(ft::make_pair(2147483647, "Int max"));
		Users.insert(ft::make_pair(-2147483648, "Int min"));
		
		ft::map<int, std::string>::key_compare	comp = Users.key_comp();
		ft::map<int, std::string>::iterator		Beg = Users.begin();
		ft::map<int, std::string>::iterator		End = Users.end();
		int										highest = Users.rbegin()->first;
		ft::map<int, std::string>	Users2(Users);
		
		std::cout << comp(Users.begin()->first, Users.rbegin()->first) << std::endl;
		
		std::cout << std::endl;

		std::cout << GREEN << "Value_comp test" << RESET << std::endl;
		ft::map<int, std::string>::value_compare	comp2 = Users.value_comp();
		ft::map<int, std::string>::iterator		Beg2 = Users2.begin();
		ft::map<int, std::string>::iterator		End2 = Users2.end();
		
		std::cout << comp2(*Beg2, *End2) << std::endl;
		
		std::cout << std::endl;
		
		std::cout << GREEN << "Find test" << RESET << std::endl;
		ft::map<int, std::string>::iterator		it = Users.find(42);
		ft::map<int, std::string>::iterator		it2 = Users.find(404);
		ft::map<int, std::string>::iterator		it3 = Users.find(0);
		
		std::cout << BLUE << "Users: " << RESET << it->first << " | " << it->second << std::endl;
		std::cout << BLUE << "Users: " << RESET << it2->first << " | " << it2->second << std::endl;
		std::cout << BLUE << "Users: " << RESET << it3->first << " | " << it3->second << std::endl;
		
		std::cout << std::endl;
		
		std::cout << GREEN << "Count test" << RESET << std::endl;
		std::cout << BLUE << "Users: " << RESET << Users.count(42) << std::endl;
		std::cout << BLUE << "Users: " << RESET << Users.count(404) << std::endl;
		std::cout << BLUE << "Users: " << RESET << Users.count(0) << std::endl;
		
		std::cout << std::endl;

		std::cout << GREEN << "Lower_bound test" << RESET << std::endl;
		ft::map<int, std::string>::iterator		it4 = Users.lower_bound(42);
		
		std::cout << BLUE << "Users: " << RESET << it4->first << " | " << it4->second << std::endl;
		
		std::cout << std::endl;
		
		std::cout << GREEN << "Upper_bound test" << RESET << std::endl;
		ft::map<int, std::string>::iterator		it5 = Users.upper_bound(42);

		std::cout << BLUE << "Users: " << RESET << it5->first << " | " << it5->second << std::endl;
		
		std::cout << std::endl;
		
		std::cout << GREEN << "Equal_range test" << RESET << std::endl;
		ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator>	ret;
		ret = Users.equal_range(42);
		
		std::cout << BLUE << "Users: " << RESET << ret.first->first << " | " << ret.first->second << std::endl;
		std::cout << BLUE << "Users: " << RESET << ret.second->first << " | " << ret.second->second << std::endl;
	}
}
