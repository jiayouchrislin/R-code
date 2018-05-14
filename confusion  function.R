confusion <- function(actual, predicted, names = NULL, printit = TRUE, prior = NULL) {                    
  if (is.null(names))
  names <- levels(actual)
  tab <- table(actual, predicted)
  acctab <- t(apply(tab, 1, function(x) x/sum(x)))
  dimnames(acctab) <- list(Actual = names, "Predicted (cv)" = names)
  if (is.null(prior)) {
  relnum <- table(actual)
  prior <- relnum/sum(relnum)
  acc <- sum(tab[row(tab) == col(tab)])/sum(tab)
  }
 else {
  acc <- sum(prior * diag(acctab))
  names(prior) <- names
  }
  if (printit)
  print(round(c("Overall accuracy" = acc, "Prior frequency" = prior),
                + 4))
  if (printit) {
  cat("\nConfusion matrix", "\n")
  print(round(acctab, 4))
  }
  invisible(acctab)
  }