int ret=0;
int speed=0;
int Kp=0;
volatile int BML,BMR;

int sw_A0=1; int sw_A1=1; int sw_A2=1; int sw_A3=1; int sw_A4=1; int sw_A5=1; int sw_A6=1; int sw_A7=1; int sw_A8=1; int sw_A9=1;

int line_white[10] = {900, 900, 900, 900, 900, 900, 900, 900, 900, 900};
int line_black[10] = {200, 200, 200, 200, 200, 200, 200, 200, 200, 200};
int line_val[10] = {0};

void setup() {
  attachInterrupt(digitalPinToInterrupt(18), ReadEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), ReadEncoderB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(2), ReadEncoderC, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), ReadEncoderD, CHANGE);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);

   for(int i = 0; i < 10; i++){
   line_val[i] = (line_white[i] + line_black[i])/2;
   
  }
}

void loop() {

  sw_A0=1; sw_A1=1; sw_A2=1; sw_A3=1; sw_A4=1; sw_A5=1; sw_A6=1; sw_A7=1; sw_A8=1; sw_A9=1;
  



  Line_Following(150,10,50,1300);
  motor(-50,-50);
  delay(100);
  // sw_A0=0;
  Line_Following(100,20,50,1300);
  motor(-50,-50);
  delay(100);
  // sw_A0=1;
  Line_Following(150,20,50,3000);
  // motor(-50,-50);
  // delay(100);
  Line_Following(100,5,50,500);
  motor(-50,-50);
  delay(100);

  T_Cross(9,80,20,50);
  motor(-50,-50);
  delay(100);
  motor(80,80);
  delay(300);
  turn_right(100,-100);
  motor(-50,-50);
  delay(100);

  Line_Following(100,10,50,1150);
  motor(-50,-50);
  delay(100);

  motor(-70,-70);
  delay(500);
  turn_left(-130,100);
  motor(-50,-50);
  delay(100);

  T_Cross(0,100,10,30);
  motor(-50,-50);
  delay(200);
  motor(80,80);
  delay(300);
  turn_left(-100,100);
  motor(-50,-50);
  delay(100);

  Line_Following(100,10,50,4100);
  motor(-50,-50);
  delay(100);
  Line_Following(70,20,50,1400);
  motor(-50,-50);
  delay(100);
  Line_Following(70,5,50,500);
  motor(-50,-50);
  delay(100);
  
  T_Cross(7,70,5,50);
  motor(-50,-50);
  delay(100);
  motor(0,0);
  delay(2000);
  motor(80,80);
  delay(600);
  motor(-50,-50);
  delay(100);
  turn_right(100,-130);
 }

void track(int a , int Kp , int Kd){

  int error,errorLast,errorDiff;
  
    if(analogRead(A0)<line_val[0] && sw_A0==1)          ret=-5;
    else if(analogRead(A1)<line_val[1] && sw_A1==1)     ret=-4;
    else if(analogRead(A2)<line_val[2] && sw_A2==1)     ret=-3;
    else if(analogRead(A3)<line_val[3] && sw_A3==1)     ret=-2;
    else if(analogRead(A4)<line_val[4] && sw_A4==1)     ret=-1;
    else if(analogRead(A5)<line_val[5] && sw_A5==1)     ret=1;
    else if(analogRead(A6)<line_val[6] && sw_A6==1)     ret=2;
    else if(analogRead(A7)<line_val[7] && sw_A7==1)     ret=3;
    else if(analogRead(A8)<line_val[8] && sw_A8==1)     ret=4;
    else if(analogRead(A9)<line_val[9] && sw_A9==1)     ret=5;

    error = ret;
    errorDiff = error-errorLast;
    errorLast = error;

    speed=ret*Kp + Kd*errorDiff;
    motor(a+speed , a-speed);
    }

void Line_Following(int speed , int Kp , int Kd , int degrees){
  BML = 0;
  BMR = 0;
 while(1){
    if((abs(BML)+abs(BMR))/2 > degrees) break;
    else track(speed,Kp,Kd);
   }
}

void T_Cross(int num , int speed , int Kp , int Kd){
   while(1){
    if(num == 0 && analogRead(A0)<line_val[0])   break;
    else if(num == 1 && analogRead(A1)<line_val[1])   break;
    else if(num == 2 && analogRead(A2)<line_val[2])   break;
    else if(num == 3 && analogRead(A3)<line_val[3])   break;
    else if(num == 4 && analogRead(A4)<line_val[4])   break;
    else if(num == 5 && analogRead(A5)<line_val[5])   break;
    else if(num == 6 && analogRead(A6)<line_val[6])   break;
    else if(num == 7 && analogRead(A7)<line_val[7])   break;
    else if(num == 8 && analogRead(A8)<line_val[8])   break;
    else if(num == 9 && analogRead(A9)<line_val[9])   break;
    
    else track(speed,Kp,Kd);
    }
    }

void motor(int left,int right){

  if (left>255) left=255;
  else if (left<-150) left=-150;

  if (right>255) right=255;
  else if (right<-150) right=-150;

  if (left>0){
  analogWrite(4, left);
  analogWrite(5, 0);
  analogWrite(10, left);
  analogWrite(11, 0);
  }
  else if(left<0){
  analogWrite(4, 0);
  analogWrite(5, left*-1);
  analogWrite(10, 0);
  analogWrite(11, left*-1);
  }
  else{
  analogWrite(4, 0);
  analogWrite(5, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
  }

  if(right>0){
  analogWrite(6, right);
  analogWrite(7, 0);
  analogWrite(8, right);
  analogWrite(9, 0);
  }
  else if(right<0){
  analogWrite(6, 0);
  analogWrite(7, right*-1);
  analogWrite(8, 0);
  analogWrite(9, right*-1);
  }
  else{
  analogWrite(6, 0);
  analogWrite(7, 0);
  analogWrite(8, 0);
  analogWrite(9, 0);
  }
}

void turn_right(int left , int right){
  while(1){
    if(analogRead(A9)<line_val[9]) break;
    else motor(left, right);
  }
  while(1){
    if(analogRead(A6)<line_val[6]) break;
    else motor((left/2)+20, (right/2)+20);
  }
  while(1){
    if(analogRead(A5)<line_val[5]) break;
}
}

void turn_left(int left , int right){
 while(1){
    if(analogRead(A0)<line_val[0]) break;
    else  motor(left,right);
  }
while(1){
    if(analogRead(A3)<line_val[3]) break;
    else  motor((left/2)+20,(right/2)+20);
  }
while(1){
    if(analogRead(A4)<line_val[4]) break;
  }
}


void ReadEncoderA()
{
    digitalRead(18) ^ digitalRead(19) ? ++BML : --BML;
//    Serial.print(BML);
}

void ReadEncoderB()
{
    digitalRead(18) ^ digitalRead(19) ? --BML : ++BML;
}

void ReadEncoderC()
{
    digitalRead(2) ^ digitalRead(3) ? --BMR : ++BMR;
    //Serial.println(BMR);
}

void ReadEncoderD()
{
    digitalRead(2) ^ digitalRead(3) ? ++BMR : --BMR;
}
