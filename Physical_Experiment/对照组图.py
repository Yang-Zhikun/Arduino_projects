import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('对照组.txt', encoding='utf-8', sep=',')
print(df)

time = range(len(df))
plt.figure(figsize=(10, 6))
plt.plot(time, df['Temperature'], label='Temperature (C)', color='red')
plt.step(time, df['Humidity'], label='Humidity (%)', color='blue')
plt.xlabel('Time')
plt.ylabel('Value')
plt.title('DHT11 Temperature and Humidity Over Time')
plt.legend()
plt.grid(True)
plt.show()