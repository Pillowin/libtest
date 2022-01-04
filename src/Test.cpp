/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 21:26:26 by agautier          #+#    #+#             */
/*   Updated: 2022/01/04 20:20:15 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"
#include <iostream>

/*
**	Default constructor.
*/
Test::Test(char const* name) : name(name) {}

/*
**	Copy constructor.
*/
Test::Test(Test const& rhs) { *this = rhs; }

/*
**	Destructor.
*/
Test::~Test(void) {}

/*
**	Register a test function to tests list.
*/
void Test::registerTest(std::string const name, t_test test) {
	this->tests.insert(std::pair< std::string const, t_test >(name, test));
}

/*
**	Run all registered tests.
*/
bool Test::run(void) const {
	std::map< std::string const, t_test >::const_iterator it;
	uint8_t												  total	 = 0;
	uint8_t												  passed = 0;

	std::cout << this->name << std::endl;

	for (it = this->tests.begin(); it != this->tests.end(); ++it) {
		if (it->second && (it->second)()) {
			std::cout << GREEN << "  ✓ " << RESET << it->first << std::endl;
			passed += 1;
		} else {
			std::cout << RED << "  ❌" << RESET << it->first << std::endl;
		}
		total += 1;
	}

	if (passed != total) {
		std::cout << RED << "[KO] " << static_cast< unsigned >(passed) << "/"
				  << static_cast< unsigned >(total) << " passed :(" << RESET
				  << std::endl;
	} else {
		std::cout << GREEN << "[OK] " << static_cast< unsigned >(passed) << "/"
				  << static_cast< unsigned >(total) << " passed :)" << RESET
				  << std::endl;
	}

	return (total == passed);
}

/*
**	Assignment operator.
*/
Test& Test::operator=(Test const& rhs) {
	if (this == &rhs)
		return (*this);
	this->tests = rhs.tests;
	return (*this);
}
