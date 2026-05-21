# ShipPolars
 - Choose the polar vessel to read. The polar had to be present also in Bridge-Command, polar available for now :
   - Copenhagen Ferry with one flettner rotor from NorsePower (30x5)
   - SC-Connector with two flettner rotors from NorsePower (30x5)	
   - Fake cargo Maersk with two flettner rotors (18x3).
   
 - Read a polar from a nc file and display it. The polar is refreshing from BridgeCommand according to "speed through water", "apparent wind speed" and "apparent wind direction".
   The position ship on the polar is alreadey displayed.

## Requirements
libgtk-4-dev libenet-dev libnetcdf-dev

## Build
```./build.sh```
   
## Use
 - Copy/paste the polar file corresponding to the scenario, rename it in polar.nc into the same folder as the binary
```./PolarManager```

## Example
![alt text](https://github.com/ENSM-Nantes/PolarInject/blob/main/res/ShipPolars_PS.png)
![alt text](https://github.com/ENSM-Nantes/PolarInject/blob/main/res/ShipPolars_PR.png)
![alt text](https://github.com/ENSM-Nantes/PolarInject/blob/main/res/ShipPolars_SM.png)
