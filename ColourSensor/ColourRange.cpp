#include "ColourRange.h"

ColourRange::ColourRange(){
  lowerColour = Colour(0, 0, 0);
  upperColour = Colour(0, 0, 0);
}

ColourRange::ColourRange(Colour lower, Colour upper){
    lowerColour = lower;
    upperColour = upper;
}
ColourRange::ColourRange(int lr, int lg, int lb, int ur, int ug, int ub){
    lowerColour = Colour(lr, lg, lb);
    upperColour = Colour(ur, ug, ub);
}
bool ColourRange::colourInRange(Colour colour){
    return  colour.r > this->lowerColour.r && colour.r < upperColour.r &&
            colour.g > this->lowerColour.g && colour.g < upperColour.g &&
            colour.b > this->lowerColour.b && colour.b < upperColour.b;
}