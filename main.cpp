#include <iostream>
#include <iomanip>
#include "Math.h"


int main() {
    using namespace Math;using namespace std;
    PowerFunction f(3,1,PowerFunction(1));
    ExpFunction e(1.01,0,Math::exp);
    cout<<setprecision(30)<<endl;
    cout<<e(3)<<endl;//2^(3^2)=
    cout<<f(5)<<endl;
    LogFunction l(2.71828182845904523536028747L,0,e);
    cout<<ln(e(11.999))<<endl;
    cout<<l(101.999)<<endl;
    cout<<std::log(e(11.999))<<endl;
    std::cout << "Hello, World!" << std::endl;

    return 0;
}