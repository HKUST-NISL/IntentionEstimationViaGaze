#include <ActionObsVertex.h>

using namespace std;

ActionObsVertex::ActionObsVertex(const string & name)
{
    task_name = name;
    actionMarkovChainCorrect(ActionObsMarkov::Type::CORRECT),
    actionMarkovChainWrong(ActionObsMarkov::Type::WRONG)
}

double ActionObsVertex::getTrueStateObsLikelihood()const
{//Likelihood of LATEST OBSERVATION w.r.t. the true chain
    return actionMarkovChainCorrect.getTransitionLikelihoodThis();
}

double ActionObsVertex::getFalseStateObsLikelihood()const
{//Likelihood of LATEST OBSERVATION w.r.t. the false chain
    return actionMarkovChainWrong.getTransitionLikelihoodThis();
}

void ActionObsVertex::resetMarkov()
{
    actionMarkovChainCorrect.resetChain();
    actionMarkovChainWrong.resetChain();
}


