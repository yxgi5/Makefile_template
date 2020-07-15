#######################
# Makefile
#######################
# source object target
SOURCE := func.cpp
OBJS   := func.o
TARGET := libfunc.so
 
# compile and lib parameter
CC      := g++
LIBS    :=
LDFLAGS := .
DEFINES :=
INCLUDE := .
CFLAGS  := 
CXXFLAGS:= -Wall -g -pedantic -shared -fPIC
 
# link
$(TARGET):$(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^
	cp $(TARGET) ../lib/
 
# compile
$(OBJS):%.o: %.cpp
	$(CC) $(CXXFLAGS) -I$(INCLUDE) -c $<
 
# clean
clean:
	rm -fr *.o
	rm -fr $(TARGET)
