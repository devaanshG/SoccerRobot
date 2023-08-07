#define IR1 A0
#define IR2 A1
#define IR3 A2
#define IR4 A3

#define BALL 13

int ballDir = 0;
int ballDelta;
int ballVel;

int prevDir = 0;

float DeltaTime(){
  static int lastTime;
  int curTime = millis();
  int delta = curTime - lastTime;
  lastTime = curTime;
  return delta;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BALL, INPUT);
  DeltaTime();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (map(analogRead(IR1), 1023, 300, 0, 100) == 0 && map(analogRead(IR2), 1023, 300, 0, 100) == 0 && map(analogRead(IR3), 1023, 300, 0, 100) == 0 && map(analogRead(IR4), 1023, 300, 0, 100) == 0) {
    Serial.println("BALL NOT FOUND");
  } else {
    int sensor1Reading = map(analogRead(IR1), 1023, 300, 0,100);
    int sensor2Reading = map(analogRead(IR2), 1023, 300, 0, 100);
    int sensor3Reading = map(analogRead(IR3), 1023, 300, 0, 100);
    int sensor4Reading = map(analogRead(IR4), 1023, 300, 0, 100);

    // ballDir = max(sensor1Reading, max(sensor2Reading, max(sensor3Reading, sensor4Reading))); // Find the sensor with the highest reading (I.e. the sensor that is most proximal to the ball)

    ballDir = sensor1Reading * 90.0f / 100.0f + sensor2Reading * 30.0f / 100.0f + sensor3Reading * -30.0f / 100.0f + sensor4Reading * -90.0f / 100.0f;
   ballDir = map(ballDir, -30, 30,-90, 90);


    ballDelta = ballDir - prevDir; // Find
    ballVel = ballDelta - DeltaTime();

    Serial.println(ballDir);
  }

  prevDir = ballDir;
}
