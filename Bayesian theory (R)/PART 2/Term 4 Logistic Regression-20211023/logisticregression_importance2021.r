###Importance sampling examples: Logistic regression
library(MASS)
library(mvtnorm)
library(LearnBayes) #for laplace function
library(arm)
library(logitnorm)


#################################################################################
##########       Logistic regression example #####################################
##################################################################################


#setwd("~/Patrick/Stat314-2017")   #change this to  whatever  folder the income data is stored in

##here I assume the data is set-up in  a folder called data

readdata <- read.csv("data/nzis11-cart-surf.csv",header=TRUE)
str(readdata)

 summary(readdata$income)
###Set up indicator for people earning more than $1250 per week
attach(readdata)
highincome <- as.numeric(readdata$income > 1250)
str(highincome)
mean(highincome)

agefactor <- relevel(as.factor(readdata$agegrp),"40")
regfactor <-  relevel(as.factor(readdata$lgr),"2")  #Auckland as ref
sexfactor <- relevel(as.factor(readdata$sex),"1")  #male as ref
qualfactor <- relevel(as.factor(readdata$qualification),"2") #school quals as ref
table(qualfactor)
occfactor <- relevel(as.factor(readdata$occupation),"1")
table(occfactor)
table(qualfactor)
wkhours_centred <- readdata$hours-mean(readdata$hours)
wkhours_cen40  <- readdata$hours-40
hourscut <- cut(readdata$hours,breaks=c(0,10,30,40,50,168),
                include.highest=TRUE,right=FALSE)
table(hourscut)
hoursfactor <- relevel(hourscut,"[0,10)")
table(hoursfactor)

###basic models  assuming uniform prors for beta parameter
logitmodel <- glm(highincome ~ hoursfactor + sexfactor + 
                     qualfactor,family=binomial(link="logit") )

summary(logitmodel)
display(logitmodel)


##re-fit  controlling  for occupation
logitmodel2 <- glm(highincome ~ hoursfactor + sexfactor + 
                    qualfactor + occfactor, 
                   family=binomial(link="logit") )

summary(logitmodel2)
display(logitmodel2)

##Should really control for age also income changes with age and age is also 
#related to quals

##re-fit  controlling  for occupation and age
logitmodel3 <- glm(highincome ~ hoursfactor + sexfactor + 
                     qualfactor + occfactor +agefactor, 
                     family=binomial(link="logit") )

summary(logitmodel3)
display(logitmodel3)

##For convenience we will base our importance sampling demonstration 
#on the simpler model:#model 1; Note this is just because its 
#easier to display the results for this model. 
##In real life choice of model would be informed by the 
#underlying theory and science and not ease of display!

###Specify priors:
###################################################################
##Analysis with an informative prior
##################################################################

###specify  desired posterior sample size
npos <- 2000

##Functions to help with  prior specification

makepriorb0 <- function(low,high,credibility) {
  #low - lower prior credible limit on the probability scale
  #high - upper prior credible limit on probability  scale
  
  ###returns mean and standard deviation for logit-transformed parameter
  require(arm)
  logit_low <- logit(low)
  logit_high <- logit(high)
  
  priormean <- 0.5*(logit_low + logit_high)
  
  normal_quantile <- 1 - (1-credibility)/2
  priorsd <- (logit_high - priormean)/qnorm(normal_quantile)
  outlist <- c(priormean,priorsd) 
}
testprior <- makepriorb0(low=0.1,high=0.5,credibility=0.95)
testprior

makepriorbreg <- function(low,high,credibility) {
  #low- lower prior credible limit on odds ratio scale
  #high - upper prior  credible limit on odds ratio scale
  
  #returns prior mean and standard deviation corresponding to
  ##log-transformed parameter
  require(arm)
  log_low <- log(low)
  log_high <- log(high)
  
  priormean <- 0.5*(log_low + log_high)
  
  normal_quantile <- 1 - (1-credibility)/2
  priorsd <- (log_high - priormean)/qnorm(normal_quantile)
  outlist <- c(priormean,priorsd) 
}

##obtain priors for parameter
##Intercept - specify prior interval on the probability scale
b0prior <- makepriorb0(low=0.1,high=0.5,credibility=0.95)
b0prior

##logistic regression parameters
##specify prior on odds ratio scale; makepriorreg converts to prior on the beta scale
bhours10_30 <- makepriorbreg(low=1,high=5,credibility=0.9)
bhours30_40 <- makepriorbreg(low=1,high=5,credibility=0.9)                          
bhours40_50 <- makepriorbreg(low=1,high=5,credibility=0.9)
bhours50pl <- makepriorbreg(low=1.1,high=10,credibility=0.9)
bfemale   <- makepriorbreg(low=0.5,high=1.1,credibility=0.95)
bqualnone <- makepriorbreg(low=0.4,high=2,credibility=0.95)
bqualtrade <- makepriorbreg(low=0.7,high=3,credibility=0.95)
bqualuni <- makepriorbreg(low=0.7,high=4,credibility=0.95)
bqualother <- makepriorbreg(low=0.1,high=10,credibility=0.95)

###check  a few of these
bfemale
bqualuni

##combine prior means into a vector and construct a 
#diagional prior variance matrix
##based on the prior  standard deviations prior.matrix 

#First put everything in matrix - column1= priormeans, 
#column 2 = prior sd
prior.matrix<- rbind(b0prior,bhours10_30,bhours30_40,bhours40_50,
                     bhours50pl,bfemale,bqualnone,bqualtrade,
                     bqualuni,bqualother)
prior.matrix

prior_mean_inf <- prior.matrix[,1]    #prior mean vector
prior_variance_inf <- diag((prior.matrix[,2])^2)  #prior variance matrix

prior_mean_inf
prior_variance_inf

###Set-up functions to compute the log-likelihood
###and log-posterior

loglike_logit <- function(beta,model) {
  ##model is a model object returned by glm(); it 
  #contains the data and information
  #about  the model that we want to fit.
  #using it as a parameter of the log-likelihood function
  #here saves re-specifying the model 
  #structure
  ##
  #################################################################
  
  if (is.vector(beta)) {beta <- matrix(beta,nrow=1,ncol=length(beta))}
  ##beta assumed to be nsim by p matrix where nsim is number of bete values to be evaluated 
  ##and p is the dimension of the parameter vector in the model
  ##model is a model object which contains the modelformula, the data, the model  matrix and so on
  X <- model.matrix(model)
  Xb <- X %*% t(beta)
  #Xb <- 
  #
  Y <- model$y
  Ymatrix <- matrix(Y,nrow=length(Y),ncol=nrow(beta),byrow=FALSE)
  loglike <- Ymatrix*Xb - log(1+exp(Xb))
  sumlogl <- colSums(loglike)
  return(sumlogl)
}


###Try out this function for a few values of beta
##at the mle
bmle <- coef(logitmodel)

loglike_good <- loglike_logit(beta=bmle,model=logitmodel)
loglike_good

loglike_bad <- loglike_logit(beta=rep(0,length(bmle)),model=logitmodel)
loglike_bad


##write a function to evaluate the unnormalized log posterior 
##(i.e ignoring the integration constant)
##We will assume  a normal prior here with mean=mean_prior, 
#variance=variance_prior,and logistic regression model likelihood


logpost_logit_norm <- function(beta,prior_mean,prior_variance,model) {
  #Function to combine a logistic model likelihood with a normal prior: 
  #the priormean for the parameters is in prior_mean
  #the prior variance matrix is prior_variance. If there are k parameters then prior_mean
  #will have length k and prior_variance will a be k by k matrix. If the parameters are
  #judged a priori independent prior_variance will be a diagonal matrix
  
  # It is assumed the function loglike_logit(beta,model) to compute the logistic
  #regression log-likelihood has already been defined
  # beta is the parameter value or values we want to evaluate the posterior for
  #beta is either a vector of length k or an nsim by k matrix. 
  log_posterior <- loglike_logit(beta=beta,model=model) + 
    dmvnorm(x=beta,mean=prior_mean,sigma=prior_variance,log=TRUE)
  return(log_posterior)
}


##We could make the log-posterior function more general  by passing in 
#the name of the log-likelihood
#function as an argument of the function and, similarly, 
#instead of assuming a 
#multivariate normal prior setting up the function to  accept the name of  
#a prior-function as an argument. However, for  simplicity, the function has been 
##defined to  be specific to a logistic regression likelihood 
#and  a multivariate
#normal prior.

###Build an approximate posterior to use as an approximating 
#density for the importance sampler. We will use a multivariate normal
#as the approximating density. We will centre this MVN density at the
#posterior mode  and approximate the variance by a measure of the shape
##of the (unnormalized) posterior near the mode 
#(inverse of second-derivative, evaluated at the mode). We can use 
#laplace() function to fund the posterior mode and approximate variance
#based on our 

postapprx <- laplace(logpost=logpost_logit_norm,mode=bmle,
                          prior_mean=prior_mean_inf,
                          prior_variance=prior_variance_inf,
                          model=logitmodel)
str(postapprx)
##Extract the approximations to posterior  mean and variance
apprxmean <- postapprx$mode
apprxvariance <- postapprx$var

apprxmean
apprxvariance[1:3,1:3] ##Just for viewing

##We will  base our  approximating density  for importance 
#sampling on the multivariate normal  defined by
#apprxmean and apprxvariance.

##We want to make the importance sampling approximation more 
#dispersed than 
##the target so inflate the variance

impcovb <- 2*apprxvariance
###draw the importance sample
impb <- mvrnorm(n=npos,mu=apprxmean,Sigma=impcovb)
# str(impb)

#Evaluate the log importance ratio at each simulated parameter value
##importance ratio is unnormalized posterior. denisty/approximating 
#density so 
 ##the log of this ratio is log(unnormalized posterior) -log approximating

logimpwt <- ( logpost_logit_norm(beta=impb,prior_mean=prior_mean_inf,
                                prior_variance=prior_variance_inf,
                                 model=logitmodel)
              - mvtnorm::dmvnorm(impb,mean=apprxmean,
                                 sigma=apprxvariance,log=TRUE
                                 )
  )
str(logimpwt)
head(logimpwt)

## plot histgram

hist(logimpwt)

## histogram of largest log importance weights

q70 <- quantile(logimpwt,probs=0.7)
hist(logimpwt[logimpwt > q70])

##get weighted up posterior summaries
##To avoid numerical issues we first centre the log weight at the 
#average log weight
relwt <- ( exp(logimpwt-mean(logimpwt))/
          sum(exp(logimpwt-mean(logimpwt)))
)
sum(relwt)
summary(relwt)
Neff <- 1/sum(relwt^2)
Neff

##so relative sampling effeciency is:
rse <- Neff / npos
rse

## posterior mean
posmean <- relwt %*% impb
posmean <- posmean[1,]  ##makes posmean a row vector; 
                        ##relwt %*% impb 
                        ##returns a matrix
posmean
##compare with the mle and the posterior mode
cbind(bmle,apprxmean,posmean)

##posterior variance because we are dealing with a vector 
##parameter this is slightly more awkward

##Crude - but we can just do a loop to build the sum
##Vector version of weighted variance
impvarb <- matrix(0,nrow=ncol(impb),ncol=ncol(impb))
for (i in 1:nrow(impb)) {
  impvarb <- (impvarb + 
            relwt[i] * (t(impb[i,]-posmean) %*% 
                          (impb[i,]-posmean) )
             )
}
##approximate standard errors

post_sd <- sqrt(diag(impvarb))
post_sd

##So one summary of the logistic regression fit is

cbind(t(posmean),post_sd)


##resample with probability proportional to relwt - 
#makes posterior calculations easier

betasamp <- sample(length(relwt),size=length(relwt),
                   replace=TRUE,prob=relwt)
newbeta <- impb[betasamp,]
colMeans(newbeta)

##compare with the weighted approximation
posmean

#posterior standard deviations
possd_resample <- sqrt(diag(cov(newbeta)))

##compare with weighted importance sampling approximation

cbind(post_sd,possd_resample)

##certainly looks like the resampling approach is reliable
## may reflect the fairly even distribution of importance weigts


#compare with standard errors from ordinary logistic regression
#and posterior apprx
stderr <- sqrt(diag(vcov(logitmodel)))  
apprxstderr <-  sqrt(diag(apprxvariance)) ##from mvn approz
cbind(stderr,apprxstderr,post_sd)

## posterior density plot for teriary education effect

density_tertiary <- density(newbeta[,9],adjust=2.0)

##normal density based on  approximation from laplace()
norm_tertiary <- dnorm(density_tertiary$x,mean=apprxmean[9],
                       sd=sqrt(apprxvariance[9,9]))


plot(density_tertiary,lwd=2,xlim=c(0.6,1.1),
     ylim=c(0,max(density_tertiary$y,norm_tertiary)),
     main="posterior density plot for tertiary effect")
lines(x=density_tertiary$x,y=norm_tertiary,col="red",lwd=2)
legend("topleft",
legend=c("normal","importance"),lwd=c(1.2,1.2),col=c("red","black"),
cex=0.8)

##repeat the whole exercise with a subsample

set.seed(200661)
sampleindx <-  sample(nrow(readdata),size=100,replace=FALSE)

sampledata <- readdata[sampleindx,]

###etc - exercise for reader
