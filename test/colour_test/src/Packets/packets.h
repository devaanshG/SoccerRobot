#ifndef PACKETS_H
#define PACKETS_H

#include "tuple/tuple.h"

const int Slave2Address = 0x24;
const int Slave1Address = 0x23;

bool GetParity(char* input);
bool GetParity(char input);

void FlushReadBuffer();

typedef struct Packet {
    public:
      virtual bool Verify() = 0;
      virtual char* Seal() = 0;
    protected:
     char parity;
} Packet;

typedef struct MasterToSlave1: public Packet{
  
  public:
    unsigned short moveSpeed; //the speed for the robot to move(0-255)
    float moveDirection; //the direction for the robot to move(0-360)
    float moveRotation; //the amount to turn

    bool dribblerOn; //whether the dribbler is on
    bool dribblerCapturing; //whether the dribbler is spinning so the ball will be captured, allowing us to reverse the dribbler to replace a kicker

    void Send();
    void Recieve();
    bool Verify();
    char* Seal();
} MasterToSlave1;

typedef struct Slave2ToMaster: public Packet{
  public:
    float leftObsticalDistance;//the distance to the obstical(wall/opponent) left of the robot, negative distance means that no obstical detected
	float rightObsticalDistance;//the distance to the obstical(wall/opponent) right of the robot, negative distance means that no obstical detected
	int estimatedBallDirection;//the estimated direction of the ball based on the sensors(0-360)
    //float estimatedBallHeading;//the "gradient" of the balls movement

    void Request();
    void Respond(int count);
    bool Verify();
    char* Seal();
} Slave2ToMaster;


#endif