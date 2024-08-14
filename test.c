#include "stdio.h"
#include "math.h"

int ft_round(float a)
{   
    float fractional_part = a - (int)a;
    if (fractional_part > 0.5)
        return ((int)a + 1);
    else
        return ((int)a);
}
int main()
{
    float a = 1.5;
    int b = ft_round(a);
    // float fractional_part = a - (int)a;
    printf ("the b %d\n", b);
}