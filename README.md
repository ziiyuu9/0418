# Arduino 距離警示器專案

這是一個使用 Arduino 製作的簡單距離警示器專案。

## 專案說明

這個專案使用 HC-SR04 超聲波感測器來偵測物體距離，並透過 LED 燈號來顯示不同的警示狀態。另外還提供了使用可調式電阻控制 LED 亮度的範例。

## 硬體需求

- Arduino 開發板（UNO 或 Nano）
- HC-SR04 超聲波感測器 x1
- LED 燈 x1（白色）
- 220Ω 電阻 x1
- 10kΩ 可調式電阻（電位器）x1
- 麵包板 x1
- 杜邦線數條

## 功能特點

- 使用超聲波感測器即時偵測物體距離
- LED 持續亮表示安全距離（>30cm）
- LED 慢速閃爍表示警示距離（10-30cm）
- LED 快速閃爍表示危險距離（<10cm）
- 可使用可調式電阻控制 LED 亮度（請參考下方的替代程式碼）

## 接線說明

### HC-SR04 超聲波感測器
- VCC → Arduino 5V
- GND → Arduino GND
- TRIG → Arduino D7
- ECHO → Arduino D8

### LED 燈
- LED 正極 → Arduino D10（PWM 輸出接腳）
- LED 負極 → GND（接地）

### 可調式電阻
- 左腳 → GND（接地）
- 中間腳 → Arduino A0（類比輸入）
- 右腳 → Arduino 5V

## Arduino 程式碼

```cpp
const int trigPin = 7;    // 超聲波感測器 TRIG 接腳
const int echoPin = 8;    // 超聲波感測器 ECHO 接腳
const int whiteLED = 12;  // 白色 LED 接腳

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(whiteLED, OUTPUT);
  Serial.begin(9600);
  
  // LED 測試：開機時閃爍一次
  digitalWrite(whiteLED, HIGH);
  delay(1000);
  digitalWrite(whiteLED, LOW);
  delay(1000);
}

void loop() {
  // 發送超聲波
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // 計算距離
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;  // 換算成公分
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 根據距離控制 LED
  if (distance > 30) {
    // 安全距離：LED 持續亮著
    digitalWrite(whiteLED, HIGH);
    delay(200);
  } else if (distance > 10) {
    // 警告距離：LED 慢速閃爍
    digitalWrite(whiteLED, HIGH);
    delay(500);
    digitalWrite(whiteLED, LOW);
    delay(500);
  } else {
    // 危險距離：LED 快速閃爍
    digitalWrite(whiteLED, HIGH);
    delay(100);
    digitalWrite(whiteLED, LOW);
    delay(100);
  }
}
```

## LED 亮度控制範例程式碼

以下是使用可調式電阻控制 LED 亮度的替代程式碼：

```cpp
const int potPin = A0;     // 可調式電阻接腳（類比輸入）
const int ledPin = 10;     // LED 接腳（使用支援 PWM 的接腳）

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // 讀取可調式電阻的值（0-1023）
  int potValue = analogRead(potPin);
  
  // 將類比值（0-1023）轉換為 PWM 值（0-255）
  int brightness = map(potValue, 0, 1023, 0, 255);
  
  // 設定 LED 亮度
  analogWrite(ledPin, brightness);
  
  // 顯示目前的亮度值
  Serial.print("亮度值: ");
  Serial.println(brightness);
  
  delay(100);  // 小延遲以避免數值更新太快
}
```

## 使用方法

1. 按照接線說明連接電路
2. 將程式碼上傳到 Arduino
3. 開啟電源後，即可透過移動物體來測試距離偵測功能
4. 觀察 LED 燈號變化：
   - LED 持續亮：物體距離大於 30 公分
   - LED 慢速閃爍：物體距離在 10-30 公分之間
   - LED 快速閃爍：物體距離小於 10 公分

### LED 亮度控制範例使用方法

1. 按照可調式電阻的接線說明連接電路
2. 上傳 LED 亮度控制程式碼到 Arduino
3. 轉動可調式電阻，即可看到 LED 亮度隨之改變
4. 可以透過序列監控視窗查看目前的亮度值（0-255）

## 改進建議

1. 可以加入蜂鳴器，提供聲音警示
2. 可以調整距離閾值，以適應不同應用場景
3. 可以增加 LCD 顯示幕，顯示實際距離數值

## 授權條款

本專案採用 MIT 授權條款。