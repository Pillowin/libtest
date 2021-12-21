/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:09:54 by agautier          #+#    #+#             */
/*   Updated: 2021/12/21 23:15:21 by agautier         ###   ########.fr       */
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

int main(void) {
	Test test("Testing tests");

	test.registerTest(&test_assert);
	test.registerTest(&test_assert_eq);
	test.registerTest(&test_assert_ne);

	if (!test.run())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

