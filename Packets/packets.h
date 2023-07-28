#ifndef PACKETS_H
#define PACKETS_H

#include "tuple/tuple.h"

bool GetParity(char* input);
bool GetParity(char input);

void FlushReadBuffer();


typedef struct{
    public:
      virtual bool Verify();
      virtual char* Seal();
    protected:
     char parity;
} Packet;

typedef struct: public Packet{
  public:
    unsigned short moveSpeed; //the speed for the robot to move(0-255)
    float moveDirection; //the direction for the robot to move(0-360)
    float moveRotation; //the amount to turn

    bool dribblerCapturing; //whether the dribbler is spinning so the ball will be captured, allowing us to reverse the dribbler to replace a kicker

    void Send();
    void Recieve();
    char* Seal();
    bool Verify();
} MasterToSlave1;

typedef struct: public Packet{
  public:
    float leftObsticalDistance;//the distance to the obstical(wall/opponent) left of the robot, negative distance means that no obstical detected
	  float rightObsticalDistance;//the distance to the obstical(wall/opponent) right of the robot, negative distance means that no obstical detected
	  float estimatedBallDirection;//the estimated direction of the ball based on the sensors(0-360)

    void Request();
    void Respond();
    char* Seal();
    bool Verify();
} Slave2ToMaster;



Tuple<MasterToSlave1 * ,Slave2ToMaster *> InitMaster();
MasterToSlave1* InitSlave1();
Slave2ToMaster* InitSlave2();

#endif