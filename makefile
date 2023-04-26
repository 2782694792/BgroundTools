ROOT = E:\workspace\BgroundTools

INCLUDE = $(ROOT)\include
CMAKE_SOURCE_DIR = $(ROOT)\src
CMAKE_BINARY_DIR = $(ROOT)\build
BIN = $(ROOT)\bin

SHELL = cmd.exe

#编译选项
CFLAGS = -g -O2 -Wall -Werror -Wno-unused -std=c++11

CMAKE_COMMAND = E:\Dev\cmake-3.25.1-windows-x86_64\bin\cmake.exe

all: run_BgTools_execl
run_BgTools_execl:main_multiProc.cpp
	BIN\BgTools_execl

