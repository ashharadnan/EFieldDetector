from serial.tools.list_ports import comports
from serial import Serial
from icecream import ic
import struct

import _thread

import numpy as np
import pandas as pd
import time

import easygui


def stop_check():
    global acquireFlag
    print("Press Q/q to end")
    i = None
    while i != "q":
        i = input("Press q to quit: ")
        ic(i)
    acquireFlag = False


coms = comports()
print("Ports: ")
for ix, comp in enumerate(coms):
    ic(ix, comp.description)

ser = Serial(coms[int(input("Enter comport index: "))].device, 230400)

acquireFlag = True
_thread.start_new_thread(stop_check, ())

ser.reset_input_buffer()
ser.reset_output_buffer()

tStart = None
series = None

while acquireFlag:
    msg = []
    while (len(msg) != 8):
        msg = ser.read_until(b'XXX\n')
    st = struct.unpack('<fxxxx', msg)

    if tStart is None:
        tStart = time.time()
    t = (time.time() - tStart)

    cap = st[0]
    ic(cap)

    if series is None:
        series = np.array([t, cap])
    else:
        new = np.array([t, cap])
        series = np.vstack((series, new))

dframe = pd.DataFrame(series, columns=["time", "captured"])
path = easygui.filesavebox("Select a location to save csv file", "Save as CSV", "data.csv", ["*.csv"])
dframe.to_csv(path, index=False)

ser.close()