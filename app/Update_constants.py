# -*- coding: utf-8 -*-
import os


os.chdir( os.getcwd() )

# Open the old header file
olddata = []
with open("CONSTANTS.h", "rb") as t:
    for line in t:
        line= line.rstrip()
        line = str(line).replace('b\'', '').split(";")
        olddata.append(line)

# Read in new variable info.
NewVarNames = []
NewVarValues = []
NewVarTypes = []
with open("CONSTANTS.txt", "rb") as newtext:
    for line in newtext:
        line= line.rstrip()
        line = str(line).replace('b\'', '').split(",")
        NewVarTypes.append(line[0])
        NewVarNames.append(line[1])
        NewVarValues.append(line[2])
 

# Finally, save the new header file
with open('CONSTANTS.h', 'w') as f:
    for line in olddata:
        line = str(line).replace('[','').replace(']','').replace('\'','').replace('\"','')
        for THING in range(len(NewVarNames)):
            if str(line).__contains__(NewVarNames[THING]):
                line = str(NewVarTypes[THING]) + ' ' +  str(NewVarNames[THING]) + '= '+  str(NewVarValues[THING]) + ','
                break
        f.write("%s\n" % str(line).replace(",",";"))

