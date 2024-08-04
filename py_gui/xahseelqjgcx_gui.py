import tkinter as tk
from tkinter import messagebox
import requests
import json

def fetch_data():
    year = entry_year.get()
    zkzh = entry_zkzh.get()
    sfzh = entry_sfzh.get()
    
    url = f"http://222.91.162.190:7173/OperatorData.ashx?Type=MTC&YearID={year}&Zkzh={zkzh}&Code=&r=100&Sfzh={sfzh}"

    try:
        response = requests.get(url)
        response.raise_for_status()
        data = response.json()
        show_data(data)
    except requests.exceptions.RequestException as e:
        messagebox.showerror("请求失败", f"请求失败: {e}")
    except json.JSONDecodeError:
        messagebox.showerror("响应错误", "响应格式错误")

def show_data(data):
    result_text.delete("1.0", tk.END)
    result_text.insert(tk.END, f"身份证号：{data.get('sfzh', 'N/A')}\n")
    result_text.insert(tk.END, f"姓名：{data.get('xm', 'N/A')}\n")
    result_text.insert(tk.END, f"毕业学校代码：{data.get('byxxdm', 'N/A')}\n")
    result_text.insert(tk.END, f"录取批次：{data.get('lqpc', 'N/A')}\n")
    result_text.insert(tk.END, f"录取学校类型：{data.get('clqpc', 'N/A')}\n")
    result_text.insert(tk.END, f"录取类别：{data.get('lqlb', 'N/A')}\n")
    result_text.insert(tk.END, f"录取类别文字：{data.get('clqlb', 'N/A')}\n")
    result_text.insert(tk.END, f"录取学校代码：{data.get('xxdm', 'N/A')}\n")
    result_text.insert(tk.END, f"录取学校：{data.get('xxmc', 'N/A')}\n")
    result_text.insert(tk.END, f"查询用时：{data.get('totaltime', 'N/A')}\n")
    result_text.insert(tk.END, "以上为清单数据。如录取学校值为空，则暂无录取信息。请核对信息是否正确。如果信息无误，请耐心等待新一批的录取。\n")
    result_text.insert(tk.END, "This is a Free and Open Source Software (GPL-3.0).\n")
    result_text.insert(tk.END, "Made by B5-Software \n")

# 创建主窗口
root = tk.Tk()
root.title("西安市城六区中考录取结果API调用器 V2-GUI版")

# 创建并放置标题标签
title_label = tk.Label(root, text="西安市城六区中考录取结果查询 V2", font=("Arial", 16, "bold"))
title_label.grid(row=0, column=0, columnspan=2, pady=10)

# 创建并放置各个控件
tk.Label(root, text="请输入查询年份:").grid(row=1, column=0, padx=10, pady=5)
entry_year = tk.Entry(root)
entry_year.grid(row=1, column=1, padx=10, pady=5)

tk.Label(root, text="请输入准考证号:").grid(row=2, column=0, padx=10, pady=5)
entry_zkzh = tk.Entry(root)
entry_zkzh.grid(row=2, column=1, padx=10, pady=5)

tk.Label(root, text="请输入身份证号:").grid(row=3, column=0, padx=10, pady=5)
entry_sfzh = tk.Entry(root)
entry_sfzh.grid(row=3, column=1, padx=10, pady=5)

btn_fetch = tk.Button(root, text="查询", command=fetch_data)
btn_fetch.grid(row=6, columnspan=2, pady=10)

result_text = tk.Text(root, height=15, width=50)
result_text.grid(row=7, columnspan=2, padx=10, pady=10)

# 运行主循环
root.mainloop()
