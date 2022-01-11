/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:09:54 by agautier          #+#    #+#             */
/*   Updated: 2022/01/11 17:00:33 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"
#include <cstdlib>
#include <signal.h>
#include <string>
#include <unistd.h>

bool test_assert(void) { assert(true); }
bool test_assert_eq(void) {
	assert_eq(std::string("toto"), std::string("toto"));
}
bool test_assert_ne(void) { assert_ne(42, 12); }
bool test_false(void) { assert(false); }
bool test_sigsegv(void) {
	raise(SIGSEGV);
	return (false);
}
bool test_sigbus(void) {
	raise(SIGBUS);
	return (false);
}
bool test_sigabrt(void) {
	raise(SIGABRT);
	return (false);
}
bool test_sigfpe(void) {
	raise(SIGFPE);
	return (false);
}
bool test_sigpipe(void) {
	raise(SIGPIPE);
	return (false);
}
bool test_sigill(void) {
	raise(SIGILL);
	return (false);
}
bool test_timeout(void) {
	sleep(15);
	return (false);
}

int main(void) {
	Test test("Test test");

	test.registerTest("assert", &test_assert);
	test.registerTest("assert_eq", &test_assert_eq);
	test.registerTest("assert_ne", &test_assert_ne);
	test.registerTest("false", &test_false); // Uncomment to see failing test
	test.registerTest("SIGSEGV", &test_sigsegv);
	test.registerTest("SIGBUS", &test_sigbus);
	test.registerTest("SIGARBT", &test_sigabrt);
	test.registerTest("SIGFPE", &test_sigfpe);
	test.registerTest("SIGPIPE", &test_sigpipe);
	test.registerTest("SIGILL", &test_sigill);
	test.registerTest("timeout", &test_timeout);

	if (!test.run())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

