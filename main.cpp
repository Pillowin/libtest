/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:09:54 by agautier          #+#    #+#             */
/*   Updated: 2022/01/04 19:51:45 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"
#include <cstdlib>
#include <string>

bool test_assert(void) { assert(true); }
bool test_assert_eq(void) {
	assert_eq(std::string("toto"), std::string("toto"));
}
bool test_assert_ne(void) { assert_ne(42, 12); }
bool test_false(void) { assert(false); }

int main(void) {
	Test test("Test test");

	test.registerTest("assert", &test_assert);
	test.registerTest("assert_eq", &test_assert_eq);
	test.registerTest("assert_ne", &test_assert_ne);
	// test.registerTest("false", &test_false);	// Uncomment to see failing test

	if (!test.run())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

