#!/bin/sh
g++ main.cpp x509.cpp -std=c++11 -o x509

./x509 cer/icytown.cer
