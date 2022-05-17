#include <TransportNet.cpp>

int main() {
    TransportNet myNet("data2.txt");
    std::cout << "List of found cities:\n";
    std::cout << myNet.cities();
    std::cout << "Cost of flight from Saint-Petersburg to Khabarovsk\n";
    std::cout << myNet.flightCost(0, 2);
    std::cout << "\nCost of flight from Ekaterinsburg to Yaroslavl\n";
    std::cout << myNet.flightCost("Ekaterinsburg", "Yaroslavl");
}