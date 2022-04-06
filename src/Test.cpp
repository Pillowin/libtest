/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 21:26:26 by agautier          #+#    #+#             */
/*   Updated: 2022/03/30 17:33:04 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

/*
**	Default constructor.
*/
Test::Test(char const* name) : name(name), total(0), passed(0) {}

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
	this->tests.push_back(std::pair< std::string const, t_test >(name, test));
}

/*
**	Execute test function in forked process.
*/
bool Test::exec_test(t_test t) const {
	alarm(TIMEOUT);
	if (t)
		exit(t());
	exit(false);
}

/*
**	Print test function result.
*/
void Test::print_result(t_test_it it) {
	pid_t pid;
	int	  wstatus;

	pid = wait(&wstatus);
	if (pid == ERROR)
		return;

	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus)) {
		std::cout << COLOR_GREEN << "  ✓ " << COLOR_RESET << it->first << std::endl;
		this->passed += 1;
	} else if (WIFEXITED(wstatus)) {
		std::cout << COLOR_RED << "  x " << COLOR_RESET << it->first << std::endl;
	}

	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGSEGV) {
		std::cout << COLOR_YELLOW << "  [SEGV] " << COLOR_RESET << it->first << std::endl;
	} else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGBUS) {
		std::cout << COLOR_YELLOW << "  [BUS ERROR] " << COLOR_RESET << it->first
				  << std::endl;
	} else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGABRT) {
		std::cout << COLOR_YELLOW << "  [SIGABRT] " << COLOR_RESET << it->first
				  << std::endl;
	} else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGFPE) {
		std::cout << COLOR_YELLOW << "  [SIGFPE] " << COLOR_RESET << it->first << std::endl;
	} else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGPIPE) {
		std::cout << COLOR_YELLOW << "  [SIGPIPE] " << COLOR_RESET << it->first
				  << std::endl;
	} else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGILL) {
		std::cout << COLOR_YELLOW << "  [SIGILL] " << COLOR_RESET << it->first << std::endl;
	} else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGALRM) {
		std::cout << COLOR_YELLOW << "  [TIMEOUT] " << COLOR_RESET << it->first
				  << std::endl;
	}

	this->total += 1;
}

/*
**	Print total tests result.
*/
void Test::print_total_result(void) const {
	if (this->passed != this->total) {
		std::cout << COLOR_RED << "[KO] " << static_cast< unsigned >(this->passed)
				  << "/" << static_cast< unsigned >(this->total) << " passed :("
				  << COLOR_RESET << std::endl;
	} else {
		std::cout << COLOR_GREEN << "[OK] " << static_cast< unsigned >(this->passed)
				  << "/" << static_cast< unsigned >(this->total) << " passed :)"
				  << COLOR_RESET << std::endl;
	}
}

/*
**	Run all registered tests.
*/
bool Test::run(void) {
	t_test_it it;
	pid_t	  pid;

	std::cout << this->name << std::endl;

	for (it = this->tests.begin(); it != this->tests.end(); ++it) {
		pid = fork();
		if (pid == ERROR) {
			return (false);
		} else if (pid == CHILD) {
			t_test test = it->second;
			this->tests.~vector();
			this->name.~basic_string();
			this->exec_test(test);
		} else {
			this->print_result(it);
		}
	}

	this->print_total_result();
	return (this->total == this->passed);
}

/*
**	Assignment operator.
*/
Test& Test::operator=(Test const& rhs) {
	if (this == &rhs)
		return (*this);
	this->tests	 = rhs.tests;
	this->total	 = rhs.total;
	this->passed = rhs.passed;
	return (*this);
}
