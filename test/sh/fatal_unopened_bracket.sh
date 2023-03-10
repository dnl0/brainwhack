#!/usr/bin/env bash

$PWD/../brainwhack $PWD/brainfuck/fatal_unclosed_bracket.bf &> /dev/null

if [[ "$?" -ne 0 ]]; then
    printf "\e[1m\033[32mTEST PASS\e[0m: \t\t\tUnopened bracket\n"
    exit 0
else
    printf "\e[1m\033[31mTEST FAIL\e[0m: \t\t\tUnopened bracket\n"
    exit 125
fi

