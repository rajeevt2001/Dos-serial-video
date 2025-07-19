// ver 1.0.1
// need to add option to change baud rate
// enable mouse
// add settings and close button which hides automatically
// transmitter can set text mode and graphics mode by using the unused bit

#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#define COM1_BASE_ADDRESS 0x3F8
#define COM2_BASE_ADDRESS 0x2F8

int comPort = COM1_BASE_ADDRESS;

void initSerial() {
    // Set up communication parameters
    outportb(comPort + 1, 0x00);    // Disable interrupts
    outportb(comPort + 3, 0x80);    // Enable DLAB (set baud rate divisor)

    // Set divisor to 1 for 115200 baud rate
    // Base clock frequency (115200) / baud rate (115200) = 1
    outportb(comPort + 0, 0x01);    // Set divisor to 1 (lo byte)
    outportb(comPort + 1, 0x00);    // Set divisor to 1 (hi byte)

    outportb(comPort + 3, 0x03);    // 8 bits, no parity, one stop bit
    outportb(comPort + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outportb(comPort + 4, 0x0B);    // IRQs enabled, RTS/DSR set

    // Test the serial port by echoing characters
    outportb(comPort + 4, 0x1E);    // Loopback mode
    outportb(comPort, 'A');         // Send character 'A'
    while ((inportb(comPort + 5) & 0x20) == 0); // Wait for transmit buffer to be empty
    if (inportb(comPort) != 'A')   // Check received character
        printf("Serial port test failed.\n");
    else
        printf("Serial port test passed.\n");
    outportb(comPort + 4, 0x0F);    // Normal mode
}

char read_serial() {
    while ((inp(comPort + 5) & 1) == 0); // Wait for data to be ready to read
    return inp(comPort);
}

void setMode13() {
    union REGS inregs, outregs;

    inregs.h.ah = 0x00; // Set video mode function
    inregs.h.al = 0x13; // Mode 13 (320x200 256-color mode)

    int86(0x10, &inregs, &outregs);
}

void setModeText() {
    union REGS inregs, outregs;

    inregs.h.ah = 0x00; // Set video mode function
    inregs.h.al = 0x03; // Text mode (80x25)

    int86(0x10, &inregs, &outregs);
}

void setPix(int x, int y, int colorIndex) {
    unsigned char far *videoBuffer = (unsigned char far *)0xA0000000L; // Far pointer to video memory
	
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        unsigned int offset = y * SCREEN_WIDTH + x; // Calculate offset in video memory

        videoBuffer[offset] = colorIndex; // Set pixel color at the specified coordinates
    }
}

int main() {
    char userChoice;

    cout << "Select COM port (1 or 2): ";
    cin >> userChoice;

    if (userChoice == '1') {
        comPort = COM1_BASE_ADDRESS;
    }
	else if (userChoice == '2') {
        comPort = COM2_BASE_ADDRESS;
    }
	else {
        cout << "Using COM1 by default." << endl;
        comPort = COM1_BASE_ADDRESS;
	}
	initSerial();
    setMode13(); 
	cout << "Waiting for data";
    char a;
    int x = 0, y = 0;
    int colorIndex;
    int bit1, bit2, bit3, bit4, bit5;
    int sync;

    while (1) {
        a = read_serial();
        sync = (a >> 6) & 0x01; // Check the 7th bit for synchronization
        if (sync == 1) {
			// Clear the graphics buffer (optional)
            //memset((unsigned char far *)0xA0000000L, 0, SCREEN_WIDTH * SCREEN_HEIGHT);
            x = 0;
            y = 0;
        } else {
            for (; y < 200; y++) {
                for (x = 0; x < 320; x += 5) {  // Increment by 5 pixels for each byte received
					a = read_serial();
                    // Extract the bits from the received character
                    bit1 = a & 0x01;
                    bit2 = (a >> 1) & 0x01;
                    bit3 = (a >> 2) & 0x01;
                    bit4 = (a >> 3) & 0x01;
					bit5 = (a >> 4) & 0x01;
                    // Convert bits to color index
                    int colorIndex1 = (bit1 == 1) ? 15 : 0;
                    int colorIndex2 = (bit2 == 1) ? 15 : 0;
                    int colorIndex3 = (bit3 == 1) ? 15 : 0;
                    int colorIndex4 = (bit4 == 1) ? 15 : 0;
					int colorIndex5 = (bit5 == 1) ? 15 : 0;
                    // Set pixels
                    setPix(x, y, colorIndex5);
                    setPix(x + 1, y, colorIndex4);
                    setPix(x + 2, y, colorIndex3);
                    setPix(x + 3, y, colorIndex2);
                    setPix(x + 4, y, colorIndex1);
                }
                // If synchronization marker is received, break out of the loop
                if (sync == 1) {
                    break;
                }
            }
            // Reset x to 0 after processing each row
            x = 0;
        }

        // Check for user input to exit the loop
        if (kbhit()) {
            break;
        }
    }

    // Restore text mode before exiting
    setModeText();
    return 0;
}

