#ifndef HSLAPIXEL_H
#define HSLAPIXEL_H

namespace cs225 {
    class HSLAPixel {
    public:
        HSLAPixel();
        HSLAPixel (double hue, double saturation, double luminance);
        HSLAPixel (double hue, double saturation, double luminance, double alpha);
        double h;
        double s;
        double l;
        double a;
};
}


#endif