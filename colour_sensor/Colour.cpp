#include "Colour.h"

Colour::Colour(int red, int green, int blue){
    r = red;
    g = green;
    b = blue;
}
Colour::Colour(){
    r = 0;
    g = 0;
    b = 0;
}
String Colour::ToString(){
    return "R" + String(r) + "G" + String(g) + "B" + String(b) + "D";
}
