#include <quadtree.hpp>
#include <string.h>

std::ostream& operator<<(std::ostream& os, const Pixel& p)
{
    switch(p.color)
    {
    case PIXEL_EMPTY:
        os << "  ";
        break;
    
    case PIXEL_BLACK :
        os << "# ";
        break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const coord2D& c)
{
    os << "[" << c.x << ",\t" << c.y << "]";
    return os;
}

Quadtree::Quadtree()
{
    set_max_depth(DEFAULT_DEPTH);
}

void Quadtree::set_max_depth(int newmd)
{
    max_depth = newmd;
    size.x = 2<<max_depth;
    size.y = size.x;
    sizeh.x = size.x/2;
    sizeh.y = size.y/2;
}

void Quadnode::del()
{
    if(topl)
    {
        delete topl;
    }

    if(topr)
    {
        delete topr;
    }

    if(botl)
    {
        delete botl;
    }

    if(botr)
    {
        delete botr;
    }
}

Quadnode::~Quadnode()
{
    del();
}

void Quadtree::generate_debug()
{
    root.topl = new Quadnode;
    root.topl->val.color = (uint8_t)PIXEL_BLACK;
    root.topl->isleaf = true;
    root.topl->depth = 1;

    root.botr = new Quadnode;
    root.botr->topl = new Quadnode;
    root.botr->depth = 1;

    root.botr->topl->val.color = (uint8_t)PIXEL_BLACK;
    root.botr->topl->isleaf = true;
    root.botr->topl->depth = 2;
}

Pixel Quadtree::pixel(coord2D coord)
{
    Quadnode const *qn = &root;

    while(qn && !qn->isleaf)
    {
        if(coord.x < sizeh.x)
        {
            if(coord.y < sizeh.y) // bottom left
            {
                qn = qn->botl;
            }
            else // bottom right
            {
                qn = qn->botr;
            }
        }
        else
        {
            if(coord.y < sizeh.y) // top left
            {
                qn = qn->topl;
            }
            else // top right
            {
                qn = qn->topr;
            }
        }

        coord.x *= 2;
        coord.y *= 2;
    }

    if(qn && qn->depth >= 1)
    {
        std::cout << "q";
    }

    if(qn) return qn->val;
    
    Pixel empt;
    return empt;
}

void Quadtree::place(Pixel_color color, coord2D start, coord2D end)
{

}


void Quadtree::print()
{
    for(int x = 0; x < size.x; x++)
    {
        for(int y = 0; y < size.y; y++)
        {
            std::cout << pixel({x, y});
        }
        
        std::cout << "|\n";
    }
}