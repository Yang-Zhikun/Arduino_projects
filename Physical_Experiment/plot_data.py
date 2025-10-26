# -*- coding: utf-8 -*-
"""
读取 `对照组.txt` 中的 Temperature 和 Humidity 数据，假设每行是按时间顺序的采样点。
在 x 轴绘制样本索引（Time），y 轴为 Value（同时绘制 Temperature 和 Humidity 两条曲线），
并将图保存为 `对照组_plot.png` 到当前工作目录。

如果文件编码不是 utf-8，会尝试用 gbk 读取。
"""
import os
import sys
from pathlib import Path

import matplotlib
matplotlib.use('Agg')  # 不打开窗口，直接保存图片
import matplotlib.pyplot as plt
import numpy as np

try:
    import pandas as pd
except Exception:
    print('需要 pandas 库，请先安装：pip install pandas')
    raise

INPUT = Path('对照组.txt')
OUT_PNG = Path('对照组_plot.png')

if not INPUT.exists():
    print(f'未找到输入文件：{INPUT.resolve()}')
    sys.exit(1)

# 尝试多种编码读取文件
for enc in ('utf-8', 'gbk', 'latin1'):
    try:
        df = pd.read_csv(INPUT, encoding=enc)
        break
    except Exception as e:
        last_exc = e
else:
    print('读取文件失败，尝试的编码均不适用，最后的错误：', last_exc)
    raise last_exc

# 期望文件具有 Temperature,Humidity 两列
expected = {'Temperature', 'Humidity'}
if not expected.issubset(set(df.columns)):
    print('输入文件列名不包含 Temperature 和 Humidity，找到的列：', list(df.columns))
    sys.exit(1)

# 使用样本索引作为 Time
time = df.index

# 将样本索引视为时间（秒）
t = time.values

plt.figure(figsize=(10, 6))

# Temperature: 红色实线（线宽略大）
plt.plot(t, df['Temperature'], label='Temperature (°C)', color='red', linewidth=1.5)

# Humidity: 蓝色阶梯线并带小点以表现离散采样（与示例接近）
plt.step(t, df['Humidity'], where='post', label='Humidity (%)', color='blue', linewidth=1)
plt.plot(t, df['Humidity'], linestyle='None', marker='.', markersize=3, color='blue', alpha=0.9)

# 轴和标题
plt.xlabel('Time (s)')
plt.ylabel('Value')
plt.title('DHT11 Temperature and Humidity Over Time')

# x 轴刻度：按 500s 或数据长度自动设定
length = len(t)
step = 500
if length <= 1000:
    step = max(1, length // 6)
xticks = np.arange(0, length + 1, step)
plt.xticks(xticks)
plt.xlim(0, max(0, length - 1))

# 网格与图例样式
plt.grid(which='major', linestyle='-', alpha=0.5)
plt.minorticks_on()
plt.grid(which='minor', linestyle=':', alpha=0.15)
plt.legend(frameon=True)

plt.tight_layout()
plt.savefig(OUT_PNG, dpi=200)
print(f'绘图已保存到: {OUT_PNG.resolve()}')
