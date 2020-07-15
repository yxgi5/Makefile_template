CC 			= g++ -g
CC_FLAGS 		= -Wall -pedantic

.PHONY			: all

all			:
				$(MAKE) --directory lib-src
				$(MAKE) --directory src

clean			:
				$(MAKE) --directory src clean
				$(MAKE) --directory lib-src clean
				rm -f *.o $(OBJS) ./lib/*
