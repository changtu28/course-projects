# 20/7/2021
# By Elena
# testing barista example

rm(list=ls())

N <- 10^4

set.seed(123)
barista <- sample(0:1, size=N, replace=T, prob=c(2/7,5/7))

coffee <- numeric(N)

coffee.probs <- array(c(.2,.5,.3,.8,.15,.05),dim=c(3,2))

system.time({
for(i in 1:N){
  coffee[i] <- sample(c('Ex','Gd','Ss'), size =1 ,
                      replace=T,
                      prob=coffee.probs[,barista[i]+1])
}

})

# evaluating conditional inverse probability 
# Pr(Expert|Excellent)

# (remember: mean of a binary vector = proportion of ones in that vector)

mean(barista[coffee=='Ex'])

