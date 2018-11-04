#!/bin/sh

gcc main.c des.c debug.c -std=c11 -o des

./des
