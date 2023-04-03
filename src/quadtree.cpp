#include <quadtree.hpp>
#include <string.h>

std::ostream& operator<<(std::ostream& os, const Pixel& p)
{
    if(!p.color)
        os << "  ";
    else
    {
        os << (int)p.depth << " ";
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
        topl = nullptr;
    }

    if(topr)
    {
        delete topr;
        topr = nullptr;
    }

    if(botl)
    {
        delete botl;
        botl = nullptr;
    }

    if(botr)
    {
        delete botr;
        botr = nullptr;
    }
}

Quadnode::~Quadnode()
{
    del();
}

Quadnode *Quadnode::create_son(QN_child_id id, Pixel_color color)
{
    Quadnode **node = &topl + id;

    if(*node == nullptr)
    {
        *node = new Quadnode;
        (*node)->val.color = color;
        (*node)->val.depth = val.depth+1;
        (*node)->isleaf = true;
    }

    return *node;
}

void Quadtree::generate_debug()
{
    root.topl = new Quadnode;
    root.topl->val.color = (uint8_t)PIXEL_BLACK;
    root.topl->isleaf = true;
    root.topl->val.depth = 1;

    root.botr = new Quadnode;
    root.botr->val.depth = 1;

    root.botr->topl = new Quadnode;
    root.botr->topl->val.color = (uint8_t)PIXEL_BLACK;
    root.botr->topl->isleaf = true;
    root.botr->topl->val.depth = 2;

    root.botr->topr = new Quadnode;
    root.botr->topr->val.color = (uint8_t)PIXEL_BLACK;
    root.botr->topr->isleaf = true;
    root.botr->topr->val.depth = 2;
}

Pixel Quadtree::pixel(coord2D coord)
{
    Quadnode const *qn = &root;

    coord2D s = sizeh;

    while(qn && !qn->isleaf)
    {   
        if(coord.x < s.x)
        {
            s.x >>= 1;

            if(coord.y < s.y) // bottom left
            {
                s.y >>= 1;
                qn = qn->botl;
            }
            else // bottom right
            {
                s.y += s.y>>1;
                qn = qn->botr;
            }
        }
        else
        {
            s.x += s.x>>1;

            if(coord.y < s.y) // top left
            {
                s.y >>= 1;
                qn = qn->topl;
            }
            else // top right
            {
                s.y += s.y>>1;
                qn = qn->topr;
            }
        }

        // coord.x *= 2;
        // coord.y *= 2;
    }

    if(qn) return qn->val;
    
    Pixel empt;
    return empt;
}

void Quadtree::place(Pixel_color color, coord2D start, coord2D end, Quadnode *node)
{
    if(!node)
        node = &root;
    
    if(start.x == 0 && start.y == 0 && end.x == size.x && end.y == size.y)
    {
        node->del();
        node->val.color = color;
    }

    if(start.x < sizeh.x && start.y < sizeh.y) // bottom left
    {
        coord2D nstart = {start.x - start.x%sizeh.x, 
                          start.y - start.y%sizeh.x};

        coord2D nend   = {end.x - end.x%sizeh.x, 
                          end.y - end.y%sizeh.x};
    }

    if(start.x < sizeh.x && end.y >= sizeh.y) // bottom right
    {
        coord2D nstart = {start.x - start.x%sizeh.x, 
                          start.y%sizeh.x};

        coord2D nend   = {end.x - end.x%sizeh.x, 
                          end.y%sizeh.x};
    }

    if(end.x >= sizeh.x && start.y < sizeh.y) // top left
    {
        coord2D nstart = {start.x%sizeh.x, 
                          start.y - start.y%sizeh.x};

        coord2D nend   = {end.x%sizeh.x, 
                          end.y - end.y%sizeh.x};
    }

    if(end.x >= sizeh.x && end.y >= sizeh.y)  // top right
    {
        coord2D nstart = {start.x%sizeh.x, 
                          start.y%sizeh.x};

        coord2D nend   = {end.x%sizeh.x, 
                          end.y - end.y%sizeh.x};
    }
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