#include <iostream>

using namespace std;

int main()
{
    double eps = 1;
    while (eps + 1 != 1)
        eps /= 2;
    cout << eps;
    return 0;
}
