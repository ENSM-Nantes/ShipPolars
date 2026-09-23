# ShipPolars
 - Bridge Command sends the ship's polar file to ShipPolars when it is launched. It is stored as `polar/polar.nc`
   and loaded automatically; the "Polar Selection" tab shows whether a polar has been received and when.

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
