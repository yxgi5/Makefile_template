TARGET=main

CC = gcc
LD = ld
OBJCOPY = objcopy
SIZE = size
CFLAGS =  -g -Wall
CFLAGS += -Wl,-Map=$(TARGET).map
LDFLAGS	= 

#SRC := $(wildcard *.c)   
#  = 是最基本的赋值
#  := 是覆盖之前的值
#  ?= 是如果没有被赋值过就赋予等号后面的值
#  += 是添加等号后面的值
#
SRC = main.c dummy.c
#$(warning $$SRC is $(SRC))
OBJS = $(addsuffix .o, $(basename $(SRC)))
#$(warning $$OBJS is $(OBJS))

.PHONY : all
#all:convert_main test_main
all:$(TARGET)

$(TARGET):$(OBJS)
	@echo "开始生成最终执行文件，请稍候..."
#	@echo "Full Version is:\033[31m\033[1m v1.0 \033[0m";
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY : clean
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).map

.PHONY : debug
debug:
	@echo $(OBJS)
	$(warning is $(OBJS))
