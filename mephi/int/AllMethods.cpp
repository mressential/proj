#include <iostream>
#include <cmath>

template< typename Type >
Type func(Type x)
{
    return sin(x);
}


template< typename Type >
Type MethodTrapezium(Type border_left, Type bordef_right, unsigned n, Type (*f)(Type x))
{
    Type
        h = (bordef_right - border_left) / n,
        sum = 0.0d;

    Type
        x_left  = border_left,
        x_right = border_left + h;

    for (unsigned i = 0;
         i <= n - 1;
         i++, x_left += h, x_right += h)
    {
        sum += h*(f(x_left) + f(x_right));
    }

    return 0.5d*sum;
}

template< typename Type >
Type MethodRectangles(Type border_left, Type bordef_right, unsigned n, Type (*f)(Type x))
{
    Type
        h = (bordef_right - border_left) / n,
        sum = 0.0d;

    Type
        x_left  = border_left;

    for (unsigned i = 0;
         i <= n - 1;
         i++, x_left += h)
    {
        sum += f(x_left)*h;
    }

    return sum;
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


typedef long double MyType;

int main()
{
    const unsigned numberPoints = 10;
    const MyType
        left = 0.0d,
        right = M_PI_2; // pi/2

    std::cout << "Simpson Method :    ";
    std::cout << std::scientific << MethodSimpson<MyType>(left, right, numberPoints, func)      << std::endl;
    std::cout << "Trapezium Method :  ";
    std::cout << std::scientific << MethodTrapezium<MyType>(left, right, numberPoints, func)    << std::endl;
    std::cout << "Rectangles Method : ";
    std::cout << std::scientific << MethodRectangles<MyType>(left, right, numberPoints, func)   << std::endl;

    return 0;
}
