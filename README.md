# SPI EEPROM writing and reading data
## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)

## General info
This project write and read data from 25C080DS21230D EEPROM memory using self-made SPI protocol.
<br>File containing code is `SPI_EEPROM_READER_WRITER/SPI_EEPROM_READER_WRITER.ino`

### How it works in action ###

The program saves the value in specified memory cell of EEPROM and then reads it and prints it in serial monitor.<br>
Value increases every iteration.<br>
Output:<br>
<br>
![Bez tytułu](https://user-images.githubusercontent.com/75041222/225675973-77472abc-df22-4447-8c6d-8f58fe146435.png)


### Schematic of project
<img src="https://user-images.githubusercontent.com/75041222/225677113-1c13e46f-47b2-4f30-9bbc-737df8084062.png" width="467" height="486">

## Technologies
Project is created with:
* C++
* Fritzing

Electric components used:
* Arduino 101
* 25C080DS21230D EEPROM
* 9x wires
