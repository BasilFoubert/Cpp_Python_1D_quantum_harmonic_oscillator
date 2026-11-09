#include "basis.h"
#include "poly.h"
#include <cmath>


#define PI 3.141592653589793

double factorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

Basis::Basis(double br, double bz, int N, double Q)
    : br(br), bz(bz), N(N), Q(Q)
{
    this->mMax=this->calc_mMax();
    this->nMax=this->calc_nMax();
    this->n_zMax=this->calc_n_zMax();
}

double Basis::get_br() const {
    return br;
}

double Basis::get_bz() const {
    return bz;
}

int Basis::get_N() const{
    return N;
}

double Basis::get_Q() const{
    return Q;
}

float Basis::nu(int i){
    return ( ((get_N() + 2) * pow(get_Q(), 2.0/3.0)) + (1.0/2.0) - i*get_Q());
}

unsigned int Basis::calc_mMax(){
    return std::floor(
        ( ((get_N() + 2) * pow(get_Q(), 2.0/3.0)) - (1.0/2.0))/get_Q()
    );
}


arma::ivec Basis::calc_nMax() {
    int mMax = calc_mMax();
    arma::ivec L;
    for (int m = 0; m < mMax; m++) {
        float n_max_m = (mMax - m - 1) * 1.0 / 2.0 + 1.0;
        L.resize(L.n_elem + 1);
        L(L.n_elem - 1) = n_max_m;
    }
    return L;
}


arma::imat Basis::calc_n_zMax(){
    int mMax = calc_mMax();
    arma::imat M;
    arma::irowvec V;


    //m = 0
    for(int n = 0; n<(mMax - 1)/2 + 1; n++){
        V.resize(V.n_elem + 1);
        V(V.n_elem - 1) = std::floor(nu(2*n + 1));
    }


    int nb_rows = V.n_elem;

    for(int m = 0; m < mMax; m++){
        arma::irowvec V = arma::zeros<arma::irowvec>(nb_rows);;
        for(int n = 0; n < ((mMax - m - 1)/2 + 1); n++){

            V(n) = nu(m + 2*n + 1);
        }

        M.insert_rows(M.n_rows, V);

    }
    return M;
}





arma::vec Basis::zPart(arma::vec z, int nz){
    poly.calcHermite(std::floor(nu(1)),(z / bz));
    arma::vec calcVals = poly.hermite(nz); //Cette ligne est correct
    double zPart_without_hermite1 = (1/std::sqrt(this->get_bz()))*(1/std::sqrt(std::pow(2,nz)*std::sqrt(PI)*factorial(nz)));
    arma::vec zPart_without_hermite2 = arma::exp(-arma::square(z)/(2*std::pow(this->get_bz(), 2)));
    arma::vec zPart_without_hermite = zPart_without_hermite1 * zPart_without_hermite2;
    return zPart_without_hermite % calcVals;
}

arma::vec Basis::rPart(arma::vec r, int m, int n){
    //b-per est bz ou br ?
    double r_without_lag1 = (1/(br*std::sqrt(PI)))*std::sqrt(factorial(n)/(factorial(n+std::abs(m))));
    arma::vec r_without_lag2=arma::exp(-arma::square(r)/(2*std::pow(br, 2)))%arma::pow((r/br), std::abs(m));
    
    // poly.calcLaguerre(std::abs(m),n,(arma::pow(r,2)/(br)));
    poly.calcLaguerre(std::abs(m),n,(arma::pow(r,2)/(pow(br,2))));
    arma::vec calc_vals_l = poly.laguerre(m,n);

    return r_without_lag1*r_without_lag2%calc_vals_l;
    
}

// arma::mat Basis::basisFunc (int m,  int n, int n_z, arma::vec zVals, arma::vec rVals){
//     arma::rowvec zPart = this->zPart(zVals, n_z);
//     arma::colvec rPart = this->rPart(rVals, m, n);
//     arma::mat result = rPart * zPart;
//     return result;
// }

arma::mat Basis::basisFunc ( int m,  int n, int n_z, arma::vec zVals, arma::vec rVals){
    arma::vec zPart = this->zPart(zVals, n_z);
    arma::vec rPart = this->rPart(rVals, m, n);
    arma::mat result = rPart * zPart.t();  // .t() transposes zPart
    return result;
}