#pragma once

#define WORLD_HEIGHT                    200.0f
#define WORLD_WIDTH                     400.0f
#define GRAVITY                         Vector2f(0.0f,10.0f)
#define BOUNDARY_THICKNESS              4.0f
#define BOUNDARY_COLOR                  RalColors::PearlBlackBerry


#define BLOCKS_PER_ROW                  20
#define NR_OF_ROWS                      5
#define BLOCK_Y                         20
#define BLOCK_X                         40
#define BLOCK_COLOR                     RalColors::WhiteAluminium

#define BALL_SIZE                       15
#define BALL_MAXIMUM_SPEED              10.0f
#define BALL_COLOR                      RalColors::DeepOrange
#define BALL_INITSPEED                  10.0f
#define BALL_DAMPENING                  0.0f

#define PADDLE_X                        60
#define PADDLE_Y                        16

#define BOUNDARY_CATEGORY               1
#define BALL_CATEGORY                   2
#define PADDLE_CATEGORY                 3
#define BLOCKS_CATEGORY                 4