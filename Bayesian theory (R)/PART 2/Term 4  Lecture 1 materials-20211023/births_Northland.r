#births_Northland
#(83 / 4580),(64 / 4640),(83 / 5450)
Y <- c(83,64,83)
N <- c(4580,4640,5450)

##Set parameters for Gamma prior

alpha <- 0.03
beta <- 1

##Sufficient statistics

sumY <- sum(Y)
sumN <- sum(N)

##updated parameters for the posterior
post_alpha <- sumY + alpha
post_beta <- sumN + beta

##Posterior predictive inference
#P(Y2018|Y,N2018)
#Suppose 10% increase in population

N2018 <- 1.1*N[3]

##repeatedly draw values of \lambda from the posterior
##then generate Y2018 from a Poisson give N2018 and the generated value of 
## \lambda

####specify desired posterior sample size

nsim <- 2000
###set up structure to store generated Y 2018 values

store_Y2018 <- vector(mode="integer",length=nsim) #note mode=integer becaue
                                                  #we generate discret counts
                                                  #mode="numeric" would be more
                                                  #general.
for (i in 1:nsim) {
  lambda_i <- rgamma(n=1,shape=post_alpha,rate=post_beta)
  Y2018_i <- rpois(n=1,lambda = (lambda_i*N2018) )
  store_Y2018[i] <- Y2018_i
}
###get some basic posterior summaries
summary(store_Y2018)
quantile(store_Y2018,probs=c(0.025,0.5,0.975))

##probability more than 120 births
mean(store_Y2018 > 120)

##histogram

hist(store_Y2018, main="Posterior predictive distibution for births in 2018")
##
##Alternative way of doing the simulation which is faster because it makes use
## use of the fact that rpois and rgamma are vectorised

lambda_post <- rgamma(n=nsim,shape=post_alpha,rate=post_beta)
summary(lambda_post)

Y2018_ppd <- rpois(n=nsim,lambda <- (N2018*lambda_post) )
summary(Y2018_ppd)
