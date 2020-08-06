[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# I2C driver synchronous - I2C EEPROM

This example application shows how to use the I2C driver in synchronous mode to perform operations on the EEPROM.

## Description

This example uses the I2C driver in synchronous mode to communicate with the EEPROM to perform write and read operations in RTOS environment. This application uses I2C driver to read and write data from an AT24CM02 EEPROM device.

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/core_apps_sam_rh71) and then click Clone button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/driver/i2c/sync/i2c_eeprom/firmware** .

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| sam_rh71_ek_freertos.X | MPLABX project for SAM RH71 Evaluation Kit |
|||

## Setting up the hardware

The following table shows the target hardware for the application projects.

| Project Name| Board|
|:---------|:---------:|
| sam_rh71_ek_freertos.X | SAM RH71 Evaluation Kit |
|||

### Setting up SAM RH71 Evaluation Kit

- To run the demo, the following additional hardware are required:
  - One [EEPROM 3 Click](https://www.mikroe.com/eeprom-3-click) board
  - One [mikroBUS Xplained Pro](https://www.microchip.com/developmenttools/ProductDetails/ATMBUSADAPTER-XPRO) boards

- Connect [mikroBUS Xplained Pro board](https://www.microchip.com/developmenttools/ProductDetails/ATMBUSADAPTER-XPRO) to J24 header
- Plug the [EEPROM 3 click Board](https://www.mikroe.com/eeprom-3-click) into the MikroBus socket of the [mikroBUS Xplained Pro board](https://www.microchip.com/developmenttools/ProductDetails/ATMBUSADAPTER-XPRO)
- Connect the J15 USB port on the board to the computer using a mini USB cable
- Connect debugger to the 20-pin JTAG header J33

## Running the Application

1. Build and program the application using its IDE
2. LED indicates success or failure:
    - The LED is turned ON when the value read from the EEPROM matched with the written value

Refer to the following table for LED name:

| Board | LED Name |
| ----- | -------- |
|  SAM RH71 Evaluation Kit | LED0 |
|||
