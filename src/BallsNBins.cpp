//============================================================================
// Author      : Itamar Cohen
// Description : The main balls-and-bins simulation source file.
//============================================================================
#include "settings.h"
#include "BallsNBins.h"

BallsNBins::~BallsNBins ()
{
	_bins.clear ();
	if (verboseIncludes(LOG) || verboseIncludes(LOG_END_SIM)) {
		_logFile.close ();
	}
	if (verboseIncludes(RES)) {
		_resFile.close ();
	}
}


/*************************************************************************************************************************************************
Open the output files:.log, .res, based on the chosen verbose option.
*************************************************************************************************************************************************/
void BallsNBins::openOutputFiles ()
{
	if (verboseIncludes(LOG) || verboseIncludes(LOG_END_SIM)) {
		string logFileName = "log_files/bb_" + genSettingStr() + ".log";
		_logFile.open(logFileName);
	}
	if (verboseIncludes(RES)) {
		string resFileName = "res/bb.res";
		if (filesystem::exists(resFileName)) {
			  _resFile.open(resFileName, std::ios_base::app);
		}
		else {
			_resFile.open(resFileName);
			_resFile << "// format: ballsX.binsY.dZ.RW : avg=A | std_over_avg=S" << endl << "// Where : " << endl;
			_resFile << "// X, Y, Z are the numbers of balls, bins, samples, resp." << endl;
			_resFile << "// W==1 if we allow repetitions, else W==0." << endl;
			_resFile << "// A is the maximal load, averaged over the experiments done. "<< endl;
			_resFile << "// S is the ratio: standard variation of the experiments, over the maximal load." << endl;
		}
	}
}

/*************************************************************************************************************************************************
Print all the bins to a log file
*************************************************************************************************************************************************/
void BallsNBins::printAllBinsToLog ()
{
	_logFile << "ball " << _ball << ", _chosenBin=" << _chosenBin << ": bins=";
	printVecToFile (_logFile, _bins);
}

/*************************************************************************************************************************************************
Return a string that details the simulation's parameters.
*************************************************************************************************************************************************/
string BallsNBins::genSettingStr ()
{
	string settingStr =
			string("balls") + to_string(_numBalls) +
			string(".bins") + to_string(_numBins) +
			string(".d") + to_string(_numSmpls) +
			string(".R");
			;
	if (_allowRepetitions && _numSmpls>1) {
		settingStr += "1";
	}
	else {
		settingStr += "0";
	}

	return settingStr;
}

/*************************************************************************************************************************************************
Simulate balls and bins
*************************************************************************************************************************************************/
void BallsNBins::sim (
		unsigned numExps,
		unsigned numSmpls, //number of samples. When 0 (sample all bins). Otherwise, sample numSmpl bins and use the minimal.
		bool 	 allowRepetitions // when True, we occasionally may sample the same bin a few time at a single round
		)
{
	_numSmpls	= numSmpls; //number of samples. When 0 (sample all bins). Otherwise, sample numSmpl bins and use the minimal.
	_allowRepetitions = allowRepetitions;
	if (_numSmpls>= (_numBins-1)) {
		printErrStrAndExit ("BallsNBins.sim() was called with numSmpls=" + to_string(_numSmpls) + "numSmpls should be up to numSmpls-1.");
	}
	vector<Bin_t> maxLd(numExps, 0);
	std::random_device rd;
	std::mt19937 rng(rd());
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, _numBins- 1);
	openOutputFiles ();
	cout << "Starting sim. NumExps=" << numExps << ", numBalls=" << _numBalls << ", numBins=" << _numBins << ", numSmpls=" << _numSmpls << endl;
	for (unsigned exp(0); exp<numExps; exp++) {
		srand(_seed + exp); // set the seed of random num generation
		fill(_bins.begin(), _bins.end(), 0); // empty all the bins
		for (_ball = 0; _ball<_numBalls; _ball++) {

			switch (_numSmpls) {

				case 0:
					_chosenBin = distance (_bins.begin(), min_element(_bins.begin(), _bins.end()));
					break;
				case 1:
					_chosenBin = dis(gen);
					break;

				default:
				Bin_t minLdFound = MAX_BIN_VAL; // init the min load found so far to infinity
				unordered_set<unsigned>smpldBins = sampleWoReplacements (_numBins, _numSmpls, gen);

				for (auto itr = smpldBins.begin(); itr != smpldBins.end(); ++itr) {
					if (_bins[*itr] < minLdFound)
					{
						_chosenBin = *itr;
						minLdFound = _bins[*itr];
					}
				}
			}
			_bins[_chosenBin]++;
			if (verboseIncludes(DEBUG)) {
				if (_bins[_chosenBin]>=MAX_BIN_VAL) {
					printErrStrAndExit ("In BallsNBins.sim(). bin" + to_string(_chosenBin) + " reached its maximal value. Please use a larger bit width for Bin_t in BallsNBins.h");
				}
			}
			if (verboseIncludes(LOG) && exp==0) { //consider logging only in the first experiment
				printAllBinsToLog ();
			}
		} // end of this experiment
		maxLd[exp] = *std::max_element(std::begin(_bins), std::end(_bins));
	}
	if (verboseIncludes(LOG_END_SIM)) { //consider logging only the last experiment
		printAllBinsToLog ();
		_logFile << "At the end of simulation:" << endl;
		_logFile << "maxLd=";
		printVecToFile (_logFile, maxLd);
	}
	if (verboseIncludes(RES)) {
		double avg 	 = mean (maxLd);
		double stdev = standardDeviation (maxLd, avg);
		_resFile << genSettingStr() << " | avg=" << avg << " | std_over_avg=" << stdev/avg << endl;
	}
	cout << "Successfully finished sim." << endl;

}

/*************************************************************************************************************************************************
Returns true iff the given verbose is found in the list of verbose to perform (this.verbose).
*************************************************************************************************************************************************/
inline bool BallsNBins::verboseIncludes (Verbose_t const verbose)
{
	return (std::find((_verbose).begin(), (_verbose).end(), verbose) != (_verbose).end());
}


/*************************************************************************************************************************************************
Run a short sim. Used for debugging.
*************************************************************************************************************************************************/
void runShortSim ()
{
	vector <Bin_t> vec= {1, 2, 3, 4};
	vector <Verbose_t> verbose 	= {RES, LOG, DEBUG};
	BallsNBins bb = BallsNBins (
		4 , // numBalls
		2,  // numBins
		verbose // verbose
	);

	bb.sim (
		2, // numExps
		1, // numSmpls
		false //_allowRepetitions
	);
}

/*************************************************************************************************************************************************
Generate a BallsNBins simulator and run it in several configurations.
*************************************************************************************************************************************************/
int main() {
	vector<int> v = {0,1};
	double avg = mean (v);
	cout << "mean=" << avg << ", stdev=" << standardDeviation (v, avg);
	return (0);
	vector <Verbose_t> verbose {RES};
	const unsigned numExps		= 100;
	const unsigned numBalls 	= 10000;
	const unsigned numBins[3] 	= {16, 32, numBalls};
	for (unsigned idx(0); idx<sizeof(numBins)/sizeof(unsigned); idx++) {
		for (unsigned numSmpls(0); numSmpls<3; numSmpls++) {
			BallsNBins bb = BallsNBins (
				numBalls,
				numBins[idx],
				verbose
			);

			bb.sim (
				numExps,
				numSmpls,
				false //_allowRepetitions
			);
		}

		// Additional single run with 2 smpls, allowing repetitions.
		BallsNBins bb = BallsNBins (
			numBalls,
			numBins[idx],
			verbose
		);
		bb.sim (
			numExps,
			2, // numSmpls
			true //_allowRepetitions
		);
	}
}
