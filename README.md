# Airport Project Cadmium
|  Linux | Windows| ESP32 | MSP432 |
|:--|:--|:--|:--|
|:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|:question:|
## Introduction
This repository contains a cadmium v2 simulation project of an airport. This project includes atomic models of a control tower, queue, runway, selector,
storage, exit and coupled models of hangar and airport. Project also contains log output displaying simulation results.

## Dependencies
This project assumes that you have Cadmium installed in a location accessible by the environment variable $CADMIUM.
_This dependency would be met by default if you are using the ARSLAB servers. To check, try `echo $CADMIUM` in the terminal_

## Build
To build this project, run:
```sh
source build_sim.sh
```
__NOTE__: Everytime you run build_sim.sh, the contents of `build/` and `bin/` will be replaced.

## Execute
To run the project, run:
```sh
./bin/sample_project
```
