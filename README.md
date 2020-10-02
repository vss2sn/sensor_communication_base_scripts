Base Scripts

This repository holds scripts that contain frequently used functions which help jump start a project. This repository currently includes base scripts for the following different hardware pins/communication protocols:
1. GPIO
2. I2C
3. PWM
4. Serial

General frequently used functions added in utils.cpp, including a wrapper function for calling system functions.

Please make sure you have the permissions to use the pins when using these scripts. If you are using Ubuntu run:
sudo usermod -a -G dialout $USER
