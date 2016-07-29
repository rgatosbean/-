#include <Arduino.h>
#define NC      (0)
#define PORT_1  (0x01)
#define PORT_2  (0x02)
#define PORT_3  (0x03)
#define PORT_4  (0x04)
#define PORT_5  (0x05)
#define PORT_6  (0x06)
#define PORT_7  (0x07)
#define PORT_8  (0x08)
#define PORT_9  (0x09)
#define PORT_10 (0x0a)
#define M1      (0x09)
#define M2      (0x0a)
typedef struct
{
  uint8_t s1;
  uint8_t s2;
} MePort_Sig;
MePort_Sig mePort[15] =
{
    {NC, NC}, {11, 8}, {13, 12}, {10, 9}, {1, 0},
    {MISO, SCK}, {A0, A1}, {A2, A3}, {A4, A5}, {6, 7}, {5, 4} ,
    { NC, NC }, { NC,  NC }, {  NC, NC }, { NC, NC }
};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(4,OUTPUT);//左边电机方向控制；0：正转；1反转
  pinMode(5,OUTPUT);//左边电机速度控制0~255
  pinMode(6,OUTPUT);//右边电机速度控制0~255
  pinMode(7,OUTPUT);//右边电机方向控制；0：正转；1反转
}

void loop() {
  // put your main code here, to run repeatedly:
  GetJoyStick(PORT_6);//将游戏杆接到PORT_6端口上进行测试
  GetFlameDigital(PORT_7);//将火焰传感器接到PORT_7端口上进行测试
  GetFlameAnalog(PORT_7);
  delay(100);
}
void goAhead(int mspeed)//前进
{
  digitalWrite(4,0);
  analogWrite(5,mspeed);
  digitalWrite(7,0);
  analogWrite(6,mspeed);
  }
void goBack(int mspeed)//后退
{
  digitalWrite(4,1);
  analogWrite(5,mspeed);
  digitalWrite(7,1);
  analogWrite(6,mspeed);
  }
void stopCar()//电机停止转动
{
  analogWrite(5,0);
  analogWrite(6,0);
  }
void SetRGBLed(unsigned char portNo,int r,int g,int b)//RGB3色LED
{
    analogWrite(3,r);
    pinMode(mePort[portNo].s1,OUTPUT);
    pinMode(mePort[portNo].s2,OUTPUT);
    analogWrite(mePort[portNo].s1,g);
    analogWrite(mePort[portNo].s2,b);
    
}
void SetRGLed(unsigned char portNo,int r,int g) //RG2色LED
{
    pinMode(mePort[portNo].s1,OUTPUT);
    pinMode(mePort[portNo].s2,OUTPUT);
    analogWrite(mePort[portNo].s1,r);
    analogWrite(mePort[portNo].s2,g);
}
void GetFlameDigital(unsigned char portNo)  //火焰传感器数字量
{
  pinMode(mePort[portNo].s1,INPUT);
  int val = digitalRead(mePort[portNo].s1);
  Serial.print("flame sensor(digital) is :");
  Serial.println(val); 
}
void GetFlameAnalog(unsigned char portNo)  //火焰传感器模拟量
{
  pinMode(mePort[portNo].s2,INPUT);
  int val = analogRead(mePort[portNo].s2);
  Serial.print("flame sensor(analog) is :");
  Serial.println(val);
 
}
void GetIRSensor(unsigned char portNo)  //红外避障传感器
{
    pinMode(mePort[portNo].s1,INPUT);
    int val = digitalRead(mePort[portNo].s1);
    Serial.print("Ir sensor is :");
    Serial.println(val);
}
void GetFindLine(unsigned char portNo)  //巡线传感器
{
    pinMode(mePort[portNo].s1,INPUT);
    int val = digitalRead(mePort[portNo].s1);
    Serial.print("Fdline sensor is :");
    Serial.println(val);
}
void GetJoyStick(unsigned char portNo)//游戏杆测试
{
  pinMode(mePort[portNo].s1,INPUT);
  pinMode(mePort[portNo].s2,INPUT);
  int x_val = analogRead(mePort[portNo].s1);
  int y_val = analogRead(mePort[portNo].s2);
  int btn   = digitalRead(2);
  Serial.print("X is :");
  Serial.println(x_val);
  Serial.print("Y is :");
  Serial.println(y_val);
  Serial.print("Button is :");
  Serial.println(btn);
  }

