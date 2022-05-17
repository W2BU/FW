#pragma once

#include <Mymap.cpp>
#include <Matrix.cpp>

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <sstream>

class TransportNet
{
    public:
        TransportNet(const std::string& filename);
        ~TransportNet();

        std::string cities();
        double flightCost(const std::string& dispatch, const std::string& destination);
        double flightCost(const int& dispatchIndex, const int& destinationIndex);

    private:

        MyMap<int, std::string> map;
        Matrix adjacencyMatrix;
        Matrix solution;
        std::string* citiesList;
        int mapSize;
        

        void loadFromFile(const std::string& filename);
        int parseForSize(const std::string& filename);
        void solveFloydWarshall();

};

TransportNet::TransportNet(const std::string& filename)
{
    loadFromFile(filename);
}

TransportNet::~TransportNet()
{
    delete[] citiesList;
}

void TransportNet::loadFromFile(const std::string& filename)
{   
    mapSize = parseForSize(filename);
    citiesList = new std::string[mapSize];
    Matrix matrix(mapSize, mapSize);
    adjacencyMatrix = matrix;
    std::string line;
    std::string cost;
    std::string dispatch;
    std::string destination;
    
    std::ifstream flightData(filename);
    if (flightData.is_open()) {
        while (getline(flightData, line)) {

            dispatch = line.substr(0, line.find(';'));
            if (map.has(dispatch)) {
                citiesList[map.findByValue(dispatch)] = dispatch;
            }
            line.erase(0, line.find(';') + 1);

            destination = line.substr(0, line.find(';'));
            if (map.has(destination)) {
                citiesList[map.findByValue(destination)] = destination;
            }
            line.erase(0, line.find(';') + 1);

            cost = line.substr(0, line.find(';'));
            if (cost == "N/A") {
                adjacencyMatrix(map.findByValue(dispatch), map.findByValue(destination)) = std::numeric_limits<double>::infinity();
            } else {
                adjacencyMatrix(map.findByValue(dispatch), map.findByValue(destination)) = std::stod(cost);
            }
            line.erase(0, line.find(';') + 1);

            cost = line.substr(0, line.find(';'));
            if (cost == "N/A") {
                adjacencyMatrix(map.findByValue(destination), map.findByValue(dispatch)) = std::numeric_limits<double>::infinity();
            } else {
                adjacencyMatrix(map.findByValue(destination), map.findByValue(dispatch)) = std::stod(cost);
            }
        }
    } else {
        throw std::invalid_argument("Cannot open the file");
    }
    flightData.close();

    //  filling empty cells with inf
    for (int i = 0; i < mapSize; i++) {
        for (int j = 0; j < mapSize; j++) {
            if (adjacencyMatrix(i, j) == 0 && i != j)
                adjacencyMatrix(i, j) = std::numeric_limits<double>::infinity();
        }
    }

    solution = adjacencyMatrix;
    solveFloydWarshall();
}

int TransportNet::parseForSize(const std::string& filename)
{
    std::string line;
    std::string cost;
    std::string dispatch;
    std::string destination;
    std::ifstream flightData(filename);
    if (flightData.is_open()) {
        while (getline(flightData, line)) {
            dispatch = line.substr(0, line.find(';'));
            line.erase(0, line.find(';') + 1);
            if (!(map.has(dispatch))) {
                map.insert(map.get_size(), dispatch);
            }

            destination = line.substr(0, line.find(';'));
            line.erase(0, line.find(';') + 1);
            if (!(map.has(destination))) {
                map.insert(map.get_size(), destination);
            } 
        }
    } else {
        throw std::invalid_argument("Cannot open the file");
    }
    flightData.close();
    return map.get_size();
}

void TransportNet::solveFloydWarshall()
{
    for (int k = 0; k < mapSize; k++)
        for (int i = 0; i < mapSize; i++)
            for (int j = 0; j < mapSize; j++)
                if (adjacencyMatrix(i, k) < std::numeric_limits<double>::infinity() &&
                    adjacencyMatrix(k, j) < std::numeric_limits<double>::infinity()) {
                    if (adjacencyMatrix(i, j) > (adjacencyMatrix(i, k) + adjacencyMatrix(k, j))) {
                        adjacencyMatrix(i, j) = adjacencyMatrix(i, k) + adjacencyMatrix(k, j);
                        solution(i, j) = k;
                    }
                }

}

std::string TransportNet::cities()
{
    std::stringstream result;
    for (int i = 0; i < mapSize; i++) {
        result << i << ". " << citiesList[i] << "\n";
    }
    return result.str();
}

double TransportNet::flightCost(const std::string& dispatch, const std::string& destination)
{
    if (!map.has(dispatch) || !map.has(destination)) {
        throw std::invalid_argument("One of the name snot found");
    } else {
        int dispatchIndex = map.findByValue(dispatch);
        int destinationIndex = map.findByValue(destination);
        if (adjacencyMatrix(dispatchIndex, destinationIndex) ==  std::numeric_limits<double>::infinity()) {
            throw std::invalid_argument("Way doesn't exist");
        } else {
            return adjacencyMatrix(dispatchIndex, destinationIndex);
        }
    }
}

double TransportNet::flightCost(const int& dispatchIndex, const int& destinationIndex)
{
    if ((dispatchIndex < 0 || dispatchIndex >= mapSize) || 
        (destinationIndex < 0 || destinationIndex >= mapSize)) {
        throw std::invalid_argument("Index not found");
    } else {
        if (adjacencyMatrix(dispatchIndex, destinationIndex) == std::numeric_limits<double>::infinity()) {
            throw domain_error("Way doesn't exist");
        } else {
            return adjacencyMatrix(dispatchIndex, destinationIndex);
        }
    }
}