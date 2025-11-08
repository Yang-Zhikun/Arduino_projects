# -*- coding: utf-8 -*-
import serial
import time
import pandas as pd
import matplotlib.pyplot as plt

PORT = 'COM3'
BAUD_RATE = 115200

try:
    ser = serial.Serial(PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {PORT} at {BAUD_RATE} baud.")
except serial.SerialException as e:
    print(f"Serial connection error: {e}")
    exit()
except AttributeError:
    print("Error: 'serial' module not found or misconfigured.")
    exit()

# 创建CSV文件
csv_file = f"dht11_data_{time.strftime('%Y%m%d_%H%M%S')}.csv"
with open(csv_file, 'w') as f:
    f.write("Timestamp,Temp_1(C),Humi_1(%),Temp_2(C),Humi_2(%),Avg_Temp(C),Avg_Humi(%)\n")

# 数据列表用于绘图
timestamps = []
avg_temps = []
avg_humis = []

start_time = time.time()

###################################################################################
duration = 700                                 # 运行时间，单位秒    
###################################################################################


try:
    while time.time() - start_time < duration:
        line = ser.readline().decode('utf-8').strip()
        # print(f"Received: {line}")
        if line:
            #print(line)  # 打印到控制台用于调试
            if "Temp_1: " in line and "Humi_1: " in line and "Temp_2: " in line and "Humi_2: " in line and "Avg Temp: " in line and "Avg Humi: " in line:
                try:
                    three_parts = line.split("; ")
                    #  part_1:  three_parts[0]内容:    Temp_1: 28 C, Humi_1: 71%
                    temp1_str = three_parts[0].split(": ")[1] .split(" C")[0]
                    humi1_str = three_parts[0].split(": ")[2] .split("%")[0]
                    temp1 = int(temp1_str)
                    humi1 = int(humi1_str)
                    # part_2:  three_parts[1]
                    temp2_str = three_parts[1].split(": ")[1] .split(" C")[0]
                    humi2_str = three_parts[1].split(": ")[2] .split("%")[0]
                    temp2 = int(temp2_str)
                    humi2 = int(humi2_str)
                    # part_3:  three_parts[2]
                    avg_temp_str = three_parts[2].split(": ")[1] .split(" C")[0]
                    avg_humi_str = three_parts[2].split(": ")[2] .split("%")[0]
                    avg_temp = float(avg_temp_str)
                    avg_humi = float(avg_humi_str)
                    print(f"Parsed data - Temp1: {temp1} C, Hum1: {humi1}%, Temp2: {temp2} C, Hum2: {humi2}%, Avg Temp: {avg_temp} C, Avg Humi: {avg_humi}%")
                    # 保存到CSV
                    timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                    with open(csv_file, 'a') as f:
                        f.write(f"{timestamp},{temp1},{humi1},{temp2},{humi2},{avg_temp},{avg_humi}\n")
                    # 保存到列表用于绘图
                    timestamps.append(time.time() - start_time)
                    avg_temps.append(avg_temp)
                    avg_humis.append(avg_humi)
                except (ValueError, IndexError) as e:
                    print(f"Error parsing data: {e}. Line: {line}")
            else:
                print(f"Unexpected line format: {line}")

except KeyboardInterrupt:
    print("\nStopped by user.")
finally:
    ser.close()
    print("Serial connection closed.")


# 绘制数据
if avg_temps and avg_humis:
    df = pd.DataFrame({
        'Time (s)': timestamps,
        'Temperature (C)': avg_temps,
        'Humidity (%)': avg_humis
    })
    
    plt.figure(figsize=(10, 6))
    plt.plot(df['Time (s)'], df['Temperature (C)'], label='Temperature (C)', color='red')
    plt.plot(df['Time (s)'], df['Humidity (%)'], label='Humidity (%)', color='blue')
    plt.xlabel('Time (s)')
    plt.ylabel('Value')
    plt.title(' DHT11 Temperature and Humidity Over Time')
    plt.legend()
    plt.grid(True)
    plt.show()
    
    print(f"Data saved to {csv_file}")
else:
    print("No data collected.")