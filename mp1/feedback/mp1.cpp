#include <string>
#include "cs225/PNG.h"
#include <cmath>
#include "cs225/HSLAPixel.h"

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
    PNG im_in;      
    
    im_in.readFromFile(inputFile);      //get initial image in im_in
    unsigned wid = im_in.width();
    unsigned hei = im_in.height();

    //PNG im_out(wid, hei);    //create a new image with the same size
    PNG im_out = im_in;

    for (unsigned x = 0; x < wid; x++){
        for (unsigned y = 0; y < hei; y++){
            HSLAPixel *pixel1 = im_in.getPixel(x,y);                        //get a pixel in im_in
            HSLAPixel *pixel2 = im_out.getPixel(wid-x-1,hei-y-1);     //get a pixel of corresponding rotated value in im_out
            pixel2->h = pixel1->h;    //equal the two pixels together
            pixel2->s = pixel1->s;
            pixel2->l = pixel1->l;
            pixel2->a = pixel1->a;
        }
    }

    im_out.writeToFile(outputFile);     //out put the rotated image
}
