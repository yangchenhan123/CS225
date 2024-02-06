/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

/** * This function is assigned a source image, the function finds a corresponding tile to each of the region in the source image **/
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    int n_rows = theSource.getRows();
    int n_columns = theSource.getColumns();
    MosaicCanvas *result = new MosaicCanvas(n_rows, n_columns); 
    vector<Point<3>> vec;
    map<Point<3>,int> tile_avg_map;
    for (unsigned i = 0; i < theTiles.size(); i++){
        Point<3> avg_point = convertToLAB(theTiles[i].getAverageColor());
        vec.push_back(avg_point);
        tile_avg_map[avg_point] = i;
    }
    KDTree<3> tree(vec);

    for(int m = 0; m < n_rows; m++){
        for(int n = 0; n < n_columns; n++){
            result->setTile(m, n, get_match_at_idx(tree, tile_avg_map, theTiles, theSource, m, n));
        }
    }

    return result;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> &tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];
}
