#ifndef PACKETS_H
#define PACKETS_H



bool GetParity(char* input);
bool GetParity(char input);

struct Packet{
    public:
      virtual bool Verify();
      virtual char* Seal();
    private:
     char parity;
}

struct MasterToSlave1: public Packet{
  public:
    uint8_t moveSpeed; //the speed for the robot to move(0-255)
    float moveDirection; //the direction for the robot to move(0-360)
    float moveRotation; //the amount to turn

    bool dribblerCapturing; //whether the dribbler is spinning so the ball will be captured, allowing us to reverse the dribbler to replace a kicker

    void Send();
    void Recieve();
}

struct Slave2ToMaster: public Packet{
  public:
    float leftObsticalDistance;//the distance to the obstical(wall/opponent) left of the robot, negative distance means that no obstical detected
	  float rightObsticalDistance;//the distance to the obstical(wall/opponent) right of the robot, negative distance means that no obstical detected
	  float estimatedBallDirection;//the estimated direction of the ball based on the sensors(0-360)

    void Request();
    void Respond();
}

#endif