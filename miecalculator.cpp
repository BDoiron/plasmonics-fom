#include <complex>
#include <cmath>
#include <boost/math/special_functions/math_fwd.hpp>

using namespace std;
using namespace boost::math;
double pi = 3.14159;

double mieCalculator (double n, double k, double size, double ns, double wav, int ref)
{
    complex<double> m(n/ns,k/ns);
    double x0 = 2*pi*ns*size/wav;
    complex<double> x(2*pi*ns*size/wav,0);

    complex<double> A=(m*m*sph_bessel(1,m*x)*(2.0*sph_bessel(1,x)-x*sph_bessel(0,x))-sph_bessel(1,x)*(2.0*sph_bessel(1,m*x)- m*x*sph_bessel(0,m*x)))/(m*m*sph_bessel(1,m*x)*0.5*(sph_hankel_1(0,x0)-sph_hankel_1(2,x0)-sph_hankel_1(1,x0)/x)-sph_hankel_1(1,x0)*(2.0*sph_bessel(1,m*x)-m*x*sph_bessel(0,m*x)));
    complex<double> B=(sph_bessel(1,m*x)*(2.0*sph_bessel(1,x)-x*sph_bessel(0,x))-sph_bessel(1,x)*(2.0*sph_bessel(1,m*x)- m*x*sph_bessel(0,m*x)))/(sph_bessel(1,m*x)*0.5*(sph_hankel_1(0,x0)-sph_hankel_1(2,x0)-sph_hankel_1(1,x0)/x)-sph_hankel_1(1,x0)*(2.0*sph_bessel(1,m*x)-m*x*sph_bessel(0,m*x)));

    if(ref==0)
    {
        return 6*(norm(A)+norm(B))/(x0*x0);
    }
    else if (ref==1)
    {
        return -6*(A.real()+B.real())/(x0*x0);
    }
    else if (ref==2)
    {
        return -6*(norm(A)+norm(B)-A.real()-B.real())/(x0*x0);
    }
    else
    {
        return 0;
    }

}


