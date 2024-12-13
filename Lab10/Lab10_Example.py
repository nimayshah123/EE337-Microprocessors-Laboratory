# Import all the required libraries
import serial
import numpy as np
import matplotlib.pyplot as plt
import time

# Use your specified COM port and baud rate
ser = serial.Serial("COM13", 4800)

# Modify these values to whatever is required (for generating input signal)
frequency = 100  # Hz
amplitude = 0.5  # Volt?
duration = 0.1   # second
sampling_rate = 1000  # samples per second

# Generate time array
t = np.linspace(0, duration, int(sampling_rate * duration), endpoint=False)

# Generate sine wave
sine_wave = amplitude * np.sin(2 * np.pi * frequency * t)

# Adding 1000 mV (or 1 V) offset and converting float to int
#(because transferring integers in mV is easier)
for i in range(len(sine_wave)):
    sine_wave[i] = int(1000 + 1000*sine_wave[i])
sine_int = np.array(sine_wave, dtype=np.int32)

# Conditioning the input signal such that each sample is a string of 4 characters
# (this will make receiving the samples and processing them easier in Pt-51)
x = [str(i) for i in sine_int] 
for i in range(len(x)):
    if len(x[i]) == 1:
        x[i] = '000' + x[i]
    elif len(x[i]) == 2:
        x[i] = '00' + x[i]
    elif len(x[i]) == 3:
        x[i] = '0' + x[i]
# x is the input array that will be sent to Pt-51

y = []
# y is the output array that will store the results obtained from Pt-51


# Send input signal serially and receive output serially
for i in range(int(sampling_rate * duration)):
    # This command will encode string into byte array and send 4 bytes (4 characters) serially to Pt-51
    d = ser.write(x[i].encode()) # ignore d (it just returns number of bytes transferred i.e 4)
    print("Sent sample " + str(i))
    time.sleep(0.1) # just a small delay to ensure smooth functioning
    
    # This command will append list y with decoded version of whatever data is sent back from Pt-51
    y.append(int(ser.readline().decode()))
    print("Received sample " + str(i))
    print()

# Plotting to visualize input and output
plt.plot(t, sine_int)
plt.plot(t, np.array(y))
plt.legend(["Input signal", "Output signal"])
plt.ylabel("Amplitude")
plt.xlabel("Time")
plt.show()
