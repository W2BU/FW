#include <TransportNet.cpp>
#include <gtest/gtest.h>

TEST(TransportNet, data1)
{
    TransportNet myNet("data.txt");
    std::cout << myNet.flightCost(0, 2);
    std::cout << myNet.flightCost("Vladivostok", "Moscow");
}

TEST(TranportNet, data2)
{
    TransportNet myNet("data.txt");
    std::cout << myNet.flightCost(0, 2);
    std::cout << myNet.flightCost("Vladivostok", "Moscow");
}

TEST(TransportNet, data3)
{
    TransportNet myNet("data.txt");
    std::cout << myNet.flightCost(0, 2);
    std::cout << myNet.flightCost("Vladivostok", "Moscow");
}