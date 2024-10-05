//============================================================================
// Author      : Itamar Cohen
// Description : The main balls-and-bins simulation source file.
//============================================================================
#include "settings.h"
#include "BallsNBins.h"

BallsNBins::~BallsNBins ()
{
	bins_.clear ();
	if (verboseIncludes(Verbose_t::LOG) || verboseIncludes(Verbose_t::LOG_END_SIM)) {
		log_file_.close ();
	}
	if (verboseIncludes(Verbose_t::RES)) {
		res_file_.close ();
	}
}


/*************************************************************************************************************************************************
Open the output files:.log, .res, based on the chosen verbose option.
*************************************************************************************************************************************************/
void BallsNBins::openOutputFiles ()
{
	if (verboseIncludes(Verbose_t::LOG) || verboseIncludes(Verbose_t::LOG_END_SIM)) {
		string logFileName = "log_files/bb_" + genSettingStr() + ".log";
		log_file_.open(logFileName);
	}
	if (verboseIncludes(Verbose_t::RES)) {
		string resFileName = "res/bb.res";
		if (filesystem::exists(resFileName)) {
			  res_file_.open(resFileName, std::ios_base::app);
		}
		else {
			res_file_.open(resFileName);
			res_file_ << "// format: ballsX.binsY.dZ.RW : avg=A | std_over_avg=S" << endl << "// Where : " << endl;
			res_file_ << "// X, Y, Z are the numbers of balls, bins, samples, resp." << endl;
			res_file_ << "// W==1 if we allow repetitions, else W==0." << endl;
			res_file_ << "// A is the maximal load, averaged over the experiments done. "<< endl;
			res_file_ << "// S is the ratio: standard variation of the experiments, over the maximal load." << endl;
		}
	}
}

/*************************************************************************************************************************************************
Print all the bins to a log file
*************************************************************************************************************************************************/
void BallsNBins::printAllBinsToLog ()
{
	log_file_ << "ball " << ball_ << ", chosen_bin_=" << chosen_bin_ << ": bins=";
	printVecToFile (log_file_, bins_);
}

/*************************************************************************************************************************************************
Return a string that details the simulation's parameters.
*************************************************************************************************************************************************/
string BallsNBins::genSettingStr ()
{
	string settingStr =
			string("balls") + to_string(num_balls_) +
			string(".bins") + to_string(num_bins_) +
			string(".d") + to_string(num_smpls_) +
			string(".R");
			;
	if (with_replacements_ && num_smpls_>1) {
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
		unsigned num_exps,
		unsigned num_smpls, //number of samples. When 0 (sample all bins). Otherwise, sample numSmpl bins and use the minimal.
		bool 	 with_replacements // when True, we occasionally may sample the same bin a few time at a single round
		)
{
	num_smpls_	= num_smpls; //number of samples. When 0 (sample all bins). Otherwise, sample numSmpl bins and use the minimal.
	with_replacements_ = with_replacements;
	if (num_smpls_>= (num_bins_-1)) {
		printErrStrAndExit ("BallsNBins.sim() was called with num_smpls=" + to_string(num_smpls_) + "num_smpls should be up to num_smpls-1.");
	}
	vector<Bin_t> maxLd(num_exps, 0);
	std::random_device rd;
	std::mt19937 rng(rd());
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, num_bins_- 1);
	openOutputFiles ();
	cout << "Starting sim. NumExps=" << num_exps << ", num_balls=" << num_balls_ << ", num_bins=" << num_bins_ << ", num_smpls=" << num_smpls_ << endl;
	for (unsigned exp(0); exp<num_exps; exp++) {
		srand(seed_ + exp); // set the seed of random num generation
		fill(bins_.begin(), bins_.end(), 0); // empty all the bins
		for (ball_ = 0; ball_<num_balls_; ball_++) {

			switch (num_smpls_) {

				case 0:
					chosen_bin_ = distance (bins_.begin(), min_element(bins_.begin(), bins_.end()));
					break;
				case 1:
					chosen_bin_ = dis(gen);
					break;

				default:
				Bin_t minLdFound = MAX_BIN_VAL; // init the min load found so far to infinity
				unordered_set<unsigned>smpld_bins_ = sampleWoReplacements (num_bins_, num_smpls_, gen);

				for (auto itr = smpld_bins_.begin(); itr != smpld_bins_.end(); ++itr) {
					if (bins_[*itr] < minLdFound)
					{
						chosen_bin_ = *itr;
						minLdFound = bins_[*itr];
					}
				}
			}
			bins_[chosen_bin_]++;
			if (verboseIncludes(Verbose_t::DEBUG)) {
				if (bins_[chosen_bin_]>=MAX_BIN_VAL) {
					printErrStrAndExit ("In BallsNBins.sim(). bin" + to_string(chosen_bin_) + " reached its maximal value. Please use a larger bit width for Bin_t in BallsNBins.h");
				}
			}
			if (verboseIncludes(Verbose_t::LOG) && exp==0) { //consider logging only in the first experiment
				printAllBinsToLog ();
			}
		} // end of this experiment
		maxLd[exp] = *std::max_element(std::begin(bins_), std::end(bins_));
	}
	if (verboseIncludes(Verbose_t::LOG_END_SIM)) { //consider logging only the last experiment
		printAllBinsToLog ();
		log_file_ << "At the end of simulation:" << endl;
		log_file_ << "maxLd=";
		printVecToFile (log_file_, maxLd);
	}
	if (verboseIncludes(Verbose_t::RES)) {
		double avg 	 = mean (maxLd);
		double stdev = standardDeviation (maxLd, avg);
		res_file_ << genSettingStr() << " | avg=" << avg << " | std_over_avg=" << stdev/avg << endl;
	}
	cout << "Successfully finished sim." << endl;

}

/*************************************************************************************************************************************************
Returns true iff the given verbose is found in the list of verbose to perform (this.verbose).
*************************************************************************************************************************************************/
inline bool BallsNBins::verboseIncludes (Verbose_t const verbose)
{
	return (std::find((verbose_).begin(), (verbose_).end(), verbose) != (verbose_).end());
}


/*************************************************************************************************************************************************
Run a short sim. Used for debugging.
*************************************************************************************************************************************************/
void runShortSim ()
{
	vector <Bin_t> vec= {1, 2, 3, 4};
	vector <Verbose_t> verbose 	= {Verbose_t::RES, Verbose_t::LOG, Verbose_t::DEBUG};
	BallsNBins bb = BallsNBins (
		4 , // num_balls
		2,  // num_bins
		verbose // verbose
	);

	bb.sim (
		2, // num_exps
		1, // num_smpls
		false //with_replacements_
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
	vector <Verbose_t> verbose {Verbose_t::RES};
	const unsigned num_exps		= 100;
	const unsigned num_balls 	= 10000;
	const unsigned num_bins[3] 	= {16, 32, num_balls};
	for (unsigned idx(0); idx<sizeof(num_bins)/sizeof(unsigned); idx++) {
		for (unsigned num_smpls(0); num_smpls<3; num_smpls++) {
			BallsNBins bb = BallsNBins (
				num_balls,
				num_bins[idx],
				verbose
			);

			bb.sim (
				num_exps,
				num_smpls,
				false //with_replacements_
			);
		}

		// Additional single run with 2 smpls, allowing repetitions.
		BallsNBins bb = BallsNBins (
			num_balls,
			num_bins[idx],
			verbose
		);
		bb.sim (
			num_exps,
			2, // num_smpls
			true //with_replacements_
		);
	}
}
