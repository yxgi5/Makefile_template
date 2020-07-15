# 增加调试信息 或者 打印变量的值

$(warning SHELL=$(SHELL))

$(warning ****)

$(info OSTYPE=$(OSTYPE))

$(info ****)

$(error "error: this will stop the compile")

这个会停止掉

echo只能在target：后面的语句中使用，且前面是个TAB, 可以用@echo


# 报错调试
比如

make UNIT_TESTING=-DUNIT_TESTING test 报错

那么通过下面命令查看为啥出错

remake -x -d UNIT_TESTING=-DUNIT_TESTING test

make -d --debug=v V=s UNIT_TESTING=-DUNIT_TESTING test

