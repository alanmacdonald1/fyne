# set directory
where_this_is = dirname(rstudioapi::getSourceEditorContext()$path)
setwd(dirname(where_this_is))

###### modelled salmon data
FIXED_START = as.Date("2013/01/1") 

Mod_nitrogen <- read.csv("ModOutput.txt", sep = "") %>%
  select("BOX","N_Nitrate","N_Ammonium"
  ) %>%
  mutate(Dates = rep(seq(FIXED_START,(FIXED_START+881), by="day"),each = 7)) %>%
  subset(Dates > as.Date("2013-09-30") &
           Dates < as.Date("2015-06-01"))

PATH = "~/OneDrive/Diverseafood/Ecosystem_and_Fatty_Acid_Model/Model_GUI/Input_Data/User_input/Ardcastle_salmon_biomass_feed_mort.xls"

Ardcastle_salmon_feed =   read_excel(PATH)

Ardcastle_salmon_feed <- Ardcastle_salmon_feed %>%
  mutate(Month = month(Date)) %>%
  left_join(
    data_frame(AllDates = seq(from =  min(Ardcastle_salmon_feed$Date) ,  max(Ardcastle_salmon_feed$Date), by = "day"),
               Month = month(AllDates), Year  = year(AllDates),
               monthDays = monthDays(AllDates))) 

Ardcastle_salmon_feed[Ardcastle_salmon_feed$variable=="Total biomass",]$monthDays = 1

Ardcastle_salmon_feed = Ardcastle_salmon_feed %>%
  mutate(value = value/monthDays) %>%
  select(AllDates,value,variable) %>%
  arrange(AllDates)

ArdcastleTotalbiomass = subset(Ardcastle_salmon_feed,variable=="Total biomass")
ArdcastleTotalbiomass$DayOfMonth = mday(ArdcastleTotalbiomass$AllDates)
MiddleMonth = ArdcastleTotalbiomass[ArdcastleTotalbiomass$DayOfMonth==15,]
LinApprox = approx(x = as.Date(MiddleMonth$AllDates) - as.Date("2013-01-01") +1,
                   y = MiddleMonth$value,
                   xout = 1:1431)
ArdcastleTotalbiomass$value = LinApprox$y      
ArdcastleTotalbiomass[1:14,]$value = 1048.0000
ArdcastleTotalbiomass = ArdcastleTotalbiomass %>%
  select(-DayOfMonth)

Ardcastle_salmon_feed = Ardcastle_salmon_feed[Ardcastle_salmon_feed$variable!="Total biomass",]

Ardcastle_salmon_feed = rbind(Ardcastle_salmon_feed,ArdcastleTotalbiomass) 

Ardcastle_salmon_feed <- Ardcastle_salmon_feed %>%
subset(AllDates > as.Date("2013-09-01") &
         AllDates < as.Date("2015-09-01"))



Ardcastle_salmon_feed %>%
  subset(variable =="Total biomass") %>%
  subset(AllDates > as.Date("2013-10-01") &
           AllDates < as.Date("2015-03-07")) %>%
  dplyr::summarise(mean(value)) 

 GB = ggplot(Ardcastle_salmon_feed,
            aes(AllDates, value)) +
  geom_line(size = 1,aes(x = AllDates, y = value))+
  xlab("Date") +
  ylab("Tonnes") + 
  facet_wrap(~       variable, scales = "free_y") +
  Standard_theme()+
  geom_vline(size=1,linetype="dotted",aes(xintercept =as.Date("2013-10-01") ))+
  geom_vline(size=1,linetype="dotted",aes(xintercept =as.Date("2015-03-07") ))+
  scale_color_manual("",
                     values = "black",
                     guide = guide_legend(override.aes = list(fill = NA))) 
 
 
### FIGURE FOR MANUSCRIPT
 
ggsave("/Users/Alan/OneDrive/Papers/Figures/Ardcastle_biomass.jpeg",
       GB,
       width = 25, height = 12)

 



