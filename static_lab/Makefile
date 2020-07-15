#######################
# Makefile
#######################
# source object target
SOURCE := main.cpp
OBJS   := main.o
TARGET := main
 
# compile and lib parameter
CC      := g++
LD 	:= ld
LIB	:= 
LDFLAGS := ./lib/libfunc.a
DEFINES :=
INCLUDE := -I./lib-src
CFLAGS  := 
CXXFLAGS:= -g -Wall -pedantic
CXXFLAGS += -Wl,-Map=$(TARGET).map

all:$(TARGET)
	

# link
# -L加-l形式的，要export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
# 如果直接给 .so 文件就可以在so文件所在目录下运行
# 比如 g++ -o hello_cpp main.cpp ./libcontrolcan.so  -lpthread 
$(TARGET):%:%.o
	$(MAKE) --directory lib-src
	$(CC) $(CXXFLAGS) $(INCLUDE) $^ -o $@ $(LIB) $(LDFLAGS)
 
# compile
$(OBJS):%.o:%.cpp
	$(CC) $(CXXFLAGS) $(INCLUDE) -c $< -o $@
 
# clean
clean:
	$(MAKE) --directory lib-src clean
	rm -fr $(TARGET) $(OBJS) $(TARGET).map
	rm -rf lib/*
