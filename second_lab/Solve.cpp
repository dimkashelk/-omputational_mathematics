#include "Solve.h"

int dimkashelk::details::solve(int n, int ndim,
                               double *a, double b[],
                               int pivot[])

/* Purpose :
   -------
   Solution of linear system, a * x = b.
   Do not use if decomp() has detected singularity.

   Input..
   -----
   n     = order of matrix
   ndim  = row dimension of a
   a     = triangularized matrix obtained from decomp()
   b     = right hand side vector
   pivot = pivot vector obtained from decomp()

   Output..
   ------
   b = solution vector, x

*/

{
    /* --- begin function solve() --- */

    int i, j, k, m;
    double t;

    if (n == 1) {
        /* trivial */
        b[0] /= a[0];
    } else {
        /* Forward elimination: apply multipliers. */
        for (k = 0; k < n - 1; k++) {
            m = pivot[k];
            t = b[m];
            b[m] = b[k];
            b[k] = t;
            for (i = k + 1; i < n; ++i) b[i] += a[(i * ndim + k)] * t;
        }

        /* Back substitution. */
        for (k = n - 1; k >= 0; --k) {
            t = b[k];
            for (j = k + 1; j < n; ++j) t -= a[(k * ndim + j)] * b[j];
            b[k] = t / a[(k * ndim + k)];
        }
    }

    return (0);
} /* --- end function solve() --- */

dimkashelk::Solve::Solve(std::vector<std::vector<double> > &matrix_left,
                         std::vector<double> &matrix_right): data_(nullptr),
                                                             pivot_(nullptr) {
}
