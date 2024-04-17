# Dos Serial Video

A monochrome 320x200 video stream communication over serial port between a server and a Dos PC.

## Table of Contents

- [About](#about)
- [Features](#features)
- [Tested-On](#Tested-On)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## About

This software is created out of pure curiosity and it is made just for fun. Made with the help of Chat Gpt 3.5, This simple software plays a low performance 320x200 monochrome video stream on a dos machine recieved through serial port. I created it for increasing the usability of DOS PCs, embracing retro futuristic ideas, and satisfying my curiosity about live video streaming over serial communication. The transmitter of the stream can be used on any platform which has a serial port and is compatible with python 3.11.9 or above, obs studio (any version which has obs virtual camera), and open cv 4.9.0.

How it works, the obs studio captures some source and sends it through obs virtual cam. In the transmitter script, open cv opens a webcam (for our case - obs virtual camera) and processes it into serial data which is sent over serial. The serial data recieved into the Dos system through serial port and interpreted and displayed on the screen.

P.S. 
Personally, I am just a Bachelors of computer application graduate, I have a very little knowledge about dos programming, python and open cv. But I have a obsession for retrofuturism which sparked from movies (like blade runner) and that creativity lead to this basic app. If I had more knowledge I would make a 256 color floyd steinberg dithered video app, but I dont know much about open cv 😞.

![Preview Image]((https://github.com/rajeevt2001/Dos-serial-video/blob/main/preview%20image.png))

## Features
- Reciever Compiled using borland turbo c.
- 320x200 monochrome video (black and white only, no greyscale).
- Around 0.5 fps at 115200 baud.
- Port and baud on transmitter can be changed.
- Port can be changed in reciever with the fixed baud rate of 115200.

## Tested On

- Transmitter tested on Windows 11 22H2 with python 3.11.9.
- Reciever Tested on Dos ver 7.1 in DOSBox-X version 2023.05.01 (Will test on real machine later). Cpu speed is set to 
- Communication established using com0com virtual serial port.

## Getting Started

There are 2 folders one is the transmitter and one is the reciever. 
On Transmitter side:
- Place the transmitter python script folder on the server or computer which is the source of the video.
- Launch obs studio, select your video source on scene and start the virtual camera (I have set the camera option to scene).
- Go to the transmitter folder and execute the transmitter with the command: python transmitter.py

connect the serial port cable between both computers (you can use virtual serial or real serial port).

On reciever side:
- Place the reciever code on the Dos machine, you can do this by copying it into a floppy disk (although floppy is rarely used today) or in an sd card and use a sd card floppy emulator on the dos machine. Or if you are on dos box, mount the reciever folder.
- Go to the reciver folder and run the command: reciever.exe
- If somehow the exe is not working, you can recompile the cpp file (located in the same folder) using turbo c compiler and then execute the exe with the same command.

## Note
- If using Dos-Box set cpu speed to ~4595 cycles (386 DX 25 Mhz) otherwise the output will not be good as the cpu lower than that will not cope up with this high baud rate
- By looking at the first point, it means that the minimum cpu requirement for the real machine is intel 386 DX or equivalent.

## Usage

Example usage of this software:
- Monitor a cctv surveillance camera on a dos computer with the help of a video transmitter server (Probably a raspberry pi).
- Watch any other slower stream on the dos computer with the help of a video transmitter server (Probably a raspberry pi).

## Contributing

I don't know about the mechanisms of the contribution. If anyone sees this program, please make it better than me.

## License

GNU General Public License (GPL)
