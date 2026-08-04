#include <stdarg.h>
#include <stdio.h>


double average(int quentity , ...);

int main(void)
{
    double w = 37.5;
    double x = 22.5;
    double y = 1.7;
    double z = 10.2;

    printf("%s%.1f; %s%.1f; %s%.1f; %s%.1f\n\n",
        "w = ", w, "x = ", x, "y = ", y, "z = ", z);
    printf("%s%.3f\n%s%.3f\n%s%.3f\n",
    "The average of w and x is ", average(2, w, x),
    "The average of w, x, and y is ", average(3, w, x, y),
    "The average of w, x, y, and z is ", average(4, w, x, y, z));
}



double average(int quentity , ...)
{
    int total = 0;
    va_list arg ;
    va_start(arg,quentity);
    for(int i = 0 ; i < quentity ; i++)
        total += va_arg(arg,double);

    va_end(arg);
    return total / quentity;
}