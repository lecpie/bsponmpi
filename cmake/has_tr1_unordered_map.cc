#include <tr1/unordered_map>

int main(int argc, char ** argv )
{
    (void) argc; (void) argv;
    std::tr1::unordered_map< int, float > map;
    map[5] = 2.30f;
    int x = map.size();
    return x != 1;
}

