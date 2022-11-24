---
parent: Harmony 3 driver and system service application examples for SAM RH71 family
title: Parallel PROM SST38 driver - SST38VF6401 memory Read Write
has_children: false
has_toc: false
---

[![MCHP](https://www.microchip.com/ResourcePackages/Microchip/assets/dist/images/logo.png)](https://www.microchip.com)

# Parallel PROM SST38 driver - SST38VF6401 memory Read Write

This example application shows how to use the Parallel PROM SST38 driver to perform read and write operations on a SST38VF6401 memory.

## Description

This example uses the Parallel PROM SST38 driver to communicate with the external SST38VF6401 parallel memory to perform write and read operations in Bare-Metal environment.

## Downloading and building the application

To clone or download this application from Github, go to the [main page of this repository](https://github.com/Microchip-MPLAB-Harmony/core_apps_sam_rh71) and then click Clone button to clone this repository or download as zip file.
This content can also be downloaded using content manager by following these [instructions](https://github.com/Microchip-MPLAB-Harmony/contentmanager/wiki).

Path of the application within the repository is **apps/driver/parallel_prom/sst38_read_write/firmware** .

To build the application, refer to the following table and open the project using its IDE.

| Project Name      | Description                                    |
| ----------------- | ---------------------------------------------- |
| sam_rh71_ek.X | MPLABX project for [SAM RH71 TFBGA Evaluation Kit](https://www.microchip.com/en-us/development-tool/SAMRH71F20-TFBGA-EK) |
|||

## Setting up the hardware

The following table shows the target hardware for the application projects.

| Project Name| Board|
|:---------|:---------:|
| sam_rh71_ek.X | [SAM RH71 TFBGA Evaluation Kit](https://www.microchip.com/en-us/development-tool/SAMRH71F20-TFBGA-EK) |
|||

### Setting up [SAM RH71 TFBGA Evaluation Kit](https://www.microchip.com/en-us/development-tool/SAMRH71F20-TFBGA-EK)

- Connect mini USB to DEBUG_USB connector to use the embedded PkoB4 debugger.

## Running the Application

1. Build and program the application using the IDE
2. The LED0 is turned ON when the value read from EEPROM matches with the written data.
