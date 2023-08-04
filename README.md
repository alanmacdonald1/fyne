<a name="readme-top"></a>
<!-- SUMMARY -->
*Still in development*
*As part of the [Diverseafood](https://www.sams.ac.uk/science/projects/diverseafood/) project *
# FYNE (Model of salmon waste and fatty acids in loch fyne IMTA farm)
 
[![Project version](https://img.shields.io/badge/version-1.0.0-blue)](https://github.com/alanmacdonald1/fyne)
[![RShiny version](https://img.shields.io/badge/R-%23276DC3.svg?style=flat&logo=r&logoColor=white)](https://hub.docker.com/layers/rocker/shiny/3.5.1/images/sha256-981ba599bae69ceb49c83d4fa88397206c98701698943c43c76536d1aafb715b?context=explore)
[![Docker version](https://img.shields.io/badge/Docker-20.10.21-blue)](https://www.docker.com/)
[![Docker Compose version](https://img.shields.io/badge/Docker%20Compose-v2.13.0-blue)](https://docs.docker.com/compose/)
 

## What is it?

A UI that simulates carbon and nitrogen flows in salmon farm given different inputs e.g. salmon diet composition, salmon number etc.

## How does it work?

R shiny app run in docker that connects to mathematical model in C.

1. Main model in C called by R
2. R shiny spits out run parameters into C
3. C spits out model output
4. R shiny displays real time (well, its not instant) model results


![image](https://user-images.githubusercontent.com/43473952/220955248-395d5697-846a-4f84-a67d-161248a5a950.png)
![image](https://user-images.githubusercontent.com/43473952/220952923-c98b3f92-1f0c-4131-b229-e17f3bae1a0b.png)
![image](https://user-images.githubusercontent.com/43473952/220955023-367e737e-3a75-45a0-8864-50aa9b6194ef.png)


# Docker setup


1. The docker-compose.yaml file has all the setup details
2. Bring up the container
 
```
docker-compose up
```


4. If changes are required, cd into the container 
```
docker exec -it <CONTAINER_ID> /bin/bash
```
Do your stuff and exit
```
exit
```
Restart the container
```
docker-compose restart <CONTAINER_ID>
```

<!-- TO DO -->
# Roadmap

- [ ] Ensure main model is compiled properly
- [ ] Add output files to download

### Further reading 
See  [Ren et al. (2012) - An ecosystem model for optimising production in integrated multitrophic aquaculture systems](https://www.sciencedirect.com/science/article/pii/S0304380012003493)


<p align="right">(<a href="#readme-top">back to top</a>)</p>

# Custom License for FYNE

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software.

## Requirements

### Commercial Use
If you wish to use this software for commercial or profit-generating activities, you must first consult with the author(s) of the software to negotiate terms.

### Disclaimer
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 

