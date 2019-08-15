#ifndef CONSTANTS_H
#define CONSTANTS_H

//地板的尺寸
const int TILE_SIZE = 10;
//蛇移动一次的尺寸
const int SNAKE_SIZE = TILE_SIZE;
//食物的半径
const int FOOD_RADIUS = 3;
//场景的尺寸
const int SCENE_SIZE = 200;

//墙的场景坐标
const int TOP_WALL = -100;
const int BOTTOM_WALL = 100;
const int LEFT_WALL = -100;
const int RIGHT_WALL = 100;

enum GameObjectsData {
    GD_Type
};

enum GameObjectTypes {
    GO_Food,
    GO_Wall
};

#endif // CONSTANTS_H
