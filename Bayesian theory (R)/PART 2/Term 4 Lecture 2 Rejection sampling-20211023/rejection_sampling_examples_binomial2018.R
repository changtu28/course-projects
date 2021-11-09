library(MASS)          
library(MCMCpack)
library(arm)   #gives access to logit and inverse logit functions
library(logitnorm)  
library(LearnBayes) ##access to laplace approximation etc
library(logitnorm)
#gives access to logit - normal density function

wd <- "~/Patrick/Stat314-2018/code" ##change to own folder or better
                                    ##still set this up as project in 
                                    ##Rsstudio

setwd(wd)
####################################################################
###Illustration of likelihood as a function of the model parameter

###Binomial - data from 6 binomial studies each with N trials


Y <- c(6,7,5,5,4,8)
N <- rep(10,length(Y) )

##Compute some summaries typically involved in Bayesian calculations
##Useful later
NmY <- N-Y

sumY <- sum(Y)
sumNmY <- sum(N-Y)
sumY
sumNmY
##We will assume a binomial likelihood

##Illustration of (log-) likelihood  as a function of the model 
#parameter function to compute the log-likelihood for a 
#given success probability. Usually best to work on a log-scale 
#when doing numerical  work with likelihoods  and posteriors

loglike_binom <- function(theta,Y,N)  {
  logl <- dbinom(Y,N,prob=theta,log=TRUE)
  return(sum(logl))
}

##Evaluate at  few points
loglike_binom(theta=0.4,Y=Y,N=N)
loglike_binom(theta=0.1,Y=Y,N=N)
loglike_binom(theta=0.8,Y=Y,N=N)
###Plot the log-likelihood for a range of sucesss probabilities

testtheta <- seq(from=0.01,to=0.99,by=0.01) #range of theta's to test

##set up structure to store log-likelihoods for plotting
loglstore <- vector(mode="numeric",length=length(testtheta))

##Loop over theta values and compute the corresponding log-likelihood

for (i in 1:length(testtheta)) {
  loglstore[i] <- loglike_binom(theta=testtheta[i],Y=Y,N=N)
}
loglstore

###Plot the log-likelihood

plot(testtheta,loglstore,main="log-likelihood for Binomial example")

##clearer if we plot a line? A continuous function after all

plot(testtheta,loglstore,type="l",lwd=2.0,main="log-likelihood for Binomial example")


##################################################################
##
##Rejection sampling for Non-conjugate problem - Binomial model for the data but
##instead of a Beta(a,b) prior we will adopt a 
##logit-normal prior for theta, i.e logit(theta) ~Normal(mu,sigma2)

###plot the logit-normal density

##first define a function to simulate from the logit-normal
rlogitnormal <- function(n,mu,sigma) {
  require(arm)
  l <- rnorm(n=n,mean=mu,sd=sigma)
  theta <- invlogit(l)
  return(theta)
}

##specify parameters of the prior
mu_prior <- logit(0.5)
sigma_prior <- 5

###Plot the prior
testtheta <- rlogitnormal(n=10000,mu=mu_prior,sigma=sigma_prior)
density_prior <- density(testtheta,from=0,to=1)
plot(density_prior,main=paste("logitN(",round(mu_prior,2),",",sigma_prior,")",sep=""))
summary(testtheta)

###rejection sampling.
###If our approximation is the prior r(\theta) is the likelihood. 
#Hence we accept draws with probability Likelihood/M
### where M is the value of the likelihood evaluated at the MLE

####Often easier to work on the log-scale
###Find log(M)

###In this case the MLE is sum(Y)/sum(N)
logM <- loglike_binom(theta=(sum(Y)/sum(N)),Y=Y,N=N) ##working with the
                                                  #unnormalized density

##Could use the sample of logit-theta  values already generated
#but to better illustrate the idea of 
#rejection sampling we use the following loop.

simnum <- 2000 #desired simulation sample size
storetheta <- vector(mode="numeric",length=simnum)
accepted <- 0
rejected <- 0

while(accepted < simnum) {
  theta_prop <- rlogitnormal(n=1,mu=mu_prior,sigma=sigma_prior)
  ###Evaluate the likelihood at this proposal
  llike_prop <- loglike_binom(Y=Y,N=N,theta=theta_prop)
  
  
  U <- runif(1)
  if (log(U) < llike_prop - logM) {
    accepted <- accepted + 1
    storetheta[accepted] <- theta_prop
  } else {
    rejected <- rejected + 1
  }
}
summary(storetheta)
plot(density(storetheta))
accepted
rejected

acceptance_rate <- accepted/(accepted+rejected)
acceptance_rate

###reproduce posterior density plot with prior superimposed 
#- to illustrate ideas around quality of 
##approximatin density
plot(density(storetheta),
     main="rejection sampler logit-normal(0,5) prior",lwd=2,xlim=c(0,1)) 
lines(density_prior,lwd=2,col="red")

##Repeat  this with  alternative prior again use prior as 
##approximating density

##specify parameters of the prior
mu_prior <- logit(0.5)  #logit(0.5) =0
sigma_prior <- 1

###Plot the prior
testtheta <- rlogitnormal(n=10000,mu=mu_prior,sigma=sigma_prior)
density_prior <- density(testtheta,from=0,to=1)
plot(density_prior,main=paste("logitN(",round(mu_prior,2),",",sigma_prior,")",sep=""))
summary(testtheta)

###rejection sampling.
###If our approximation is the prior r(\theta) is the likelihood. 
#Hence we accept draws with probability Likelihood/M
### where M is the value of the likelihood evaluated at the MLE

####Often easier to work on the log-scale
###Find log(M)

###In this case the MLE is sum(Y)/sum(N)
logM <- loglike_binom(theta=(sum(Y)/sum(N)),Y=Y,N=N) ##working with the
#unnormalized density

##Could use the sample of logit-theta  values already generated
#but to better illustrate the idea of 
#rejection sampling we use the following loop.

simnum <- 2000 #desired simulation sample size
storetheta <- vector(mode="numeric",length=simnum)
accepted <- 0
rejected <- 0

while(accepted < simnum) {
  theta_prop <- rlogitnormal(n=1,mu=mu_prior,sigma=sigma_prior)
  ###Evaluate the likelihood at this proposal
  llike_prop <- loglike_binom(Y=Y,N=N,theta=theta_prop)
  
  
  U <- runif(1)
  if (log(U) < llike_prop - logM) {
    accepted <- accepted + 1
    storetheta[accepted] <- theta_prop
  } else {
    rejected <- rejected + 1
  }
}
summary(storetheta)
plot(density(storetheta))
accepted
rejected

acceptance_rate <- accepted/(accepted+rejected)
acceptance_rate

###reproduce posterior density plot with prior superimposed 
#- to illustrate ideas around quality of 
##approximatin density
plot(density(storetheta),
     main="rejection sampler logit-normal(0,1) prior",lwd=2,xlim=c(0,1)) 
lines(density_prior,lwd=2,col="red")

##change the approximation 

##a better approximating density could be obtained by
## approximating the logit-normal prior by a beta distribution and 
### using conjugacy to obtain a beta approximation to the posterior

##Go back to the original prior
mu_prior <- logit(0.5)
sigma_prior <- 5
##Re-draw the logit-normal  sample from the prior
testtheta <- rlogitnormal(n=10000,mu=mu_prior,sigma=sigma_prior)
density_prior <- density(testtheta)
plot(density(testtheta,from=0,to=1),main=paste("logitN(",round(mu_prior,2),",",sigma_prior,")",sep=""))
summary(testtheta)

###obtain a beta distribution with the same mean and variance as logit-normal sample
mean_theta <- mean(testtheta)
var_theta <- (sd(testtheta))^2
mean_theta
var_theta

a <- (mean_theta^2*(1-mean_theta) - var_theta*mean_theta)/var_theta 
b <- a*(1-mean_theta)/mean_theta
a
b

###plot the beta density with these values 
##could  do  exactly using dbeta but will simulate

apprxtheta <- rbeta(10000,a,b)
summary(apprxtheta)
mean(apprxtheta)
(sd(apprxtheta))^2
density_prior_beta <- density(apprxtheta,from=0,to=1)

plot(density_prior_beta,main=paste("beta(",round(a,2),",",round(b,2),")",sep=""))


###beta approximation to the posterior  -- 
#this will be the approximating density for the rejection sampler
## That is we are approximating the posterior with a distribution 
## that could plausibly  have been the posterior had a conjugate prior
##prior been adopted.

apos <- a + sumY #sum_i Y_i
bpos <- b + sumNmY  #sum_i (N_i-Y_i)

#check approximate posterior mean
apos/(apos+bpos)

pos_approx <- rbeta(10000,apos,bpos)
density_pos_betaapprx <- density(pos_approx)
plot(density(pos_approx))

####Need to find max of 
#Binomial(Y|N,\theta)logit(theta|mu,\sigma) / beta(\theta|apos,bpos);
# (on log scale)
###set up a function for logr(theta)
##Function to compute logr
logr <- function(phi) {
  rtheta <- (sum(Y)*log(phi) + sum(N-Y)*log(1-phi) + 
               dlogitnorm(q=phi,mu=mu_prior,s=sigma_prior,log=TRUE))
              - dbeta(phi,shape1=apos,shape2=bpos,log=TRUE)
  return(rtheta)}

#evaluate logr over the (0,1) interval

theta_test <- seq(from=0.001,to=0.999,by=0.0001)
logrtheta<- logr(phi=theta_test)
summary(logrtheta)

plot(theta_test,logrtheta)

which.max(logrtheta)  ###This identifies the position in the logrtheta vector
                      ###at which the maximum value of logrtheta is found

theta_maxr <- theta_test[which.max(logrtheta)]     #Value of theta which maximises logrtheta
logM2 <- logrtheta[which.max(logrtheta)]
theta_maxr
logM2
##check logM2 should equal the value of logr evaluated at theta_maxr
logr(theta_maxr)

 ###Set up the rejection sampler
simnum <- 2000 #desired simulation sample size
storetheta2 <- vector(mode="numeric",length=simnum)
accepted2 <- 0
rejected2 <- 0

while(accepted2 < simnum) {
  theta_prop <- rbeta(n=1,shape=apos,shape2=bpos)
  ###Evaluate the log - importance ratio at this proposal
  logr_prop <- logr(phi=theta_prop)
  
  U <- runif(1)
  if (log(U) < logr_prop - logM2) {
    accepted2 <- accepted2 + 1
    storetheta2[accepted2] <- theta_prop
  } else {
    rejected2 <- rejected2 + 1
  }
}
summary(storetheta2)
plot(density(storetheta2))
accepted2
rejected2

acceptance_rate2 <- accepted2/(accepted2 + rejected2)
acceptance_rate2
##Superimpose density plot for beta approximation  densisty to 
#illustrate good approximator
plot(density(storetheta2),main="rejection sampler using beta density as the
       approximator",
     xlim=c(0,1),lwd=2)
lines(density_pos_betaapprx,lwd=2,col="red")

####Repeat the beta-approximation approach for the model with 
#(logit-normal(0,1) ) prior

mu_prior <- logit(0.5)
sigma_prior <- 1

##Re-draw the logit-normal  sample from the prior
testtheta <- rlogitnormal(n=10000,mu=mu_prior,sigma=sigma_prior)
density_prior <- density(testtheta)
plot(density(testtheta,from=0,to=1),main=paste("logitN(",round(mu_prior,2),",",sigma_prior,")",sep=""))
summary(testtheta)

###obtain a beta distribution with the same mean and variance as logit-normal sample
mean_theta <- mean(testtheta)
var_theta <- (sd(testtheta))^2
mean_theta
var_theta

a <- (mean_theta^2*(1-mean_theta) - var_theta*mean_theta)/var_theta 
b <- a*(1-mean_theta)/mean_theta
a
b

###plot the beta density with these values 
##could  do  exactly using dbeta but will simulate

apprxtheta <- rbeta(10000,a,b)
summary(apprxtheta)
mean(apprxtheta)
(sd(apprxtheta))^2
density_prior_beta <- density(apprxtheta,from=0,to=1)
plot(density_prior_beta,main=paste("beta(",round(a,2),",",round(b,2),")",sep=""))


###beta approximation to the posterior  -- 
#this will be the approximating density for the rejection sampler
## That is we are approximating the posterior with a distribution 
## that could plausibly  have been the posterior had a conjugate prior
##prior been adopted.

apos <- a + sumY #sum_i Y_i
bpos <- b + sumNmY  #sum_i (N_i-Y_i)

#check approximate posterior mean
apos/(apos+bpos)

pos_approx <- rbeta(10000,apos,bpos)
density_pos_betaapprx <- density(pos_approx)
plot(density(pos_approx))

####Need to find max of 
#Binomial(Y|N,\theta)logit(theta|mu,\sigma) / beta(\theta|apos,bpos);
# (on log scale)
###set up a function for logr(theta)
##Function to compute logr
logr <- function(phi) {
  rtheta <- (sum(Y)*log(phi) + sum(N-Y)*log(1-phi) + 
               dlogitnorm(q=phi,mu=mu_prior,s=sigma_prior,log=TRUE))
  - dbeta(phi,shape1=apos,shape2=bpos,log=TRUE)
  return(rtheta)}

#evaluate logr over the (0,1) interval

theta_test <- seq(from=0.001,to=0.999,by=0.0001)
logrtheta<- logr(phi=theta_test)
summary(logrtheta)

plot(theta_test,logrtheta)

which.max(logrtheta)  ###This identifies the position in the logrtheta vector
###at which the maximum value of logrtheta is found

theta_maxr <- theta_test[which.max(logrtheta)]     #Value of theta which maximises logrtheta
logM2 <- logrtheta[which.max(logrtheta)]
theta_maxr
logM2
##check logM2 should equal the value of logr evaluated at theta_maxr
logr(theta_maxr)

###Set up the rejection sampler
simnum <- 2000 #desired simulation sample size
storetheta3 <- vector(mode="numeric",length=simnum)
accepted3 <- 0
rejected3 <- 0

while(accepted3 < simnum) {
  theta_prop <- rbeta(n=1,shape=apos,shape2=bpos)
  ###Evaluate the log - importance ratio at this proposal
  logr_prop <- logr(phi=theta_prop)
  
  U <- runif(1)
  if (log(U) < logr_prop - logM2) {
    accepted3<- accepted3 + 1
    storetheta3[accepted3] <- theta_prop
  } else {
    rejected3 <- rejected3 + 1
  }
}
summary(storetheta3)
plot(density(storetheta3))
accepted3
rejected3

acceptance_rate3 <- accepted3/(accepted3 + rejected3)
acceptance_rate3
##Superimpose density plot for beta approximation  densisty to 
#illustrate good approximator
plot(density(storetheta3),main="rejection sampler using beta density as the
     approximator",
     xlim=c(0,1),lwd=2)
lines(density_pos_betaapprx,lwd=2,col="red")


##################################################################################################
####Population estimation example


theta = 0.87  #assumed known capture probability
X  = 4350   ##observed sample size

#set-up functions that are needed
logpN <- function(N,n,p0) { #log-likelihood
  ##N is the population size
  ##n is the observed count
  ##p0 is is the probability of under coverage; i.e 
  #probability of being missed in the
  ##observed count.
  
  logdens <- lchoose(N,n) + (N-n)*log(p0)
  return(logdens)
}

###illustrate logpN
logpN(N=5000,n=4350,p0=(1-0.87))
logpN(N=4000,n=4350,p0=(1-0.87)) #see what happens to the likelihood
                                 #at points less than the observed count


acceptN_uniprior <- function(n0,pmiss,ntry,lower,upper) {
  ##assumes a  uniform prior in the interval lower,upper 
  #n0 is the observed number of people
  #pmiss 
  #ntry is the maximum number of attemts at generating N
  ###values for testing
  #n0 <- 5000000
  #pmiss <- 0.1
  
  ##calls the function logpN
  
  #max_logdens <- logpN(N=guess,n=nobs,p0=pmiss)
  #max_logdens <- max_logpN
  
  guess = n0/(1-pmiss)
  
  max_logdens <- logpN(N=guess,n=n0,p0=pmiss)
  
  #
  accept <- 0
  attempt <- 1
  while((accept < 1) & (attempt < (ntry + 1))) {
    Ntest <- round(runif(1,(lower-0.5),(upper+0.5)))  #proposal drawn from a uniform
    logpNtest <- logpN(N=Ntest,n=n0,p0=pmiss)
    check <- logpNtest - max_logdens
    u <- runif(1,0,1)
    if (u <= exp(check)) 
    {accept <- 1}
    attempt <- attempt + 1
  }   #end while loop
  return(c(Ntest,attempt))
}  #End function

###Rejection sampling to obtain a sample of  2000
npos <- 2000
possamp <- vector(mode="numeric",length=npos)
nattempts <- vector(mode="numeric",length=npos)

##set prior for population sample size

lower_prior <- 4000
upper_prior <- 6350
for (i in 1:npos) {
  newN <- acceptN_uniprior(n0=X,pmiss=(1-theta),ntry=5000,
                           lower=lower_prior,upper=upper_prior)
  possamp[i] <- newN[1]
  nattempts[i] <- newN[2]
}
summary(possamp)
summary(nattempts) 
##total number attempts to get posterior sample of size simnum
sum(nattempts)

##acceptance rate:
npos/sum(nattempts)

#plot posterior histogram
hist(possamp,main=expression(paste("posterior histogram for N given: X=4350,",theta,"=0.87")))

##get summary from the prior for comparison
Napprox <- round(runif(npos,min=lower_prior-0.5,max=upper_prior+0.5)) #approximating discrete uniform
summary(Napprox)  #prior
summary(possamp)  # rejection sampling

###And get some other quantiles
quant_prior <- quantile(Napprox,probs=c(0.025,0.05,0.5,0.95,0.975))
quant_rejection <- quantile(possamp,probs=c(0.025,0.05,0.5,0.95,0.975))

##And get true quantiles by direct computation
range = seq(from=lower_prior,to=upper_prior,by=1)
logprange <- logpN(range,n=4350,p0=1-theta)
probs <- exp(logprange)/sum(exp(logprange))
cdf <- cumsum(probs)

q025 <- sum(cdf <= 0.025)
q05 <- sum(cdf <= 0.05)
q50 <- sum(cdf <= 0.5)
q95 <- sum(cdf <= 0.95)
q975 <- sum(cdf <= 0.975)

##Find the corresponding  quantiles in range

true_quantiles <- range[(1+c(q025,q05,q50,q95,q975))]

##compare with prior and rejection sample

true_quantiles
quant_rejection
quant_prior
