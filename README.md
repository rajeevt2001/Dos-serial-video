# Dos Serial Video

A monochrome 320x200 video stream communication over a serial port between a server and a DOS PC.

## About

This software was created out of pure curiosity, and it is made just for fun. Made with the help of ChatGPT 3.5 and Gemini for Version 2, this simple software plays a low-performance 320x200 monochrome video stream from a DOS machine over the serial port. I created it to improve the usability of DOS PCs, embrace retro-futuristic ideas, and satisfy my curiosity about live video streaming over serial communication. The transmitter of the stream can be used on any platform that has a serial port and is compatible with Python 3.14 or above, OBS Studio (any version that has OBS virtual camera), and OpenCV 4.9.0.

How it works, the OBS Studio captures a source and sends it through OBS Virtual Cam. In the transmitter script, OpenCV opens a webcam (for our case, OBS virtual camera) and processes it into serial data, which is sent over serial. The serial data received into the Dos system through serial port and interpreted and displayed on the screen.

P.S. 
Personally, I am just a Bachelor's of Computer Application graduate, I have very little knowledge about DOS programming, Python, and OpenCV. But I have an obsession for retrofuturism, which sparked from movies (like Blade Runner) and that creativity led to this basic app. If I had more knowledge, I would make a 256 color floyd steinberg dithered video app, but I don't know much about OpenCV 😞.


![Preview Image](https://github.com/rajeevt2001/Dos-serial-video/blob/main/v2-screenshot.png)

## Features
- Receiver compiled using Borland Turbo C.
- 320x200 monochrome video (black and white only, no greyscale).
- Greater than or equal to 0.5 fps at 115200 baud.
- The port on the transmitter can be changed.
- The port can be changed in the receiver with the fixed baud rate of 115200.

## Tested On

- Transmitter tested on Windows 11 22H2 with Python 3.14
- Receiver tested on DOS ver 7.1 in DOSBox-X version 2023.05.01 (Will test on real machine later). CPU speed is 486 DX2 at 66 MHz
- Communication established using com0com virtual serial port.

## Getting Started

Download the Zip from the releases section. Extract the contents of the zip file.
There are 2 folders, one is the transmitter, and the other is the receiver. 
On the transmitter side:
- Place the transmitter Python script folder on the server or computer that is the source of the video.
- Launch OBS Studio, select your video source on the scene and start the virtual camera (I have set the camera option to scene).
- Go to the transmitter folder and execute the transmitter with the command: python transmitter.py

Connect the serial port cable between both computers (you can use a virtual serial or real serial port).

On the receiver side:
- Place the receiver code on the DOS machine. You can do this by copying it into a floppy disk (although floppy is rarely used today) or into an SD card and using an SD card floppy emulator on the DOS machine. Or if you are on DOSBox, mount the receiver folder.
- Go to the receiver folder and run the command: receiver.exe
- If somehow the exe is not working, you can recompile the cpp file (located in the same folder) using Turbo C compiler and then execute the exe with the same command.

## Note
- If using Dos-Box, set the CPU speed to 486 DX2 at 66 MHz; otherwise, the output will not be good as the CPU lower than that will not cope with this high baud rate
- By looking at the first point, it means that the minimum CPU requirement for the real machine is Intel 486 DX2 or equivalent.

## Usage

Example usage of this software:
- Monitor a CCTV surveillance camera on a DOS computer with the help of a video transmitter server (Probably a Raspberry Pi).
- Watch any other slower stream on the DOS computer with the help of a video transmitter server (Probably a Raspberry Pi).

## Contributing

I don't know about the mechanisms of the contribution. If anyone sees this program, please make it better than what I made.
