#include "controller.hxx"

#include <stdexcept>
#include <string>

using namespace std;

int main()
{
    Player p({750, 800}, {0, 0});
    Controller(p).run();
}