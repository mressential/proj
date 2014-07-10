#include <iostream>

using namespace std;

typedef float Tf;

char GetSymbol()
{
    return cin.get();
}

void SetSymbol(char c)
{
    cin.putback(c);
}


Tf GetNumber()
{
    char c;
    Tf word = 0;
    for (;;)
    {
        c = GetSymbol();
        if ((c >= '0')&&(c <= '9'))
        {
            word = word * 10 + c - '0';
        }
        else
        {
            SetSymbol(c);
            break;
        }
    }
    return word;
}



Tf Priority2()
{
    Tf word = GetNumber();
    for (;;)
    {
        char c = GetSymbol();
        switch (c)
        {
        case '*':
            word *= GetNumber();
            break;
        case '/':
            word /= GetNumber();
            break;
        default:
            SetSymbol(c);
            return word;
        }

    }
}


Tf Priority3()
{
    Tf word = Priority2();
    for (;;)
    {
        char c = GetSymbol();
        switch (c)
        {
        case '+':
            word += Priority2();
            break;
        case '-':
            word -= Priority2();
            break;
        default:
            SetSymbol(c);
            return word;
        }

    }
}

Tf Priority1()
{
    char c = GetSymbol();
    if ('(' == c)
    {
        float word = Priority3();
        if (GetSymbol() != ')')
            cout << "error )" << endl;
        return word;
    }
    else
    {
        SetSymbol(c);
        return GetNumber();
    }
}

int main()
{
    cout << "res = " << Priority3() << endl;
    return 0;
}
