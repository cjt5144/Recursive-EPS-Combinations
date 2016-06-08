/*
The MIT License (MIT) Copyright (c) 2016 Christopher Thompson

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <Rcpp.h>
#include "polyfeatures.h"

/* EPSC
 *
 * Exponential Power Sum Combinations Matrix Input Function
 *
 * Function illustrates how to use powerTable function in 
 * in polyfeatures.h to create a matrix with all
 * combinations of exponential power sums.
 * 
 * Args
 * ----
 * a NumericMatrix
 * 		Input
 * maxeps Unsigned
 * 		Max power sum number
 *
 * Returns
 * -------
 * NumericMatrix of the size (<number of example a> x <length of powerTable>)
 */
// [[Rcpp::export]]
Rcpp::NumericMatrix epsc(Rcpp::NumericMatrix a, unsigned maxeps) {
	using namespace Rcpp;
	
	PTable pt = PTable();
	unsigned nFeatures = a.ncol();
	unsigned nrows = a.nrow();
	
	powerTable(nFeatures, maxeps, &pt);
	
	unsigned L = pt.t.size();
	NumericMatrix mx = NumericMatrix(nrows, L);
	
	for(unsigned i = 0; i < L; i++) {
		for(unsigned j = 0; j < nrows; j++) {
			mx(_, i) = mx(_, i) * pow(a(_, j), pt.t.at(i).at(j));
		}
	}
	return mx;
}
