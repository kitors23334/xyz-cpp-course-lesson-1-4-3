#pragma once
#include <string>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
extern float INITIAL_SPEED; // Pixels per second
const float PLAYER_SIZE = 20.f;
const float ACCELERATION = 20.f; // Pixels per second
const float APPLE_SIZE = 20.f;
const float PAUSE_LENGTH = 3.f;
const int NUM_ROCKS = 10;
const float ROCK_SIZE = 20.f;
const int Volume = 50;
const int Const_NUM_APPLES = 500;
extern int NUM_APPLES;

const int Mode = 0; // 0 - ramdom apple, 1 - 20 apple, 2 - 20 apple and speed, 3 - 50 apple and speed
