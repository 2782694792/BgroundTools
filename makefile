#指定编译器
CC = g++

# #找出当前目录下，所有的源文件（以.cpp结尾）
# SRCS := $(shell find ./* -type f | grep '\.cpp' | grep -v 'main\.cpp')
# $(warning SRCS is ${SRCS})

# #确定cpp源文件对应的目标文件
# OBJS := $(patsubst %.cpp, %.o, $(filter %.cpp, $(SRCS)))
# $(warning OBJS is ${OBJS})

#编译选项
CFLAGS = -g -O2 -Wall -Werror -Wno-unused -std=c++11 -pthread -fexec-charset=UTF-8
$(warning CFLAGS is ${CFLAGS})

#找出当前目录下所有的头文件
INCLUDE = -I./include

SRC_MAIN = ./src/main_multi_thread.cpp
OBJ_MAIN = ${SRC_MAIN:%.cpp=%.o}
# OBJ_MAIN = ${SRC_MAIN}
EXE_MAIN = main_multi_thread

target: ./bin/${EXE_MAIN}

# $(EXE_MAIN): $(OBJ_MAIN) $(OBJS)
$(EXE_MAIN): $(OBJ_MAIN)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDE)
# $@ 表示目标文件
# $^ 表示所有的依赖文件
# $< 表示第一个依赖文件
# $? 表示比目标还要新的依赖文件列表

clean:
	# del /q /s ${EXE_MAIN}.exe 
#	rm -f ${OBJS} ${OBJ_MAIN} ${EXE_MAIN}

%.o: %.cpp
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@
