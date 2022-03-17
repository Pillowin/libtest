/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 21:27:10 by agautier          #+#    #+#             */
/*   Updated: 2022/03/17 17:47:31 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
#define TEST_HPP

#include <stdint.h>
#include <string>
#include <vector>

#define RESET  "\033[0m"
#define RED	   "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"

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

typedef bool (*t_test)(void);
typedef std::vector< std::pair< std::string, t_test > >::const_iterator
	t_test_it;

class Test {
	public:
		Test(char const* name = "Test");
		Test(Test const& rhs);

		~Test(void);

		Test& operator=(Test const& rhs);

		void registerTest(std::string const name, t_test test);
		bool run(void);

	private:
		std::vector< std::pair< std::string, t_test > > tests;
		const std::string								name;
		uint8_t											total;
		uint8_t											passed;

		bool exec_test(t_test t) const;
		void print_result(t_test_it it);
		void print_total_result(void) const;
};

#endif
