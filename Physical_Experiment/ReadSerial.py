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

temp1_list = []
hum1_list = []
temp2_list = []
hum2_list = []

# 一直读取数据，并画图实时显示
while True:
    line = ser.readline().decode('utf-8').strip()
    if line:
        #print(line)  # 打印到控制台用于调试
        if "Temperature1: " in line and "Humidity1: " in line:
            # 解析行数据（格式："Temperature1: 25.C, Humidity1: 60%"）
            try:
                parts = line.split(", ")
                temp_str = parts[0].split(": ")[1].split(".C")[0]
                hum_str = parts[1].split(": ")[1].split("%")[0]
                temp = int(temp_str)
                hum = int(hum_str)
                
                # 打印解析结果
                print(f"Parsed Temperature1: {temp} C, Humidity1: {hum} %")
                # # 保存到列表
                # temp1_list.append(temp)
                # hum1_list.append(hum)
            except (ValueError, IndexError) as e:
                print(f"Error parsing data1: {e}, Line: {line}")

        if "Temperature2: " in line and "Humidity2: " in line:
            # 解析行数据（格式："Temperature2: 25.C, Humidity2: 60%"）
            try:
                parts = line.split(", ")
                temp_str = parts[0].split(": ")[1].split(".C")[0]
                hum_str = parts[1].split(": ")[1].split("%")[0]
                temp = int(temp_str)
                hum = int(hum_str)
                
                # 打印解析结果
                print(f"Parsed Temperature2: {temp} C, Humidity2: {hum} %")
                # # 保存到列表
                # temp2_list.append(temp)
                # hum2_list.append(hum)
            except (ValueError, IndexError) as e:
                print(f"Error parsing data2: {e}, Line: {line}")
        
        print()
        
        

    time.sleep(0.1)  # 避免CPU占用过高
