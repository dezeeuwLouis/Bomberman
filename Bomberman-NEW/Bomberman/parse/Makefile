##
## Makefile for libParse in /root/Desktop/projetlib/ovre_j/libParse
##
## Made by OVRE Jordan
## Login   <ovre_j@etna-alternance.net>
##
## Started on  Sun Apr 26 21:55:40 2015 OVRE Jordan
## Last update Tue Apr 28 22:36:27 2015 OVRE Jordan
##
CC	=	gcc
NAME	=	libParse
SRC	=	main.c \
		check_arg.c \

OBJ	=	$(SRC:%.c=%.o)
CFLAGS	=	-W -Werror -Wall
RM	=	rm -f

all :		libParse.a

libParse.a:	$(OBJ)
		ar r libParse.a *.o
		ranlib libParse.a

clean :
		$(RM) *.o
fclean :		clean
		$(RM) libParse.a
re : 		fclean all
