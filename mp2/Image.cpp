#include "Image.h"
#include <iostream>

namespace cs225{
    void Image::lighten() {
        unsigned w = width();
        unsigned h = height();
        HSLAPixel *pixel = new HSLAPixel();
        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel = getPixel(x,y);
                pixel->l += 0.1;
                if (pixel->l > 1) {
                    pixel->l = 1;
                }
            }
        }
    }
    
    void Image::lighten(double amount) {
        unsigned w = width();
        unsigned h = height();
        HSLAPixel *pixel = new HSLAPixel();
        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel = getPixel(x,y);
                pixel->l += amount;
                if (pixel->l > 1) {
                    pixel->l = 1;
                }
            }
        }
    }

    void Image::darken() {
        unsigned w = width();
        unsigned h = height();
        HSLAPixel *pixel = new HSLAPixel();
        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel = getPixel(x,y);
                pixel->l -= 0.1;
                if (pixel->l < 0) {
                    pixel->l = 0;
                }
            }
        }
    }

    void Image::darken(double amount) {
        unsigned w = width();
        unsigned h = height();
        HSLAPixel *pixel = new HSLAPixel();
        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel = getPixel(x,y);
                pixel->l -= amount;
                if (pixel->l < 0) {
                    pixel->l = 0;
                }
            }
        }
    }

    void Image::saturate() {
        unsigned w = width();
        unsigned h = height();
        HSLAPixel *pixel = new HSLAPixel();
        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel = getPixel(x,y);
                pixel->s += 0.1;
                if (pixel->s > 1) {
                    pixel->s = 1;
                }
            }
        }
    }

    void Image::saturate(double amount) {
        unsigned w = width();
        unsigned h = height();
        HSLAPixel *pixel = new HSLAPixel();
        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel = getPixel(x,y);
                pixel->s += amount;
                if (pixel->s > 1) {
                    pixel->s = 1;
                }
            }
        }
    }

    void Image::desaturate() {
        unsigned w = width();
        unsigned h = height();
        HSLAPixel *pixel = new HSLAPixel();
        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel = getPixel(x,y);
                pixel->s -= 0.1;
                if (pixel->s < 0) {
                    pixel->s = 0;
                }
            }
        }
    }

    void Image::desaturate(double amount) {
        unsigned w = width();
        unsigned h = height();
        HSLAPixel *pixel = new HSLAPixel();
        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel = getPixel(x,y);
                pixel->s -= amount;
                if (pixel->s < 0) {
                    pixel->s = 0;
                }
            }
        }
    }

    void Image::grayscale() {
        unsigned w = width();
        unsigned h = height();
        HSLAPixel *pixel = new HSLAPixel();
        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel = getPixel(x,y);
                pixel->s = 0;
            }
        }
    }

    void Image::rotateColor(double degrees){
        unsigned w = width();
        unsigned h = height();
        HSLAPixel *pixel = new HSLAPixel();
        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel = getPixel(x,y);
                pixel->h += degrees;
                while (pixel->h > 360){
                    pixel->h = pixel->h -360;
                }
                while (pixel->h < 0){
                    pixel->h = pixel->h +360;
                }
            }
        }
    }

    void Image::illinify(){
        unsigned w = width();
        unsigned h = height();
        HSLAPixel *pixel = new HSLAPixel();
        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel = getPixel(x,y);
                if (pixel->h >= 114 && pixel->h <= 293){
                    pixel->h = 216;
                }else{
                    pixel->h = 11;
                }
            }
        }
    }

    void Image::scale(double factor){
        unsigned width_ori = width();
        unsigned height_ori = height();
        unsigned w = width_ori * factor;
        unsigned h = height_ori *factor;

        Image *copy = new Image;
        *copy = *this;
        this->resize(w,h);

        HSLAPixel *pixel1 = new HSLAPixel();
        HSLAPixel *pixel2 = new HSLAPixel();

        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel1 = this->getPixel(x,y);
                pixel2 = copy->getPixel(x * width_ori / w, y * height_ori / h);
                *pixel1 = *pixel2;
            }
        }

    }

    void Image::scale(unsigned w, unsigned h){
        unsigned width_ori = width();
        unsigned height_ori = height();
        //double factor_w = w / width_ori;
        //double factor_h = h / height_ori;
        
        Image *copy = new Image;
        *copy = *this;
        this->resize(w,h);

        HSLAPixel *pixel1 = new HSLAPixel();
        HSLAPixel *pixel2 = new HSLAPixel();

        for (unsigned x = 0; x < w; x++){
            for (unsigned y = 0; y < h; y++){
                pixel1 = this->getPixel(x,y);
                pixel2 = copy->getPixel(x * width_ori / w, y * height_ori / h);
                *pixel1 = *pixel2;
            }
        }

    }

}

