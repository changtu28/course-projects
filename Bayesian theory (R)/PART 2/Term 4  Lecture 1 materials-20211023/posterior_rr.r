####Using simulation to generate the posterior of a function of 
#random variables
###e.g.  two groups of patients randomised to group drug A and drug B respectively.

###set-up the data
YA <- 7   #successes
Na <- 10

YB <- 3
Nb <- 10

##YA |Na, thetaA ~ Binomial(thetaA,Na)
##YB |Nb, thetaB ~ Binomial(thetaB,Nb)

##p(thetaA,thetaB) = p(thetaA)p(thetaB)
##thetaA ~ Beta(1,1)
#thetaB ~ (Beta(1,1)
##We are interested in the relative risk thetaA/thetaB

### Suppose we are interested in the relative risk: thetaA /thetaB

#Under our model assumptions
#p(thetaA,thetaB|data) = p(thetaA|DataA)p(thetaB|DataB)
#                      = Beta(1+YA,Na-YA+1)Beta(1+YB,Nb-YB+1)

##Monte Carlo evaluation for relative risk is therefore

nsim <- 10000 ## fix  simulation sample size

postA <- rbeta(n=nsim,shape1=1+YA,shape2=Na-YA+1)
postB <- rbeta(n=nsim,shape1=1+YB,shape2=Nb-YB+1)

str(postA)
str(postB)

RR <- postA / postB
plot(density(RR))

summary(RR)
##Get useful summary quantiles
qRR <- quantile(RR,probs=c(0.025,0.5,0.975))
qRR
 
###Frequentist approach - large sample approximation

##Variance of logRR #

thetaAhat = YA/Na
thetaBhat = YB/Nb
RRhat = thetaAhat/thetaBhat
logRRhat <- log(RRhat)

  
  
VlogRR <- (1/YA)^2 *Na*thetaAhat*(1 - thetaAhat) + (1/YB)^2*Nb*thetaBhat*(1-thetaBhat)
selogRR <- sqrt(VlogRR)

###Find confidence interval endpoints
loglowcl <- logRRhat - 1.96*selogRR
loghicl <- logRRhat + 1.96*selogRR

lowcl <- exp(loglowcl)
hicl <- exp(loghicl)

c(lowcl,RRhat,hicl)
qRR

##Frequentist confidence interval uses  an asymptotic approximation
##Bayes credible interval uses a Monte Carlo  approximation
