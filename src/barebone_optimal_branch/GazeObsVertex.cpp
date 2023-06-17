#include <GazeObsVertex.h>

using namespace std;

GazeObsVertex::GazeObsVertex(const string& name)
{
    task_name = name;
    gazeMarkovChainCorrect(obsType,GazeMarkov::CORRECT),
    gazeMarkovChainWrong(obsType,GazeMarkov::WRONG)
}

void GazeObsVertex::resetMarkov()
{
    gazeMarkovChainCorrect.resetChain();
    gazeMarkovChainWrong.resetChain();
}

double GazeObsVertex::getTrueStateObsLikelihood()
{//Likelihood of LATEST OBSERVATION w.r.t. the true chain
    return gazeMarkovChainCorrect.getTransitionLikelihoodThis();
}

double GazeObsVertex::getFalseStateObsLikelihood()
{//Likelihood of LATEST OBSERVATION w.r.t. the false chain
    return gazeMarkovChainWrong.getTransitionLikelihoodThis();
}




