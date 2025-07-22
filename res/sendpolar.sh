#!/bin/bash

#Send to all rpis
sshpass -p "linuxRPIpwd" scp $1 flo@rpi5-somos-1.local:/home/flo/bc/resources/nc/polar.nc 

#Copy nc file here for Polar Reader
cp $1 .

echo $?
