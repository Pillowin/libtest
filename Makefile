# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agautier <agautier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 21:10:22 by agautier          #+#    #+#              #
#    Updated: 2022/01/04 19:46:54 by agautier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S			=	src/
I			=	header/
O			=	obj/
D			=	dep/

NAME		=	libtest.a
SRC			=	$(wildcard $S*.cpp)

OBJ			=	$(SRC:$S%.cpp=$O%.o)
DEP			=	$(SRC:$S%.cpp=$D%.d)

CXX			=	clang++

CXXFLAGS	+=	-I$I
CXXFLAGS	+=	-Wall -Wextra -Werror -std=c++98 -pedantic-errors

RM			=	/bin/rm -f
RMDIR		=	/bin/rm -Rf

.PHONY: all clean fclean re

all: $(NAME)

$O:
	@mkdir -p $@

$(OBJ): | $O

$(OBJ): $O%.o: $S%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$D:
	@mkdir -p $@

$(DEP): | $D

$(DEP): $D%.d: $S%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MM -MF $@ -MT "$O$*.o $@" $<

$(NAME): $(OBJ)
	ar rcs $@ $^

test: $(NAME)
	@$(CXX) $(CXXFLAGS) main.cpp $(NAME)
	@./a.out

clean:
	$(RMDIR) $(wildcard $(NAME).dSYM)
	$(RMDIR) $O
	$(RM) $(wildcard $(DEP))
	$(RMDIR) $D

fclean: clean
	$(RM) $(NAME)
	@$(RM) a.out

re: fclean
	$(MAKE)

-include $(DEP)
