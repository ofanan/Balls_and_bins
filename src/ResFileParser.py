import os, numpy as np
import pylab, matplotlib, seaborn, matplotlib.pyplot as plt

import settings
from settings import warning, error, checkIfInputFileExists

ballsIdx    = 0
binsIdx     = 1
smplsIdx    = 2
repetIdx    = 3

def printTheoreticMaxLd ():
    """
    Print the theoretical maximal load when picking the bin either u.a.r., or using the power of two choices.  
    """
    numBalls = 10**6
    lgLg = np.log(np.log (numBalls))
    print (f'u.a.r={np.log (numBalls)/lgLg}, P of 2={lgLg}')


class ResFileParser (object):  
    
    def __init__ (self):
        self.listOfDicts  = [] # list of dictionaries, that will hold all the data parsed from .res files.
        self.dict         = None
        
    def parseLine (
            self, 
            line : str = None   # line to parse
        ) -> bool:  # Return True iff the line was successfully parsed.
        """
        Parse a single line of a .res file.
        """
        unsplittedLine = line 
        splittedLine = line.split ("|")
         
        if len (splittedLine)<3:
            error (f'parseLine encountered format error in file {self.relativePathToInputFile}. splittedLine={splittedLine}')
        if len (splittedLine[1].split("="))<2:
            error ('format error. splittedLine={}' .format (splittedLine))
        maxLd   = float(splittedLine[1].split("=")[1])
        stdOverAvg    = float(splittedLine[2].split("=")[1])

        settingStr = splittedLine[0]
        splittedSettingStr = settingStr.split (".")
        if len(splittedSettingStr)<repetIdx+1:
            print (f'Parsing error. settingStr={settingStr}')
            return False
        self.dict = {
            'numBalls'      : int (splittedSettingStr [ballsIdx].split("balls")[1]),   
            'numBins'       : int (splittedSettingStr  [binsIdx].split("bins")[1]),   
            'd'             : int (splittedSettingStr  [smplsIdx].split("d")[1]),   
            'Repet'         : int (splittedSettingStr  [repetIdx].split("R")[1]),   
            'maxLd'         : maxLd,
            'stdOverAvg'    : stdOverAvg
            }
        return True

     
    def parseFiles (self, 
            inputFileNames : list = [], # list of files to parse
        ):
        """
        Parse each file in the list inputFileNames, and save the parsed data in self.listOfDicts
        """
        for inputFileName in inputFileNames:
            self.relativePathToInputFile = f'../res/{inputFileName}'
            checkIfInputFileExists (relativePathToInputFile=self.relativePathToInputFile)
            self.inputFile         = open (self.relativePathToInputFile,  "r")
            lines               = (line.rstrip() for line in self.inputFile) # "lines" contains all lines in input file
            lines               = (line for line in lines if line)       # Discard blank lines
            
            for line in lines:
            
                # Discard lines with comments / verbose data
                if (line.split ("//")[0] == ""):
                    continue

                if not (self.parseLine(line)):
                    error (f'problematic file is {input_file_name}')
               
                if (not(self.dict in self.listOfDicts)):
                    self.listOfDicts.append(self.dict)
                        
            self.inputFile.close
        print (self.listOfDicts)

if __name__ == '__main__':
    try:
        rfp = ResFileParser()
        rfp.parseFiles (['bb.res'])
    except KeyboardInterrupt:
        print('Keyboard interrupt.')

