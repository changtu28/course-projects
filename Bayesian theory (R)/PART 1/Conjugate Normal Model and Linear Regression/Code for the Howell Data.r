rm(list=ls())
d <- read.csv("P:\\H\\lectures\\MOOCB1\\DATA\\howell1.csv",sep=';')
d.adult <- d[d$age>=18,]
library(ggplot2)
ggplot(data=d.adult,aes(x=height,y=weight))+
  geom_point()

m1 <- lm(weight ~ height, data=d.adult)
summary(m1)

par(mfrow=c(2,2)); plot(m1)


# The Bayesian way
library(MCMCglmm)

m1b <- MCMCglmm(weight ~ height, data=d.adult, verbose=F)
summary(m1b)

plot(m1b)

# Pr(beta[1]>0|data) > .999






### Model Fit: Using Posterior Predictive Distribution
# on a grid of reasonable values of height

dtf <- data.frame(height=seq(130,185,.1))

# a function to produce a posterior pred. estimate
pred.reg <- function(x,a,b,sigma){
  a+b*x+rnorm(length(a),0,sd=sigma)
}

m1b.pred <- sapply(dtf$height, pred.reg,
      a=m1b$Sol[,1],b=m1b$Sol[,2],sigma=sqrt(m1b$VCV))

dtf$pp.mean <- apply(m1b.pred,2,mean)
dtf$pp.q025 <- apply(m1b.pred,2,quantile,.025)
dtf$pp.q975 <- apply(m1b.pred,2,quantile,.975)

ggplot()+
  geom_point(data=d.adult,aes(x=height,y=weight))+
  geom_ribbon(data=dtf,aes(x=height,ymin=pp.q025,ymax=pp.q975),alpha=.5,col='salmon')+
  geom_line(data=dtf,aes(x=height,y=pp.mean),size=1.5,alpha=.8,col='red')


# NB. for the posterior mean estimate (that's for mu, not for y):

pred.reg.mean <- function(x,a,b){
  a+b*x
}

m1b.post.mn <- sapply(dtf$height, pred.reg.mean,
                   a=m1b$Sol[,1],b=m1b$Sol[,2])

dtf$post.mean <- apply(m1b.post.mn,2,mean)
dtf$post.q025 <- apply(m1b.post.mn,2,quantile,.025)
dtf$post.q975 <- apply(m1b.post.mn,2,quantile,.975)

ggplot()+
  geom_point(data=d.adult,aes(x=height,y=weight))+
  geom_ribbon(data=dtf,aes(x=height,ymin=pp.q025,ymax=pp.q975),alpha=.5,col='salmon')+
  #geom_line(data=dtf,aes(x=height,y=pp.mean),size=1.5,alpha=.8,col='red')+
  geom_ribbon(data=dtf,aes(x=height,ymin=post.q025,ymax=post.q975),alpha=.5,col='plum')+
  geom_line(data=dtf,aes(x=height,y=post.mean),size=1.5,alpha=.8,col='purple')

# note posterior mean and posterior predictive mean lines will be the same.

