# Parameters and accessory functions
import os, math, itertools, numpy as np, scipy.stats as st 

# Colors for print-out messages
STDOUT_FAIL     = '\033[91m'
STDOUT_ENDC     = '\033[0m'
# Other bcolors:
#     HEADER = '\033[95m'
#     OKBLUE = '\033[94m'
#     OKCYAN = '\033[96m'
#     OKGREEN = '\033[92m'
#     WARNING = '\033[93m'
#     FAIL = '\033[91m'
#     ENDC = '\033[0m'
#     BOLD = '\033[1m'
#     UNDERLINE = '\033[4m'
   
# Calculate the confidence interval of an array of values ar, given its avg. Based on 
# https://stackoverflow.com/questions/15033511/compute-a-confidence-interval-from-sample-data
confInterval = lambda ar, avg, confLvl=0.95 : st.t.interval (confLvl, len(ar)-1, loc=avg, scale=st.sem(ar)) if np.std(ar)>0 else [avg, avg]
   
def warning (str2print):
    """
    Print an error msg and exit.
    """
    print (f'{STDOUT_FAIL}Warning: {str2print}{STDOUT_ENDC}')

def error (str2print):
    """
    Print an error msg and exit.
    """
    print (f'{STDOUT_FAIL}Error: {str2print}{STDOUT_ENDC}')
    exit  ()

def checkIfInputFileExists (
        relativePathToInputFile : str,
        exitError               = True
        ):
    """
    Check whether an input file, given by its relative path, exists.
    If the file exists, return True. 
    Else, print proper error msg, and:
        if exitError=True, exit with error; else, return False 
    """
    if os.path.isfile (relativePathToInputFile):
        return True
    if exitError:
        error (f'the input file {relativePathToInputFile} does not exist')
    else:
        warning (f'the input file {relativePathToInputFile} does not exist')
        return False

