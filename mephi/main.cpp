/**
*   Иванов Дмитрий
*       Т05-31
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include "interpolation/interpolation.hpp"
using namespace std;



#include <cmath>
float MyFunc(float x)
{
    return sin(exp(x/3)/10);
}




void PrintArray(vector<double> &p)
{
    for (std::vector<double>::iterator it = p.begin(); it != p.end(); ++it)
        cout << *it << " ";
    cout << endl;
}


int main()
{
    cout << "Enter the number of known points:";
    int size;
    cin >> size;
    vector<double> x;
    vector<double> y;
    cout << size << endl;
    cout << "Enter the specify certain position for each point:" << endl;
    /*  заносим точки по оси x*/
    for (int i = 0; i < size; i++)
    {
        double temp;
        cout << "x[" << i+1 << "] = ";
        cin >> temp;
        x.push_back(temp);
    }
    /* сортируем */
    sort(x.begin(), x.end());
    /* получем теор. значения */
    for (int i = 0; i < size; i++)
    {
        y.push_back(MyFunc(x.at(i)));
    }
    //PrintArray(x);
    //PrintArray(y);
    /* массив промежуточных знач. по оси x*/
    vector<double> x_p;
    for (int i = 0; i < size-1; i++)
    {
        x_p.push_back((x.at(i) + x.at(i+1))/2);
    }

    vector<double> y_lagr, y_newton, y_teor;
    cout.precision(4);
    for (int i = 0; i < size-1; i++)
    {
        y_lagr.push_back(LagrangeInterpolation(x, y, x_p.at(i)));
        y_newton.push_back(NewtonInterpolation(x, y, x_p.at(i)));
        y_teor.push_back(MyFunc(x_p.at(i)));
        cout << fixed;
        cout << "x = " << x_p.at(i) << " lagr delta  : "  << abs(y_teor.at(i) - y_lagr.at(i)/y_teor.at(i))*100 << "%" << endl;
        cout << "x = " << x_p.at(i) << " newton delta: "  << abs(y_teor.at(i) - y_newton.at(i)/y_teor.at(i))*100 << "%" << endl;
    }

    return 0;
}
