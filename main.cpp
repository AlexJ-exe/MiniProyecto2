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
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::ifstream dataset("../dataset.csv");
    std::string aux;
    std::getline(dataset, aux);

    Point center(map_lat_to_int(0.0f), map_lon_to_int(0.0f));
    int distance = INT_MAX / 16;
    
    
    
    Quad plane(Point(-INT_MAX, -INT_MAX), Point(INT_MAX, INT_MAX));
    size_t cnt = 0;
    start = std::chrono::system_clock::now();
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

        Node *n = new Node(Point(lat2int, lon2int), std::stoi(data[4]));
        cnt++;
        plane.insert(n);
        end = std::chrono::system_clock::now();
        if(!(cnt % 100000)) std::cout << "Inserted " << cnt << ", took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() <<'\n';
        if(cnt == 3173647) break;
    }
    end = std::chrono::system_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Inserted all nodes, t = " << elapsed.count() << '\n';

    const size_t runs = 20;
    std::cout << "Testing " << runs << " runs per task, and averaging...";
    
    size_t dists[] = { 51200, 102400, 204800, 409600, 819200, 1638400, 3276800, 6553600, 13107200, 26214400, 52428800, 104857600, INT_MAX / 8 };
    
   
    
    for(size_t dist_i = 0; dist_i < 12; dist_i++) {
        double avg = 0;
        std::cout << "Test " << dist_i + 1 << " with distance " << dists[dist_i] << '\n';
        for(size_t i = 0; i < runs; i++) {
            start = std::chrono::system_clock::now();
            
            plane.aggregateRegion(center, dists[dist_i]);
            
            end = std::chrono::system_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            avg += elapsed.count();
        }
        avg /= runs;
        
        std::cout << "    Average: " << avg << '\n';
    }
    
}
