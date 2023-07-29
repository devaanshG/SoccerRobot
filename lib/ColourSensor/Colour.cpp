#include "Colour.h"

Colour::Colour(int red, int green, int blue){
    this->r = red;
    this->g = green;
    this->b = blue;
}
Colour::Colour(){
    this->r = 0;
    this->g = 0;
    this->b = 0;
}
String Colour::ToString(){
    return "R" + String(this->r) + " G" + String(this->g) + " B" + String(this->b);
}
