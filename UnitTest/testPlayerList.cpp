#include "pch.h"
#include "../2048_SFML/PlayerList.hpp"
#include "../2048_SFML/PlayerList.cpp"

// Test the default constructor
TEST(PlayerListTest, DefaultConstructor) {
    PlayerList list;
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_EQ(list.getMaxScore(), 0);
}

// Test adding a player
TEST(PlayerListTest, AddPlayer) {
    PlayerList list;
    list.addPlayer("player1", 100, 10.0, "password1");
    EXPECT_EQ(list.getSize(), 1);
    EXPECT_EQ(list.getMaxScore(), 100);
    EXPECT_TRUE(list.findPlayer("player1"));
}

// Test removing a player
TEST(PlayerListTest, RemovePlayer) {
    PlayerList list;
    list.addPlayer("player1", 100, 10.0, "password1");
    list.removePlayer("player1");
    EXPECT_EQ(list.getSize(), 0);
    EXPECT_FALSE(list.findPlayer("player1"));
}

// Test finding a player
TEST(PlayerListTest, FindPlayer) {
    PlayerList list;
    list.addPlayer("player1", 100, 10.0, "password1");
    EXPECT_TRUE(list.findPlayer("player1"));
    EXPECT_FALSE(list.findPlayer("player2"));
}

// Test getting a player
TEST(PlayerListTest, GetPlayer) {
    PlayerList list;
    list.addPlayer("player1", 100, 10.0, "password1");
    Player* player = list.getPlayer("player1");
    EXPECT_EQ(player->getName(), "player1");
    EXPECT_EQ(player->getScore(), 100);
    EXPECT_EQ(player->getTime(), 10.0);
    EXPECT_EQ(player->getPassword(), "password1");
}

// Test finding a player's position
TEST(PlayerListTest, FindPlayerPosition) {
    PlayerList list;
    list.addPlayer("player1", 100, 10.0, "password1");
    list.addPlayer("player2", 200, 20.0, "password2");
    EXPECT_EQ(list.findPlayerPosition(150, 15.0), 2);
    EXPECT_EQ(list.findPlayerPosition(250, 25.0), 1);
}
