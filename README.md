# PolarManagement
 - Send polar file from Shiplify.io to BridgeCommand 
 - Read a polar from a nc file and display it. The polar is refreshing from BridgeCommand according to "speed through water", "apparent wind speed" and "apparent wind direction".
   The position ship on the polar is alreadey displayed.

## Requirements
libgtk-4-dev libenet-dev libnetcdf-dev

## Build
```g++ *.cpp *.c -o PolarManager `pkg-config --cflags --libs gtk4` -lm -lnetcdf -lenet```
   
## Use
Put a polar file, named polar.nc in the same folder as the binary
./PolarManager

## Example
![alt text](https://github.com/ENSM-Nantes/PolarInject/blob/main/res/screenshot.png)
