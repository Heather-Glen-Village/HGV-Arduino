import numpy as np

# Combine the two uint16_t values into a byte array
# Create a numpy array of the uint16_t values
uint16_array = np.array([28836,16709], dtype=np.uint16)

# Convert the uint16 array to bytes
byte_array = uint16_array.tobytes()

# Use numpy to interpret the byte array as a float
float_value = np.frombuffer(byte_array, dtype=np.float32)[0]

print("The converted float value is:", float_value)
