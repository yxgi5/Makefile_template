TARGETS=server client sendfile recvfile

CC = gcc
LD = ld
OBJCOPY = objcopy
SIZE = size
CC_FLAGS = -g -Wall -pedantic
CC_FLAGS += -Wl,-Map=$(TARGET).map
CL_FLAGS = -L../lib -ludt-c -lpthread
#CL_FLAGS = ./libudt-c.so -lpthread
INC = ../include/udt.h

SRC = server.c \
	client.c \
	sendfile.c \
	recvfile.c
	
#$(warning $$SRC is $(SRC))
OBJS = $(addsuffix .o, $(basename $(SRC)))
#$(warning $$OBJS is $(OBJS))
#OBJS = server.o \
#	client.o \
#	sendfile.o \
#	buffer.o \
#	recvfile.o

all:$(TARGETS)

$(TARGETS):%:%.o
	$(CC) $(CC_FLAGS) -I. $< -o $@ $(CL_FLAGS)
#$(TARGETS):$(OBJS)
#	@echo "开始生成最终执行文件，请稍候..."
#	@echo "Full Version is:\033[31m\033[1m v1.0 \033[0m";
#	$(CC) $(CC_FLAGS) $(OBJS) -o $@ $(CL_FLAGS)

$(OBJS):%.o:%.c $(INC) Makefile
#	$(CC) $(CC_FLAGS) -I../src -c $<
#%.o: %.c
#	$(CC) $(CC_FLAGS) -c $< -o $@ $(CL_FLAGS)
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGETS) $(TARGETS).map

debug:
	@echo $(OBJS)
	$(warning is $(OBJS))
