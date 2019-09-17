#include <iostream>
#include <stdio.h>
#include <string>
#include "function.h"
using namespace std;

class Polynomial
{
    public:
        Polynomial();
        Polynomial(const int , const int [51]);
        Polynomial add( const Polynomial) const; // add function
        Polynomial subtract( const Polynomial ) const; // subtract function
        Polynomial multiplication( const Polynomial ) const; // multiplication function
        void output() const;
    private:
        int coefficients[101]; // integer coefficients
        int greatestPower; // integer greatestPower
}; // end class Polynomial

Polynomial::Polynomial()
{
    for(int i=0;i<=101;i++){
        coefficients[i]=0;
    }
    greatestPower = 0;
}
Polynomial::Polynomial(const int power,const int coefficient[51])
{
    greatestPower = power;
    for(int i=0;i<=power;i++){
        coefficients[i]=coefficient[i];
    }
    for(int i = power+1;i<=51;i++){
        coefficients[i]=0;
    }
}
Polynomial Polynomial::add(const Polynomial b) const
{
    Polynomial ans;
    if(b.greatestPower>=this->greatestPower) ans.greatestPower = b.greatestPower;
    else ans.greatestPower = this->greatestPower;
    for(int i=0;i<=ans.greatestPower;i++){
        ans.coefficients[i] = b.coefficients[i] + this->coefficients[i];
    }
    return ans;
}
Polynomial Polynomial::subtract(const Polynomial b) const
{
    Polynomial ans;
    if(b.greatestPower>=this->greatestPower) ans.greatestPower = b.greatestPower;
    else ans.greatestPower = this->greatestPower;
    for(int i=0;i<=ans.greatestPower;i++){
        ans.coefficients[i] = this->coefficients[i] - b.coefficients[i];
    }
    return ans;
}
Polynomial Polynomial::multiplication(const Polynomial b) const
{
    Polynomial ans;
    ans.greatestPower = this->greatestPower+b.greatestPower;
    for(int i=0;i<=b.greatestPower;i++){
        for(int j=0;j<=this->greatestPower;j++){
            ans.coefficients[i+j] = ans.coefficients[i+j] + this->coefficients[j]*b.coefficients[i];
        }
    }
    return ans;
}
void Polynomial::output() const
{
    for(int i=this->greatestPower;i>=1;i--){
        cout << this->coefficients[i] << " ";
    }
    cout << this->coefficients[0];
}
int main()
{
    int greatestPower1, greatestPower2;
    int coefficient1[51], coefficient2[51];
    Polynomial ans;

    cin>>greatestPower1;
    for(int i = greatestPower1 ; i >= 0; i--)
    {
        cin>>coefficient1[i];
    }
    cin>>greatestPower2;
    for(int i = greatestPower2 ; i >= 0 ; i--)
    {
        cin>>coefficient2[i];
    }
    Polynomial a(greatestPower1, coefficient1), b(greatestPower2, coefficient2) ;

    ans = a.add( b );
    ans.output();
    cout << endl;

    ans = a.subtract( b );
    ans.output();
    cout << endl;

    ans = a.multiplication( b );
    ans.output();
    cout << endl;

} // end main
