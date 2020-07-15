#######################
# Makefile
#######################
# source object target
SOURCE := func.cpp
OBJS   := func.o
TARGET := libfunc.a
 
# compile and lib parameter

AR      := ar
CC      := g++
LIBS    :=
LDFLAGS := .
DEFINES :=
INCLUDE := .
CFLAGS  := 
CXXFLAGS:= -Wall -g -pedantic -shared -fPIC
 
# link
$(TARGET):$(OBJS)
	$(AR) -r $@ $^
	cp $(TARGET) ../lib/
 
# compile
$(OBJS):%.o: %.cpp
	$(CC) $(CXXFLAGS) -I$(INCLUDE) -c $<
 
# clean
clean:
	rm -fr *.o
	rm -fr $(TARGET)
