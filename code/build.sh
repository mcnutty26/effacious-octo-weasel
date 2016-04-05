#!/bin/sh

cd liboctodrone
make clean all
cd ../liboctodronecomms
make clean all
cd ../programs
make clean all
cd ../simulations
make clean all
