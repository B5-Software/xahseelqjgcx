#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <conio.h> // for _getch()

// W-String
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// 输出
void printData(const std::string& explanation, const Json::Value& data, const std::string& key) {
    std::cout << explanation << "：" << data[key].asString() << std::endl;
}

// 清屏
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    while (true) {
        std::string input0, input1, input2;
        
        std::cout << "西安市城六区中考录取结果API调用器 CPP版 V2" << std::endl;

        std::cout << "请输入查询年份: ";
        std::getline(std::cin, input0);

        std::cout << "请输入准考证号: ";
        std::getline(std::cin, input1);

        std::cout << "请输入身份证号: ";
        std::getline(std::cin, input2);

        std::string url = "http://222.91.162.190:7173/OperatorData.ashx?Type=MTC&YearID=" + input0 +
                          "&Zkzh=" + input1 + "&Code=&r=100&Sfzh=" + input2;

        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            if(res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            } else {
                // 解析
                Json::Reader reader;
                Json::Value obj;
                reader.parse(readBuffer, obj);

                // 输出
                printData("身份证号", obj, "sfzh");
                printData("姓名", obj, "xm");
                printData("毕业学校代码", obj, "byxxdm");
                printData("录取批次", obj, "lqpc");
                printData("录取学校类型", obj, "clqpc");
                printData("录取类别", obj, "lqlb");
                printData("录取类别文字", obj, "clqlb");
                printData("录取学校代码", obj, "xxdm");
                printData("录取学校", obj, "xxmc");
                printData("查询用时", obj, "totaltime");
            }
        }

        std::cout << "按任意键继续查询..." << std::endl;
        _getch();
        clearScreen();
    }

    return 0;
}
