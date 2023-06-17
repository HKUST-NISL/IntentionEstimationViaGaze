#ifndef OPTIMAL_BRANCH_H
#define OPTIMAL_BRANCH_H

#include <OptimalBranchVertex.h>

using namespace std;

class OptimalBranch
{
    private:
        vector<OptimalBranchVertex*> optimalBranchTaskVertices;//vertices on the optimal branch that correspond to a TASK
        OptimalBranchVertex* dontWantToBeCuedVtx_;//An extra vertex belonging to the branch but NOT a TASK
        double CUE_THRESH;

    public:
        OptimalBranch(
            const std::vecotr<string> & task_names,
            const std::vector<TaskInstance> & optimal_branch_task_seq,
            const string& dont_want_to_be_cued_name);

        void setParams(
            //The user needs to supply parameters for the branch such as "CUE_THRESH"
            //as well as for each vertex on the optimal branch,
            //including the one representing the "want-cue" state.
            //This could be done by recursively calling the setParams() method 
            //of each vertex on the branch and supply it with parameters the user sees fit for each task on the branch.
        );

        void resetBeliefEstimation();

        //This is an example pseudo code that the user's program
        //should implement and call per iteration
        void template_call_per_iteration(NEW_OBS_ACTION_GAZE)
        {
            procObservations(NEW_OBS_ACTION_GAZE);
            updateBeliefEstimation();
            int level_idx_to_cue = chooseActionByPolicy();
        };

    private:
        void procObservations(
            //The use needs to implement how to discretize the latest raw observations of 
            //task-specific action and gaze sequence for each vertex on the optimal branch,
            //following the discretization method described in the paper / see also the markov chain
            //code and in particular the updateChain() method.

            //Depending on the nature of the task definition, this may involve
            //processing at different modules like the optimal branch,
            //the optimal branch vertex or even the observation vertex. We leave
            //all such handles to the user to implement. 
        );

        void updateBeliefEstimation();        

        const int chooseActionByPolicy();
};







#endif