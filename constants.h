

#define WORLD_HEIGHT                    100.0f
#define WORLD_WIDTH                     80.0f
#define WORLD_HALF_HEIGHT               (WORLD_HEIGHT/2)
#define WORLD_HALF_WIDTH                (WORLD_WIDTH/2)
#define WORLD_PADDLE_WIDTH             (WORLD_HALF_WIDTH - PADDLE_X/2)

#define GRAVITY                         Vector2f(0.0f,10.0f)
#define BOUNDARY_THICKNESS              4.0f
#define BOUNDARY_COLOR                  RalColors::OceanBlue


#define LAST_ROW_HEIGHT                 0
#define FIRST_ROW_HEIGHT                -40
#define BLOCK_Y                         10
#define BLOCK_X                         10
#define BLOCK_ROW_DIST                  0
#define BLOCK_COL_DIST                  2
#define BLOCK_COLOR                     RalColors::WhiteAluminium

#define BALL_SIZE                       1.5f
#define BALL_COLOR                      RalColors::DeepOrange
#define BALL_INIT_POS                   0.0f,10.0f
#define BALL_INITSPEED                  20.0f
#define BALL_DAMPENING                  0.0f
#define PADDLE_HIT_MULTIPLIER           35.0f



#define PADDLE_START_Y                  40.0f
#define PADDLE_X                        8.0f
#define PADDLE_Y                        1.6f
#define PADDLE_COLOR                    RalColors::LemonYellow
#define PADDLE_DAMPENING                0.95f
#define PADDLE_ACC                      0.015f
#define MAX_PADDLE_VEL                  0.2f
#define MIN_PADDLE_VEL                  0.001f

#define MAX_NOT_CONTROL_MULT            0.9f
#define MIN_NOT_CONTROL_MULT            0.05f
#define CONTROL_UP_MULT                 1.1f

#define BOUNDARY_CATEGORY               1
#define BALL_CATEGORY                   2
#define PADDLE_CATEGORY                 3
#define BLOCKS_CATEGORY                 4