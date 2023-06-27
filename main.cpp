#include <iostream>
#include <chrono>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <climits>

#include "QuadTreeADT.h"

#define LAT2INT ((double) (INT_MAX / 2) / 90.0f)
#define LON2INT ((double) (INT_MAX / 2) / 180.0f)


int map_lat_to_int(float x) {
    return x * LAT2INT;
}

int map_lon_to_int(float x) {
    return x * LON2INT;
}

float map_lat_to_flt(float x) {
    return x / LAT2INT;
}

float map_lon_to_flt(float x) {
    return x / LON2INT;
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
        
        std::cout << "  Latitude2Int:  " << lat2int << " (err: " << map_lat_to_flt(lat2int) - lat << ")\n"
                  << "  Longitude2Int: " << lon2int << " (err: " << map_lon_to_flt(lon2int) - lon << ")\n";
        */
        Node *n = new Node(Point(lat2int, lon2int), std::stoi(data[4]));
        cnt++;
        plane.insert(n);
        std::cout << cnt << '\n';
        if(cnt == 3173647) break;
    }
}
