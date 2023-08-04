


DATES = seq( from = min(c(FIXED_START,SalmonStart,MusselStart,SeaweedStart)),
                        to = max(c(FIXED_START,SalmonEnd,MusselEnd,SeaweedEnd)), by = "day")

DATES = rep(DATES, 7)

ModOutput0 <- read.csv("ModOutput.txt", sep = "") 

ModOutput0[ModOutput0==0] <- NA


 # print(ModOutput0$W_salmon[758*6 + (1:6)])
 
 
ModOutput = ModOutput0 %>%
  arrange(BOX) %>%
  mutate(Zooplankton_carbon = C_Zooplankton_structure + C_Zooplankton_reserves) %>%
  mutate(Date = DATES) %>%
  mutate(Phyto_N_quota = N_phytoplankton/ C_phytoplankton) %>%
  mutate(MusselALA = mantle_ALA_muss.box. + gill_ALA_muss.box. + gland_ALA_muss.box.) %>%
  mutate(MusselEPA = mantle_EPA_muss.box. + gill_EPA_muss.box. + gland_EPA_muss.box.) %>%
  mutate(MusselDHA = mantle_DHA_muss.box. + gill_DHA_muss.box. + gland_DHA_muss.box.)

ModOutput$C_seaweed = as.numeric(as.vector(ModOutput$C_seaweed))
ModOutput$N_seaweed = as.numeric(as.vector(ModOutput$N_seaweed))


 ModOutput =
 ModOutput %>%
mutate_at(vars(contains('salmon')), ~ifelse(Date > SalmonStart & Date < SalmonEnd,
                                              ., .*NA)) %>%
   mutate_at(vars(contains('mussel')), ~ifelse(Date > MusselStart & Date <= MusselEnd,
                                               ., .*NA)) %>%
   mutate_at(vars(contains('muss')), ~ifelse(Date > MusselStart & Date <= MusselEnd,
                                               ., .*NA)) %>%
   mutate_at(vars(contains('seaweed')), ~ifelse(Date > SeaweedStart & Date <= SeaweedEnd,
                                               ., .*NA))

 
   


Number_cultured_species = ModOutput %>%
  dplyr::select(matches('No_|Date|BOX'))
Length_cultured_species = ModOutput %>%
  dplyr::select(matches('L_|Date|BOX'))
Energy_cultured_species = ModOutput %>% # joules
  dplyr::select(matches('E_|Date|BOX'))
Weight_cultured_species = ModOutput %>% # grams
  dplyr::select(matches('W_|Date|BOX'))


ModOutput = ModOutput %>%
  reshape2::melt(c("BOX","Date"))

  
FattyAcidDudes = ModOutput %>%
  subset(variable == "salmon_ALA" |  variable == "salmon_EPA" |
           variable == "salmon_DHA" |  variable == "salmon_LIN") %>%
  full_join(., Fillet_VS_whole_body,by = "variable") %>%
  full_join(by = c("BOX","Date"), ModOutput %>% subset(variable == "W_salmon")) %>%
  mutate(value_fillet  = 1e-3 * .5 * value.y * (X.Intercept. + 1e3 *
                                                  slope * (value.x / value.y)))

FattyAcidDudes$value_fillet[FattyAcidDudes$value_fillet<0] = 0

# write.csv(FattyAcidDudes,"FattyAcidDudes.csv",row.names = F)


 


#~~~~ Change levels
levels(ModOutput$variable) = factor(
  c(
    "Salmon biomass",
    "Feed",
    "Waste feed",
  "Salmon faeces",
    "mantle_ALA_muss",
    "mantle_ARA_muss",
    "DHA (mantle)",
    "EPA (mantle)",
    "mantle_LIN_muss",
    "gland_ALA_muss",
    "gland_ARA_muss",
    "DHA (gland)",
    "EPA (gland)",
    "gland_LIN_muss",
    "gill_ALA_muss",
    "gill_ARA_muss",
    "DHA (gill)",
    "EPA (gill)",
    "gill_LIN_muss",
    "ALA",
    "ARA",
    "EPA",
    "DHA",
    "LIN",
  "Time",
    "Sediment carbon",
    "Sediment nitrogen",
    "Nitrate",
    "Dissolved organic nitrogen",
    "Ammonium",
    "Particulate organic carbon",
    "Particulate organic nitrogen",
    "Phytoplankton carbon",
    "Phytoplankton nitrogen",
    "C_Zooplankton_structure",
    "C_Zooplankton_reserves",
  "C_seaweed",
    "N_seaweed",
    "No_salmon",
    "No_mussel",
    "No_sea_cucumber",
    "E_salmon",
    "E_mussel",
    "E_sea_cucumber",
    "E.R_salmon",
    "E.R_mussel",
    "E.R_sea_cucumber",
    "V_salmon",
    "V_mussel",
    "V_sea_cucumber",
    "L_salmon",
    "L_mussel",
    "L_sea_cucumber",
    "Salmon weight",
    "Mussel weight",
    "W_sea_cucumber",
    "Zooplankton carbon",
  "Phyto_N_quota",
  "ALA in gill,mantle and digestive gland",
  "EPA in gill,mantle and digestive gland",
  "DHA in gill,mantle and digestive gland"
  )
)

 


FattyAcidDudes_mussel = ModOutput %>%
  subset(variable == "ALA in gill,mantle and digestive gland" |  
           variable == "EPA in gill,mantle and digestive gland" |
           variable =="DHA in gill,mantle and digestive gland")
 

levels(FattyAcidDudes_mussel$variable) = factor(
  c(
    "Salmon biomass",
    "Feed",
    "Waste feed",
    "Salmon faeces",
    "mantle_ALA_muss",
    "mantle_ARA_muss",
    "DHA (mantle)",
    "EPA (mantle)",
    "mantle_LIN_muss",
    "gland_ALA_muss",
    "gland_ARA_muss",
    "DHA (gland)",
    "EPA (gland)",
    "gland_LIN_muss",
    "gill_ALA_muss",
    "gill_ARA_muss",
    "DHA (gill)",
    "EPA (gill)",
    "gill_LIN_muss",
    "ALA",
    "ARA",
    "EPA",
    "DHA",
    "LIN",
    "Time",
    "Sediment carbon",
    "Sediment nitrogen",
    "Nitrate",
    "Dissolved organic nitrogen",
    "Ammonium",
    "Particulate organic carbon",
    "Particulate organic nitrogen",
    "Phytoplankton carbon",
    "Phytoplankton nitrogen",
    "C_Zooplankton_structure",
    "C_Zooplankton_reserves",
    "C_seaweed",
    "N_seaweed",
    "No_salmon",
    "No_mussel",
    "No_sea_cucumber",
    "E_salmon",
    "E_mussel",
    "E_sea_cucumber",
    "E.R_salmon",
    "E.R_mussel",
    "E.R_sea_cucumber",
    "V_salmon",
    "V_mussel",
    "V_sea_cucumber",
    "L_salmon",
    "L_mussel",
    "L_sea_cucumber",
    "Salmon weight",
    "Mussel weight",
    "W_sea_cucumber",
    "Zooplankton carbon",
    "Phyto_N_quota",
    "ALA",
    "EPA",
    "DHA"
  )
)


 
FattyAcidDudes_mussel$value = 1e-3*FattyAcidDudes_mussel$value


NitrogenDudes = ModOutput %>%
  subset(
    variable == "Sediment nitrogen" |  variable == "Nitrate" |
      variable == "Dissolved organic nitrogen" |
      variable == "Ammonium" |
      variable == "Particulate organic nitrogen"
  )


PlanktonDudes_carbon = ModOutput %>%
  subset(variable == "Phytoplankton carbon" |
           variable == "Zooplankton carbon")


Phyto_nitrogen = ModOutput %>%
  subset(variable == "Phytoplankton nitrogen")

CarbonDudes = ModOutput %>%
  subset(variable == "Sediment carbon" |
           variable == "Particulate organic carbon")

fecesDudes = ModOutput %>%
  subset(variable == "Salmon faeces")

Musselweight = ModOutput %>%
  subset(variable == "Mussel weight")


 

 
#
# ModOutput %>%
#   select(waste_feed,fish_feces,Time) %>%
#   ggplot(.,
#          aes(Time, (1e-3*waste_feed/1410000) + (1e-3*2*fish_feces/1410000))) +
#   xlab("Date") +
#   geom_line()+
#   ylab(expression(paste("grams waste feed and faeces m" ^ -3))) +
#   Standard_theme()+
#   xlab("Days since start of production cycle")
#
# # ggsave("waste_feed_estimate.jpeg",width = 25, height = 12)


Number_plots =  function(VARIABLE) {
  Number_cultured_species %>%
    reshape2::melt(id.vars =c("BOX", "Date"))%>%
    subset(variable == VARIABLE) %>%
    mutate(Species = sub(".*_", "", variable)) %>%
    ggplot(., aes(Date, value)) +
    xlab("Date") +
    geom_line(aes(Date, value,group=BOX)) +
    ylab("Number") +
    Standard_theme() +
    facet_wrap( ~ Species)
}
Length_plots =  function(VARIABLE) {
  Length_cultured_species %>%
    reshape2::melt(id.vars =c("BOX", "Date"))%>%
    subset(variable == VARIABLE) %>%
    mutate(Species = sub(".*_", "", variable)) %>%
    ggplot(., aes(Date, value)) +
    xlab("Date") +
    geom_line(aes(Date, value,group=BOX)) +
    ylab("Length (cm)") +
    Standard_theme() +
    facet_wrap( ~ Species)
}
Weight_plots =  function(VARIABLE) {
  if(VARIABLE=="W_salmon"){
  PLOT = Weight_cultured_species %>%
    subset(BOX==2) %>%
    reshape2::melt(id.vars =c( "Date"))%>%
    subset(variable == VARIABLE) %>%
    mutate(Species = sub(".*_", "", variable)) %>%
    ggplot(., aes(Date, value)) +
    xlab("Date") +
    geom_line(aes(Date, value)) +
    ylab("Weight (g)") +
    Standard_theme() +
    facet_wrap( ~ Species)} else {
      PLOT = Weight_cultured_species %>%
        reshape2::melt(id.vars =c("BOX", "Date"))%>%
        subset(variable == VARIABLE) %>%
        mutate(Species = sub(".*_", "", variable)) %>%
        ggplot(., aes(Date, value)) +
        xlab("Date") +
        geom_line(aes(Date, value,group=BOX)) +
        ylab("Weight (g)") +
        Standard_theme() +
        facet_wrap( ~ Species)}
  PLOT
}



 

WieghtFunc =  function(VARIABLE) {
  ggplot(subset(ModOutput, variable == "Salmon weight"),
         aes(Date, value)) +
    xlab("Date") +
    geom_line(aes(Date, value,group=BOX)) +
    ylab("g") +
    facet_wrap( ~ variable, scales = "free_y") +
    Standard_theme()
}

BiomassFunc =  function(VARIABLE) {
  ggplot(subset(ModOutput, variable == "Salmon biomass"),
         aes(Date, value)) +
    xlab("Date") +
    geom_line(aes(Date, value,group=BOX)) +
    ylab("Tonnes") +
    facet_wrap( ~ variable, scales = "free_y") +
    Standard_theme()
}

FatFunc = function(VARIABLE) {
  ggplot(subset(FattyAcidDudes, variable.x == VARIABLE),
         aes(Date, value.x)) +
    xlab("Date") +
    geom_line(aes(Date, value.x,group=BOX)) +
    ylab("Fatty acid (g)") +
    facet_wrap(~       variable.x, scales = "free_y") +
    Standard_theme()

}




FatFunc_fillet = function(VARIABLE) {
  ggplot(subset(FattyAcidDudes, variable.x == VARIABLE),
         aes(Date, value_fillet)) +
    xlab("Date") +
    geom_line(aes(Date, value_fillet,group=BOX)) +
    ylab("Fatty acid (g)") +
    facet_wrap(~       variable.x, scales = "free_y") +
    Standard_theme()
}

CarbonPlots =  function(VARIABLE) {
  CarbonDudes %>%
    subset(variable == VARIABLE) %>%
    mutate(Species = sub(".*_", "", variable)) %>%
    ggplot(., aes(Date, value)) +
    xlab("Date") +
    geom_line(aes(Date, value,group=BOX)) +
    ylab(expression(paste("mgC m" ^ -3))) +
    Standard_theme() +
    facet_wrap( ~ Species)
}



PlanktonPlot_carbon = function(VARIABLE) {
  ggplot(subset(PlanktonDudes_carbon, variable == VARIABLE),
         aes(Date, value)) +
    xlab("Date") +
    geom_line(aes(Date, value,group=BOX)) +
    ylab(expression(paste("mgC m" ^ -3))) +
    facet_wrap(~       variable, scales = "free_y") +
    Standard_theme()

}


Phyto_N_quota = function() {

  ggplot(subset(ModOutput, variable == "Phyto_N_quota"),
         aes(Date, value)) +
    xlab("Date") +
    geom_line(aes(Date, value,group=BOX)) +
    ylab("Phytoplankton N ratio") +
    facet_wrap(~       variable, scales = "free_y") +
    Standard_theme()


}


PlanktonPlot_nitrogen = function(VARIABLE) {
  ggplot(subset(Phyto_nitrogen, variable == VARIABLE),
         aes(Date, value)) +
    xlab("Date") +
    geom_line(aes(Date, value,group=BOX)) +
    ylab(expression(paste("mgN m" ^ -3))) +
    facet_wrap(~       variable, scales = "free_y") +
    Standard_theme()
}

NitrogenPlot = function(VARIABLE) {
  ggplot(subset(NitrogenDudes, variable == VARIABLE),
         aes(Date, value)) +
    xlab("Date") +
    geom_line(aes(Date, value,group=BOX)) +
    ylab(expression(paste("mgN m" ^ -3))) +
    facet_wrap(~       variable, scales = "free_y") +
    Standard_theme()
}


 
 
 

FattyAcidDudes_musselPLOTS = function(VARIABLE) {
  ggplot(subset(FattyAcidDudes_mussel,variable == VARIABLE),
         aes(Date, value)) +
    xlab("Date") +
    facet_wrap(~variable)+
    geom_line(aes(Date, value,group=BOX)) +
    ylab(expression(paste("g")))+
    Standard_theme()
}





fecesPLOTS =
  fecesDudes %>%
  full_join(Number_cultured_species) %>%
  mutate(mgC_feces_total =No_salmon*value  ) %>%
  mutate(gC_feces_per_m2 =1e-3*(mgC_feces_total/(940*240)  ) ) %>%
  ggplot(.,
         aes(Date, gC_feces_per_m2)) +
    xlab("Date") +
    geom_line(aes(Date, gC_feces_per_m2,group=BOX)) +
  ylab(expression(paste("gC m" ^ -2))) +
  Standard_theme() +
  facet_wrap(~       variable, scales = "free_y")

 musselweightplot =
   Musselweight %>%
   ggplot(.,
          aes(Date, value)) +
   xlab("Date") +
   geom_line(aes(Date, value,group=BOX)) +
   ylab("g") + 
   Standard_theme()+
   facet_wrap(~variable, scales = "free_y")
 

 




G1 = NitrogenPlot("Sediment nitrogen")   +   ylab(expression(paste("mgC m" ^-2)))
G2 = NitrogenPlot("Nitrate")
G3 = NitrogenPlot("Dissolved organic nitrogen")
G4 = NitrogenPlot("Ammonium")
G5 = NitrogenPlot("Particulate organic nitrogen")



G6 = WieghtFunc()
G7 = FatFunc("salmon_ALA")
G8 = FatFunc("salmon_EPA")
G9 = FatFunc("salmon_DHA")
G10 = FatFunc("salmon_LIN")


G11 = FatFunc_fillet("salmon_ALA")
G12 = FatFunc_fillet("salmon_EPA")
G13 = FatFunc_fillet("salmon_DHA")
G14 = FatFunc_fillet("salmon_LIN")


G15 = PlanktonPlot_carbon("Phytoplankton carbon")
G16 = PlanktonPlot_carbon("Zooplankton carbon")

G17 = PlanktonPlot_nitrogen("Phytoplankton nitrogen")


G18 = Number_plots(VARIABLE = "No_salmon")
G19 = Number_plots(VARIABLE = "No_mussel")
G20 = Number_plots(VARIABLE = "No_sea_cucumber")


G21 = Length_plots(VARIABLE = "L_salmon")
G22 = Length_plots(VARIABLE = "L_mussel")
G23 = Length_plots(VARIABLE = "L_sea_cucumber")

G24 = Weight_plots(VARIABLE = "W_salmon")
G25 = Weight_plots(VARIABLE = "Mussel weight")
G26 = Weight_plots(VARIABLE = "W_sea_cucumber")


G27 = CarbonPlots(VARIABLE = "Sediment carbon") +   ylab(expression(paste("mgC m" ^-2)))+
  scale_y_continuous(limits = c(0,300000))
G28 = CarbonPlots(VARIABLE = "Particulate organic carbon")

G29 = FattyAcidDudes_musselPLOTS(VARIABLE="ALA")
G30 = FattyAcidDudes_musselPLOTS(VARIABLE="EPA")
G31 = FattyAcidDudes_musselPLOTS(VARIABLE="DHA")
G32 = musselweightplot

 

G35 = fecesPLOTS

G36 = BiomassFunc()

G37 = Phyto_N_quota()

print("test")


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
################################################################################################################################################
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#



lay <-
  rbind(c(1, 2), c(3, 4), c(5, 6), c(7, 8),  c(9, 10), c(11, 12))


