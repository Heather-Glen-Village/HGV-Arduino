import numpy as np


def floatConvertion(unit16_1, unit16_2):
    uint16_array = np.array([unit16_1,unit16_2], dtype=np.uint16)
    byte_array = uint16_array.tobytes()
    float_value = np.frombuffer(byte_array, dtype=np.float32)[0]
    return float_value