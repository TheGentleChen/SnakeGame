#ifndef CONSTANTS_H
#define CONSTANTS_H

//Floor size
const int TILE_SIZE = 10;
//The size of the snake moving once
const int SNAKE_SIZE = TILE_SIZE;
//Radius of food
const int FOOD_RADIUS = 3;
//Scene size
const int SCENE_SIZE = 200;

//The scene coordinates of Wall
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
