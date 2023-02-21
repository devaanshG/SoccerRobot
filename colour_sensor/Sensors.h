#include "Adafruit_TCS34725.h"

class ColourSensor{
    public:
        static const ColourRange[] ranges;

        static void init();
        static void get_current_colour_ID();
    private:
        static Adafruit_TCS34725 tcs;
        
        static void update_colours();
        static void get_col_id();

};

struct Colour
{
    public:
        Colour(int r, int g, int b);
        int r;
        int g;
        int b;
};


struct ColourRange
{
    public:
        ColourRange(Colour lower, Colour upper);
        ColourRange(int lr, int lg, int lb, int ur, int ug, int ub);

        char[] name;
        Colour lowerColour;
        Colour upperColour;

        bool colourInRange(Colour col);
};
