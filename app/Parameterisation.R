# PARAMETERISATION

# Model GUI


# set directory
where_this_is = dirname(rstudioapi::getSourceEditorContext()$path)
setwd(where_this_is)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#~~~~ Import data sets  ~~~~#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~#


PARAMETERS  <- read.csv("PARS.csv")[,-1]




system("R CMD SHLIB  Parameterisation.cpp")

Modrun = function(XXX)
{
  {
    ESTIMATED_PAR = c(XXX[1],XXX[2],XXX[3],XXX[4])
  
    ecomod =  .C("ECOSYSTEM_MODEL",
                 c(as.double(PARAMETERS),
                   as.double(ESTIMATED_PAR)))
    
    # load .so file
    dyn.load("Parameterisation.so")
    
     Parameterisation_stuff <- read.table("~/OneDrive/Diverseafood/Ecosystem_and_Fatty_Acid_Model/Model_GUI/Parameterisation_stuff.txt", quote="\"", comment.char="")
    NROW = nrow(Parameterisation_stuff)
      as.numeric(as.vector(Parameterisation_stuff[NROW,1]))
    # ecomod[["result"]]
    
    
      }
}
 
 
for(A1 in c(227234,327236.2,437239))
  {
  for(A2 in c(6379.51,26379.51,76379.51))
    {
    for(A3 in seq(50,500,50))
    {
      for(A4 in seq(.4,.8,.01))
      {
    
# call ecosystem model
# Modrun(XXX=c(307260, 263795.1,300,.6))
    Modrun(XXX=c(A1, A2,A3,A4))
        
      }
    }
  }
}

              

Number.of.fitted.parameters = 4
no.para = Number.of.fitted.parameters
Identity = diag(no.para)
ui = NULL
for (i in 1:no.para)
{
  ui = rbind(ui , rbind(Identity[i,],-1 * Identity[i,]))
}
rm(Identity,i)

######### ci ###########

ci = c(127233, -427235, 
       26, -20638900, 
       10, -4000, 
       0.34, -1)   

NMr = function(XXX)
{
  RunNM <- constrOptim( XXX ,f = Modrun,ui=ui,
                        ci=ci,method="Nelder-Mead",
                        control= list(maxit = 1e4,hessian=T,trace=T,reltol=1e-60,tmax=1,temperature=100
                        ))
}

params = NMr(c(227234, 26379.51,300,.55))
  
# salmon half sat 295754.6

# original abundance 346220.6

Parameterisation_stuff$V1  = as.numeric(Parameterisation_stuff$V1)

Parameterisation_stuff %>%
  subset(V1<1E28) %>%
  reshape2::melt(id.vars = "V1") %>%
ggplot() +
  geom_point(aes(V1,value)) +
  facet_wrap(~variable)

  