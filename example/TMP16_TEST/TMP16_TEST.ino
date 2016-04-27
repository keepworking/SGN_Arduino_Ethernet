

#define DEBUG

char ID[] = "admin";//사용자의 ID를 입력합니다.
char DEVICE_CODE[] = "SmX4JdWJv2FuKMg5oQ3t";//장치 코드를 입력해주도록 합니다.
IPAddress IP(192, 168, 0, 177);//IP주소를 입력해줍니다.

dotori sensor("rPp7H");//사용할 센서를 할당된 코드와함께 선언해줍니다.

void setup() {
  Serial.begin(9600);
  dev.init(ID,DEVICE_CODE,IP);
}

void loop() {
  float V = (float) analogRead(A0) * 5 /1024;
  float TEMP = (float) 100*(V-0.5);
  sensor.sendvalue(TEMP);
  delay(3600000);
}
