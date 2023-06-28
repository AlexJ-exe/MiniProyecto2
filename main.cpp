#include <iostream>
#include <chrono>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <climits>

#include "QuadTreeADT.h"

#define LAT2INT ((double) (INT_MAX / 4) / 180.0f)
#define LON2INT ((double) (INT_MAX / 4) / 360.0f)


int map_lat_to_int(float x) {
    return (x + 90.0f) * LAT2INT;
}

int map_lon_to_int(float x) {
    return (x + 180.0f) * LON2INT;
}

float map_lat_to_flt(float x) {
    return (x / LAT2INT) - 90.0f;
}

float map_lon_to_flt(float x) {
    return (x / LON2INT) - 180.0f;
}


std::vector<std::string> read_csv(std::istream &is) {
    std::vector<std::string> res;
    std::string line;
    std::getline(is, line);
    
    std::stringstream ss(line);
    std::string curr;
    
    while(std::getline(ss, curr, ';')) {
        res.push_back(curr);
    }
    return res;
}

int main(int argc, char *argv[]) {
    std::ifstream dataset("../dataset.csv");
    std::string aux;
    std::getline(dataset, aux);

    Point center(map_lat_to_int(36.8201f), map_lon_to_int(73.0444f));
    int distance = INT_MAX / 16;
    
    
    
    Quad plane(Point(-INT_MAX, -INT_MAX), Point(INT_MAX, INT_MAX));
    size_t cnt = 0;
    while(1) {
        std::vector<std::string> data = read_csv(dataset);
        
        std::string lats = data[5];
        std::string lons = data[6];
        
        std::replace(lats.begin(), lats.end(), ',', '.');
        std::replace(lons.begin(), lons.end(), ',', '.');
        
        float lat = std::stof(lats);
        float lon = std::stof(lons);
        
        int lat2int = map_lat_to_int(lat);
        int lon2int = map_lon_to_int(lon);
        /*
        std::cout << "Population: " << data[4]
                  << ", Latitude: " << lat
                  << ", Longitude: " << lon
                  << '\n';
        
        std::cout << "  Latitude2Int:  " << lat2int << " (err: " << map_lat_to_flt(lat2int) - lat << ", act: " << lats << ")\n"
                  << "  Longitude2Int: " << lon2int << " (err: " << map_lon_to_flt(lon2int) - lon << ", act: " << lons << ")\n";
        */
        Node *n = new Node(Point(lat2int, lon2int), std::stoi(data[4]));
        cnt++;
        plane.insert(n);
        //std::cout << cnt << '\n';
        if(cnt == 3173647) break;
    }
    //Prueba del método totalPoints
    std::cout << "Total Points test 2: "<< plane.totalPoints()<<std::endl;

    //Prueba del método totalNodes
    std::cout << "Total Nodes test 1: "<< plane.totalNodes()<<std::endl;

    // Obtener la lista de puntos almacenados en el Quadtree
    std::list<std::pair<Point, int>> pointList = plane.list();

    //Prueba del método countRegion
    int count = plane.countRegion(center, distance);
    std::cout << "Number of points in the region: " << count << std::endl;

    //Prueba del método aggregateRegion
    int aggregate = plane.aggregateRegion(center, distance);
    std::cout << "Aggregate value in the region: " << aggregate << std::endl;

}
