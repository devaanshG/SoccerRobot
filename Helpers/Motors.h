#ifndef MOTORS_H
#define MOTORS_H
class Motors{
    public:
        static void init();

        static void MoveMotors(float theta, int speed, float angle);

    private:
        static void MoveMotor(int motor, float speed);

};
#endif