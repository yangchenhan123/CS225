
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  PNG base;
  base.readFromFile("man.png");

  FloodFilledImage flood(base);
  
  DFS dfs(base, Point(0,0), 0.1);
  BFS bfs(base, Point(0,0), 0.1);
  MyColorPicker mine;
  RainbowColorPicker rain(2);

  flood.addFloodFill(dfs, mine);
  flood.addFloodFill(bfs, rain);
  Animation animation = flood.animate(40000);
  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("my.png");
  animation.write("my.gif");
  return 0;
}
