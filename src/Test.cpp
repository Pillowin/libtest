#include "Test.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
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
**	Destructorg
*/
Test::~Test(void) {}

/*
**	Register a test function to tests list.
*/
void Test::registerTest(std::string const name, t_test_fn fn, char const* expected_output) {
	t_test test = {
		name,
		fn,
		expected_output ? std::string(expected_output) : std::string(),
		std::string("/tmp/libtest_XXXXXX"),
		-1
	};
	this->tests.push_back(test);
}

/*
**	Execute test function in forked process.
*/
bool Test::exec_test(t_test_fn fn) const {
	alarm(TIMEOUT);
	if (fn)
		exit(fn());
	exit(false);
}

/*
**	Print test function result.
*/
void Test::print_result(t_test_it test) {
	pid_t pid;
	int	  wstatus;

	pid = wait(&wstatus);
	if (pid == ERROR)
		return;

	close(test->fd);
	if (!test->expected_output.empty()) {
		std::ifstream tmpFile(test->filename.c_str());
		std::stringstream buffer;
		buffer << tmpFile.rdbuf();
		std::string const str = buffer.str();
		if (test->expected_output.compare(str) != 0) {
			std::cout << COLOR_RED << "  x " << COLOR_RESET << test->name << std::endl;
			this->total += 1;
			return ;
		}
	}

	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus)) {
		std::cout << COLOR_GREEN << "  ✓ " << COLOR_RESET << test->name << std::endl;
		this->passed += 1;
	} else if (WIFEXITED(wstatus)) {
		std::cout << COLOR_RED << "  x " << COLOR_RESET << test->name << std::endl;
	}

	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGSEGV) {
		std::cout << COLOR_YELLOW << "  [SEGV] " << COLOR_RESET << test->name << std::endl;
	} else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGBUS) {
		std::cout << COLOR_YELLOW << "  [BUS ERROR] " << COLOR_RESET << test->name
				  << std::endl;
	} else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGABRT) {
		std::cout << COLOR_YELLOW << "  [SIGABRT] " << COLOR_RESET << test->name
				  << std::endl;
	} else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGFPE) {
		std::cout << COLOR_YELLOW << "  [SIGFPE] " << COLOR_RESET << test->name << std::endl;
	} else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGPIPE) {
		std::cout << COLOR_YELLOW << "  [SIGPIPE] " << COLOR_RESET << test->name
				  << std::endl;
	} else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGILL) {
		std::cout << COLOR_YELLOW << "  [SIGILL] " << COLOR_RESET << test->name << std::endl;
	} else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGALRM) {
		std::cout << COLOR_YELLOW << "  [TIMEOUT] " << COLOR_RESET << test->name
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
	pid_t	  pid;

	std::cout << this->name << std::endl;

	for (t_test_it test = this->tests.begin(); test != this->tests.end(); ++test) {
		int fd = -1;
		if (!test->expected_output.empty()) {
			fd = mkstemp(&(*test->filename.begin()));
			if (fd == -1)
				return (false);
		}
		pid = fork();
		if (pid == ERROR) {
			return (false);
		} else if (pid == CHILD) {
			dup2(fd, STDOUT_FILENO);
			this->tests.~vector();
			this->name.~basic_string();
			this->exec_test(test->fn);
		} else {
			this->print_result(test);
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
