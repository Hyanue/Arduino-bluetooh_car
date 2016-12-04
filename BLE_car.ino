#define AT 2
#define LED 13
int INA = 4; //电机A正反转控制端
int PWMA = 5; //电机A调速端
int INB = 7; //电机B正反转控制端
int PWMB = 6; //电机B调速端

void motosp(int sp1,int sp2)//声明电机速度控制函数。括号内定义的变量分别为左右电机速
//度值，范围-255～+255，正值为正转，负值为反转。
{
  if(sp1>0) {
   digitalWrite(INA, HIGH);    
  }
  else
  {
   digitalWrite(INA, LOW); 
  }
  if(sp2>0)
  {
   digitalWrite(INB, HIGH); 
  }
  else
  {
   digitalWrite(INB, LOW); 
  }
  analogWrite(PWMA,abs (sp1)); 
  analogWrite(PWMB,abs (sp2));
}

void setup() {
  // put your setup code here, to run once:
pinMode(LED,OUTPUT);  
  pinMode(AT,OUTPUT);  
  digitalWrite(AT,HIGH); //AT的电平给高，用于输入AT指令
  Serial.begin(9600);//这里应该和你的模块通信波特率一致
  delay(100);
  Serial.println("AT");
  delay(100);
  Serial.println("AT+NAME=ICAT-BT02");//命名模块名
  delay(100);
  Serial.println("AT+ROLE=0");//设置主从模式：0从机，1主机
  delay(100);
  Serial.println("AT+PSWD=1234");//设置配对密码，如1234
  delay(100);
  Serial.println("AT+UART=9600,0,0");//设置波特率9600，停止位1，校验位无
  delay(100);
  Serial.println("AT+RMAAD");//清空配对列表
  pinMode(INA,OUTPUT);
  pinMode(INB,OUTPUT);
}

void loop()
{
  int cd=Serial.read(); //从串口读取一个字符
  switch(cd){
  case 'g'://前进
    motosp(0,225);
    break;
  
  case 'b'://后退
    motosp(0,-225);
    break;
    
    case '1'://左前
    motosp(-225,150);
    break;
    
    case '2'://右前
    motosp(255,150);
    break;
    
    case '3'://左后
    motosp(-225,-150);
    break;
    
    case '4'://右后
    motosp(255,-150);
    break;

    case '0'://停
    motosp(0,0);
    break;
  }
   delay(100);
}

