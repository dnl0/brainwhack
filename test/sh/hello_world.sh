#!/usr/bin/env bash

COMMAND=$($PWD/../brainwhack $PWD/brainfuck/hello_world.bf)

if [ "$COMMAND" == "Hello World!" ]; then
    printf "\e[1m\033[32mTEST PASS\e[0m: \t\t\tHello world\n"
    exit 0
else
    printf "\e[1m\033[31mTEST FAIL\e[0m: \t\t\tHello world\n"
    exit 125
fi

