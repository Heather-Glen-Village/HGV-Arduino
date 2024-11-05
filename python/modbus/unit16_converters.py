import numpy as np
from struct import pack, unpack

def floatConvertion(unit16_1, unit16_2):
    uint16_array = np.array([unit16_1,unit16_2], dtype=np.uint16)
    byte_array = uint16_array.tobytes()
    float_value = np.frombuffer(byte_array, dtype=np.float32)[0]
    return float_value



def floatToUint16(val):
    uint16_list = []
    # Pack each float as two uint16 values
    float_bytes = pack('f', val)
    uint16_vals = unpack('HH', float_bytes)
    uint16_list.extend(uint16_vals)
    return uint16_list[0], uint16_list[1]