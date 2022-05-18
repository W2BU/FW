#include <TransportNet.cpp>
#include <gtest/gtest.h>

TEST(TransportNet, data1)
{
    TransportNet myNet("data.txt");
    EXPECT_EQ(myNet.cities(), "0. Saint-Petersburg\n1. Moscow\n2. Khabarovsk\n3. Vladivostok\n");
    EXPECT_EQ(myNet.flightCost("Saint-Petersburg", "Moscow"), 10);
    EXPECT_EQ(myNet.flightCost("Moscow", "Saint-Petersburg"), 20);
    EXPECT_EQ(myNet.flightCost("Khabarovsk", "Saint-Petersburg"), 55);
    EXPECT_THROW(myNet.flightCost("Vladivostok", "Moscow"), std::invalid_argument);
}

TEST(TranportNet, data2)
{
    TransportNet myNet("data2.txt");
    EXPECT_EQ(myNet.cities(), "0. Ekaterinsburg\n1. Yaroslavl\n2. Tomsk\n");
    EXPECT_EQ(myNet.flightCost("Ekaterinsburg", "Yaroslavl"), 1);
    EXPECT_EQ(myNet.flightCost("Yaroslavl", "Ekaterinsburg"), 1);
    EXPECT_EQ(myNet.flightCost("Yaroslavl", "Tomsk"), 1);
    EXPECT_EQ(myNet.flightCost("Tomsk", "Yaroslavl"), 1);
    EXPECT_EQ(myNet.flightCost("Tomsk", "Ekaterinsburg"), 1);
    EXPECT_EQ(myNet.flightCost("Ekaterinsburg", "Tomsk"), 1);
    EXPECT_EQ(myNet.flightCost(0, 1), 1);
    EXPECT_EQ(myNet.flightCost(1, 0), 1);
    EXPECT_EQ(myNet.flightCost(1, 2), 1);
    EXPECT_EQ(myNet.flightCost(2, 1), 1);
    EXPECT_EQ(myNet.flightCost(0, 2), 1);
    EXPECT_EQ(myNet.flightCost(2, 1), 1);
    EXPECT_THROW(myNet.flightCost(0, 3), std::invalid_argument);
    EXPECT_THROW(myNet.flightCost("Moscow", "Ekaterinsburg"), std::invalid_argument);
}

TEST(TransportNet, data3)
{
    TransportNet myNet("data3.txt");
    EXPECT_EQ(myNet.cities(), "0. Ekaterinsburg\n1. Izhevsk\n2. Tomsk\n3. Vladivostok\n");
    EXPECT_EQ(myNet.flightCost("Izhevsk", "Vladivostok"), 3);
    EXPECT_THROW(myNet.flightCost("Vladivostok", "Izhevsk"), std::invalid_argument);
}