#!/usr/bin/env bash

FAIL=0
SUCC=0

printf "\t\t\e[1mrunning tests\e[0m\n\n"

for script in sh/*.sh; do
    bash "$script"
    if [[ "$?" -ne 0 ]]; then
        ((++FAIL))
    else
        ((++SUCC))
    fi
done

printf "\n\e[1mpassed tests: \033[32m$SUCC\e[0m"
if [[ "$FAIL" -gt 0 ]]; then
    printf "\n\e[1mfailed tests: \033[31m$FAIL\e[0m"
else
    printf "\n\e[1mfailed tests: \033[32m$FAIL\e[0m"
fi

