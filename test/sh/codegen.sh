#!/usr/bin/env bash

$PWD/brainwhack --codegen $PWD/brainfuck/hello_world.bf &> /dev/null

if [[ "$?" -eq 0 ]]; then
    gcc $PWD/brainfuck/hello_world.c
    OUT=$($PWD/a.out)

    if [[ "$OUT" == "Hello World!" ]]; then
        rm $PWD/a.out
        rm $PWD/brainfuck/hello_world.c

        printf "\e[1m\033[32mTEST PASS\e[0m: \t\t\tCode generation\n"
        exit 0
    fi
    rm $PWD/a.out
fi
rm $PWD/brainfuck/hello_world.c

printf "\e[1m\033[31mTEST FAIL\e[0m: \t\t\tCode generation\n"
exit 125

