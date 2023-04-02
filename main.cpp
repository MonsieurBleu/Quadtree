#include <quadtree.hpp>

void checkheap()
{
    int hchk = _heapchk();
    if(hchk == _HEAPOK)
        std::cout << "Program quit with no heap error\n";
    else
        std::cout << "Program quit with heap error " << hchk <<" !\n";
}

int main(int argv, char* argc[])
{
    atexit(checkheap);
    std::cout << "~~~ QUADTREE ~~~\n";



    return EXIT_SUCCESS;
}