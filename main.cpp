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
    system("cls");
    std::cout << "~~~ QUADTREE ~~~\n";

    Quadtree qt;
    qt.generate_debug();

    qt.print();

    return EXIT_SUCCESS;
}