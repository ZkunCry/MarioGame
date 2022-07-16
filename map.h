#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

const int H = 17;
const int W = 166;
float offsetX = 0, offsetY = 0;

String TileMap[H] = {
"0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                                    0",
"0                                                                                                                                                                    0",
"0                                       w                                 2                                                                                          0",
"0                   w                                  W                              w                                                                              0",
"0                                                                                                                                                                    0",
"0                      c                                                                                      kkkkkkkkkkk                                            0",
"0                                                                                                                                                                    0",
"0                                                                                                                                                                    0",
"0                                                                                                                                                                    0",
"0               c    kckck                                               t0           t0                   kck                                                       0",
"0                                                      t0                00           00                                                                             0",
"0G                                     t0              00                00 G         00                                                                             0",
"0           d    g        u            00              00        g       y0           y0d    g    u                                                                  0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPqqPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPqqPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPqqPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};
