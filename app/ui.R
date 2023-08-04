  # Model GUI

  # set directory

if(Sys.info()['sysname']=="Windows"){
setwd("/Users/sa07am/OneDrive/Diverseafood/Ecosystem_and_Fatty_Acid_Model/Model_GUI/app/")
} 

# extra packages required
library(lubridate)
library(shiny)
library(Hmisc)
library(shinyalert)
library(leaflet)
library(shinydashboard)
library(magrittr)
library(readxl)
library(ggplot2)
library(gridExtra)
library(hablar)
library(plyr);library(dplyr)
library(ggmap)
library(DT)
#library(devtools)
 

sidebar <- dashboardSidebar(uiOutput("Sidebar"))

body <- dashboardBody(uiOutput("TABUI"))

# Put them together into a dashboardPage
ui <- dashboardPage(
dashboardHeader(title = "FYNE"),
sidebar,
body,
skin = 'green')

  

 

