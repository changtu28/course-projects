##tongue_cancer  analysis
cancerdata <- read.csv("data/tongue_cancer.csv",header=TRUE)
str(cancerdata)
#only a small dataset so why not just print it to have a look

cancerdata

rates <- cancerdata$Cases / cancerdata$Population
summary(rates)

#may make more  sense if expressed as rate per 100000
rates100000 <- rates*100000
summary(rates100000)

rates.df <-  data.frame(cancerdata$Demography,rates100000,rates,
                        cancerdata$Cases,cancerdata$Population)
names(rates.df) <-  c("Dhb","rate_100000","rate","Cases")
rates.df

#What is the overall rate
rawrate <- sum(cancerdata$Cases) /sum(cancerdata$Population)
rawrate*100000 #3.634198

## Basic analysis to  estimate assumed common rate for  all  DHBs
##Simplistic model  but but useful  as  base to  compare against.

##Gamma prior 
a <- 3/100000
b <- 1      #Like saying prior  evidence is  equivalent  to
            #one extra tiny DHB of size 1

totcases <- sum( cancerdata$Cases)
totpop <- sum(cancerdata$Population)

##update to get  parameters of the posterior, using conjugacy

apost <- a + totcases
bpost <- b + totpop

##Compute posterior  summaries
postmean <- apost/bpost
post_median <-  qgamma(0.5,shape=apost,rate = bpost)

postmean * 100000
post_median * 100000

q025 <- qgamma(0.025,shape=apost,rate=bpost)
q975 <-  qgamma(0.975,shape=apost,rate=bpost)

exact_quantiles <- 100000*c(q025,post_median,q975)
exact_quantiles

# Simulation approach - first look at modest size Monte Carlo  sample
post_lambda100 <- rgamma(n=100,shape=apost,rate=bpost)

##check quantiles 
post_quantiles100 <- 
  quantile(post_lambda100,probs=c(0.025,0.5,0.975))

post_quantiles100
exact_quantiles

#check_mean
post_mean100 <- mean(post_lambda100)
100000*post_mean100  #3.662318 

exact_mean <- apost / bpost
100000*exact_mean   #3.634198 

#check standard deviation
post_sd100 <-  sd(post_lambda100)


##Monte Carlo  error for the posterior mean is 
MCerror <- post_sd100 / sqrt(100)
MCerror   #tiny

#makes more sense multiplied by 100000, as per the rates themselves
#  Var(C\theta) = C^2 x Var(\theta) so
# sd(C\theta)    = C X sd(\theta)

100000 * MCerror #0.02695065, still pretty small
                 #MC mean is about 1 MC standard error  from the exact mean



##see what  happens for  a bigger posterior sample

post_lambda1000 <- rgamma(n=1000,shape=apost,rate=bpost)

post_quantiles1000 <- quantile(post_lambda1000,probs=c(0.025,0.5,0.975))
##Compare true and simulation results

exact_quantiles
100000*post_quantiles100
100000*post_quantiles1000

#tail quantiles looking pretty  good by the time Monte Carlo 
#simulation size reaches 1000

#MC error for nsim=1000

post_sd1000 <-  100000*sd(post_lambda1000)
post_sd1000

MC_error1000 <- post_sd1000/sqrt(1000)
MC_error1000

post_mean1000 <- 100000*mean(post_lambda1000)
post_mean1000
100000*exact_mean  #So the MC mean is just over MC standard error from
                   # the true mean
                  #The MC error is fairly trivial though and represents
                  # 1/sqrt(1000) = 3.2% of the posterior standard deviation

# Monte Carlo for  a more complex estimand and model -----------------------
#estimand is "thing to be estimated"

#Instead of  simple common  rate model, let's go to the 
#other extreme and let  each DHB have its own parameter;
#probability that each DHB has highest rate among all DHBs.

#Then we can ask questions like "what is the probability that  each  DHB 
#" has the highest underlying rate among all DHBs"
#" How does a particular  DHB rank in a 'league table' of rates by DHB

# we will use the same prior  for  each DHB
#\lambda ~ gamma(a,b)  a = 3/100000; b=1

fulla_post <-  a + cancerdata$Cases        #vector
fullb_post <- b +   cancerdata$Population  #vector

fulla_post
fullb_post

## rgamma is partially vectorised; Easiest to  loop
## over simulations and on each iteration generate   the vector of lambda
##lambda values for the 20 DHBs
## also  need to  work out the maximum and rank for  each  set  of  lambdas
##generated

M <- 1000 ##number of  draws from  the posterior
n <- length(rates)  #number of groups - DHBs in this case

##Set-up structures  for  storing output

post_fullambda <- matrix(nrow=M,ncol=n )
                     
post_max <- matrix(nrow=M,ncol=n)

post_rank  <- matrix(nrow=M,ncol=n)

for (i in 1:M ) {
  ##can probably draw gammas for all DHBs in one-hit
  fullambda <- rgamma(n,shape=fulla_post,rate=fullb_post)
  
  ranks <- rank(fullambda)
  ismax <- (ranks == max(ranks) )

  post_fullambda[i,] <- fullambda
  post_rank[i,]  <- ranks
  post_max[i,]  <- ismax
 
  }

##check results

##posterior  quantiles for  each DHB

fullpost_quantiles <-  apply(post_fullambda,MARGIN=2,FUN=quantile,
                              probs=c(0.025,0.5,0.975))

fullpost_quantiles.df <-  data.frame(rates.df$Dhb,t(100000*fullpost_quantiles))


fullpost_quantiles.df <- 
cbind(fullpost_quantiles.df,rates.df$Cases)

names(fullpost_quantiles.df) <- c("DHB","q025","q50","q975","cases")
fullpost_quantiles.df

##posterior quantiles for  each DHB's rank
fullpost_ranks_quantiles.df <-  
  apply(post_rank,MARGIN=2,FUN=quantile,
                                    probs=c(0.025,0.5,0.975))

fullpost_ranks_quantiles.df <-  
 data.frame( t(apply(post_rank,MARGIN=2,FUN=quantile,
        probs=c(0.025,0.5,0.975)) ) )

fullpost_ranks_quantiles.df$Dhb <- rates.df$Dhb
fullpost_ranks_quantiles.df
names(fullpost_ranks_quantiles.df)[1:3] <- c("q025","q50","q975")

fullpost_ranks_quantiles.df
##posterior probability that rate in each DHB is the maximum

fullpost_max <- colMeans(post_max)
fullpost_max.df <- data.frame(rates.df$Dhb,fullpost_max)
names(fullpost_max.df) <- c("Dhb","prob")

##What about probability in the top 5

intop5 <- (post_rank >= 16)

Prtop5 <- colMeans((intop5) )

Prtop5.df <- data.frame(rates.df$Dhb,Prtop5)
Prtop5.df
