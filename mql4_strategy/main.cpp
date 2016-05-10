#include <iostream>

using namespace std;

extern void OnInit();
extern void OnDeinit();
extern void OnTick();

int main()
{
    OnInit();



    OnDeinit();
    return 0;
}

