#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#~~~~ Import parameter values  ~~~~#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
Boxes = 7

# updates maximum number of days and the number of biometric paramters
write.table(data.frame(Ctype=c("int","int","static const"),
                       Parameter =c("MaxDays","no_bio_parameters", "NO_PARAS"),
                       value = paste(c(length(TEMPERATURE_KELVIN), 31*Boxes+32 +28,
                                       ( 5*length(TEMPERATURE_KELVIN)) +31*Boxes+32  + 1*length(ALL_TRANSPORT) + 6*length(plankton_carbon)),",")),
            file ="CONSTANTS.txt",quote=F,sep = ",",row.names = F,col.names = F)

print("we are here!!!!!!!!!!!")
system('python Update_constants.py')





SALMON_FEED_VEC = SALMON_FEED() %>%
  subset(variable=="Feed") %>%
  select(value) %>%
  use_series(value)

SALMON_TB_VEC = SALMON_FEED() %>%
  subset(variable=="Total biomass") %>%
  select(value) %>%
  use_series(value)

SALMON_MB_VEC = SALMON_FEED() %>%
  subset(variable=="Mortality biomass") %>%
  select(value) %>%
  use_series(value)





N = X[1:(3*Boxes)]
E =X[(3*Boxes+1):(6*Boxes)]  
E_R = X[(6*Boxes+1):(9*Boxes)]
V = X[(9*Boxes+1):(12*Boxes)]
L = X[(12*Boxes+1):(15*Boxes)]
W = X[(15*Boxes+1):(18*Boxes)]
CA = X[(18*Boxes+1):(19*Boxes)]
NAs  =X[(19*Boxes+1):(20*Boxes)]

CZ = X[(20*Boxes+1):(21*Boxes)]
EZ = X[(21*Boxes+1):(22*Boxes)]
CP = X[(22*Boxes+1):(23*Boxes)]
NP = X[(23*Boxes+1):(24*Boxes)]
POC =X[(24*Boxes+1):(25*Boxes)]
PON =X[(25*Boxes+1):(26*Boxes)]

ND =X[(26*Boxes+1):(27*Boxes)]
NH =X[(27*Boxes+1):(28*Boxes)]
NO =X[(28*Boxes+1):(29*Boxes)]
CS=X[(29*Boxes+1):(30*Boxes)]
NS=X[(30*Boxes+1):(31*Boxes)]




P_fat = X[31*Boxes+1]
P_NFE = X[31*Boxes+2]
P_fibre = X[31*Boxes+3]
P_phos =X[31*Boxes+4]
P_min = X[31*Boxes+5]

# 10 metre depth of cages, 28 metres across
# thats 10*pi*14^2 ~ 6157.522 m3 a cage
SALMON_FEED_VEC= 1e9*SALMON_FEED_VEC/55417.7


Temperature_climate = Temperature   %>%
  mutate(Year = year(Date), jday = yday(Date)) 

Temperature_climate = Temperature_climate %>%
  group_by(jday) %>%
  summarise(MeanTemp = mean(temperature_fit))  %>%
  left_join(.,Temperature_climate) %>%
  arrange(Date) %>%
  select(MeanTemp) %>%
  use_series(MeanTemp)

# TEMPERATURE_KELVIN   = 3 +Temperature_climate[1:882]  + 273.15 	#Temperature (K)


PARAMETERS = c(
  as.double(E),
  as.double(E_R),
  as.double(V),
  as.double(N),
  as.double(CA),
  as.double(NAs),
  as.double(CZ),
  as.double(EZ),
  as.double(CP),
  as.double(NP),
  as.double(POC),
  as.double(PON),
  as.double(ND),
  as.double(NH),
  as.double(NO),
  as.double(CS),
  as.double(NS),
  as.double(W),
  as.double(L),
  as.double(ALA_COMP),
  as.double(ARA_COMP),
  as.double(EPA_COMP),
  as.double(DHA_COMP),
  as.double(DPA_COMP),
  as.double(LIN_COMP),
  as.double(OLA_COMP),
  as.double(PAM_COMP),
  as.double(P_fat),
  as.double(P_NFE),
  as.double(P_fibre),
  as.double(P_phos),
  as.double(P_min),
  
  as.double(X[31*Boxes+6]),
  as.double(X[31*Boxes+7]),
  as.double(X[31*Boxes+8]),
  as.double(X[31*Boxes+9]),
  as.double(X[31*Boxes+10]),
  as.double(X[31*Boxes+11]),
  as.double(X[31*Boxes+12]),
  as.double(X[31*Boxes+13]),
  as.double(X[31*Boxes+14]),
  as.double(X[31*Boxes+15]),
  as.double(X[31*Boxes+16]),
  as.double(X[31*Boxes+17]),
  as.double(X[31*Boxes+18]),
  as.double(X[31*Boxes+19]),
  as.integer(as.numeric(SalmonStart - min(c( FIXED_START, SalmonStart, MusselStart, SeaweedStart)))),
  as.integer(as.numeric(MusselStart - min(c( FIXED_START, SalmonStart, MusselStart, SeaweedStart)))),
  as.integer(as.numeric(SeaweedStart - min(c( FIXED_START, SalmonStart, MusselStart, SeaweedStart)))),
  as.integer(as.numeric( SalmonEnd - min(c(FIXED_START,SalmonStart, MusselStart, SeaweedStart)))),
  as.integer(as.numeric( MusselEnd - min(c(FIXED_START,SalmonStart, MusselStart, SeaweedStart)))),
  as.integer(as.numeric( SeaweedEnd - min(c(FIXED_START,SalmonStart, MusselStart, SeaweedStart)))),
  as.double(TEMPERATURE_KELVIN),
  as.double( as.numeric(LIGHT()$Irradiance)), 
  as.double( SALMON_FEED_VEC),
  as.double( SALMON_TB_VEC),
  as.double( SALMON_MB_VEC),
  # export
  as.double(ALL_TRANSPORT),
  as.double(plankton_carbon),
  as.double(background_NH),
  as.double(background_NO),
  as.double(DON_loch_etive),
  as.double(BACKGROUND_POC),
  as.double(Zoo_NS)
)
# 122658 1329 0.0968871

write.csv(PARAMETERS,"PARS.csv")

