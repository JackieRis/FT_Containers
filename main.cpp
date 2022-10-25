/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <tnguyen-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 01:26:39 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/10/19 20:02:20 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "iterator.hpp"

using namespace ft;

std::ostream& operator<<(std::ostream& os, const ft::vector<int>& v)
{
	os << "cap: " <<  v.capacity() << std::endl;
	os << "last: " << v.size() << std::endl;
	for (ft::vector<int>::const_iterator it = v.begin(); it < v.end(); ++it)
		os << "array[" << ft::distance(v.begin(), it) << "] = " << *it << std::endl;
	return (os);
}

int	main(void)
{
	vector<int>	aled;
	vector<int>	oskour(30);
	vector<char> test(50);
	
	std::cout << "empty vector test: " << aled.empty() << std::endl;
	for (size_t i = 0; i < 30; i++)
		oskour[i] = i;
	std::cout << "max_size is: " << oskour.max_size() << std::endl;
	std::cout << "max_size is: " << test.max_size() << std::endl;
	std::cout << oskour;
	std::cout << std::endl;
	std::cout << "testing push_back and realloc \n";
	//oskour.reserve(50);
	oskour.push_back(-42);
	std::cout << oskour;
	std::cout << "begin: " << &(*oskour.begin()) << " | end: " << &(*oskour.end()) << std::endl;

	std::cout << std::endl;
	std::cout << "resizing vector oskour:\n";
	oskour.resize(16, 42);
	std::cout << oskour;
	std::cout << std::endl;
	std::cout << oskour;
	std::cout << oskour.back() << std::endl;
	
	//ONLY ONE BY ONE INSERTING
	vector<int>::iterator	it = oskour.begin();
	std::cout << std::endl;
	std::cout << "Inserting one time" << std::endl;
	it = oskour.insert(oskour.end(), 3000);
	std::cout << oskour;
	std::cout << std::endl;
	
	//MULTIPLE INSERTING
	std::cout << "Inserting multiple times" << std::endl;
	it = oskour.begin() + 9;
	it = oskour.insert(it, 10, 93);
	std::cout << oskour;

	//SIMPLE ERASE
	std::cout << std::endl;
	std::cout << "Erasing one time" << std::endl;
	it = oskour.erase(oskour.begin() + 2);
	std::cout << oskour;
	
	//RANGE ERASE
	std::cout << std::endl;
	std::cout << "Erasing whole array" << std::endl;
	it = oskour.erase(oskour.begin() + 2, oskour.end() - 2);
	std::cout << *it << std::endl;
	std::cout << oskour;

	//swapping vectors
	std::cout << std::endl;
	std::cout << "Swapping oskour and aled vectors" << std::endl; 
	std::cout << std::endl;
	oskour.swap(aled);
	std::cout << "Oskour: " << std::endl;
	std::cout << oskour;
	std::cout << std::endl;
	std::cout << "Aled: " << std::endl;
	std::cout << aled;

	const vector<int>::const_iterator it1 = ((const ft::vector<int>)aled).begin();
	it = aled.end() - 2;
	
	std::cout <<  (it < it1) << std::endl;

	return (0);
}
