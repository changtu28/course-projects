rm(list=ls())
data(Nile)

plot(Nile)

df.Nile <- data.frame(year = as.numeric(time(Nile)),
                      flow=as.numeric(Nile))




library(R2WinBUGS)

my.model <- function(){
  for(i in 1:N){
    y[i] ~ dnorm(mu[i],tau)
    mu[i] <- a+b*step(x[i]-c)
  }
  
  # priors
  a ~ dnorm(0,1.0E-10)
  b ~ dnorm(0,1.0E-10)
  c ~ dunif(10,90)
  
  tau ~ dgamma(.01,.01)
}


# the file I will temporarily save it too
my.file <- "p:\\temp.txt"

## write model file:
write.model(my.model,my.file)


#system.time(
m1.bugs <- bugs(data=list(N=100,y=df.Nile$flow,
                          x=df.Nile$year-1870),
                inits=list(list(tau=1, a=1000,b=0,c=30)),
                parameters.to.save=c('a','b','c','tau'),
                ### PATH TO THE MODEL FILE
                model.file=my.file,
                n.chains=1,
                n.iter=1000,
                n.sim=500,
                n.burnin=500,
                n.thin=1,
                DIC=F,
                bugs.directory=paste0(Sys.getenv(c("USERPROFILE")), "\\WinBUGS14"),debug=T)
#)

round(m1.bugs$summary,1)
# posterior distributions-1
par(mfrow=c(2,2))
plot(501:1000,m1.bugs$sims.list$a,xlab='iter',ylab=expression(a),ty='l')
plot(501:1000,m1.bugs$sims.list$b,xlab='iter',ylab=expression(b),ty='l')
plot(501:1000,m1.bugs$sims.list$c,xlab='iter',ylab=expression(c),ty='l')
plot(501:1000,m1.bugs$sims.list$tau,xlab='iter',ylab=expression(tau),ty='l')

# posterior distributions-2
par(mfrow=c(2,2))
plot(density(m1.bugs$sims.list$a),xlab=expression(a),main='')
plot(density(m1.bugs$sims.list$b),xlab=expression(b),main='')
plot(density(m1.bugs$sims.list$c),xlab=expression(c),main='')
plot(density(m1.bugs$sims.list$tau),xlab=expression(tau),main='')

# model averaging
x.vals <- seq(1,100,1); Nx <- length(x.vals)

y.vals <- array(dim=c(4000,Nx))

for(i in 1:Nx){
  y.vals[,i] <- m1.bugs$sims.list$a+
    m1.bugs$sims.list$b*(x.vals[i]>m1.bugs$sims.list$c)
}

# plotting the models corresponding to the three first iterations
par(mfrow=c(1,1))
plot(df.Nile$year,df.Nile$flow,pch=16,col='gray40',ty='b')
lines(x.vals+1870,y.vals[1,],col='red',lwd=2)
lines(x.vals+1870,y.vals[100,],col='darkgreen',lwd=2)
lines(x.vals+1870,y.vals[200,],col='blue',lwd=2)



# plotting the average model
plot(df.Nile$year,df.Nile$flow,pch=16,col='gray40',ty='b')
lines(x.vals+1870,apply(y.vals,2,quantile,.025),
      col='brown',lty=3,lwd=2)
lines(x.vals+1870,apply(y.vals,2,quantile,.975),col='brown',lty=3,lwd=2)
lines(x.vals+1870,apply(y.vals,2,mean),col='brown',lwd=2)



