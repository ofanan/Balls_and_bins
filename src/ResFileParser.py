import os, numpy as np
import pylab, math, matplotlib, seaborn, matplotlib.pyplot as plt

import settings
from settings import warning, error, checkIfInputFileExists

# Indices of the fields and the settingStr.
ballsIdx    = 0
binsIdx     = 1
smplsIdx    = 2
repetIdx    = 3

# Codes of lovely colors
SKY_BLUE    = '#56B4E9'

# convenient sizes and parameters for plots
BAR_WIDTH               = 0.25
BAR_WIDTH_BETWEEN_GRPS  = 0.25
FONT_SIZE               = 16
FONT_SIZE_SMALL         = 5
LEGEND_FONT_SIZE        = FONT_SIZE
LEGEND_FONT_SIZE_SMALL  = 5 
USE_FRAME               = False # When True, plot a "frame" (box) around the plot 


def printTheoreticMaxLd (
        numBalls = 10**6    
    ):
    """
    Print the theoretical maximal load when picking the bin either u.a.r., or using the power of two choices.  
    0"""
    lgLg = np.log(np.log (numBalls))
    print (f'u.a.r={np.log (numBalls)/lgLg}, P of 2={lgLg/math.log(2)}')

class ResFileParser (object):  
    
    setPltParams = lambda self, size='large' : matplotlib.rcParams.update({'font.size': FONT_SIZE, 
                                                                             'legend.fontsize': LEGEND_FONT_SIZE,
                                                                             'xtick.labelsize':FONT_SIZE,
                                                                             'ytick.labelsize':FONT_SIZE,
                                                                             'axes.labelsize' : FONT_SIZE,
                                                                             'axes.titlesize' :FONT_SIZE,}) if (size=='large') else matplotlib.rcParams.update({
                                                                             'font.size'     : FONT_SIZE_SMALL, 
                                                                             'legend.fontsize': LEGEND_FONT_SIZE_SMALL,
                                                                             'xtick.labelsize':FONT_SIZE_SMALL,
                                                                             'ytick.labelsize':FONT_SIZE_SMALL,
                                                                             'axes.labelsize': FONT_SIZE_SMALL,
                                                                             'axes.titlesize':FONT_SIZE_SMALL,
                                                                             })
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
            'repet'         : int (splittedSettingStr  [repetIdx].split("R")[1]),   
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

    def genBars (
            self,
            numBalls    = 10000,
            numBins     = 16,
            numOfBars   = 4,
            normalize   = True, # when True, normalize the results w.r.t Opt.
        ):
        
        self.setPltParams ()
        
        normalizationFactor = math.ceil(numBalls/numBins) if normalize else 1 
        points      = [point for point in self.listOfDicts if point['numBalls']==numBalls and point['numBins']==numBins] # consider only relevant points from the data 
        fig         = plt.figure () 
        maxLd       = np.zeros (numOfBars) # Will hold the values of the bars to plot. 
        
        # Extract the values of the points of sampling 1, 2, or all the bins, without repet, and assign them in the corresponding places in the list maxLd 
        for d in range(numOfBars-1):
            pointsWithThisD = [point for point in points if point['d']==d and point['repet']==0]
            if len(pointsWithThisD)==0:
                warning (f'genBars did not find points with numBalls={numBalls}, numBalls={numBins}, d={d}')
            if len(pointsWithThisD)==2:
                error (f'genBars found 2 points with numBalls={numBalls}, numBalls={numBins}, d={d}, repet=0.')
            point = pointsWithThisD[0]
            if d==0:
                maxLd[-1] = point['maxLd']/normalizationFactor
            else:
                maxLd[d-1] = point['maxLd']/normalizationFactor

        # Now, add the last point, that represents sampling 2 bins, with repetitions allowed.
        pointsWithThisD = [point for point in points if point['d']==2 and point['repet']==1]
        if len(pointsWithThisD)==0:
            warning (f'genBars did not find points with numBalls={numBalls}, numBalls={numBins}, d={d}')
        if len(pointsWithThisD)==2:
            warning (f'genBars found 2 points with numBalls={numBalls}, numBalls={numBins}, d={d}, repet=0. taking the first one')
        point = pointsWithThisD[0]        
        maxLd[2] = point['maxLd']/normalizationFactor
        plt.bar([i for i in range(len(maxLd))], maxLd, color = ['black', 'blue', SKY_BLUE, 'green'])
        plt.xlabel ('# of Bins Sampled')
        plt.ylabel ('{}Load' .format ('Normalized ' if normalize else ''))
        plt.xticks([bar for bar in range(len(maxLd))], ['1', '2', '2 with repet.', 'All bins'])        
        if numBins>1000:
            plt.title ('{:.0f}K balls, {:.0f}K bins' .format(numBalls/1000, numBins/1000))
        else:
            plt.title ('{:.0f}K balls, {} bins' .format(numBalls/1000, numBins))
        if normalize and numBins in [16, 32]:
            plt.ylim ([0, 1.2])
        for spine in plt.gca().spines.values(): # remove the frame around the bars
            spine.set_visible(False)        
        plt.savefig ('../res/bb_{}bins_{}.pdf' .format (numBins, 'rel' if normalize else 'abs'), bbox_inches='tight', dpi=100)

if __name__ == '__main__':
    try:
        vec = [0,1]
        print (f'mean={np.mean(vec)}, stdev={np.std(vec)}')
        exit ()
        rfp = ResFileParser()
        rfp.parseFiles (['bb.res'])
        for numBins in [16, 32]:
            rfp.genBars (numBins=numBins, normalize=False)
        for numBins in [16, 32, 10000]:
            rfp.genBars (numBins=numBins, normalize=True)
    except KeyboardInterrupt:
        print('Keyboard interrupt.')

