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

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

     std::vector<Point<3>> points;
     points.resize(theTiles.size());
     std::map<Point<3>, unsigned int> tilesMap;
     for(unsigned int i = 0; i < theTiles.size(); ++i){
         HSLAPixel pixel = theTiles[i].getAverageColor();
         std::cout << "Pixel i" << i << " h:" << pixel.h << " s: " << pixel.s << " l:" << pixel.l << std::endl;
         points[i] = convertToLAB(pixel);
         std::cout << "Pixel i" << i << " h:" << points[i][0] << " s: " << points[i][1] << " l:" << points[i][2] << std::endl;
         tilesMap[points[i]] = i;
     }

     KDTree<3>* tree = new KDTree<3>(points);
     for(int i = 0; i < theSource.getRows(); ++i){
         for(int j = 0; j < theSource.getColumns(); ++j){
             HSLAPixel regionPixel = theSource.getRegionColor(i, j);
             Point<3> closestPoint = tree->findNearestNeighbor(convertToLAB(regionPixel));
             std::cout << "Pixel i: " << i << " h:" << closestPoint[0] << " s: " << closestPoint[1] << " l:" << closestPoint[2] << std::endl;

             unsigned int index = tilesMap[closestPoint];
            canvas->setTile(i, j, &theTiles[index]);
         }
     }
    delete tree;
    return canvas;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
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
