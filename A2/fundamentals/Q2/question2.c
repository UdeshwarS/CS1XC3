#include <stdio.h>
#include <math.h>

void mileage(void)
{
    double total_fuel = 0.0;
    double total_dist = 0.0;

    char more = 'y';

    while (more == 'y' || more == 'Y')
    {

        double fuel = 0.0;
        double dist = 0.0;

        printf("How much fuel have you used? : ");
        scanf("%lf", &fuel);

        printf("How far did you travel? : ");
        scanf("%lf", &dist);

        total_fuel += fuel;
        total_dist += dist;

        printf("Do you have more data to enter? (y/n) : ");
        scanf(" %c", &more);
    }

    if (total_fuel != 0.0)
    {
        double mileage = total_dist / total_fuel;
        double truncated = trunc(mileage * 10000.0) / 10000.0;
        printf("Your gas mileage is %.4f\n", truncated);
    }
}
int main()
{

    mileage();

    return 0;
}