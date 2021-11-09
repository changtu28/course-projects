# Drinkers vs. Tee-totallers

x <- rep(c(0:7),c(22,6,18,23,18,10,3,0))

length(x)
sum(x)

7*100 - sum(x)

# => p|x ~ Beta(252,450)

# posterior predictive distribution

# how many zeroes in a sample of 100?

set.seed(123)
p.post <- rbeta(10^5, 252, 450)

post.pred.zero <- numeric(10^5)

for(i in 1:10^5){
  post.pred.zero[i] <- sum(rbinom(100,7,p.post[i]) == 0)
}


hist(post.pred.zero,seq(-.5,20.5,1),col="plum")

mean(post.pred.zero>=22)

### take another look at the data

hist(x, seq(-.5,7.5,1), col='orange')
