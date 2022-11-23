#define EN1 3
#define EN2 9
#define EN3 11
#define PH1 2
#define PH2 8
#define PH3 10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);
  pinMode(PH1, OUTPUT);
  pinMode(PH2, OUTPUT);
  pinMode(PH3, OUTPUT);
}

void loop() {
//  // put your main code here, to run repeatedly:
//  for (int i = 0; i<=255; i++){
//    move_robot(0, i, 0);
//    delay(10);
//  }
//  delay(500);
//  for (int i = 0; i<=255; i++){
//    move_robot(180, i, 0);
//    delay(10);
//  }
//  delay(500);
//
//  for (int i = 0; i<=255; i++){
//    move_robot(90, i, 0);
//    delay(10);
//  }
//  delay(500);
//  for (int i = 0; i<=255; i++){
//    move_robot(270, i, 0);
//    delay(10);
//  }
//  delay(500);

  for (int i = 0; i<=255; i++){
    move_robot(0, i, 0);
    delay(10);
  }
  delay(500);
}

int speed1 = 0;
int speed2 = 0;
int speed3 = 0;
float angle1 = 0;
float angle2 = 0;
float angle3 = 0;

void move_robot(int theta, int magnitude, int rotation){
  angle1 = (30 + theta) * 0.01745;
  angle2 = (150 + theta) * 0.01745;
  angle3 = (90 + theta) * 0.01745;
    
  speed1 = cos(angle1) * magnitude + rotation;
  speed2 = cos(angle2) * magnitude + rotation;
  speed3 = cos(angle3) * magnitude + rotation;

  Serial.print("Speed 1: ");
  Serial.println(abs(speed1));
  Serial.print("Speed 2: ");
  Serial.println(abs(speed2));
  Serial.print("Speed 3: ");
  Serial.println(abs(speed3));
  
  digitalWrite(PH1, speed1 < 0 ? 1 : 0);
  digitalWrite(PH2, speed2 < 0 ? 1 : 0);
  digitalWrite(PH3, speed3 < 0 ? 0 : 1);

  analogWrite(EN1, abs(speed1));
  analogWrite(EN2, abs(speed2));
  analogWrite(EN3, abs(speed3));
}
