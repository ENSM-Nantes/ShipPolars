# ShipPolars
 - Choose the polar vessel to read. The polar had to be present also in Bridge-Command, polar available for now :
   - Copenhagen Ferry with one flettner rotor from NorsePower (30x5)
   - SC-Connector with two flettner rotors from NorsePower (30x5)	
   - Fake cargo Maersk with two flettner rotors (18x3)
   - Fake KVLCC2 cargo with four flettner rotors (24x4)
   - Fake KVLCC2 cargo with five flettner rotors (30x5)
   
 - Read a polar from a nc file and display it. The polar is refreshing from BridgeCommand according to "speed through water", "apparent wind speed" and "apparent wind direction".
   The position ship on the polar is alreadey displayed.

- nc files have been generated thanks to [Shiplify](https://shiplify.io/index) online tool.

- Wiki : https://somos-project.fr/dokuwiki/doku.php?id=start 

## Requirements
libgtk-4-dev libenet-dev libnetcdf-dev

## Build
```./build.sh```
   
## Use
```./bin/ShipPolars```

## Example
![alt text](https://github.com/ENSM-Nantes/ShipPolars/blob/main/res/ShipPolars_PS.png)
![alt text](https://github.com/ENSM-Nantes/ShipPolars/blob/main/res/ShipPolars_PR.png)
![alt text](https://github.com/ENSM-Nantes/ShipPolars/blob/main/res/ShipPolars_SM.png)
