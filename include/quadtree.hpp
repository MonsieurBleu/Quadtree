#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <iostream>

// #define NODE_NON_UNIFORM 0b11111111
// #define PIXEL_EMPTY 0
// #define PIXEL_BLACK 1

typedef enum
{
    NODE_UNIFORM = 0b11111111,
    PIXEL_EMPTY = 0,
    PIXEL_BLACK = 1,
} Pixel_color;

typedef enum
{
    TOP_LEFT = 0,
    TOP_RIGHT = 1,
    BOTTOM_LEFT = 2,
    BOTTOM_RIGHT = 3
} QN_child_id;

#define DEFAULT_DEPTH 3

struct Pixel
{
    uint8_t color = PIXEL_EMPTY;
    uint8_t depth;
};

std::ostream& operator<<(std::ostream& os, const Pixel& p);

struct coord2D
{
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& os, const coord2D& p);

struct Quadnode
{   
    Pixel val = {PIXEL_EMPTY};
    bool isleaf = false;

    Quadnode *topl = nullptr;
    Quadnode *topr = nullptr;
    Quadnode *botl = nullptr;
    Quadnode *botr = nullptr;

    ~Quadnode();
    void del();
    Quadnode *create_son(QN_child_id id, Pixel_color color);
};

class Quadtree
{
    private :
        Quadnode root;

        uint8_t max_depth = DEFAULT_DEPTH;
        coord2D size;
        coord2D sizeh;

    public : 
        Quadtree();
        void set_max_depth(int newmd);
        Pixel pixel(coord2D coord);
        void place(Pixel_color color, coord2D start, coord2D end, Quadnode *node = NULL);

        void generate_debug();
        void print();
};



#endif