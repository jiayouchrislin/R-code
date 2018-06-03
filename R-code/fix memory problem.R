# address 0xdb, cause 'memory not mapped'

install.packages(c("RCurl", "swirl"))
library(swirl)
swirl()

# address 0x18, cause ‘memory not mapped’  
ip <- installed.packages()
pkgs.to.remove <- ip[!(ip[,"Priority"] %in% c("base", "recommended")), 1]
sapply(pkgs.to.remove, remove.packages)
ip <- installed.packages()
pkgs.to.remove <- ip[!(ip[,"Priority"] %in% c("base", "recommended")), 1]
sapply(pkgs.to.remove, install.packages)

#address 0x8, cause 'memory not mapped'
Rcpp.package.skeleton('testpkg1', module=T)
require(testpkg1)
modtest <- new(World)
show(modtest)
modtest$set('hello')