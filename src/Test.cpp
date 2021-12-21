/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 21:26:26 by agautier          #+#    #+#             */
/*   Updated: 2021/12/21 23:15:35 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"
#include <iostream>

/*
**	Default constructor.
*/
Test::Test(char const* name) : tests(0), name(name) {}

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
void Test::registerTest(t_test test) { this->tests.push_back(test); }

/*
**	Run all registered tests.
*/
bool Test::run(void) const {
	std::list< t_test >::const_iterator it;
	uint8_t total  = 0;
	uint8_t passed = 0;

	std::cout << "Starting " << this->name << std::endl;

	for (it = this->tests.begin(); it != this->tests.end(); ++it) {
		if (*it && (*it)())
			passed += 1;
		total += 1;
	}

	if (passed != total) {
		std::cout << "[KO]\t" << total - passed << "/"
				  << static_cast< unsigned >(total) << " Tests failed :("
				  << std::endl;
	} else {
		std::cout << "[OK]\t" << static_cast< unsigned >(total) << "/"
				  << static_cast< unsigned >(total)
				  << " Tests passed successfully :)" << std::endl;
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
