#pragma once

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const float GRAVITY = 9.81f;


constexpr int PIXELS_PER_METER = 80; // 640 / 80 = 8

constexpr int SCALED_WIDTH = SCREEN_WIDTH / PIXELS_PER_METER;
constexpr int SCALED_HEIGHT = SCREEN_HEIGHT / PIXELS_PER_METER;
