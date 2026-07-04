#pragma once
#include <string>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
extern float INITIAL_SPEED; // Pixels per second
const float PLAYER_SIZE = 20.f;
const float Mode_SIZE = 120.f;
const float ACCELERATION = 20.f; // Pixels per second
const float APPLE_SIZE = 20.f;
const float PAUSE_LENGTH = 3.f;
const int NUM_ROCKS = 10;
const float ROCK_SIZE = 20.f;
const int Volume = 50;
const int Const_NUM_APPLES = 500;
extern int NUM_APPLES;
extern unsigned int activeModes;
extern int PreSpeed;

enum GameMode 
{
    MODE_NONE = 0,
    MODE_1 = 1 << 0,
    MODE_2 = 1 << 1,
    MODE_3 = 1 << 2,
    MODE_4 = 1 << 3
};