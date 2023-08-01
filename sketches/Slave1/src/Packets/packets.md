# networking architecture for the FutBot

## problem

The FutBot now will use 3 seperate boards, each performing seperate tasks, one board(rpi pico) will be the master, it needs a way to send and recieve data to and from the slaves. 

## soloution

I will implement a networking protocol using i2c as the transport layer that allows the boards to communicate. The boards will control diffferent subsytems, as illustrated below:

Master(pi pico):
	- Game Logic
	- Magnetometer

Slave 1(motors)(arduino nano):
	- Ball control system
	- Propulsion system

Slave 2(peripherals)(arduino nano):
	- Ball detection system
	- Wall detection system

from this i can devise the architecture of the system as both slaves can only send or recieve data from the master.

         Master
          |  |
Slave 2->-/	 \->- Slave 1

### Packets

#### Master -> Slave 1
```
	byte moveSpeed; //the speed for the robot to move(0-255)
	float32 moveDirection; //the direction for the robot to move(0-360)
	float32 moveRotation; //the amount to turn

	bool dribblerCapturing; //whether the dribbler is spinning so the ball will be captured, allowing us to reverse the dribbler to replace a kicker
```

#### Slave 2 -> Master
```
	float leftObsticalDistance;//the distance to the obstical(wall/opponent) left of the robot, negative distance means that no obstical detected
	float rightObsticalDistance;//the distance to the obstical(wall/opponent) right of the robot, negative distance means that no obstical detected
	float estimatedBallDirection;//the estimated direction of the ball based on the sensors(0-360)
```