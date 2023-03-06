#!/usr/bin/env bash

COMMAND=$($PWD/brainwhack $PWD/brainfuck/print_seven.bf)

if [ "$COMMAND" == "7" ]; then
    printf "\e[1m\033[32mTEST PASS\e[0m: \t\t\tPrint seven\n"
    exit 0
else
    printf "\e[1m\033[31mTEST FAIL\e[0m: \t\t\tPrint seven\n"
    exit 125
fi

