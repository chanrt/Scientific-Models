#define PI 3.14159265358979323846

#include<iostream>
#include<math.h>

using namespace std;

class Complex
{
    private:
        float real, imag;

    public:
        Complex()
        {}

        Complex(float r)
        {
            real = r;
            imag = 0.0;
        }

        Complex(float r, float i)
        {
            real = r;
            imag = i;
        }

        void setComplex(float r, float i)
        {
            real = r;
            imag = i;
        }

        void displayComplex(int format)
        {
            //mode corresponds to a+bi form 
            printf("\n%f + i%f",real,imag);
        }

        void displayComplex()
        {
            //default mode corresponds to (a,b) form
            printf("\n( %f , %f )",real,imag);
        }

        void displayPolar()
        {
            float r, angle;
            getPolar(r,angle);
            printf("\nPolar form: ( %f , %f )",r,angle);
        }

        float getRealPart()
        {
            return real;
        }

        float getImagPart()
        {
            return imag;
        }

        float getMagnitude()
        {
            return sqrt(real*real + imag*imag);
        }

        Complex getConjugate()
        {
            Complex conj;

            conj.real = real;
            conj.imag = - imag;

            return conj;
        }

        Complex operator + (Complex c)
        {
            Complex sum;

            sum.real = real + c.real;
            sum.imag = imag + c.imag;

            return sum;
        }

        Complex operator - ()
        {
            Complex neg;

            neg.real = - real;
            neg.imag = - imag;

            return neg;
        }

        Complex operator - (Complex c)
        {
            Complex neg;

            neg.real = real - c.real;
            neg.imag = imag - c.imag;
        }

        Complex operator * (Complex c)
        {
            Complex prod;

            prod.real = real*c.real - imag*c.imag;
            prod.imag = real*c.imag + imag*c.real;

            return prod;
        }

        Complex operator / (Complex c)
        {
            Complex quo;
            float deno;

            deno = c.real*c.real - c.imag*c.imag;
            quo.real = (real*c.real + imag*c.imag) / deno;
            quo.imag = (imag*c.real - real*c.imag) / deno;

            return quo;
        }

        Complex operator = (Complex c)
        {
            Complex eq;

            eq.real = c.real;
            eq.imag = c.imag;

            return eq;
        }

        bool operator == (Complex c)
        {
            return (real == c.real && imag == c.imag);
        }

        void getPolar(float &r, float &angle)
        {
            r = sqrt(real*real + imag*imag);
            angle = atan(imag/real);
            angle = 180 * angle / PI;
        }
};

 Complex reciprocal (Complex c)
{
    Complex reci;
    float deno;
    float r = c.getRealPart(), i = c.getImagPart();

    deno = r*r - i*i;
    reci.setComplex(r / deno, - i / deno);

    return reci;
}

Complex rationalize(Complex nr, Complex dr)
{
    Complex rational;
    float deno;
    float r = dr.getRealPart(), i = dr.getImagPart();

    deno = r*r - i*i;
    Complex prod = nr * dr.getConjugate();
    rational.setComplex( prod.getRealPart() / deno, prod.getImagPart() / deno);

    return rational;
}

Complex power(Complex c, int pow)
{
    if(pow == 0)
    {
        Complex r(1);
        return r;
    }
    else if(pow == 1)
    {
        return c;
    }
    else if(pow < 0)
    {
        return reciprocal(power(c, -pow));
    }
    else
    {
        return c * power(c, pow-1);
    }
}

int main()
{
    /* code */
}
