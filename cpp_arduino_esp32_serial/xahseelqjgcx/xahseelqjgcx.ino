#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your_SSID";      // 替换你的WiFi SSID
const char* password = "your_PASSWORD"; // 替换你的WiFi密码

void setup() {
  // 初始化串口
  Serial.begin(115200);
  // 连接到WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (Serial.available() > 0) {
    // 读取串口输入的年份、准考证号和身份证号
    Serial.println("西安市城六区中考录取结果API调用器 ESP32版 V2");

    Serial.println("请输入查询年份: ");
    String year = Serial.readStringUntil('\n');
    year.trim();
    
    Serial.println("请输入准考证号: ");
    String zkzh = Serial.readStringUntil('\n');
    zkzh.trim();
    
    Serial.println("请输入身份证号: ");
    String sfzh = Serial.readStringUntil('\n');
    sfzh.trim();
    
    // 构建URL
    String url = "http://222.91.162.190:7173/OperatorData.ashx?Type=MTC&YearID=" + year + "&Zkzh=" + zkzh + "&Code=&r=100&Sfzh=" + sfzh;

    // 发送HTTP GET请求
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(url);
      int httpCode = http.GET();
      
      if (httpCode > 0) {
        // 请求成功
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println("查询成功，以下为清单数据：");
          
          // 解析JSON响应
          DynamicJsonDocument doc(1024);
          deserializeJson(doc, payload);

          if (doc.containsKey("sfzh")) {
            Serial.print("身份证号: ");
            Serial.println(doc["sfzh"].as<String>());
          } else {
            Serial.println("身份证号: N/A");
          }

          if (doc.containsKey("xm")) {
            Serial.print("姓名: ");
            Serial.println(doc["xm"].as<String>());
          } else {
            Serial.println("姓名: N/A");
          }

          if (doc.containsKey("byxxdm")) {
            Serial.print("毕业学校代码: ");
            Serial.println(doc["byxxdm"].as<String>());
          } else {
            Serial.println("毕业学校代码: N/A");
          }

          if (doc.containsKey("lqpc")) {
            Serial.print("录取批次: ");
            Serial.println(doc["lqpc"].as<String>());
          } else {
            Serial.println("录取批次: N/A");
          }

          if (doc.containsKey("clqpc")) {
            Serial.print("录取学校类型: ");
            Serial.println(doc["clqpc"].as<String>());
          } else {
            Serial.println("录取学校类型: N/A");
          }

          if (doc.containsKey("lqlb")) {
            Serial.print("录取类别: ");
            Serial.println(doc["lqlb"].as<String>());
          } else {
            Serial.println("录取类别: N/A");
          }

          if (doc.containsKey("clqlb")) {
            Serial.print("录取类别文字: ");
            Serial.println(doc["clqlb"].as<String>());
          } else {
            Serial.println("录取类别文字: N/A");
          }

          if (doc.containsKey("xxdm")) {
            Serial.print("录取学校代码: ");
            Serial.println(doc["xxdm"].as<String>());
          } else {
            Serial.println("录取学校代码: N/A");
          }

          if (doc.containsKey("xxmc")) {
            Serial.print("录取学校: ");
            Serial.println(doc["xxmc"].as<String>());
          } else {
            Serial.println("录取学校: N/A");
          }

          if (doc.containsKey("totaltime")) {
            Serial.print("查询用时: ");
            Serial.println(doc["totaltime"].as<String>());
          } else {
            Serial.println("查询用时: N/A");
          }

          Serial.println("以上为清单数据。如录取学校值为空，则暂无录取信息。请核对信息是否正确。如果信息无误，请耐心等待新一批的录取。");
        }
      } else {
        Serial.print("请求失败: ");
        Serial.println(http.errorToString(httpCode));
      }
      http.end();
    } else {
      Serial.println("WiFi未连接");
    }
  }
}
