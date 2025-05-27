import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import easygui

path = easygui.fileopenbox("Select a csv file to load", "Load from csv", "data.csv", ["*.csv"])
dframe = pd.read_csv(path)

print(dframe)

fig, ax = plt.subplots()

ax.set(xlabel='time', ylabel='mV', title='Acquisition')
ax.plot(dframe['time'], dframe['captured'])
plt.show()