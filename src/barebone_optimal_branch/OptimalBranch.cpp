#include <OptimalBranch.h>

OptimalBranch::OptimalBranch(
    const std::vecotr<string> & task_names,
    const std::vector<TaskInstance> & optimal_branch_task_seq,
    const string& dont_want_to_be_cued_name)
{
    optimalBranchTaskVertices = vector<OptimalBranchVertex*>();

    //(1) Assume depth-first serialization of the optimal plan
    for(int i = 0 ; i < optimal_branch_task_seq.size(); i++)
    {
        optimalBranchTaskVertices.push_back(
            new OptimalBranchVertex(task_names[i])
            );
    }

    //(2) Setup parent-child connections
    for(int i = 0 ; i < optimalBranchTaskVertices.size(); i ++)
    {
        //Parent of this vertex
        OptimalBranchVertex* parent_vertex = nullptr;
        int parent_idx = i - 1;
        if( parent_idx >= 0)
        {
            parent_vertex = optimalBranchTaskVertices[parent_idx];
        }

        //Child of this vertex
        OptimalBranchVertex* child_vertex = nullptr;
        int child_idx = i + 1;
        if( child_idx < optimalBranchTaskVertices.size() )
        {
            child_vertex = optimalBranchTaskVertices[child_idx];
        }

        //Connect parent and childs
        optimalBranchTaskVertices[i]->setupConnection(parent_vertex, child_vertex);
    }

    //(3) Special treatment of the "don't want to be cued" state
    dontWantToBeCuedVtx_ = new OptimalBranchVertex(dont_want_to_be_cued_name);


    //(4) The parameters of the optimal branch, as well as all its 
    //vertices need to be set, which is the user's responsibility to 
    //supply and implement.
    setParams();

}

void OptimalBranch::resetBeliefEstimation()
{
    int start_idx = 0;

    for(int i = start_idx ; i < optimalBranchTaskVertices.size(); i++)
    {
        optimalBranchTaskVertices[i]->resetBeliefEstimation();
    }
    dontWantToBeCuedVtx_->resetBeliefEstimation();
}
        
void OptimalBranch::updateBeliefEstimation()
{
    for(int i = 0 ; i < optimalBranchTaskVertices.size(); i++)
    {
        optimalBranchTaskVertices[i]->computePosterior();
    }
    dontWantToBeCuedVtx_->computePosterior();
}

const int OptimalBranch::chooseActionByPolicy()
{
    //(1) Check if any action's true state posterior is below threshold
    for(int i = 0; i < optimalBranchTaskVertices.size(); i++)
    {
        if(optimalBranchTaskVertices[i]->getTrueStatePosterior() <= CUE_THRESH)
        {
            return i;
        }
    }
    
    
    //(2) If no action's true state posterior is below threshold, then check if the user wants to be cued
    if(dontWantToBeCuedVtx_->getTrueStatePosterior() <= CUE_THRESH)
    {
        double min_posterior = 1;
        int min_idx = -1;

        for(int i = 0; i < optimalBranchTaskVertices.size(); i++)
        {
            if(optimalBranchTaskVertices[i]->getTrueStatePosterior() <= min_posterior)
            {
                min_posterior = optimalBranchTaskVertices[i]->getTrueStatePosterior();
                min_idx = i;
            }
        }

        return min_idx;
    }
    else
        {//Do nothing
            return -1;
        }

}
