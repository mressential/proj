#include <iostream>
#include <cmath>

template< typename Type >
Type func(Type x)
{
    return sin(x);
}

template< typename Type >
Type MethodSimpson(Type border_left, Type bordef_right, unsigned n, Type (*f)(Type x))
{

    Type
        h   = (bordef_right - border_left) / n,
        sum = 0.0d;

    Type
        x_left  = border_left,
        x_right = border_left + h;

    for (unsigned i = 0;
         i <= n - 1;
         i++, x_left += h, x_right += h)
    {
        sum += f(x_left) + 4.0d*f(x_left + h/2.0d) + f(x_right);
    }

    return (h/6.0d)*sum;
}


int main()
{
    std::cout << std::scientific << MethodSimpson<long double>(0.0d, M_PI_2, 50, func);
    return 0;
}
