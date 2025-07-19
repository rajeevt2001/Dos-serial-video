# ver 1.0.1
# add feature to enable text and graphics mode of the reciever
import cv2
import numpy as np
import serial
  
def convert_frame_to_binary(frame):
    # Convert the frame to grayscale
    grayscale_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # Apply binary thresholding to create a binary image
    _, binary_frame = cv2.threshold(grayscale_frame, 100, 255, cv2.THRESH_BINARY)
    # Convert binary pixels to 0s and 1s
    binary_pixels = (binary_frame / 255).astype(np.uint8)
    # Flatten the binary pixel array
    binary_array = binary_pixels.flatten()
    return binary_array

def quantize_colors(frame):
    # Convert frame to grayscale
    grayscale_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Apply binary thresholding to create black and white image
    _, binary_frame = cv2.threshold(grayscale_frame, 100, 255, cv2.THRESH_BINARY)
    
    # Convert binary frame back to BGR (3 channels)
    quantized_frame = cv2.cvtColor(binary_frame, cv2.COLOR_GRAY2BGR)
    
    return quantized_frame

def send_pix_to_serial(binary_data, serial_port):
    packed_byte = 0  # Initialize the packed byte
    bit_count = 0    # Initialize the bit count
    
    # Iterate over the binary data
    for pixel in binary_data:
        # Add the current pixel value to the packed byte
        packed_byte |= pixel << (4 - bit_count)  # Pack 6 pixels into a byte
        
        # Increment the bit count
        bit_count += 1
        
        # If 6 pixels have been packed or all pixels have been processed
        if bit_count == 5 or len(binary_data) == 5:
            # Convert packed byte to ASCII character and send it to the serial port
            char_value = chr(packed_byte)  # Convert to ASCII character ('0' to '9')
            serial_port.write(char_value.encode())  # Send the character over serial
            
            # Reset packed byte and bit count for the next byte
            packed_byte = 0
            bit_count = 0
    
    # Send the end of frame indicator (sync marker)
    serial_port.write(chr(64).encode())
    print('sync sent')

def main():
    Port = 'COM6'
    BaudRate = 115200
    cam_index = 0
    
    user_input = input(f"Enter COM Port (e.g., COM6) [Default: {Port}]: ")
    Port = user_input if user_input else Port  # Use default port if user doesn't enter anything

    user_baud_input = input(f"Enter Baud Rate (e.g., 9600, 115200) [Default: {BaudRate}]: ")
    BaudRate = int(user_baud_input) if user_baud_input else BaudRate  # Use default baud rate if user doesn't enter anything

    user_cam_index = input(f"Enter Camera Index (e.g., 0) [Default: {cam_index}]: ")

    # Open serial port
    serial_port = None
    try:
        serial_port = serial.Serial(Port, BaudRate)
        print(f"Serial port opened on {Port} at {BaudRate} baud rate")
    except serial.SerialException as e:
        print(f"Error opening serial port: {e}")
        return

    # Open the default webcam (usually index 0)
    cap = cv2.VideoCapture(int(user_cam_index) if user_cam_index else cam_index)
    if not cap.isOpened():
        print("Error: Failed to open webcam")
        if serial_port:
            serial_port.close()
        return

    try:
        print("Transmission started")
        while True:
            # Capture frame-by-frame
            ret, frame = cap.read()

            if not ret:
                print("Error: Failed to capture frame")
                break

            frame = cv2.resize(frame, (320, 200))

            # Quantize the colors of the frame using the custom palette
            quantized_frame = quantize_colors(frame)

            # Get binary pixel coordinates
            binary_data = convert_frame_to_binary(quantized_frame)

            # Send binary pixel coordinates to serial port
            send_pix_to_serial(binary_data, serial_port)

            # Check for the 'q' key to quit
            key = cv2.waitKey(1)
            if key == ord('q'):
                break
    finally:
        # Release the webcam and close the window
        cap.release()
        cv2.destroyAllWindows()
        
        # Close the serial port
        if serial_port:
            serial_port.close()

if __name__ == "__main__":
    main()
