/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agautier <agautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 21:27:10 by agautier          #+#    #+#             */
/*   Updated: 2021/12/21 23:14:47 by agautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
#define TEST_HPP

#include <list>
#include <stdint.h>
#include <string>

#define assert(expr)                                                           \
	if (expr) {                                                                \
		return true;                                                           \
	}                                                                          \
	return false;

#define assert_eq(expr1, expr2)                                                \
	if ((expr1) == (expr2)) {                                                  \
		return true;                                                           \
	}                                                                          \
	return false;

#define assert_ne(expr1, expr2)                                                \
	if ((expr1) != (expr2)) {                                                  \
		return true;                                                           \
	}                                                                          \
	return false;

typedef bool (*t_test)(void);

class Test {
	public:
		Test(char const* name = "Test");
		Test(Test const& rhs);

		~Test(void);

		Test& operator=(Test const& rhs);

		void registerTest(t_test test);
		bool run(void) const;

	private:
		std::list< t_test > tests;
		const std::string name;
};

#endif
