#include <OptimalBranchVertex.h>

OptimalBranchVertex::OptimalBranchVertex(const string& ti_name):
vertexName(ti_name)
{
    actionObsVtx_ = new ActionObsVertex(vertexName); 
    gazeObsVtx_ = new GazeObsVertex(vertexName); 
}

void OptimalBranchVertex::setupConnection(
            OptimalBranchVertex * parent_vertex_ = nullptr, 
            OptimalBranchVertex * child_vertex_ = nullptr)
{
    parentVertex_ = parent_vertex_;
    childVertex_ = child_vertex_;
}


void OptimalBranchVertex::computePosterior()
{
    double true_state_gaze_likelihood = gazeObsVtx_->getTrueStateObsLikelihood();
    double true_state_config_likelihood = actionObsVtx_->getTrueStateObsLikelihood();

    double false_state_gaze_likelihood = gazeObsVtx_->getFalseStateObsLikelihood();
    double false_state_config_likelihood = actionObsVtx_->getFalseStateObsLikelihood();

    //Accumulate over time in an incremental manner
    double true_state_joint_prob = true_state_gaze_likelihood * true_state_config_likelihood * trueStatePosterior;
    double false_state_joint_prob = false_state_gaze_likelihood * false_state_config_likelihood * falseStatePosterior;
    double normalize_factor = true_state_joint_prob + false_state_joint_prob;

    //If numerical issue is encountered, or exact timeout behavior is desired,
    //we could try capping these posterior values as a quick hack:
    // trueStatePosterior = min(true_state_joint_prob / normalize_factor,TRUE_STATE_PRIOR);
    trueStatePosterior = true_state_joint_prob / normalize_factor;
    falseStatePosterior = 1 - trueStatePosterior;
}

void OptimalBranchVertex::resetBeliefEstimation()
{
    trueStatePosterior = TRUE_STATE_PRIOR;
    falseStatePosterior = FALSE_STATE_PRIOR;

    actionObsVtx_->resetMarkov();
    gazeObsVtx_->resetMarkov();
}

double OptimalBranchVertex::getTrueStatePosterior()
{
    return trueStatePosterior;
}









