//============================================================================
// Author      : Itamar Cohen
// Description : Implementation of funcs used throughout this project.
//============================================================================
# include "settings.h"

/*************************************************************************************************************************************************
Returns true iff the given file name already exists.
*************************************************************************************************************************************************/
bool fileExists (const std::string& name) // returns true iff the given fileName already exists
{
	struct stat buffer;
	return ((name.c_str(), &buffer) == 0);
}

/*************************************************************************************************************************************************
* Print the given error msg, and call Omnet's "error" func' to exit with error.
**************************************************************************************************************************************************/
void printErrStrAndExit (const string &errorMsgStr)
{
	char errorMsg[errorMsgStr.length() + 1];
	strcpy(errorMsg, errorMsgStr.c_str());
	cerr << errorMsg;
	exit (0);
}

///*************************************************************************************************************************************************
//Print a vector to a log file
//*************************************************************************************************************************************************/
//void printVecToLog (ofstream logFile, vector <Bin_t> vec)
//{
//	logFile << "[";
//	for (const auto bin : vec) {
//		logFile << bin << " ";
//	}
//	logFile << "]" << endl;
//}

