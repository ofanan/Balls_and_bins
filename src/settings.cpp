//============================================================================
// Author      : Itamar Cohen
// Description : Implementation of funcs used throughout this project.
//============================================================================
# include "settings.h"

/*************************************************************************************************************************************************
* Print the given error msg, and call Omnet's "error" func' to exit with error.
**************************************************************************************************************************************************/
void printErrStrAndExit (const string &errorMsgStr)
{
	char errorMsg[errorMsgStr.length() + 1];
	strcpy(errorMsg, errorMsgStr.c_str());
	perror (errorMsg);
	exit (1);
}

/*************************************************************************************************************************************************
Returns an unordered set of numSmpls distinct integers, picked u.a.r without replacements
out of the range 0..N-1.
*************************************************************************************************************************************************/
std::unordered_set<unsigned> sampleWoReplacements
	(unsigned N,
	 unsigned numSmpls,
	 std::mt19937& gen)
{
    std::unordered_set<unsigned> elems;
    for (unsigned r = N - numSmpls; r < N; ++r) {
        unsigned v = std::uniform_int_distribution<>(0, r)(gen);
        // there are two cases.
        // v is not in candidates ==> add it
        // v is in candidates ==> well, r is definitely not, because
        // this is the first iteration in the loop that we could've
        // picked something that big.
        if (!elems.insert(v).second) {
            elems.insert(r);
        }
    }
    return elems;
}
