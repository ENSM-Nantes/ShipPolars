#!/bin/bash

sshpass -p "linuxRPIpwd" scp $1 flo@rpi5-somos-1.local:/home/flo/bc/resources/nc/polar.nc 

echo $?
