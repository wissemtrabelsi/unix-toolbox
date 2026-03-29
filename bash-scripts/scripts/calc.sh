#!/bin/bash

# Calculator - supports ADD, SUB, MULT, DIV, MOD, EXP
if [ $# -ne 3 ]; then
    echo "Usage: $0 <num> <operator> <num>" >&2
    echo "Operators: ADD, SUB, MULT, DIV, MOD, EXP" >&2
    exit 1
fi

case $2 in
    ADD)  echo "$(($1 + $3))" ;;
    MULT) echo "$(($1 * $3))" ;;
    SUB)  echo "$(($1 - $3))" ;;
    DIV)  echo "$(($1 / $3))" ;;
    MOD)  echo "$(($1 % $3))" ;;
    EXP)  echo "$(($1 ** $3))" ;;
    *)
        echo "Error: invalid operator '$2'" >&2
        exit 1
        ;;
esac