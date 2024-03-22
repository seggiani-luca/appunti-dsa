import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

data = pd.read_csv('data.csv')
grouped_data = data.groupby('TRESHOLD')

plt.figure(figsize=(12,6))

for treshold, group in grouped_data:
    hsv_color = (treshold / 30, 1, 1)
    rgb_color = mcolors.hsv_to_rgb(hsv_color)
    plt.plot(group['SIZE'], group ['TIME'], label=f'{treshold}', color=rgb_color)

plt.xlabel('Size')
plt.ylabel('Time')
plt.legend(loc='right', bbox_to_anchor=(1.1,0.5))
plt.show()
