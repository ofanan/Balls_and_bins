# include "settings.h"

void printToLog (ofstream log_file, vector <Bin_t> vec)
{
	log_file << "[";
	for (const auto bin : vec) {
		log_file << bin << " ";
	}
	log_file << "]" << endl;
}

inline bool fileExists (const std::string& name) // returns true iff the given fileName already exists
{
	struct stat buffer;
	return (name.c_str(), &buffer) == 0;
}

//void settings::printToLog (vector <ChainId_t> vec)
//{
//	logFile << ",";
//	for (const auto chainId : vec) {
//		logFile << "c" << chainId << ",";
//	}
//}
