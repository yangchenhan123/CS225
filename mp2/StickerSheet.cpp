#include "StickerSheet.h"
namespace cs225{
    StickerSheet::StickerSheet(){
        max_ = 1;
        curr_num_ = 0;
        base_ = new Image();
        stickers_ = new Image[max_];
        x_ = new unsigned[max_];
        y_ = new unsigned[max_];
    }
    
    StickerSheet::StickerSheet(const Image &picture, unsigned max){
        max_ = max;
        curr_num_ = 0;
        base_ = new Image(picture);
        stickers_ = new Image[max_];
        x_ = new unsigned[max_];
        y_ = new unsigned[max_];
        std::cout<< "1" << std::endl;
    }

    void StickerSheet::copy_(StickerSheet const & other){
        max_ = other.max_;
        curr_num_ = other.curr_num_;
        stickers_ = new Image[max_];
        base_ = new Image;
        *base_ = *other.base_;
        x_ = new unsigned[max_];
        y_ = new unsigned[max_];
        for (unsigned i = 0; i < max_; i++){
            stickers_[i] = other.stickers_[i];
            x_[i] = other.x_[i];
            y_[i] = other.y_[i];
        }
        std::cout<< "2" << std::endl;
    }

    void StickerSheet::delete_(){
        delete base_;
        delete[] x_;
        delete[] y_;
        delete[] stickers_;
        std::cout<< "3" << std::endl;
    }

    StickerSheet::~StickerSheet(){
        delete_();
        std::cout<< "4" << std::endl;
    }

    StickerSheet::StickerSheet(const StickerSheet &other){
        copy_(other);
        std::cout<< "5" << std::endl;
    }

    const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
        delete_();
        copy_(other);
        return *this;
        std::cout<< "6" << std::endl;
    }

    void StickerSheet::changeMaxStickers(unsigned max){
        unsigned old_max = max_;
        max_ = max;
        Image * copy_stickers = new Image[max_];
        unsigned * copy_x = new unsigned[max];
        unsigned * copy_y = new unsigned[max];
        if (old_max <= max){
            for (unsigned i = 0; i < curr_num_; i++){
                copy_stickers[i] = stickers_[i];
                copy_x[i] = x_[i];
                copy_y[i] = y_[i];
            }
            
            delete[] stickers_;
            delete[] x_;
            delete[] y_;
            
            stickers_ = new Image[max_];
            x_ = new unsigned[max_];
            y_ = new unsigned[max_];

            for (unsigned j = 0; j < curr_num_; j++){
                stickers_[j] = copy_stickers[j];
                x_[j] = copy_x[j];
                y_[j] = copy_y[j];
            }

        }

        else{
            if (curr_num_ > max){   //此处可能有问题,可能要把所有都复制一遍
                curr_num_ = max;
            }

            for (unsigned i = 0; i < curr_num_; i++){
                copy_stickers[i] = stickers_[i];
                copy_x[i] = x_[i];
                copy_y[i] = y_[i];
            }

            delete[] stickers_;
            delete[] x_;
            delete[] y_;

            stickers_ = new Image[max_];
            x_ = new unsigned[max_];
            y_ = new unsigned[max_];

            for (unsigned j = 0; j < curr_num_; j++){;
                stickers_[j] = copy_stickers[j];
                x_[j] = copy_x[j];
                y_[j] = copy_y[j];
            }
        }
        std::cout<< "7" << std::endl;
    }

    int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
        if (curr_num_ >= max_){
            return -1;
        }

        else{
            stickers_[curr_num_] = sticker;
            x_[curr_num_] = x;
            y_[curr_num_] = y;
            curr_num_ += 1;

            return curr_num_ - 1;  //not certain here
        }
        std::cout<< "8" << std::endl;
    }

    bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
        if (index >= 0 && index < curr_num_){
            x_[index] = x;
            y_[index] = y;
            return true;
        }

        else{
            return false;
        }
        std::cout<< "9" << std::endl;
    }

    void StickerSheet::removeSticker(unsigned index){
        if (index >= 0 && index < curr_num_){
            for(unsigned i = index; i < curr_num_ - 1; i++){
                stickers_[i] = stickers_[i + 1];
                x_[i] = x_[i+1];
                y_[i] = y_[i+1];
            }
            curr_num_ -= 1;
        }
        std::cout<< "10" << std::endl;
    }

    Image * StickerSheet::getSticker(unsigned index) const{
        if (index >= 0 && index < curr_num_){
            return &(stickers_[index]);
        }

        else{
            return NULL;
        }
        std::cout<< "11" << std::endl;
    }

    Image StickerSheet::render() const{
    	Image output(*base_);
	    for (unsigned i = 0; i < curr_num_; i++) {
		    unsigned layer_w = stickers_[i].width();
		    unsigned layer_h = stickers_[i].height();
            unsigned base_w = output.width();
            unsigned base_h = output.height();

		    if ((layer_w + x_[i]) > base_w) {
			    base_w = layer_w + x_[i];
		    }
		    if ((layer_h + y_[i]) > base_h) {
                base_h = layer_h + y_[i];
		    }
            
            output.resize(base_w, base_h);

		    for (unsigned j = 0; j < layer_w; j++) {
			    for (unsigned k = 0; k < layer_h; k++) {
				    HSLAPixel * pixel1 = output.getPixel(x_[i] + j, y_[i] + k);
				    HSLAPixel * pixel2 = stickers_[i].getPixel(j, k);
				    if (pixel2->a != 0) {
					    *pixel1 = *pixel2;
				    }
			    }
		    }
	    }
        std::cout<< "12" << std::endl;
	    return output;
    }
}