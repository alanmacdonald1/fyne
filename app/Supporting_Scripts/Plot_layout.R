
if (input$category == "Cultured species (number)") {
  gs = list(ggplotGrob(G18),ggplotGrob(G36),
            ggplotGrob(G19))
}



if (input$category == "Cultured species (length)") {
  gs = list(ggplotGrob(G21), ggplotGrob(G22))
}
if (input$category == "Cultured species (weight)") {
  gs = list(ggplotGrob(G24), ggplotGrob(G25))
}

if (input$category == "Nutrients (pelagic)") {
  gs = list(ggplotGrob(G2),
            ggplotGrob(G3),
            ggplotGrob(G4),
            ggplotGrob(G5))
}

if (input$category == "Nutrients (demersal)") {
  gs = list(ggplotGrob(G1))
}

if (input$category == "Fatty acids (salmon, whole body)") {
  gs = list(
    ggplotGrob(G6),
    ggplotGrob(G7),
    ggplotGrob(G8),
    ggplotGrob(G9)
    # ggplotGrob(G10)
  )
}




if (input$category == "Fatty acids (salmon, fillet)") {
  gs = list(
    ggplotGrob(G6),
    ggplotGrob(G11),
    ggplotGrob(G12),
    ggplotGrob(G13),
    ggplotGrob(G14)
  )
}




if (input$category == "Fatty acids (mussels)") {
  gs = list(ggplotGrob(G32), ggplotGrob(G30), ggplotGrob(G31),ggplotGrob(G29))
            
}


if (input$category == "Plankton (carbon)") {
  gs = list(ggplotGrob(G15), ggplotGrob(G16))
}

if (input$category == "Phytoplankton nitrogen") {
  gs = list(ggplotGrob(G17))
}


if (input$category == "Carbon concentrations") {
  gs = list(ggplotGrob(G27), ggplotGrob(G28))
  
}


if (input$category == "Salmon faeces") {
  gs = list(ggplotGrob(G35))
  
}



if (length(input$Yehaa) != 0) {
  
  
  gs = c(list(
    ggplotGrob(
      data.frame(DayOfYear = 1:365, y =  TEMPERATURE_CELCIUS) %>%
        ggplot(., aes(DayOfYear, y)) +
        geom_point() +
        geom_line() +
        xlab("Day of the year") +
        ylab(expression(paste(
          "Temperature (" ^ o, "C)"
        ))) +
        Standard_theme()+
        scale_y_continuous(limits = c(2,16),breaks = seq(2,16,2),labels = seq(2,16,2))
    )
  ), gs)
}

vals$distPlot = grid.arrange(grobs = gs, layout_matrix = lay)



output$ModelPlots <- downloadHandler(
  filename = function() {
    "ModelPlots.jpeg"
  },
  content = function(file) {
    if (length(gs) < 2) {
      lay <- rbind(c(1,1))
      WW = 40
      HH = 20
    }
    if (length(gs) > 1 & length(gs) <3 ) {
      lay <- rbind(c(1, 2))
      WW = 20
      HH = 10
    }
    if (length(gs) > 2 &
        length(gs) < 5) {
      lay <- rbind(c(1, 2), c(3, 4))
      WW = 20
      HH = 10
    }
    if (length(gs) > 4) {
      lay <- rbind(c(1, 2), c(3, 4), c(5, 6))
      WW = 20
      HH = 10
    }
    vals$distPlot = grid.arrange(grobs = gs, layout_matrix = lay)
    
    
    ggsave(
      vals$distPlot,
      filename = "ModelPlots.jpeg",
      width = WW,
      height = HH
    )
    #dev.off()
  }
)