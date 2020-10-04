# Sensor Communication #

### This repository contains class implementations that enable the easy use of frequently used hardware pins/communication protocols ###

#### This is currently a WIP (working on testing) ####

The following classes have been implemented (The last 2 being thread safe implementations):
1. LegacyGpio (using `sysfs`)
2. I2C
3. PWM
4. Serial
5. SafeLegacyGpio (using `sysfs`)
6. SafeI2C

General frequently used functions added in utils.cpp, including a wrapper function for calling system functions.

Please make sure you have the permissions to use the pins when using these scripts. If you are using Ubuntu run:

`sudo usermod -a -G dialout $USER`

#### Quickstart ####
    git clone https://github.com/vss2sn/sensor_communication_base_scripts.git  
    cd sensor_communication_base_scripts
    mkdir -p build && cd build  
    cmake ..
    make -j4
    ./communicate

#### TODO ####
1. Add examples
2. Add documentation
3. Add tests and their counterparts (Arduino)
4. New Gpio wrapper class
