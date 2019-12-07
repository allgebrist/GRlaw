
plot_earthquake_distribution <- function(earthquake_count, earthquake_magnitude, fit_line = FALSE) {
  
  earthquake_distribution <- data.frame("earthquake_count" = earthquake_count, 
                                        "earthquake_magnitude" = earthquake_magnitude)
  
  plt <- plot_ly(earthquake_distribution, 
                 x = ~earthquake_magnitude, 
                 y = ~earthquake_count, 
                 color = ~earthquake_magnitude, 
                 size = ~earthquake_magnitude) %>%
         add_trace(x = ~earthquake_magnitude, 
                   name = 'Earthquake') %>%
         layout(title = "Earthquake Distribution",
                yaxis = list(type = "log"))
  plt
}