
ALL_TRANSPORT =  NULL
for(FILE in ALL_NUTRIENT_FILES)
  {

TRANSPORT<- read.csv(paste0("~/OneDrive/FYNE_particle_tracking/Transport_matrices/IMPORT/nutrients/",FILE)) %>%
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
ALL_TRANSPORT = rbind(ALL_TRANSPORT, data.frame(NROW = 1:63,FILE = FILE, TRANSPORT))
}

AVERAGE_TRANSPORT = ALL_TRANSPORT %>%
  group_by(NROW) %>%
  dplyr::summarise(MeanT = mean(TRANSPORT)) %>%
  use_series(MeanT)



