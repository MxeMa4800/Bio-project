# Stegosaurus Project


## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Configuration](#configuration)
6. [Contributing](#contributing)
7. [License](#license)
8. [Acknowledgements](#acknowledgements)

## <img src="image/image-7.png" width="25" height="25">  Installation 
In order to ensure a smooth start, this section includes a list of prerequisites and instructions for installing the required hardware and software for the robot project.

### Prerequisites
#### 1. Operating System 
- Windows

   ![Static Badge](https://img.shields.io/badge/Windows-%23E6E6FA?style=for-the-badge&logo=windows&logoColor=%23FFFAFA&labelColor=%230099FF)
   ![Static Badge](https://img.shields.io/badge/Version%20-%2011_or_laster%20-%230099FF)

#### 2. Software 
- Arduino IDE (for programming Arduino)

   ![Static Badge](https://img.shields.io/badge/Arduino_ide%20-%20%20%23009999?style=for-the-badge&logo=arduino&logoColor=%23009999&logoSize=auto&labelColor=%23F0F8FF)
   ![Static Badge](https://img.shields.io/badge/2.3.2-%23009999?label=Version)
   ![Static Badge](https://img.shields.io/badge/Downlond-https%3A%2F%2Fwww.arduino.cc%2Fen%2Fsoftware-%23009999)

- SolidWorks (for robot design)

   ![Static Badge](https://img.shields.io/badge/SOLIDWORK%20-%20%23FF3333%09?style=for-the-badge&logo=dassaultsystemes&labelColor=%23BEBEBE) 
   ![Static Badge](https://img.shields.io/badge/2022-%23FF0000?label=Version&link=https%3A%2F%2Fwww.arduino.cc%2Fen%2Fsoftware)
   ![Static Badge](https://img.shields.io/badge/Downlond-https%3A%2F%2Fwww.solidworks.com%2Fsw%2Fsupport%2Fdownloads.htm-%23FF0000)

#### 3. Hardware




### Software Installation Steps
1. Install Arduino IDE
- The Arduino IDE can be downloaded and installed from the [Arduino website](https://www.arduino.cc/en/software/).
- Launch the Arduino IDE and add the required libraries, like Math and [SCServo](https://github.com/zompin/SCServoBothMode). 

2. Install SolidWorks
- SolidWorks can be downloaded and installed from the [SolidWorks official website](https://www.solidworks.com/sw/support/downloads.htm).
- Launch SolidWorks and confirm that all required modules, including Part, Simulation and Electrical, are installed.

### Hardware Installation Steps
1. Assemble the Robot Structure
- The robot's primary structure can be constructed using the assembly guide found in the SolidWorks files.
- Place electrical in the designated locations.


   
   <img src="image/image-4.png" width="55" height="60">[รูปAssemble แบบที่เห็นวางติด อิเล็กไว้ตรงไหนบ้าง] 

2. Connect the Electrical Circuit

- Use the electrical circuit diagram to install and connect wires between the microcontroller, motors, sensors, and battery
- Ensure all connections are secure and safe
Install Sensors:

Install the various sensors on the robot in their designated positions
Connect the sensors to the microcontroller and verify the functionality of each sensor
Configure Communication between Hardware and Software:

Use Arduino IDE or Python to write programs that control the motors and sensors
Test the communication between hardware and software to ensure proper control functionality