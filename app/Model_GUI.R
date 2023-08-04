# Model GUI


# set directory
where_this_is = dirname(rstudioapi::getSourceEditorContext()$path)
setwd(where_this_is)

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
#~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#~~~~ Import data sets  ~~~~#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~# 

source("Supporting_Scripts/Import_datasets.R", local = TRUE)

SALMON_FEED = NULL

FIXED_START = as.Date("2013/01/1")


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#~~~~ Need unique key to use google maps  ~~~~#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
library(ggmap)
register_google(key = <YOUR-GOOGLE-KEY>)
has_google_key()

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Any computations that can be done outside main program
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

Ingredient_choices =
  FeedComp %>%
  distinct(Ingredient) %>%
  use_series(Ingredient)

sidebar <- dashboardSidebar(uiOutput("Sidebar"))

body <- dashboardBody(uiOutput("TABUI"))

# Put them together into a dashboardPage
ui <- dashboardPage(
dashboardHeader(title = "FYNE"),
sidebar,
body,
skin = 'green')

server <- shinyServer(function(input, output, session) {
  vals <- reactiveValues(distPlot = NULL, p1 = NULL)
  
  ntabs <- 4
  tabnames <-
    c("Farm_setup",
      "Stocking_parameters",
      "Feed_composition",
      "Results")
  tabnames_full <-
    c("Farm setup",
      "Stocking parameters",
      "Feed composition",
      "Results")
  
  checkboxnames <-
    paste0(tabnames, 'group') # "tab1group", "tab2group", ...
  plotnames <- paste0("plot", 1:ntabs) # "plot1", "plot2", ...
  
  
  output$Sidebar <- renderUI({
    Menus <- vector("list", ntabs)
    Menus[[1]] <-   menuItem(
      tabnames_full[1],
      tabName = tabnames[1],
      icon = icon("wrench", lib = "glyphicon"),
      selected = 1
    )
    Menus[[2]] <-   menuItem(
      tabnames_full[2],
      tabName = tabnames[2],
      icon = icon("tasks", lib = "glyphicon"),
      selected = 1
    )
    Menus[[3]] <-   menuItem(
      tabnames_full[3],
      tabName = tabnames[3],
      icon = icon("tasks", lib = "glyphicon"),
      selected = 1
    )
    Menus[[4]] <-   menuItem(
      tabnames_full[4],
      tabName = tabnames[4],
      icon = icon("grain", lib = "glyphicon"),
      selected = 1
    )
    do.call(function(...)
      sidebarMenu(id = 'sidebarMenu', ...), Menus)
  })
  
  output$TABUI <- renderUI({
    Tabs <- vector("list", ntabs)
    
    Tabs[[1]] <- tabItem(
      tabName = tabnames[1],
      tags$head(
        tags$link(rel = "icon",
                  type = "jpg",
                  href = "https://upload.wikimedia.org/wikipedia/commons/thumb/5/5e/Copley_Fielding_-_The_Head_of_Loch_Fyne%2C_with_Dindarra_Castle_-_B1977.14.4316_-_Yale_Center_for_British_Art.jpg/640px-Copley_Fielding_-_The_Head_of_Loch_Fyne%2C_with_Dindarra_Castle_-_B1977.14.4316_-_Yale_Center_for_British_Art.jpg")
      ),
      fluidRow(column(
        12,
        leafletOutput("myMap", width = "900px", height = "400px")
      )),
      br(),
      br(),
      br(),
      column(
        6,
        fileInput('file1', 'Please select file for farm setup',
                  accept = c(".xls"))
      ),
      
      column(6,        fileInput(
        'file2', 'Please select diets',
        accept = c(".xls")
      )),
      column(
        6,
        fileInput(
          'file3',
          'Please select file for salmon feed in tonnes',
          accept = c(".xls")
        )
      ),
      column(
        6,
        selectInput('Saved_settings', 'Saved settings', choices = c("No", "Yes"))
      ),
      column(6,
             htmlOutput("testHTML3"),)
    )
    
    
    
    Tabs[[2]] <- tabItem(
      tabName = tabnames[2],
      tags$head(
        tags$style(HTML('.content-wrapper {
               overflow: auto;
           }')),
        tags$script(src = "http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS_HTML-full", type = 'text/javascript'),
        tags$script(
          "MathJax.Hub.Config({tex2jax: {inlineMath: [['$','$'], ['\\(','\\)']]}});",
          type = 'text/x-mathjax-config'
        )
      ),
      
      tags$img(
        src = "salmon_farm_scotland3.jpg",
        height = "100%",
        width = "200%",
        style = 'display: block; margin-left: auto; margin-right: auto; position: absolute; opacity: 1;top:0;bottom:0;left:0'
      ),
      fluidRow(
        column(
          3,
          shinydashboard::box(
            solidHeader = TRUE,
            status = "primary",
            title = "Finfish abundance",
            width = 12,
            collapsible = T,
            collapsed = T,
            
            numericInput(
              "Number_salmon",
              "Salmon (no):",
              317308.32221  , #307260 
              min = 0,
              max = 700000
            ),
            htmlOutput("testHTML2")
            
          )
        ),
        
        
        shinydashboard::box(
          solidHeader = TRUE,
          status = "primary",
          title = "Finfish size",
          width = 3,
          collapsible = T,
          collapsed = T,
          column(12,
                 wellPanel(
                   numericInput(
                     "Weight_salmon",
                     label = HTML("Weight $ &#8203 (g &#8203) $"),
                     min = 0,
                     max = 1000,
                     value = 80,
                     step = 1
                   ),
                   
                   numericInput(
                     "Length_salmon",
                     label = HTML("Length $ &#8203 (cm &#8203) $"),
                     min = 0,
                     max = 100,
                     value = 20,
                     step = 1
                   )
                 ))
        ),
        
        
        shinydashboard::box(
          solidHeader = TRUE,
          status = "primary",
          title = "IMTA species abundance",
          width = 3,
          collapsible = T,
          collapsed = T,
          column(
            12,
            
            numericInput(
              "Number_mussel",
              label = HTML("Mussel $ &#8203 (individuals &#8203) $"),
              min = 0,
              max = 1000000,
              value = 5,
              step = 10000
            ),
            numericInput(
              "Seaweed_biomass",
              label = HTML("Seaweed biomass $ &#8203 (kg &#8203) $"),
              min = 0,
              max = 0.001,
              value = 0.00019,
              step = 0.00001
            ),
          )
        ),
        
        
        shinydashboard::box(
          solidHeader = TRUE,
          status = "primary",
          title = "IMTA species size",
          width = 3,
          collapsible = T,
          collapsed = T,
          column(
            12,
            
            numericInput(
              "Length_mussel",
              label = HTML("Mussel length $ &#8203 (cm &#8203) $"),
              min = 0,
              max = 1000,
              value = 2.85,
              step = 1
            ),
            numericInput(
              "Weight_mussel",
              label = HTML("Mussel weight $ &#8203 (g &#8203) $"),
              min = 0,
              max = 50,
              value = 2.25,
              step = .1
            )
            
          )
        )
        
        
      ),
      
      fluidRow(
        shinydashboard::box(
          solidHeader = TRUE,
          status = "primary",
          title = "Production schedule",
          width = 4,
          collapsible = T,
          collapsed = T,
          
          column(
            12,
            wellPanel(
              dateRangeInput(
                inputId = "dates",
                label = h6("Finfish"),
                start = "2013-10-01",
                end = "2015-06-01",
                min = "2012-06-01",
                max = "2017-06-01"
              ),
              dateRangeInput(
                inputId = "dates2",
                label = h6("Mussels"),
                start = "2014-07-15",
                end = "2015-04-15",
                min = "2012-06-01",
                max = "2017-06-01"
              ),
              dateRangeInput(
                inputId = "dates3",
                label = h6("Seaweed"),
                start = "2015-01-01",
                end = "2015-05-01",
                min = "2012-06-01",
                max = "2017-06-01"
              )
            )
          )
        ),
        shinydashboard::box(
          status = "primary",
          title = "Finfish feed",
          solidHeader = T,
          width = 8,
          collapsible = T,
          collapsed = T,
          plotOutput(outputId = "test")
          
        )
        
      )
      
      
    )
    
    
    
    
    Tabs[[3]] <- tabItem(
      tabName = tabnames[3],
      tags$head(
        tags$style(HTML('.content-wrapper {
               overflow: auto;
           }')),
        tags$script(src = "http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS_HTML-full", type = 'text/javascript'),
        tags$script(
          "MathJax.Hub.Config({tex2jax: {inlineMath: [['$','$'], ['\\(','\\)']]}});",
          type = 'text/x-mathjax-config'
        )
      ),
      
      tags$img(
        src = "salmon_farm_scotland3.jpg",
        height = "100%",
        width = "200%",
        style = 'display: block; margin-left: auto; margin-right: auto; position: absolute; opacity: 1;top:0;bottom:0;left:0'
      ),
      fluidRow(column(
        7,
        # saved diets, ingredient selections, prox composition
        fluidRow(
          column(6,
                 wellPanel(
                   selectInput('diet', 'Saved diets', "")
                 )),
          column(
            6,
            selectizeInput(
              'food_id',
              'Ingredient',
              choices = Ingredient_choices,
              options = list(
                placeholder = 'Type to search for ingredient',
                onInitialize = I('function() { this.setValue(""); }')
              )
            ),
            conditionalPanel(
              'input.food_id != ""',
              numericInput(
                'Percentage',
                'Percentage',
                value = 1,
                min = 0,
                step = 1
              )
            ),
            actionButton("add", "Add ingredient"),
            actionButton("remove", "Remove ingredient")
          )
        ),
        fluidRow(
          column(
            12,
            plotOutput(outputId = "Prox.composition",
                       # width = "320px",
                       # height = "500px")))
            )),
          
          
        )
      ),
      column(
        5,
        shinydashboard::box(
          title = "Protein",
          solidHeader = T,
          width = 12,
          collapsible = T,
          collapsed = F,
          tags$p(textOutput("serving", inline = T)),
          div(DT::DTOutput("nutrient_table"), style = "font-size: 70%;")
        )
        
      )))
    
    
    
    
    
    Tabs[[4]] <- tabItem(tabName = tabnames[4],
                         fluidRow(
                           column(
                             4,
                             useShinyalert(),
                             actionButton('switchtab', 'Run the model!'),
                             wellPanel(
                               withMathJax(),
                               tags$div(
                                 HTML(
                                   "<script type='text/x-mathjax-config'>
                MathJax.Hub.Config({
                tex2jax: {inlineMath: [['$','$']]}
                });
                </script>
                "
                                 )
                               ),
                               selectInput(
                                 "category",
                                 "Category",
                                 choices = c(
                                   "Fatty acids (salmon, whole body)",
                                   "Fatty acids (salmon, fillet)",
                                   "Carbon concentrations",
                                   "Cultured species (number)",
                                   "Cultured species (length)",
                                   "Cultured species (weight)",
                                   "Plankton (carbon)",
                                   "Phytoplankton nitrogen",
                                   "Nutrients (pelagic)",
                                   "Nutrients (demersal)",
                                   
                                   "Fatty acids (mussels)",
                                   "Salmon faeces"
                                 )
                               )
                             )
                           ),
                           column(
                             12,
                             offset = 0,
                             plotOutput(
                               outputId = "distPlot",
                               width = "1000px",
                               height = "2000px"
                             )
                           )
                         ))
    
    
    
    do.call(tabItems, Tabs)
  })
  
  
  
  # add feed data frame
  salmon_feed = reactive({
    inFile <- input$file3
    if (is.null(inFile))
      return(NULL)
    
    Ardcastle_salmon_feed =   read_excel(inFile$datapath)
    
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
    
    Ardcastle_salmon_feed
    
  })
  
  
  
  SpeciesDates <- reactiveValues()
  
  observe({
    SpeciesDates$SalmonStart =  input$dates[1]
  })
  observe({
    SpeciesDates$SalmonEnd = input$dates[2]
  })
  observe({
    SpeciesDates$MusselStart = input$dates2[1]
  })
  observe({
    SpeciesDates$MusselEnd = input$dates2[2]
  })
  observe({
    SpeciesDates$SeaweedStart = input$dates3[1]
  })
  observe({
    SpeciesDates$SeaweedEnd = input$dates3[2]
  })
  
  
  
  
  
  
  LIGHT = reactive({
    
    SalmonStart = SpeciesDates$SalmonStart
    SalmonEnd =   SpeciesDates$SalmonEnd
    MusselStart =  SpeciesDates$MusselStart
    MusselEnd =  SpeciesDates$MusselEnd
    SeaweedStart = SpeciesDates$SeaweedStart
    SeaweedEnd =  SpeciesDates$SeaweedEnd
    
    if (!is.null(SalmonStart))
    {
      
      LIGHT0 = Irradiance  %>%
        filter(Date >= min(c(FIXED_START, as.Date(SalmonStart),as.Date(MusselStart), as.Date(SeaweedStart))) &
                 Date <= max(c( as.Date( SalmonEnd),as.Date(MusselEnd), as.Date(SeaweedEnd))))
      
    }
    
    LIGHT0
    
  })
  
  PHYTO_GROWTH = reactive({
    
    SalmonStart = SpeciesDates$SalmonStart
    SalmonEnd =   SpeciesDates$SalmonEnd
    MusselStart =  SpeciesDates$MusselStart
    MusselEnd =  SpeciesDates$MusselEnd
    SeaweedStart = SpeciesDates$SeaweedStart
    SeaweedEnd =  SpeciesDates$SeaweedEnd
    
    if (!is.null(SalmonStart))
    {
      
      PHYTO_GROWTH0 = Irradiance  %>%
        filter(Date >= min(c( FIXED_START,as.Date(SalmonStart),as.Date(MusselStart), as.Date(SeaweedStart))) &
                 Date <= max(c( as.Date( SalmonEnd),as.Date(MusselEnd), as.Date(SeaweedEnd))))
      
    }
    
    PHYTO_GROWTH0
    
  })
  
  
  
  
  
  
  SALMON_FEED = reactive({
    
    
    SalmonStart = SpeciesDates$SalmonStart
    SalmonEnd =   SpeciesDates$SalmonEnd
    MusselStart =  SpeciesDates$MusselStart
    MusselEnd =  SpeciesDates$MusselEnd
    SeaweedStart = SpeciesDates$SeaweedStart
    SeaweedEnd =  SpeciesDates$SeaweedEnd
    
    if (!is.null(SalmonStart))
    {
      
      
      SALMON_FEED0 = salmon_feed()  %>%
        filter(AllDates >= min(c( FIXED_START,as.Date(SalmonStart),as.Date(MusselStart), as.Date(SeaweedStart))) &
                 AllDates <= max(c( as.Date( SalmonEnd),as.Date(MusselEnd), as.Date(SeaweedEnd))))
      
      
      
    }
    
    SALMON_FEED0
    
  })
  
  
  
  
  output$test <- renderPlot({
    if (input$file3[1] != "") {
      
      
      SALMON_FEED()  %>%
        ggplot(aes(AllDates,value))+
        facet_wrap(~variable,nrow = 2,scales = "free")  +
        geom_point()+
        geom_line() +
        xlab("Date")+
        ylab(expression(paste("tonnes d" ^ -1))) +
        Standard_theme() +
        theme(strip.text.x = element_text(size = 20),
              axis.text.x =element_text(size=20))
      
    }
    
  })
  
  
  
  ing_df <- shiny::reactiveValues()
  ing_df$df <- data.frame(
    "Ingredient" = character(),
    "Percentage" = numeric(),
    stringsAsFactors = F
  )
  
  
  
  
  
  
  outVar = reactive({
    inFile <- input$file2
    if (is.null(inFile))
      return(NULL)
    DietChoices = read_excel(inFile$datapath) %>%
      select(-Ingredient,-Veg,-Emery) %>%
      names()
    # gives names of diets
  })
  
  observe({
    updateSelectInput(session, "diet",
                      choices = outVar())
  })
  
  
  # add presaved ingredients to data table
  observe({
    inFile <- input$file2
    if (is.null(inFile))
      return(NULL)
    
    if (input$diet == "")
      return(NULL)
    
    
    
    DATA = read_excel(inFile$datapath) %>%
      select(Ingredient, input$diet)
    
    
    names(DATA)[2] = "percentage"
    
    
    
    ing_df$df <- data.frame(
      "Ingredient" = character(),
      "Percentage" = numeric(),
      stringsAsFactors = F
    )
    
    isolate(ing_df$df[1, ] <- c("Total", 0))
    
    
    isolate(for (ING in unique(DATA$Ingredient))
    {
      ing_df$df[nrow(ing_df$df) + 1, ] <-
        c(DATA[DATA$Ingredient == ING,]$Ingredient,
          as.numeric(as.character(DATA[DATA$Ingredient == ING,]$percentage)))
      
    })
    
    isolate(ing_df$df[, 2] <- as.numeric(ing_df$df[, 2]))
    
    isolate(ing_df$df[1, ] <-
              c("Total", sum(as.numeric(
                as.character(ing_df$df[, 2])
              ))))
    
    
  })
  
  
  observeEvent(input$remove, {
    isolate(ing_df$df <- ing_df$df[-(nrow(ing_df$df)),])
    
    isolate(ing_df$df[1, ] <-
              c("Total", sum(as.numeric(
                as.character(ing_df$df[-1 , 2])
              ))))
    
    
  })
  
  observeEvent(input$add, {
    # is added ingredient already there?
    SUM = sum(str_detect(ing_df$df$Ingredient, input$food_id))
    
    # If not
    if (SUM == 0) {
      isolate(ing_df$df[nrow(ing_df$df) + 1, ] <- c(input$food_id,
                                                    as.numeric(as.character(
                                                      input$Percentage
                                                    ))))
    }
    
    #  If yes
    if (SUM != 0) {
      isolate(ing_df$df[ing_df$df$Ingredient == input$food_id, 2] <-
                as.numeric(as.character(input$Percentage)) +
                as.numeric(as.character(ing_df$df[ing_df$df$Ingredient == input$food_id, 2])))
    }
    
    isolate(ing_df$df[1, ] <-
              c("Total", sum(as.numeric(
                as.character(ing_df$df[-1 , 2])
              ))))
    
    
    
    # update choices
    updateNumericInput(session, 'Percentage', 'Percentage', 1)
    updateSelectInput(session, 'food_id', '1. Ingredient', choices = Ingredient_choices)
    
    
  })
  
  # display nutrients necessary for label
  nutrient_table <- reactive({
    ing_df$df
  })
  
  
  
  # get proximate composition of ingredients
  proximate_compostion <- reactive({
    
    Prox.comp = nutrient_table() %>%
      right_join(FeedComp) %>%
      write.csv(.,"test.csv")
    
    
    Prox.comp = nutrient_table() %>%
      right_join(FeedComp) %>%
      mutate_at(vars(starts_with("Percentage")), funs(as.numeric)) %>%
      group_by(Parameter) %>%
      na.omit() %>%
      summarise(composition = weighted.mean(As.fed, Percentage)) %>%
      write.csv(.,"test2.csv")
    
    Prox.comp = nutrient_table() %>%
      right_join(FeedComp) %>%
      mutate_at(vars(starts_with("Percentage")), funs(as.numeric)) %>%
      group_by(Parameter) %>%
      na.omit() %>%
      summarise(composition = weighted.mean(As.fed, Percentage))
    
    Prox.comp$composition = round(Prox.comp$composition, 2)
    
    PROXCOMP = data.frame(
      C16 = Prox.comp[Prox.comp$Parameter == "C16:0 palmitic acid",]$composition,
      C18.1 = Prox.comp[Prox.comp$Parameter == "C18:1 oleic acid",]$composition,
      C18.2 = Prox.comp[Prox.comp$Parameter == "C18:2 linoleic acid",]$composition,
      C18.3 = Prox.comp[Prox.comp$Parameter == "C18:3 linolenic acid",]$composition,
      C20.4 = Prox.comp[Prox.comp$Parameter == "C20:4 arachidonic acid",]$composition,
      C20.5 = Prox.comp[Prox.comp$Parameter == "C20:5 eicosapentaenoic acid",]$composition,
      C22.5 = Prox.comp[Prox.comp$Parameter == "C22:5 docosapentaenoic acid",]$composition,
      C22.6 = Prox.comp[Prox.comp$Parameter == "C22:6 docosahexaenoic acid",]$composition,
      
      Protein = Prox.comp[Prox.comp$Parameter == "Crude protein",]$composition,
      Fat = Prox.comp[Prox.comp$Parameter == "Crude fat",]$composition,
      NFE = Prox.comp[Prox.comp$Parameter == "NFE",]$composition,
      Fibre = Prox.comp[Prox.comp$Parameter == "Crude fibre",]$composition,
      Ash = Prox.comp[Prox.comp$Parameter == "Ash",]$composition,
      Phos = Prox.comp[Prox.comp$Parameter == "Phosp_percentage",]$composition,
      Min = Prox.comp[Prox.comp$Parameter == "Mineral_percentage",]$composition,
      Moisture = Prox.comp[Prox.comp$Parameter == "Water",]$composition,
      Energy = 0.239 * Prox.comp[Prox.comp$Parameter == "Crude protein",]$composition +
        0.398 * Prox.comp[Prox.comp$Parameter == "Crude fat",]$composition +
        0.176 * Prox.comp[Prox.comp$Parameter == "NFE",]$composition
      
    )
    
    # 1 g crude protein = 23.9 kJ, 1 g crude fat = 39.8 kJ, and 1 g NFE = 17.6 kJ.
    PROXCOMP
    
  })
  
  
  output$nutrient_table <-
    DT::renderDataTable(
      nutrient_table(),
      selection = 'none',
      editable = TRUE,
      server = F
    )
  
  
  observeEvent(input$nutrient_table_cell_edit, {
    info = input$nutrient_table_cell_edit
    
    isolate(ing_df$df[info$row, info$col] <-
              as.numeric(as.character(info$value)))
    
    isolate(ing_df$df[1, ] <-
              c("Total", sum(as.numeric(
                as.character(ing_df$df[-1, 2])
              ))))
    
  })
  
  
  output$Prox.composition <- renderPlot({
    # labels = proximate_compostion() %>% names()
    
    # labels[6]  = expression(paste("Energy (kJ g" ^ -1, ")"))
    
    P1 = proximate_compostion() %>%
      reshape2::melt() %>%
      dplyr::filter(!grepl("C16|C18|C20|C22", variable)) %>%
      ggplot(., aes(variable, value)) +
      geom_bar(
        fill = "darkgrey",
        colour = "black",
        position = 'dodge',
        stat = "identity"
      ) +
      geom_text(aes(label = value),
                position = position_dodge(width = 0.9),
                vjust = -0.25) +
      Standard_theme() +
      theme_bw() +
      theme(
        panel.border = element_blank(),
        panel.grid.minor = element_blank(),
        axis.line = element_line(colour = "black")
      ) +
      xlab("") +
      ylab("") +
      scale_y_continuous(
        limits = c(0, 70),
        breaks = seq(0, 100, 10),
        labels = seq(0, 100, 10)
      ) +
      ggtitle("Proximate composition (%)") +
      theme(
        axis.text.x = element_text(
          angle = 45,
          hjust = 1,
          size = 10
        ),
        axis.text.y = element_text(size = 10),
        axis.text = element_blank(),
        axis.ticks.length = unit(0, "mm"),
        plot.margin = unit(c(4, 2,-5, 0), "mm")
      )
    # scale_x_discrete(labels = labels)
    
    
    
    
    
    PUFA_comp = select(
      proximate_compostion(),
      matches('C16|C18.1|C18.2|C18.3|C20.4|C20.5|C22.5|C22.6')
    )  %>%
      reshape2::melt()
    
    
    P2 = PUFA_comp %>%
      ggplot(., aes(variable, value)) +
      geom_bar(
        fill = "darkgrey",
        colour = "black",
        position = 'dodge',
        stat = "identity"
      ) +
      geom_text(aes(label = value),
                position = position_dodge(width = 0.9),
                vjust = -0.25) +
      Standard_theme() +
      theme_bw() +
      theme(
        panel.border = element_blank(),
        panel.grid.minor = element_blank(),
        axis.line = element_line(colour = "black")
      ) +
      xlab("") +
      ylab("") +
      # scale_y_continuous(
      #   limits = c(0, 1 + max(PUFA_comp$value)),
      #   breaks = seq(0, max(PUFA_comp$value), 1),
      #   labels = seq(0, max(PUFA_comp$value), 1)
      # ) +
      scale_y_continuous(
        limits = c(0, 6),
        breaks = seq(0, 6, 1),
        labels = seq(0, 6, 1)
      ) +
      ggtitle("PUFA composition (%)") +
      theme(
        axis.text.x = element_text(
          angle = 45,
          hjust = 1,
          size = 10
        ),
        axis.text.y = element_text(size = 10),
        axis.text = element_blank(),
        axis.ticks.length = unit(0, "mm"),
        plot.margin = unit(c(4, 2,-5, 0), "mm")
      )
    # scale_x_discrete(labels = labels)
    
    
    gsg = list(ggplotGrob(P1), ggplotGrob(P2))
    
    
    grid.arrange(grobs = gsg)
    
    
    
  })
  
  
  
  output$myMap <- renderLeaflet(
    leaflet() %>%
      addTiles() %>%
      addProviderTiles('Esri.WorldImagery') %>%
      addProviderTiles("CartoDB.PositronOnlyLabels") %>%
      setView(
        lng = -5.28449,
        lat = 56.078,
        zoom = 14
      ) %>%
      addScaleBar() 
    # addCircles(
    #   fill = T,
    #   fillOpacity = 1,
    #   lng = c(-5.29138,-5.28846,-5.28575,-5.26512),
    #   lat = c(56.07548,56.07943,56.08235,56.09128))
    
    
    
    
    
  )
  
  
  
  observeEvent(input$file1, {
    inFile <- input$file1
    if (is.null(inFile))
      return(NULL)
    DATA = read_excel(inFile$datapath)
    
    IMTA_data = DATA %>%
      subset(Farm_type == "IMTA")
    
    First_second_vertices = IMTA_data %>%
      arrange(-Lat) %>%
      slice(1:2)
    
    Third_fourth_vertices = IMTA_data %>%
      anti_join(First_second_vertices)
    
    nearest.point = get.knnx(data = Third_fourth_vertices[, c("Lat", "Long")],
                             query = First_second_vertices[2, c("Lat", "Long")],
                             k = 2)
    
    IMTA_data = rbind.data.frame(First_second_vertices,
                                 Third_fourth_vertices[nearest.point$nn.index,])
    
    
    
    leafletProxy("myMap")  %>%
      addPolygons(
        color = "black" ,
        fillOpacity = 1,
        fill = "black" ,
        lng = IMTA_data$Long,
        lat = IMTA_data$Lat
      ) %>%
      addMarkers(
        lng = -5.28,
        lat = 56.081,
        label = "Fish farm",
        labelOptions = labelOptions(
          noHide = T,
          direction = "bottom",
          style = list(
            "color" = "red",
            "font-family" = "serif",
            "font-style" = "bold",
            "box-shadow" = "3px 3px rgba(0,0,0,0.25)",
            "font-size" = "30px",
            "border-color" = "rgba(0,0,0,0.5)"
          )
        )
      ) %>%
      addMarkers(
        lng = -5.284,
        lat = 56.075,
        label = "IMTA",
        labelOptions = labelOptions(
          noHide = T,
          direction = "bottom",
          style = list(
            "color" = "red",
            "font-family" = "serif",
            "font-style" = "bold",
            "box-shadow" = "3px 3px rgba(0,0,0,0.25)",
            "font-size" = "30px",
            "border-color" = "rgba(0,0,0,0.5)"
          )
        )
      ) %>%
      addCircles(
        fill = T,
        fillOpacity = 1,
        lng = c(
          -5.28577,
          -5.28577 - .05 / 111,
          -5.28577 - .1 / 111,
          -5.28577 - .2 / 111,
          -5.28577 - .25 /
            111,
          -5.2849 - .05 / 111,
          -5.2849 - .1 / 111,
          -5.2849 - .2 / 111,
          -5.2849
        ),
        lat = c(
          56.08216,
          56.08216 - .05 / 111,
          56.08216 - .1 / 111,
          56.08216 - .2 / 111,
          56.08216 - .25 / 111,
          
          56.0819 - .05 / 111,
          56.0819 - .1 / 111,
          56.0819 - .2 / 111,
          
          56.0819
        ),
        weight = 1,
        radius = 15
      )
  })
  
  
  observeEvent(input$file2, {
    inFile <- input$file2
    if (is.null(inFile))
      return(NULL)
    DATA = read_excel(inFile$datapath)
    
    
  })
  
  
  
  
  output$testHTML2 <- renderText({
    Volume = 9 * 25 * pi * 14 ^ 2 # volume 9 cages
    # A salmon cage with a radius of 14 m and depth of 25 m has a volume of 15394 m3 (IDREEM, 2019).
    
    
    
    paste("Salmon density:",
          round(input$Number_salmon / Volume, 2),
          "m<sup>3</sup>")
  })
  
  
  
  
  
  
  observeEvent(input$switchtab, {
    INGREDIENT_TOTAL = as.numeric(ing_df$df[ing_df$df$Ingredient == 'Total',]$Percentage)
    
    if (INGREDIENT_TOTAL == 100) {
      # compile c code
      system("R CMD SHLIB  Main_script.cpp")
      
      
      
      SalmonStart = SpeciesDates$SalmonStart
      SalmonEnd =   SpeciesDates$SalmonEnd
      MusselStart =  SpeciesDates$MusselStart
      MusselEnd =  SpeciesDates$MusselEnd
      SeaweedStart = SpeciesDates$SeaweedStart
      SeaweedEnd =  SpeciesDates$SeaweedEnd
      
      TEMPERATURE = Temperature  %>%
        filter(Date >= min(c( FIXED_START,as.Date(SalmonStart),as.Date(MusselStart), as.Date(SeaweedStart))) &
                 Date <= max(c( as.Date( SalmonEnd),as.Date(MusselEnd), as.Date(SeaweedEnd))))
      
      
      TEMPERATURE_CELCIUS = TEMPERATURE$temperature_fit
      
      TEMPERATURE_KELVIN   =  TEMPERATURE_CELCIUS  + 273.15 	#Temperature (K)
      
      # seaweed carbon is proportional to biomass
      mu_CA = 0.3 # grams carbon per grams
      SB = input$Seaweed_biomass # total kg per m3
      Seaweed_carbon =  SB * (10 ^ 6) * mu_CA  # W_a is kg m-3
      
      PUFAs_prox_comp = proximate_compostion()
      print(        
        nutrient_table()  %>%
          right_join(FeedComp)  %>%
          subset(Parameter=="Crude protein"))
      
      ProteinContents =  nutrient_table()  %>%
        right_join(FeedComp)  %>%
        subset(Parameter=="Crude protein")  %>%
        hablar::convert(num(Percentage,As.fed)) %>%
        mutate(ProteinContent = Percentage*As.fed/10000)
      
      
      
      # we have 7 boxes
      # "A" is the IMTA - area 46276.3 m2
      # "B" surroudning salmon rings - area 48780.67 m2
      # "C" has 9 salmon rings - area 5538.054 m2
      # "D" is north of the farm
      # "E" middle of the farm
      # "FF" south farm
      #  "G" middle of IMTA
      
      
      
      
      X = c(
        c(0,0,(9/9)*input$Number_salmon, 0,0,0,0),
        c(0,(3/3)*input$Number_mussel,0,0,0,0,0),
        rep(0,7),
        rep(5,7), # Energy_salmon,
        rep(5,7), # Energy_mussel,
        rep(5,7), # Energy_sea_cucumber,
        rep(5,7), # Reproductive_energy_salmon,
        rep(5,7), # Reproductive_energy_mussel,
        rep(5,7), # Reproductive_energy_sea_cucumber,
        rep(4,7), # Biovolume_salmon,
        rep(5,7),# Biovolume_mussel,
        rep(5,7),# Biovolume_sea_cucumber,
        rep(input$Length_salmon,7), # Length_salmon
        rep(input$Length_mussel,7),# Length_mussel,
        rep(2,7), # Length_sea_cucumber,
        rep(input$Weight_salmon,7),# Weight_salmon
        rep(input$Weight_mussel,7),# Weight_mussel
        rep(1,7), # Weight_sea_cucumber
        c((3/3)*Seaweed_carbon,0,0,0,0,0,0), # Seaweed_carbon
        c(.15*(3/3)*Seaweed_carbon,0,0,0,0,0,0), # Seaweed_nitrogen
        rep(.08,7),# Zooplankton_structure_weight
        rep(.1,7), # Zooplankton_reserves
        rep(.1,7),# Phytoplankton_carbon
        rep(.2*.1,7), # Phytoplankton_nitrogen
        rep(1e-2,7),# Pelagic_non_plankton_organic_carbon
        rep(.18*1e-2,7),# Pelagic_non_plankton_organic_nitrogen
        rep(8.0e+01,7),# DON
        rep(10,7), # Ammonium
        rep(5,7),# Nitrate
        rep(1e-4,7), # Sediment_organic_carbon
        rep(.18*1e-4,7),  # Sediment_organic_nitrogen
        PUFAs_prox_comp$Fat / 100 ,#P_fat
        PUFAs_prox_comp$NFE / 100 , #P_NFE
        PUFAs_prox_comp$Fibre / 100 , #P_fibre
        PUFAs_prox_comp$Phos / 100 ,# P_phos
        PUFAs_prox_comp$Min / 100 , #P_min
        0.01*ProteinContents[ProteinContents$Ingredient == 'fish-meal-protein-65',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'fish-meal-protein-70',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'soybean-protein-concentrate-protein-70-90',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'processed-animal-proteins-poultry-protein-70',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'whey-permeate',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'Blood-meal',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'wheat-gluten',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'DL-methionine',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'maize',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'corn-gluten-meal',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'corn-gluten-feed',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'Pea-protein-concentrate',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'feather-meal',]$Percentage,
        0.01*ProteinContents[ProteinContents$Ingredient == 'Potato-protein-concentrate',]$Percentage
      )
      
      
      
      
      
      X = as.numeric(X)
      
      
      
      
      
      DHA_COMP = PUFAs_prox_comp$C22.6 / 100
      EPA_COMP = PUFAs_prox_comp$C20.5 / 100
      DPA_COMP = PUFAs_prox_comp$C22.5 / 100
      ALA_COMP = PUFAs_prox_comp$C18.3 / 100
      LIN_COMP = PUFAs_prox_comp$C18.2 / 100
      ARA_COMP = PUFAs_prox_comp$C20.4 / 100
      OLA_COMP = PUFAs_prox_comp$C18.1 / 100
      PAM_COMP = PUFAs_prox_comp$C16 / 100
      
      
      source("Supporting_Scripts/Parameters.R", local = TRUE)
      
      
      # 2012-12-21 - 2017-12-20 irradiance
      
      # 2013-01-01 2016-12-30 temperature
      
      # 2013-01-01 2016-12-01 salmon feed
      
      
      
      Modrun = function()
      {
        {
          ecomod =  .C("ECOSYSTEM_MODEL",
                       as.double(PARAMETERS))
        }
      }
      
      # load .so file
      dyn.load("Main_script.dll")
      
      # call ecosystem model
      Modrun()
      
      source("Supporting_Scripts/Plot_results.R", local = TRUE)
      
      output$distPlot <- renderPlot({
        source("Supporting_Scripts/Plot_layout.R", local = TRUE)
        
      })
      
      
    } else {
      shinyalert(
        "Oops!",
        paste0(
          "Ingredients must add to 100%. They currently add up to ",
          INGREDIENT_TOTAL,
          "%"
        ),
        type = "error"
      )
    }
    
    
  })
  
  
  
  
})

shinyApp(ui, server)


test = NULL
Nit_t = 0
for(tt in 1:6000)
  
{
  #Nit_t = 0.02382086 + 0.96*Nit_t
  
  Nit_t = 0.03607563 + 0.96*Nit_t
  
  
  test = c(test,Nit_t)
}




