# Parameters and accessory functions
import os, math, itertools, numpy as np, scipy.stats as st 

# Colors for print-out messages
STDOUT_FAIL     = '\033[91m'
STDOUT_ENDC     = '\033[0m'
   
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

