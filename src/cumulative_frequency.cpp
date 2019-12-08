#include <Rcpp.h>
#include <algorithm>

// [[Rcpp::export]]
// Function cumulative_frequency
Rcpp::NumericVector cumulative_frequency(Rcpp::NumericVector& M) {
  Rcpp::NumericVector freq(M.size(), 0);
  if (freq.size() == 1) {
    freq[0] = 1;
  } else {
    std::sort(freq.begin(), freq.end());
    freq[freq.size()-1] = 1;
    for (int k = freq.size()-2; k >= 0; k--) {
      freq[k] = freq[k+1] + 1;
    }
  }
  return freq;
}



/*** R
cumulative_frequency(c(1, 1, 5))
cumulative_frequency(c(6, 5, 4, 3, 2, 1, 1))
*/
