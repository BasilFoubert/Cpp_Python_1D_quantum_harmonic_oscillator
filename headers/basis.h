#ifndef BASIS_H
#define BASIS_H

#include <cstdint>
#include <armadillo>
#include "poly.h"


/**
 * @class Basis
 * @brief Represents a basis set for quantum mechanical calculations.
 *
 * This class encapsulates the parameters and functions necessary to define a
 * basis set in terms of cylindrical coordinates for quantum mechanical systems.
 * It includes methods for calculating various components of the basis functions
 * and the maximum values of quantum numbers based on the truncation scheme.
 */
class Basis {
    private:
        double br;   ///< Basis deformation parameter in the radial direction.
        double bz;   ///< Basis deformation parameter in the z direction.
        int N;       ///< Principal quantum number for truncation.
        double Q;    ///< Charge or other related quantum mechanical parameter.
        Poly poly;   ///< Polynomial object for various calculations within the basis.

    public:
        /**
         * @brief Construct a new Basis object.
         * @param br Basis deformation parameter in the radial direction.
         * @param bz Basis deformation parameter in the z direction.
         * @param N Principal quantum number for truncation.
         * @param Q Charge or other related quantum mechanical parameter.
         */
        Basis(double br, double bz, int N, double Q);

        // Accessor methods for the basis parameters.
        double get_br() const; ///< Get the radial deformation parameter.
        double get_bz() const; ///< Get the z deformation parameter.
        int get_N() const;     ///< Get the principal quantum number.
        double get_Q() const;  ///< Get the quantum mechanical parameter Q.

        // Maximum quantum numbers based on the basis truncation scheme.
        unsigned int mMax;     ///< Maximum azimuthal quantum number.
        arma::ivec nMax;       ///< Maximum principal quantum number for each m.
        arma::imat n_zMax;     ///< Maximum quantum number in the z direction for each m and n.
        
        /**
        * @brief Compute the value of ν for a given index i.
        *
        * The function ν(i) is defined as (N + 2)^2 * Q^(2/3) + 1/2 - i * Q, where N and Q are
        * the basis truncation parameters.
        *
        * @param i The index for which ν is to be calculated.
        * @return float The calculated value of ν for the given index i.
        */
        float nu(int i); 



        /**
        * @brief Calculate the maximum value of the quantum number m (mMax).
        *
        * mMax is defined as the supremum of {i : ν(i) ≥ 1}. This function calculates the largest
        * integer value of m for which ν(m) is greater than or equal to 1.
        *
        * @return unsigned int The maximum value of the quantum number m.
        */
        unsigned int calc_mMax();

        /**
        * @brief Calculate the maximum value of the quantum number n for each m (nMax).
        *
        * nMax[m] is defined as 1/2 * (mMax - m - 1) + 1. This function calculates the vector of
        * nMax values for a range of m values.
        *
        * @return arma::ivec A vector of the maximum n values for each m.
        */
        arma::ivec calc_nMax();

        /**
        * @brief Calculate the maximum value of the quantum number n_z for each combination of m and n (n_zMax).
        *
        * n_zMax[m, n] is defined as ν(m + 2n + 1). This function calculates a matrix of n_zMax values
        * for a range of m and n values.
        *
        * @return arma::imat A matrix of the maximum n_z values for each combination of m and n.
        */
        arma::imat calc_n_zMax();

        /**
        * @brief Calculate the Z part of the basis function in cylindrical coordinates.
        * 
        * 
        * @param z A vector of the z-coordinate in cylindrical coordinates.
        * @param nz The quantum number associated with the z direction.
        * @return arma::vec The evaluated Z component as a vector.
        */
        arma::vec zPart(arma::vec z, int nz);
        

        /**
        * @brief Calculate the R part of the basis function in cylindrical coordinates.
        *
        * 
        * @param r A vector of the perpendicular (radial) component of the position vector in cylindrical coordinates.
        * @param m The azimuthal quantum number, representing the angular momentum component along the z-axis.
        * @param n The principal quantum number associated with the energy level of the system.
        * @return arma::vec The evaluated R component as a vector.
        */
        arma::vec rPart(arma::vec r, int m, int n);

        /**
        * @brief Calculates the basis function matrix for given quantum numbers and spatial values.
        * 
        * This method multiplies the Z component by the R component to form the basis function
        * for the given quantum numbers (m, n, n_z) and spatial vectors (zVals, rVals).
        * The Z component depends on the z-coordinate and the quantum number n_z.
        * The R component depends on the radial coordinate and the quantum numbers m and n.
        * The result is a matrix constructed by the outer product of the R and Z vectors.
        * 
        * @param m Azimuthal quantum number related to the angular component.
        * @param n Principal quantum number related to the radial component.
        * @param n_z Quantum number related to the z component.
        * @param zVals Vector of z-coordinate values.
        * @param rVals Vector of radial coordinate values.
        * @return arma::mat Matrix representing the basis function.
        */
        arma::mat basisFunc ( int m,  int n, int n_z, arma::vec zVals, arma::vec rVals);
};

#endif // BASIS_H
