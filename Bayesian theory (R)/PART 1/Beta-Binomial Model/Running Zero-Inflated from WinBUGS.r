# 25/07/2019
# by Elena Moltchanova
# Running Drinkers vs. Teetotallers (zero-inflated binomial example) from R

rm(list=ls())
library(R2WinBUGS)

# the actual model
my.model <- function(){
  
  # likelihood
  for(i in 1:k){
    x[i] ~ dbin(p.x[i],7)
    p.x[i] <- p*z[i]
    z[i] ~ dbern(omega)
  }
  
  # priors
  p ~ dbeta(1,1)
  omega ~ dbeta(1,1)
}



# the file I will temporarily save it too
my.file <- "p:\\temp.txt"

## write model file:
write.model(my.model,my.file)

## and let's take a look at that file:
file.show(my.file)

# the drinkers vs. teetotallers data
x <- rep(0:7,c(22,6,18,23,18,10,3,0))

# running the model in WinBUGS:

system.time(
  m.bugs <- bugs(data=list(k=length(x),x=x),
                 inits=list(list(p=.5,omega=.5,z=rep(1,length(x)))),
                 parameters.to.save=c("p","omega","z"),
                 ### PATH TO THE MODEL FILE
                 model.file=my.file,
                 n.chains=1,
                 n.iter=10000,
                 n.sim=5000,
                 n.burnin=5000,
                 n.thin=1,
                 DIC=F,
                 bugs.directory=paste0(Sys.getenv(c("USERPROFILE")), "\\WinBUGS14"),debug=F
                 #bugs.directory="c:\\Program Files\\WinBUGS14\\WinBUGS14",debug=F
  )
)

# Now, the m.bugs object contains all the information on
names(m.bugs)

# For example, plotting traces and posterior densities of omega and p
par(mfrow=c(2,2))
plot(m.bugs$sims.list$omega,ty='l',xlab='iteration',ylab=expression(omega))
plot(m.bugs$sims.list$p,ty='l',xlab='iteration',ylab=expression(p))
plot(density(m.bugs$sims.list$omega),ty='l',xlab=expression(omega),lwd=2,main='')
plot(density(m.bugs$sims.list$p),ty='l',xlab=expression(p),lwd=2,main='')

# checking summaries
m.bugs$summary

# generating posterior predictive density
# the posterior samples on omega and p are already available.
# just sample z and then x
z.pred <- rbinom(5000,1,m.bugs$sims.list$omega)
x.pred <- rbinom(5000,7,z.pred*m.bugs$sims.list$p)

# observed and generated frequencies

plot(0:7,c(table(factor(x,levels=0:7))/100),xlim=c(0,7),lwd=2,ty='o',xlab="days per week",ylab="f(x)",ylim=c(0,.4))
lines(0:7,c(table(factor(x.pred,levels=0:7))/5000),col='red',ty='o',pch=8,lwd=2)