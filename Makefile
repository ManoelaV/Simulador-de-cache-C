CC = gcc
	CFLAGS = -Iinclude - Wall - Wextra - g SRC = src / main.c src / cache.c src / utils.c OBJ = $(SRC :.c =.o)
													 EXEC = cache_simulator

																	all : $(EXEC)

																			  $(EXEC) : $(OBJ)
																							$(CC) -
																						o $ @$ ^

															%.o : %.c $(CC) $(CFLAGS) - c $ < -o $ @

																								  clean : rm -
																								  f $(OBJ) $(EXEC)

																									  .PHONY : all clean