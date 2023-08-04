#~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#~~~~ Import data sets  ~~~~#

#~~~~~~~~~~~~~~~~~~~~~~~~~~~#

DaysSince2014 = data.frame(DaysSince2014 = 88:888)


FeedComp <-
  read.csv("Input_Data/Diet/FeedComp.csv",
           header = T)[,-1]

FeedComp_NFE =FeedComp[FeedComp$Parameter=="Starch" | FeedComp$Parameter=="Total sugars" ,]
FeedComp_NFE =FeedComp_NFE %>%
  group_by( Ingredient, Unit) %>%
  dplyr::summarise(As.fed = sum(As.fed)) %>%
    mutate(Parameter= "NFE")
FeedComp =FeedComp[FeedComp$Parameter!="Starch" & FeedComp$Parameter!="Total sugars" ,] %>%
  bind_rows(.,FeedComp_NFE)


################

Temperature_data <-
  read.csv("Input_Data/Temperature/Ardcastle_temperature_between_5_7m_smoothed.csv") %>%
  arrange(DaysSince2014) %>%
  mutate(Date = DaysSince2014+as.Date("2014/1/1")-1) %>%
  mutate(JulianDay = yday(Date))

# taking average temp at day for smoothed data to be temp at day
Temperature_extrap = data.frame(Date = c( seq( from = as.Date("2013/1/1"), to =as.Date("2014-03-28"),by="day" ),
                            seq( from = as.Date("2016-06-07"), to =as.Date("2016-12-30"),by="day" )
                            )) %>%
  mutate(JulianDay = yday(Date)) %>%
  left_join(Temperature_data,by="JulianDay") %>%
  group_by(Date.x) %>%
  dplyr::summarise(temperature_fit = mean(temperature_fit)) %>%
  rename(Date = Date.x )

Temperature = Temperature_data %>%
  select(Date,temperature_fit ) %>%
  bind_rows(Temperature_extrap) %>%
  arrange(Date)


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#~~~~~~~~~~ Relationship between PUFA content into fillet PUFA content ~~~~~~~~~~#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# To transform whole body PUFA content into fillet PUFA content (after model run)
Fillet_VS_whole_body <-
  read.csv("Input_Data/Fillet_whole_body_relationships/Fillet_VS_whole_body.csv",
           header = T) %>%
  dplyr::select(fatty_acid, X.Intercept., slope)  %>%
  rename(variable = fatty_acid) %>%
  mutate(variable = paste0("salmon_",variable))


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#~~~~~~~~~~~~~ Diets ~~~~~~~~~~~~#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

Dietary_PUFA <- read.csv("Input_Data/Diet/Dietary_PUFA.csv")


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#~~~~~~~~~~ Bathymetry ~~~~~~~~~~#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#


Bathymetry <- read.csv("Input_Data/Depth/Bathymetry.csv")


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#~~~~~~~~~~ Irradiance ~~~~~~~~~~#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# Irradiance (in einsteins, the energy in 1 mole photons)
# we need micromols phot
# so multiply by 1e6

IrradianceData  <- read.csv("Input_Data/Irradiance/SeaSurfaceIrradiance_interpolated.csv") %>%
  mutate(DayofYear =seq( as.Date("2012/12/21"),as.Date("2013/12/20"), by="day")) %>%
  mutate(DaysSince2014 = yday(DayofYear)-1)  %>%  # days since any year
 arrange(DaysSince2014) %>%
  bind_rows(.,.) %>%
  bind_rows(.,.) %>%
  mutate(DaysSince2014 = 0: (n()-1)) %>%
  right_join(.,DaysSince2014) %>%
  mutate(JulianDay = yday(DayofYear)) %>%
  group_by(JulianDay) %>%
  dplyr::summarise(value = mean(value))

IrradianceData = full_join(IrradianceData,  data.frame( JulianDay=355 ,  value = 1.766111) )  %>%
  arrange(JulianDay)

DATES = data_frame(
Date = seq( as.Date("2012/12/21"),as.Date("2017/12/20"), by="day"),
JulianDay = yday(Date))


Irradiance = IrradianceData %>%
  left_join(DATES) %>%
  arrange(Date) %>%
  rename(Irradiance = value) %>%
  select( Date ,Irradiance)


 
 GrowthCurvePhyto <- read.csv("Input_Data/Fitted/Dowd.csv")
 
 Interpolated.g = approx(xout = seq(0,500,1),GrowthCurvePhyto$x , y = GrowthCurvePhyto$y, method = "linear") %>%
   as_tibble() %>%
   rename(JulianDay = x)
 
 DATES = data_frame(
   Date = seq( as.Date("2012/12/21"),as.Date("2017/12/20"), by="day"),
   JulianDay = yday(Date))
 
 test = Interpolated.g %>%
   left_join(DATES) %>%
   arrange(Date)   %>%
   rename(Irradiance = y) %>%
   select( Date ,Irradiance)
 
 test[is.na(test$Irradiance),]$Irradiance = 0.362

 test[test$Irradiance>1,]$Irradiance = 1
 
 



 
 

ALL_TRANSPORT =NULL

ALL_NUTRIENT_FILES = sort(list.files(path = "Input_Data/Transport/nutrients/"))

ALL_POOP_FILES = sort(list.files(path = "Input_Data/Transport/salmonpoop/"))

ALL_POC_FILES = sort(list.files(path = "Input_Data/Transport/det/"))

ALL_PHYTO_FILES = sort(list.files(path = "Input_Data/Transport/det/"))


ALL_FEED_FILES = sort(list.files(path = "Input_Data/Transport/feed/"))

ALL_NUTRIENT_FILES = 
  data.frame(ALL_NUTRIENT_FILES,
             DAYS = as.integer(stringr::str_extract(sub("\\_7.nc*", "", 
                                                        ALL_NUTRIENT_FILES), "\\d+"))) %>%
  arrange(DAYS) %>%
  use_series(ALL_NUTRIENT_FILES)

ALL_POOP_FILES = 
  data.frame(ALL_POOP_FILES,
             DAYS = as.integer(stringr::str_extract(sub("\\_7.nc*", "", 
                                                        ALL_POOP_FILES), "\\d+"))) %>%
  arrange(DAYS) %>%
  use_series(ALL_POOP_FILES)

ALL_POC_FILES = 
  data.frame(ALL_POC_FILES,
             DAYS = as.integer(stringr::str_extract(sub("\\_7.nc*", "", 
                                                        ALL_POC_FILES), "\\d+"))) %>%
  arrange(DAYS) %>%
  use_series(ALL_POC_FILES)

ALL_PHYTO_FILES = 
  data.frame(ALL_PHYTO_FILES,
             DAYS = as.integer(stringr::str_extract(sub("\\_7.nc*", "", 
                                                        ALL_PHYTO_FILES), "\\d+"))) %>%
  arrange(DAYS) %>%
  use_series(ALL_PHYTO_FILES)



ALL_FEED_FILES = 
  data.frame(ALL_FEED_FILES,
             DAYS = as.integer(stringr::str_extract(sub("\\_7.nc*", "", 
                                                        ALL_FEED_FILES), "\\d+"))) %>%
  arrange(DAYS) %>%
  use_series(ALL_FEED_FILES)

ALL_NUTRIENT_FILES = c(ALL_NUTRIENT_FILES,ALL_NUTRIENT_FILES,ALL_NUTRIENT_FILES,
                       ALL_NUTRIENT_FILES,ALL_NUTRIENT_FILES,ALL_NUTRIENT_FILES)

  for(DAY in 1:21){
  
NUTRIENT_FILE = ALL_NUTRIENT_FILES[DAY]

POOP_FILE = ALL_POOP_FILES[DAY]
POOP_FILE = "poopylag_1_11.nc.csv"

POC_FILE = "detpylag_1_11.nc.csv"

PHYTO_FILE = "detpylag_1_11.nc.csv"

FEED_FILE = "feedpylag_1_11.nc.csv"

TRANSPORT <- read.csv( "Input_Data/Transport/nutpylag_16_11.nc.csv") %>%
arrange(AA)
TRANSPORT0 = TRANSPORT %>%
  slice(1:(n()-7))
TRANSPORT1 = TRANSPORT %>%
  slice( (n()-6):n())
TRANSPORT = rbind(TRANSPORT1,TRANSPORT0)

PR_VOL_A = TRANSPORT[,"A"]*TRANSPORT$Volume
PR_VOL_B = TRANSPORT[,"B"]*TRANSPORT$Volume
PR_VOL_C = TRANSPORT[,"C"]*TRANSPORT$Volume
PR_VOL_D = TRANSPORT[,"D"]*TRANSPORT$Volume
PR_VOL_E = TRANSPORT[,"E"]*TRANSPORT$Volume
PR_VOL_FF = TRANSPORT[,"FF"]*TRANSPORT$Volume
PR_VOL_G = TRANSPORT[,"G"]*TRANSPORT$Volume




TRANSPORT = c(
c(PR_VOL_A[1:7] , sum(PR_VOL_A[-1:-7]), sum(PR_VOL_A) ),
c(PR_VOL_B[1:7] , sum(PR_VOL_B[-1:-7]), sum(PR_VOL_B) ),
c(PR_VOL_C[1:7] , sum(PR_VOL_C[-1:-7]), sum(PR_VOL_C) ),
c(PR_VOL_D[1:7] , sum(PR_VOL_D[-1:-7]), sum(PR_VOL_D) ),
c(PR_VOL_E[1:7] , sum(PR_VOL_E[-1:-7]), sum(PR_VOL_E) ),
c(PR_VOL_FF[1:7] , sum(PR_VOL_FF[-1:-7]), sum(PR_VOL_FF) ),
c(PR_VOL_G[1:7] , sum(PR_VOL_G[-1:-7]), sum(PR_VOL_G) )
)


# TAKING AN AVERAGE OF 7 DAYS
# TRANSPORT =AVERAGE_TRANSPORT


ALL_TRANSPORT = c(ALL_TRANSPORT,TRANSPORT)

 



  
  TRANSPORT<- read.csv(paste0("Input_Data/Transport/salmonpoop/",POOP_FILE))
  
  PR_VOL_A = TRANSPORT[,"A"]*TRANSPORT$Volume
  PR_VOL_B = TRANSPORT[,"B"]*TRANSPORT$Volume
  PR_VOL_C = TRANSPORT[,"C"]*TRANSPORT$Volume
  PR_VOL_D = TRANSPORT[,"D"]*TRANSPORT$Volume
  PR_VOL_E = TRANSPORT[,"E"]*TRANSPORT$Volume
  PR_VOL_FF = TRANSPORT[,"FF"]*TRANSPORT$Volume
  PR_VOL_G = TRANSPORT[,"G"]*TRANSPORT$Volume
  
  
  TRANSPORT = c(
    c(PR_VOL_A[1:7] , sum(PR_VOL_A[-1:-7]), sum(PR_VOL_A) ),
    c(PR_VOL_B[1:7] , sum(PR_VOL_B[-1:-7]), sum(PR_VOL_B) ),
    c(PR_VOL_C[1:7] , sum(PR_VOL_C[-1:-7]), sum(PR_VOL_C) ),
    c(PR_VOL_D[1:7] , sum(PR_VOL_D[-1:-7]), sum(PR_VOL_D) ),
    c(PR_VOL_E[1:7] , sum(PR_VOL_E[-1:-7]), sum(PR_VOL_E) ),
    c(PR_VOL_FF[1:7] , sum(PR_VOL_FF[-1:-7]), sum(PR_VOL_FF) ),
    c(PR_VOL_G[1:7] , sum(PR_VOL_G[-1:-7]), sum(PR_VOL_G) )
  )
  ALL_TRANSPORT = c(ALL_TRANSPORT,TRANSPORT)

 
  
  TRANSPORT <- read.csv( "Input_Data/Transport/nutpylag_16_11.nc.csv") %>%
    arrange(AA)
  TRANSPORT0 = TRANSPORT %>%
    slice(1:(n()-7))
  TRANSPORT1 = TRANSPORT %>%
    slice( (n()-6):n())
  TRANSPORT = rbind(TRANSPORT1,TRANSPORT0)
  
  PR_VOL_A = TRANSPORT[,"A"]*TRANSPORT$Volume
  PR_VOL_B = TRANSPORT[,"B"]*TRANSPORT$Volume
  PR_VOL_C = TRANSPORT[,"C"]*TRANSPORT$Volume
  PR_VOL_D = TRANSPORT[,"D"]*TRANSPORT$Volume
  PR_VOL_E = TRANSPORT[,"E"]*TRANSPORT$Volume
  PR_VOL_FF = TRANSPORT[,"FF"]*TRANSPORT$Volume
  PR_VOL_G = TRANSPORT[,"G"]*TRANSPORT$Volume
  

  TRANSPORT = c(
    c(PR_VOL_A[1:7] , sum(PR_VOL_A[-1:-7]), sum(PR_VOL_A) ),
    c(PR_VOL_B[1:7] , sum(PR_VOL_B[-1:-7]), sum(PR_VOL_B) ),
    c(PR_VOL_C[1:7] , sum(PR_VOL_C[-1:-7]), sum(PR_VOL_C) ),
    c(PR_VOL_D[1:7] , sum(PR_VOL_D[-1:-7]), sum(PR_VOL_D) ),
    c(PR_VOL_E[1:7] , sum(PR_VOL_E[-1:-7]), sum(PR_VOL_E) ),
    c(PR_VOL_FF[1:7] , sum(PR_VOL_FF[-1:-7]), sum(PR_VOL_FF) ),
    c(PR_VOL_G[1:7] , sum(PR_VOL_G[-1:-7]), sum(PR_VOL_G) )
  )
  ALL_TRANSPORT = c(ALL_TRANSPORT,TRANSPORT)


 

  

  TRANSPORT<- read.csv(paste0("Input_Data/Transport/det/",PHYTO_FILE)) %>%
  arrange(AA)
  TRANSPORT0 = TRANSPORT %>%
    slice(1:(n()-7))
  TRANSPORT1 = TRANSPORT %>%
    slice( (n()-6):n())
  TRANSPORT = rbind(TRANSPORT1,TRANSPORT0)
  

  
  
  PR_VOL_A = TRANSPORT[,"A"]*TRANSPORT$Volume
  PR_VOL_B = TRANSPORT[,"B"]*TRANSPORT$Volume
  PR_VOL_C = TRANSPORT[,"C"]*TRANSPORT$Volume
  PR_VOL_D = TRANSPORT[,"D"]*TRANSPORT$Volume
  PR_VOL_E = TRANSPORT[,"E"]*TRANSPORT$Volume
  PR_VOL_FF = TRANSPORT[,"FF"]*TRANSPORT$Volume
  PR_VOL_G = TRANSPORT[,"G"]*TRANSPORT$Volume
  

  TRANSPORT = c(
    c(PR_VOL_A[1:7] , sum(PR_VOL_A[-1:-7]), sum(PR_VOL_A) ),
    c(PR_VOL_B[1:7] , sum(PR_VOL_B[-1:-7]), sum(PR_VOL_B) ),
    c(PR_VOL_C[1:7] , sum(PR_VOL_C[-1:-7]), sum(PR_VOL_C) ),
    c(PR_VOL_D[1:7] , sum(PR_VOL_D[-1:-7]), sum(PR_VOL_D) ),
    c(PR_VOL_E[1:7] , sum(PR_VOL_E[-1:-7]), sum(PR_VOL_E) ),
    c(PR_VOL_FF[1:7] , sum(PR_VOL_FF[-1:-7]), sum(PR_VOL_FF) ),
    c(PR_VOL_G[1:7] , sum(PR_VOL_G[-1:-7]), sum(PR_VOL_G) )
  )
  
  
  print(c(DAY,sum(PR_VOL_A),sum(PR_VOL_B),sum(PR_VOL_C),
          sum(PR_VOL_D),sum(PR_VOL_E),sum(PR_VOL_FF),
          sum(PR_VOL_G)))
 
  
  ALL_TRANSPORT = c(ALL_TRANSPORT,TRANSPORT)
  
  
  
  
  
  
  TRANSPORT<- read.csv(paste0("Input_Data/Transport/feed/",FEED_FILE))
  
  PR_VOL_A = TRANSPORT[,"A"]*TRANSPORT$Volume
  PR_VOL_B = TRANSPORT[,"B"]*TRANSPORT$Volume
  PR_VOL_C = TRANSPORT[,"C"]*TRANSPORT$Volume
  PR_VOL_D = TRANSPORT[,"D"]*TRANSPORT$Volume
  PR_VOL_E = TRANSPORT[,"E"]*TRANSPORT$Volume
  PR_VOL_FF = TRANSPORT[,"FF"]*TRANSPORT$Volume
  PR_VOL_G = TRANSPORT[,"G"]*TRANSPORT$Volume
  
  
  TRANSPORT = c(
    c(PR_VOL_A[1:7] , sum(PR_VOL_A[-1:-7]), sum(PR_VOL_A) ),
    c(PR_VOL_B[1:7] , sum(PR_VOL_B[-1:-7]), sum(PR_VOL_B) ),
    c(PR_VOL_C[1:7] , sum(PR_VOL_C[-1:-7]), sum(PR_VOL_C) ),
    c(PR_VOL_D[1:7] , sum(PR_VOL_D[-1:-7]), sum(PR_VOL_D) ),
    c(PR_VOL_E[1:7] , sum(PR_VOL_E[-1:-7]), sum(PR_VOL_E) ),
    c(PR_VOL_FF[1:7] , sum(PR_VOL_FF[-1:-7]), sum(PR_VOL_FF) ),
    c(PR_VOL_G[1:7] , sum(PR_VOL_G[-1:-7]), sum(PR_VOL_G) )
  )
  ALL_TRANSPORT = c(ALL_TRANSPORT,TRANSPORT)
  

  
  }


 

ALL_TRANSPORT = rep(ALL_TRANSPORT, 42)
 
  
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #
#~~~~~ BACKGROUND CONCENTRATIONS ~~~~~#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ #
  
## THIS IS HARD CODED!!!  
  
FIXED_START = as.Date("2013/01/1")
dataset_dates = data.frame(date = seq(FIXED_START, as.Date("2015-06-01"),by="day")) %>%
  mutate(Month = month(date))

dataset_dates = dataset_dates %>%
  mutate(Year = year(date))

# PLANKTON CARBON (BACKGROUND)
  

chl_a_mean_monthly <- read.csv( "Input_Data/Fitted/mean_monthly_chla_furnace.csv")

plankton_carbon = chl_a_mean_monthly %>%
   group_by(Month) %>%
   mutate(plankton_carbon = 40*mean_chl_a_at_month)  %>% # mgC m-3
   left_join(.,dataset_dates)  %>%
   arrange(date) %>%
   use_series(plankton_carbon)
 
 
 

# Amonnium and nitrate (BACKGROUND)


background_NH <- read.csv( "Input_Data/Fitted/background_NH.csv") %>%
  left_join(.,dataset_dates) %>%
  arrange(date) %>%
  subset(date<=as.Date("2015-06-01")) %>%
  use_series(NH)

# background_NH = .6*background_NH

 
background_NO <- read.csv("Input_Data/Fitted/background_NO.csv") %>%
  left_join(.,dataset_dates) %>%
  arrange(date) %>%
  subset(date<=as.Date("2015-06-01")) %>%
  use_series(NO)

# DON (BACKGROUND)

DON_loch_etive <- read.csv( "Input_Data/Fitted/DON_loch_etive.csv") %>%
  left_join(.,dataset_dates)   %>%
  arrange(date) %>%
  subset(date<=as.Date("2015-06-01"))  %>%
  use_series(Mean_DON)


# POC (BACKGROUND)

# from Solorzano 77,
# poc in mgC m3
# chla in mgC m3
#poc =  394 + 38.5 chla
#poc =  216  + 50 chla
# poc =  305 + 44.25 chla (AVERAGE)

BACKGROUND_POC <- 305 + 44.25*(plankton_carbon/40)
 
 

# Zooplankton (BACKGROUND)

Zoo_NS <- read.csv("Input_Data/Fitted/Zoo_NS.csv") %>%
  select(Month, Mean_zoo) %>%
  left_join(.,dataset_dates)   %>%
  arrange(date) %>%
  subset(date<=as.Date("2015-06-01"))  %>%
  use_series(Mean_zoo)

 

#plankton_carbon
#plankton_nitrogen (0.18*plankton_carbon) 
#background_NH
#background_NO
#DON_loch_etive
#POC
# PON (0.18*POC)
#Zoo_NS


    