#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <iostream>

// #define NODE_NON_UNIFORM 0b11111111
// #define PIXEL_EMPTY 0
// #define PIXEL_BLACK 1

typedef enum
{
    NODE_NON_UNIFORM = 0b11111111,
    PIXEL_EMPTY = 0,
    PIXEL_BLACK = 1,
} Pixel_color;

#define DEFAULT_DEPTH 4

struct Pixel
{
    uint8_t color = PIXEL_EMPTY;
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
    Pixel val = {NODE_NON_UNIFORM};
    uint8_t depth = 0;

    Quadnode *topl = nullptr;
    Quadnode *topr = nullptr;
    Quadnode *botl = nullptr;
    Quadnode *botr = nullptr;

    ~Quadnode();
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
        void place(Pixel_color color, coord2D start, coord2D end);

        void generate_debug();
};



#endif