# -*- coding: utf-8 -*-
import serial
import time
import pandas as pd
import matplotlib.pyplot as plt

# 配置串口（根据实际COM端口修改，例如'COM3'或'/dev/ttyUSB0'）
PORT = 'COM3'  # 替换为您的实际端口
BAUD_RATE = 115200

try:
    # 初始化串口连接
    ser = serial.Serial(PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {PORT} at {BAUD_RATE} baud.")
except serial.SerialException as e:
    print(f"Serial connection error: {e}")
    exit()
except AttributeError:
    print("Error: 'serial' module not found or misconfigured. Please ensure pyserial is installed (pip install pyserial) and check for file name conflicts (e.g., serial.py).")
    exit()

# 创建CSV文件
csv_file = f"dht11_data_{time.strftime('%Y%m%d_%H%M%S')}.csv"
with open(csv_file, 'w') as f:
    f.write("Timestamp,Temperature(C),Humidity(%)\n")

# 数据列表用于绘图
timestamps = []
temperatures = []
humidities = []

# 测试持续时间（例如60秒，根据需要调整）
start_time = time.time()
duration = 60  # 秒

try:
    while time.time() - start_time < duration:
        line = ser.readline().decode('utf-8').strip()
        if line:
            print(line)  # 打印到控制台用于调试
            if "Temperature: " in line:
                # 解析行数据（格式："Temperature: 25.C, Humidity: 60%"）
                try:
                    parts = line.split(", ")
                    temp_str = parts[0].split(": ")[1].split(".C")[0]
                    hum_str = parts[1].split(": ")[1].split("%")[0]
                    temp = float(temp_str)
                    hum = float(hum_str)
                    
                    # 保存到CSV
                    timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                    with open(csv_file, 'a') as f:
                        f.write(f"{timestamp},{temp},{hum}\n")
                    
                    # 追加到列表用于绘图
                    timestamps.append(time.time() - start_time)
                    temperatures.append(temp)
                    humidities.append(hum)
                except (ValueError, IndexError) as e:
                    print(f"Error parsing data: {e}, Line: {line}")
        time.sleep(0.5)  # 与Arduino延迟匹配
except KeyboardInterrupt:
    print("\nStopped by user.")
finally:
    ser.close()
    print("Serial connection closed.")

# 绘制数据
if temperatures and humidities:
    df = pd.DataFrame({
        'Time (s)': timestamps,
        'Temperature (C)': temperatures,
        'Humidity (%)': humidities
    })
    
    plt.figure(figsize=(10, 6))
    plt.plot(df['Time (s)'], df['Temperature (C)'], label='Temperature (C)', color='red')
    plt.plot(df['Time (s)'], df['Humidity (%)'], label='Humidity (%)', color='blue')
    plt.xlabel('Time (s)')
    plt.ylabel('Value')
    plt.title('DHT11 Temperature and Humidity Over Time')
    plt.legend()
    plt.grid(True)
    plt.show()
    
    print(f"Data saved to {csv_file}")
else:
    print("No data collected.")