TAGET = test

OBJS = main.o
#	用下面方法输出变量及行位置是极好的
$(info OBJS=$(OBJS))
$(warning OBJS=$(OBJS))
$(warning SHELL=$(SHELL))
$(warning CURDIR=$(CURDIR))

$(TAGET):$(OBJS)
#	@echo $(SHELL)
#	@echo $(CURDIR)
#	@env
# @	不回显命令本身
	@echo "开始生成最终执行文件，请稍候..."
#	echo可以输出的有颜色字体等
	@echo -e "Full Version is:\033[31m\033[1m v1.0 \033[0m";
	g++ main.o -o test
#	@g++ main.o -o test

#%.o: %.cpp
main.o:main.cpp
	g++ -c main.cpp -o main.o
#	@g++ -c main.cpp -o main.o
# @	@g++ main.o -o test和g++ main.o -o test的区别，是不在make的时候显示出来
#
#	g++ -c $< -o $@
#	@g++ -c $< -o $@
# $<	是第一个依赖对象
# $@	表示本地目标对象

.PHONY : clean
clean:
	rm -rf main.o test
#   $(RM) $(OBJS) $(TAGET)

.PHONY : debug
debug:
	$(info OBJS=$(OBJS))
	@echo "OBJS="$(OBJS)

