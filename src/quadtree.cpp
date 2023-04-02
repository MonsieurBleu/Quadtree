#include <quadtree.hpp>

std::ostream& operator<<(std::ostream& os, const Pixel& p)
{
    switch(p.color)
    {
    case PIXEL_EMPTY:
        os << " ";
        break;
    
    case PIXEL_BLACK :
        os << "#";
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

Quadnode::~Quadnode()
{
    if(topl) delete topl;
    if(topr) delete topr;
    if(botl) delete botl;
    if(botr) delete botr;
}

void Quadtree::generate_debug()
{
    root.topl = new Quadnode;
    root.topl->val.color = PIXEL_BLACK;
}

Pixel Quadtree::pixel(coord2D coord)
{
    Quadnode *qn = &root;

    while(qn && qn->val.color == NODE_NON_UNIFORM)
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
    }

    if(qn) return qn->val;
    
    Pixel empt;
    return empt;
}

void Quadtree::place(Pixel_color color, coord2D start, coord2D end)
{

}
