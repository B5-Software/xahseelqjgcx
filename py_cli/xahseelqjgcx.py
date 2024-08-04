import requests
import json
import os

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

def print_data(explanation, data, key):
    print(f"{explanation}：{data.get(key, 'N/A')}")

def main():
    while True:
        print("西安市城六区中考录取结果API调用器 Python版 V2")
        input0 = input("请输入查询年份: ")
        input1 = input("请输入准考证号: ")
        input2 = input("请输入身份证号: ")

        url = f"http://222.91.162.190:7173/OperatorData.ashx?Type=MTC&YearID={input0}&Zkzh={input1}&Code=&r=100&Sfzh={input2}"

        try:
            response = requests.get(url)
            response.raise_for_status()
            data = response.json()

            # Outputdata
            print("查询成功，以下为清单数据：")
            print_data("身份证号", data, "sfzh")
            print_data("姓名", data, "xm")
            print_data("毕业学校代码", data, "byxxdm")
            print_data("录取批次", data, "lqpc")
            print_data("录取学校类型", data, "clqpc")
            print_data("录取类别", data, "lqlb")
            print_data("录取类别文字", data, "clqlb")
            print_data("录取学校代码", data, "xxdm")
            print_data("录取学校", data, "xxmc")
            print_data("查询用时", data, "totaltime")
            print("以上为清单数据。如录取学校值为空，则暂无录取信息。请核对信息是否正确。如果信息无误，请耐心等待新一批的录取。")
            print("This is a Free and Open Source Software (GPL-3.0).")
            print("Made by B5-Software")

        except requests.exceptions.RequestException as e:
            print(f"请求失败: {e}")
        except json.JSONDecodeError:
            print("响应格式错误")

        input("按回车键继续查询……")
        clear_screen()

if __name__ == "__main__":
    main()
