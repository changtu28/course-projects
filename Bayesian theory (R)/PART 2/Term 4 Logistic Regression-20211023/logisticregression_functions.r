###Functions to help with logistic regression examples.

###Setting priors
##Functions to help with  prior specification

makepriorb0 <- function(low,high,credibility) {
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

###Function to evaluate the log-likelihood for a given logistic
###regression model at a given set of parameter values
##It is assumed glm or bayesglm has already been run and the result
#returned to as an R model object  

loglike_logit <- function(beta,model) {
  ##model is a model object returned by glm(); it 
  #contains the data and information
  #about  the model that we want to fit.
  #using it as a parameter  here saves re-specifying the model 
  #structure
  ##
  ##for testing
  #model <- logitmodel  
  #beta <- bhat
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

# function to evaluate log-posterior for  a logistic regression model 
#with specified prior mean and variance, evaluated at a given 
#set of parameter values


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

###version of laplace that allows maximum number of iterations to be
## increased
##modified version of laplace which allows iteration number to be set
##default is set to 1000. (original laplace function has maxiter set 500)
mylaplace <- function (logpost, mode, maxiter=1000,...) 
{
  options(warn = -1)
  fit = optim(mode, logpost, gr = NULL, ..., hessian = TRUE, 
              control = list(fnscale = -1,maxit=maxiter))
  options(warn = 0)
  mode = fit$par
  h = -solve(fit$hessian)
  p = length(mode)
  int = p/2 * log(2 * pi) + 0.5 * log(det(h)) + logpost(mode, 
                                                        ...)
  stuff = list(mode = mode, var = h, int = int, 
               converge = fit$convergence ==  0,
               code=fit$convergence,counts=fit$counts)
  return(stuff)
}