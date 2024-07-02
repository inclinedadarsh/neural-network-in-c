#!/bin/sh

set -xe

cc -Wall -Wextra -o linear_line linear_line.c
cc -Wall -Wextra -o gate gate.c -lm
