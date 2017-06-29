int pwm1 = 3;
int pwm2 = 5;
int pwm3 = 6;
int inputPin = 8;
int outputPin = 9;
int Einput = 12;
int Toutput = 13;
int pwm4 = 11;
int i = 0;
int cnt = 0;
int distance;
int remote;
char shift = '9';
int stopwait = 0;
void setup()
{
  Serial.begin(9600);
  //pinMode(ledpin,OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);
  pinMode(Einput, INPUT);
  pinMode(Toutput, OUTPUT);
}
void loop()
{
  if (shift == '9')
  {
    cnt ++;
    digitalWrite(outputPin, LOW); // 使发出发出超声波信号接口低电平2μs
    delayMicroseconds(2);
    digitalWrite(outputPin, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
    delayMicroseconds(10);
    digitalWrite(outputPin, LOW); // 保持发出超声波信号接口低电平
    int distance1 = pulseIn(inputPin, HIGH); // 读出脉冲时间

    digitalWrite(Toutput, LOW); // 使发出发出超声波信号接口低电平2μs
    delayMicroseconds(2);
    digitalWrite(Toutput, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
    delayMicroseconds(10);
    digitalWrite(Toutput, LOW); // 保持发出超声波信号接口低电平
    int remote1 = pulseIn(Einput, HIGH);

    char d = Serial.read();
    Serial.println(d);
    if (d == '8') {
      shift = '8';
      Serial.println(123456);
    }
    if (cnt == 1)
    {
      distance  = distance1;
      remote = remote1;
    }
    else {
      if (distance1 - distance <= 5 || distance - distance1 <= 5)
      {

        distance = distance1;
      }
      if (remote1 - remote <= 5 || remote - remote1 <= 5)
      {
        remote = remote1;
      }
    }
    distance = distance / 58; // 将脉冲时间转化为距离（单位：厘米）
    remote = remote1 / 58;
    delay(50);
    if ((distance < 40 && distance >= 0) && (remote < 40 && remote >= 0))
    {

      stopwait++;
      if (stopwait > 1) {
        analogWrite(pwm1, 0);
        analogWrite(pwm2, 198);
        analogWrite(pwm3, 0);
        analogWrite(pwm4, 200);
      }
      else {
        analogWrite(pwm1, 0);
        analogWrite(pwm2, 0);
        analogWrite(pwm3, 0);
        analogWrite(pwm4, 0);
      }
    }
    else if ((distance < 40 && distance >= 0) && ( remote >= 0)) {
      int stopwait=0;
      analogWrite(pwm1, 0);
      analogWrite(pwm2, 0);
      analogWrite(pwm3, 0);
      analogWrite(pwm4, 0);
    }
    else if (( distance >= 0) && (remote < 40 && remote >= 0)) {
      stopwait=0;
      analogWrite(pwm1, 50);
      analogWrite(pwm2, 0);
      analogWrite(pwm3, 0);
      analogWrite(pwm4, 0);
    }
    else if ((distance >= 0) && ( remote >= 0)) {
      stopwait=0;
      analogWrite(pwm1, 198);
      analogWrite(pwm2, 0);
      analogWrite(pwm3, 200);
      analogWrite(pwm4, 0);
    }
  }
  else if (shift == '8') {
    analogWrite(pwm1, 0);
    analogWrite(pwm2, 0);
    analogWrite(pwm3, 0);
    analogWrite(pwm4, 0);
    while (1) {
      if (Serial.available()) {
        char c = Serial.read();
        Serial.println(c);
        if (c == '0')
        {
          analogWrite(pwm1, 220);
          analogWrite(pwm2, 0);
          analogWrite(pwm3, 220);
          analogWrite(pwm4, 0);
          Serial.println(c);
        }
        else if (c == '5' || c == '6')
        { analogWrite(pwm1, 0);
          analogWrite(pwm2, 0);
          analogWrite(pwm3, 0);
          analogWrite(pwm4, 0);
          Serial.println(c);
        }
        else if (c == '1')
        { analogWrite(pwm1, 0);
          analogWrite(pwm2, 220);
          analogWrite(pwm3, 0);
          analogWrite(pwm4, 220);
          Serial.println(c);
        }
        else if (c == '2')
        {
          analogWrite(pwm1, 220);
          analogWrite(pwm2, 0);
          analogWrite(pwm3, 0);
          analogWrite(pwm4, 0);
          Serial.println(c);
        }
        else if (c == '3')
        {
          analogWrite(pwm1, 0);
          analogWrite(pwm2, 0);
          analogWrite(pwm3, 220);
          analogWrite(pwm4, 0);
          Serial.println(c);
        }
        else if (c == '9') {
          shift = '9';
          break;
        }
      }
    }
  }
}

