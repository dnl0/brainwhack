#!/usr/bin/env bash

COMMAND=$($PWD/../brainwhack $PWD/brainfuck/print_twelve.bf)

if [ "$COMMAND" == "12" ]; then
    printf "\e[1m\033[32mTEST PASS\e[0m: \t\t\tPrint twelve\n"
    exit 0
else
    printf "\e[1m\033[31mTEST FAIL\e[0m: \t\t\tPrint twelve\n"
    exit 125
fi

