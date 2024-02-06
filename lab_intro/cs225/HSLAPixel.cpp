#include "HSLAPixel.h"
cs225::HSLAPixel::HSLAPixel(){
    cs225::HSLAPixel(1,1,1,1);
}

cs225::HSLAPixel::HSLAPixel(double hue, double saturation, double luminance){
    h = hue;
    s = saturation;
    l = luminance;
    a = 1;
}

cs225::HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha){
    h = hue;
    s = saturation;
    l = luminance;
    a = alpha;
}
