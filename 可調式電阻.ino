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