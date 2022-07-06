/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:09:54 by agautier          #+#    #+#             */
/*   Updated: 2022/07/06 10:49:21 by webforce3        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"
#include <cstdlib>
#include <iostream>
#include <signal.h>
#include <string>
#include <unistd.h>

bool test_assert(void) { ltest_assert(true); }
bool test_assert_eq(void) {
	ltest_assert_eq(std::string("toto"), std::string("toto"));
}
bool test_assert_ne(void) { ltest_assert_ne(42, 12); }
bool test_false(void) { ltest_assert(false); }
bool test_stdout(void) {
	std::cout << "You should not see me" << std::endl;
	return (true);
}
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
	test.registerTest("false", &test_false);
	test.registerTest("stdout", &test_stdout);
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

