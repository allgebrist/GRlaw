#include <Rcpp.h>
#include <algorithm>

// [[Rcpp::export]]
// Function cumulative_frequency
Rcpp::List cumulative_frequency(Rcpp::NumericVector& magnitudes) {
  Rcpp::List cumulative_frequencies; 
  Rcpp::NumericVector frequencies(magnitudes.size(), 0);
  
  if (frequencies.size() == 1) {
    frequencies[0] = 1;
  } else {
    std::sort(magnitudes.begin(), magnitudes.end());
    std::sort(frequencies.begin(), frequencies.end());
    frequencies[frequencies.size()-1] = 1;
    for (int k = frequencies.size()-2; k >= 0; k--) {
      frequencies[k] = frequencies[k+1] + 1;
    }
  }
  
  cumulative_frequencies = Rcpp::List::create( Rcpp::Named("magnitude") = magnitudes, 
                                               Rcpp::Named("count") = frequencies );
  
  return cumulative_frequencies;
}



/*** R
cumulative_frequency(c(1, 1, 5))
cumulative_frequency(c(6, 5, 4, 3, 2, 1, 1))
*/
