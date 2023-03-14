#!/usr/bin/env bash

COMMAND=$($PWD/../brainwhack $PWD/brainfuck/newbie.bf)

if [ "$COMMAND" == "Hello" ]; then
    printf "\e[1m\033[32mTEST PASS\e[0m: \t\t\tNewbie\n"
    exit 0
else
    printf "\e[1m\033[31mTEST FAIL\e[0m: \t\t\tNewbie\n"
    exit 125
fi

