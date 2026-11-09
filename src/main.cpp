#include <iostream>
#include <string>
#include "basis.h"
#include "plot.h"
#include <chrono>

//1ère mesure Time taken: 32307 milliseconds (basil)

arma::mat rho; // global


arma::mat calcDensityOpti(arma::vec const& rvals, arma::vec const& zvals, Basis& basis, bool verbose){
    arma::mat result = arma::zeros(rvals.n_elem, zvals.n_elem); // number of points on r- and z- axes
    int a = 0;
    int b = 0;
    int n_vec = 0; // total number of vectors
    int* n_vec_per_m = new int[basis.mMax]; // number of vectors for each value of m

    for (unsigned int m = 0; m < basis.mMax; m++)
    {
        n_vec_per_m[m] = 0;
        for (int n = 0; n < basis.nMax(m); n++)
        {
            n_vec_per_m[m] += basis.n_zMax(m, n) >= 0 ? basis.n_zMax(m, n) : 0;
        }
        n_vec += n_vec_per_m[m];
    }

    arma::mat* func = new arma::mat[n_vec]; // pre-computing the basis

    for (unsigned int m = 0; m < basis.mMax; m++)
    {
        for (int n = 0; n < basis.nMax(m); n++)
        {
            for (int n_z = 0; n_z < basis.n_zMax(m, n); n_z++)
            {
                func[a] = basis.basisFunc(m,  n,  n_z, zvals, rvals);
                a++;
            }
        }
    }

    a = 0;

    for (unsigned int m = 0; m < basis.mMax; m++) {
        int start = a;
        int next_stop = a + n_vec_per_m[m];
        for (; a < next_stop; a++) {
            for (b = start; b < a; b++) {
                result += func[a] % func[b] * rho(a, b); // mat += mat * double
            }
        }
    }

    result = 2 * result;
    
    for (int i = 0; i < n_vec; i++)
    {
        result += func[i] % func[i] * rho(i, i);
        a++;
    }

    delete[] n_vec_per_m;
    delete[] func;
    return result;
}

/**
 * @brief The main function of the program.
 * 
 * writes the density DF3 (3D) and CSV (2D files) from the density matrix rho.arma
 * 
 * @return int Returns 0 upon successful execution.
 */
int main(int argc, char** argv) {
    double br = 1.935801664793151;
    double bz = 2.829683956491218; 
    int N = 14;
    double Q = 1.3;
    rho.load("assets/rho.arma", arma::arma_ascii); 

    Basis basis(br, bz, N, Q);

    Plot plt(20, 40, 32, 64);
    arma::vec rVals3D = plt.get_r_values_3D();
    arma::vec rVals2D = plt.get_r_values_2D();
    arma::vec zVals = plt.get_z_values();

    // benchmarking the computation of the 3D plot
    auto start = std::chrono::high_resolution_clock::now();
    arma::mat polar_values_3D = calcDensityOpti(rVals3D, zVals, basis, true);
    arma::cube plot3D = plt.polar_to_cartesian_3D(polar_values_3D);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken for 3D plot computation : " << duration.count() << " milliseconds" << std::endl;


    plt.write_3D(plot3D, "assets/density3D.df3");
    
    

    // enchmarking the computation of the 2D plot
    start = std::chrono::high_resolution_clock::now();
    arma::mat polar_values_2D = calcDensityOpti(rVals2D, zVals, basis, true);// computation
    arma::mat plot2D = plt.polar_to_cartesian_2D(polar_values_2D);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken for 2D plot computation : " << duration.count() << " milliseconds" << std::endl;


    plt.write_2D(plot2D, "assets/density2D.csv");
    
    return 0;
}
