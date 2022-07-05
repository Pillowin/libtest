#pragma once

#include <stdint.h>
#include <string>
#include <vector>

#define COLOR_RESET  "\033[0m"
#define COLOR_RED	 "\033[31m"
#define COLOR_GREEN  "\033[32m"
#define COLOR_YELLOW "\033[33m"

#define CHILD	0
#define ERROR	-1
#define TIMEOUT 10

#define ltest_assert(expr)                                                     \
	if ((expr) == true) {                                                      \
		return true;                                                           \
	}                                                                          \
	return false;

#define ltest_assert_n(expr)                                                   \
	if ((expr) != true) {                                                      \
		return true;                                                           \
	}                                                                          \
	return false;

#define ltest_assert_eq(expr1, expr2)                                          \
	if ((expr1) == (expr2)) {                                                  \
		return true;                                                           \
	}                                                                          \
	return false;

#define ltest_assert_ne(expr1, expr2)                                          \
	if ((expr1) != (expr2)) {                                                  \
		return true;                                                           \
	}                                                                          \
	return false;

typedef bool (*t_test_fn)(void);
typedef struct s_test
{
	std::string name;
	t_test_fn	fn;
	std::string expected_output;
	std::string filename;
	int			fd;
}	t_test;
typedef std::vector< t_test >::iterator t_test_it;

class Test {
	public:
		Test(char const* name = "Test");
		Test(Test const& rhs);

		~Test(void);

		Test& operator=(Test const& rhs);

		void registerTest(std::string const name, t_test_fn fn, char const* expected_output = NULL);
		bool run(void);

	private:
		std::vector< t_test >	tests;
		const std::string		name;
		uint8_t					total;
		uint8_t					passed;

		bool exec_test(t_test_it test) const;
		void print_result(t_test_it it);
		void print_total_result(void) const;
};
