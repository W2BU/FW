#include <TransportNet.cpp>

int main() {
    TransportNet myNet("data.txt");
    std::cout << "List of found cities:\n";
    std::cout << myNet.cities();
    std::cout << "Cost of flight from Saint-Petersburg to Khabarovsk\n";
    std::cout << myNet.flightCost(0, 2);
    std::cout << "\nCost of flight from Vladivostok to Moscow\n";
    std::cout << myNet.flightCost("Vladivostok", "Moscow");
}