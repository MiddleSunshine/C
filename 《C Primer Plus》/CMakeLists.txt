cmake_minimum_required(VERSION 3.15)
project(C C)

set(CMAKE_C_STANDARD 99)

add_executable(C main.c public.h private.h public2.h DataStructure/List.h const.h DataStructure/Stack.h DataStructure/StackExample.h DataStructure/Queue.h function.c)