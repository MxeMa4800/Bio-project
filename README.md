# Stegosaurus Project
## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Installation](#installation)

   - [Prerequisites](#prerequisites)

   - [Software Installation Steps](#software_installation_steps)

   - [Hardware Installation Steps](#prerequisites)
4. [Robot Design](#robot_design)
5. [Code](#code)
6. [Configuration and Customization](#contributing)
7. [License](#license)
8. [Authors and Contributors](#authors)


## Installation 
In order to ensure a smooth start, this section includes a list of prerequisites and instructions for installing the required hardware and software for the robot project.

### **Prerequisites**

1. Operating System 
   - Windows

      ![Static Badge](https://img.shields.io/badge/Windows-%23E6E6FA?style=for-the-badge&logo=windows&logoColor=%23FFFAFA&labelColor=%230099FF)
      ![Static Badge](https://img.shields.io/badge/Version%20-%2011_or_laster%20-%230099FF)

2. Software 
- Arduino IDE (for programming Arduino)

   ![Static Badge](https://img.shields.io/badge/Arduino_ide%20-%20%20%23009999?style=for-the-badge&logo=arduino&logoColor=%23009999&logoSize=auto&labelColor=%23F0F8FF)
   ![Static Badge](https://img.shields.io/badge/2.3.2-%23009999?label=Version)
   ![Static Badge](https://img.shields.io/badge/build-%20https%3A%2F%2Fwww.arduino.cc%2Fen%2Fsoftware%20-009999?label=Downlond&link=https%3A%2F%2Fwww.arduino.cc%2Fen%2Fsoftware)

- SolidWorks (for robot design)

   ![Static Badge](https://img.shields.io/badge/SOLIDWORK%20-%20%23FF3333%09?style=for-the-badge&logo=dassaultsystemes&labelColor=%23BEBEBE) 
   ![Static Badge](https://img.shields.io/badge/2022-%23FF0000?label=Version&link=https%3A%2F%2Fwww.arduino.cc%2Fen%2Fsoftware)
   ![Static Badge](https://img.shields.io/badge/build-%20https%3A%2F%2Fwww.solidworks.com%2Fsw%2Fsupport%2Fdownloads.htm%20-FF0000?label=Downlond&link=https%3A%2F%2Fwww.solidworks.com%2Fsw%2Fsupport%2Fdownloads.htm)


 3. Hardware




### **Software Installation Steps**
1. Install Arduino IDE
- The Arduino IDE can be downloaded and installed from the [Arduino website](https://www.arduino.cc/en/software/).
- Launch the Arduino IDE and add the required libraries, like Math and [SCServo](https://github.com/IS2511/SCServo/blob/master/SCSCL.cpp). 
   
   **Zip file installation for the library**
   - Get the Library from here in a zip file. 

      <img src="image/1.jpg" width="400" height="250">

   - Open the Arduino IDE program, go to Sketch > Include Library > Add .ZIP Library, then pick the file that you downloaded.

      <img src="image/2.jpg" width="400" height="250">

    **Installing more Arduino libraries**

     - Open the Arduino IDE program, go to Sketch > Include Library > Manage Libraries.
     
        <img src="image/3.png" width="400" height="250">

    - In the search box, type the name of the desired library. Click More info to see how to utilize it. Click the Install button in order to install.
      
      <img src="image/4.jpg" width="400" height="250">

2. Install SolidWorks
- SolidWorks can be downloaded and installed from the [SolidWorks official website](https://www.solidworks.com/sw/support/downloads.htm).
- Launch SolidWorks and confirm that all required modules, including Part, Simulation and Electrical, are installed.

### **Hardware Installation Steps**
1. Assemble the Robot Structure
- The robot's primary structure can be constructed using the assembly guide found in the SolidWorks files.
- Place electrical in the designated locations.   
   <img src="image/image-4.png" width="55" height="60">[รูปAssemble แบบที่เห็นวางติด อิเล็กไว้ตรงไหนบ้าง] 

2. Connect the Electrical Circuit

- Wires between the microcontroller(Arduino uno r4), servo, sensors, and batteries should be installed and connected using the electrical circuit schematic.
- Make sure every connection is safe and secure.

   <img src="image/image-4.png" width="55" height="60">[รูปแผงวงจร] 

## Robot Design
### **Main Structure**
- Robots with sturdy, lightweight main structures can move with greater agility. The body is made of PLA and wood.

 <img src="image/image-4.png" width="55" height="60">[ภาพถ่ายหุ่นเปลือย ไร้หนัง] 

### **Joints and Actuators**

- The robot has wood for its joints and legs. To further aid secure the armor to the ground, rubber was also used to protect the feet.

<img src="image/image-4.png" width="55" height="60">[วิดีโอตอนขาขยับ] 

## Codeอาจจะไม่ใส่

## Configuration and Customization
-วิธีการตั้งค่าและปรับแต่งหุ่นยนต์ตามความต้องการ 

- ค่าพารามิเตอร์ที่สามารถปรับเปลี่ยนได้ ลิงค์กับ excel

## License

- เอกสารสูตรที่เอามา
## Authors and Contributors
- ข้อมูลเกี่ยวกับผู้พัฒนาและผู้มีส่วนร่วมในโปรเจกต์ 
