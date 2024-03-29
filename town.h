/*
 * A class to represent a town name with its coordinates
 * and to read towns from a file
 */

#pragma once

#include <string>
using std::string;
#include <vector>
using std::vector;
#include <utility>
using std::pair;
#include <iostream>
using std::ostream;

#include "point2d.h"


//
// A town has a name and coordinates in different reference systems:
//  - geographic coordinates (latitude, longitude),
//  - cartesian coordinates (x,y) in the Lambert 93 projection.
//
// Note that Lambert 93 is only appropriate for metropolitan France.
// There are other parameters of the Lambert conformal conic projection
// for other areas in the world.
//
class Town
{
protected:
    // Name
    string _name;
    // Geographic coordinates (latitude, longitude)
    float _lat, _lon;
    // Lambert 93 coordinates (x,y)
    float _x, _y;
public:
    // Construct a new dummy town
    Town();
    // Construct a new town given its name, latitude and longitude
    Town(string _name, float _lat, float _lon);
    // Get the town name
    inline string name() const { return _name; }
    // Get the town latitude
    inline float lat() const { return _lat; }
    // Get the town longitude
    inline float lon() const { return _lon; }
    // Get the town X-coordinate in Lambert 93 projection
    inline float x() const { return _x; }
    // Get the town Y-coordinate in Lambert 93 projection
    inline float y() const { return _y; }
    // Return the 2D point coordinates (in Lambert 93 projection)
    inline Point2D point() const { return Point2D(_x,_y); }

    //QUESTION 3: DEFINITION OF AN ORDER BETWEEN TOWNS
    bool operator<(const Town &town) const{
        return(_name<town.name() || (_name==town.name() && this->point()<town.point()));
    }

    bool operator!=(const Town &town) const{
        return(_name!=town.name() || !(this->point()==town.point()));
    }

    // Return the distance to given town (in kilometers)
    float dist(const Town town) const;

    // Read file of town names and coordinates, and add them into a vector
    // Return number of towns read, or negative value if some error occurred
    static int read_file(string townFile, vector<Town> &towns);
    // Read file of town names and coordinates, and add them into a vector
    // also keeping track of the coordinates bounding box
    // Return number of towns read, or negative value if some error occurred
    static int read_file(string townFile, vector<Town> &towns,
			 float &xmin, float &ymin, float &xmax, float &ymax);

    // Return a vector of towns that have a given name
    static vector<Town>
    towns_with_name(const vector<Town> towns, string name);

    // Return a vector of towns with given Lambert 93 (x,y) coordinates
    vector<Town>
    towns_with_x_y(const vector<Town> towns, float x, float y);

    // Return a vector of towns with given geographic coordinates
    static vector<Town>
    towns_with_lat_lon(const vector<Town> towns, float lat, float lon);
};

//
// Display town: name[lat,lon](x,y)
//
ostream &operator<<(ostream &os, Town const &town);
ostream &operator<<(ostream &os, Town* const &townp);

// Convert geographic coordinates (latitude, longitude in degrees) into
// cartesian coordinates (in kilometers) using the Lambert 93 projection.
pair<float,float> geoToLambert93(float latitude,float longitude);
