# include "settings.h"

void printToLog (ofstream log_file, vector <Bin_t> vec)
{
	log_file << "[";
	for (const auto bin : vec) {
		log_file << bin << " ";
	}
	log_file << "]" << endl;
}

//void MyConfig::printToLog (vector <ChainId_t> vec)
//{
//	logFile << ",";
//	for (const auto chainId : vec) {
//		logFile << "c" << chainId << ",";
//	}
//}
