#include<windows.h>
#include<direct.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"chan_graphics.c"

typedef struct states
{
    float position, velocity, accn;
} State;

void delay(float mill)
{
    float wait=(mill);

    clock_t start_time = clock();
    while(clock() < start_time + wait);
}

void cwipeline(int y)
{
    for(int x = 2; x <= 109; x++)
    {
        gotoxy(x,y);
        printf(" ");
    }
}

void main()
{
    State *init = (State *) malloc(sizeof(State));
    State *final = (State *) malloc(sizeof(State));

    float pos,vel;
    float intv[81];

    float mass, springConstant, precision, k;
    int limit;

    drawBorder();

    gotoxy(4,2);
    printf("---> Spring Motion <---");

    gotoxy(4,4);
    printf("Enter a high value of k/m to get high frequencies");
    gotoxy(4,5);
    printf("Model is unstable at high frequencies");
    gotoxy(4,6);
    printf("For optimised result, type: 5, 0, 1, 25, 10, 0.01");

    gotoxy(4,8);
    printf("Enter initial position: ");
    scanf("%f",&pos);
    gotoxy(4,9);
    printf("Enter initial velocity: ");
    scanf("%f",&vel);
    gotoxy(4,10);
    printf("Enter mass of body: ");
    scanf("%f",&mass);
    gotoxy(4,11);
    printf("Enter spring constant: ");
    scanf("%f",&springConstant);
    gotoxy(4,12);
    printf("Enter time of simulation: ");
    scanf("%d",&limit);
    gotoxy(4,13);
    printf("Enter precision required: ");
    scanf("%f",&precision);

    k = springConstant / mass;

    init->position = pos;
    init->velocity = vel;
    init->accn = - k * pos;

    float iv = pos / 30;

    for(int i = 0; i <= 39; i++)
    {
        intv[i] = (i - 40)*iv;
    }
    intv[40] = 0.0;
    for(int j = 41; j <= 80; j++)
    {
        intv[j] = (j - 42)*iv;
    }

    for(float time = 0; time <= limit; time = time + precision)
    {
        final->velocity = init->velocity + init->accn * precision;
        final->position = init->position + final->velocity * precision;
        final->accn = - k * final->position;

        gotoxy(24,19);
        printf("Time = %f\t   Position: %f\tVelocity: %f",time,final->position,final->velocity);

        cwipeline(24);
        for(int k = 1; k <= 80; k++)
        {
            if(final->position == 0.0)
            {
                gotoxy(55,20);
                printf("*");
                break;
            }
            else if(final->position < intv[0])
            {
                gotoxy(1,24);
                printf("Out of purview");
            }
            else if(final->position > intv[80])
            {
                gotoxy(98,24);
                printf("Out of purview");
            }
            else if(intv[k] <= final->position && final->position <= intv[k+1])
            {
                gotoxy(15+k,24);
                printf("*");
                if(k > 41)
                {
                    for(int l = 55; l < 15+k; l++)
                    {
                        gotoxy(l,24);
                        printf("-");
                    }
                }
                else
                {
                    for(int l = 55; l > 15+k; l--)
                    {
                        gotoxy(l,24);
                        printf("-");
                    }
                }
            }
            gotoxy(55,24);
            printf("|");
        }

        init->velocity = final->velocity;
        init->position = final->position;
        init->accn = final->accn;
    }
}
