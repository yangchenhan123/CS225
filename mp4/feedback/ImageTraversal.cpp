#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : traversal_(nullptr), if_end(false) {
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(PNG image, Point start, double tolerance, ImageTraversal* tra) : image_(image), start_(start), curr_(start), traversal_(tra), tolerance_(tolerance), if_end(false) {
  /** @todo [Part 1] */
  //initialize the visit_list
  visit_list.resize(image_.width() * image_.height(), false);
  //check if the start point is available
  if(!if_available(start_)) {
    if_end = true;
  }else{
    visit_list[start_.x + start_.y * image_.width()] = true;
    traversal_->add(start_);
  }
}


bool ImageTraversal::Iterator::if_available(Point p){
  //check if the point is out of range
  if(p.x >= image_.width() || p.y >= image_.height()) {  
    return false;
  }
  //check if the point is already visited
  if(visit_list[p.x + ( (p.y) * (image_.width()) )]) {
    return false;
  }
  //check if the point is within the tolerance
  HSLAPixel start_pixel = *image_.getPixel(start_.x, start_.y);
  HSLAPixel curr_pixel = *image_.getPixel(p.x, p.y);
  if(calculateDelta(start_pixel, curr_pixel) >= tolerance_) {
    return false;
  }
  return true;
}

void ImageTraversal::Iterator::set_if_end(bool set){
  if_end = set;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //push available point into traversal stack or queue
  Point right = Point(curr_.x + 1, curr_.y);
  if (if_available(right)){traversal_->add(right);}
  Point below = Point(curr_.x, curr_.y + 1);
  if (if_available(below)){traversal_->add(below);}
  Point left = Point(curr_.x - 1, curr_.y);
  if (if_available(left)){traversal_->add(left);}
  Point above = Point(curr_.x, curr_.y - 1);
  if (if_available(above)){traversal_->add(above);}
  
  //check if there is nothing to be traverse
  if(traversal_->empty()){
    if_end = true;
    return *this;
  }
  //get next Point to be traversal
  curr_ = traversal_->pop();
  while(visit_list[curr_.x + ( (curr_.y) * (image_.width()) )]){
    if (traversal_->empty()) {
      set_if_end(true);
      return *this;
    }else{curr_ = traversal_->pop();}
  }
  visit_list[curr_.x + ( (curr_.y) * (image_.width()) )] = true;
  return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr_;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return (if_end != other.if_end);
}