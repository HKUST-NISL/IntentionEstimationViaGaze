#ifndef OPTIMAL_BRANCH_VERTEX_H
#define OPTIMAL_BRANCH_VERTEX_H

#include <std_msgs/String.h>
#include <GazeObsVertex.h>
#include <ActionObsVertex.h>



using namespace std;

class OptimalBranchVertex
{
    private:
        const string vertexName;
        OptimalBranchVertex* parentVertex_;
        OptimalBranchVertex* childVertex_;
        ActionObsVertex* actionObsVtx_;
        GazeObsVertex* gazeObsVtx_;

        //These two quantities evolve over timein an incremental manner
        double trueStatePosterior;
        double falseStatePosterior;

        /*
        *   Parameters to be specified by the user
        */
        //Prior probability that the person is executing the right task or not
        double FALSE_STATE_PRIOR;
        double TRUE_STATE_PRIOR;

    public:
        OptimalBranchVertex(
            const string& ti_name,  
            OptimalBranchVertex * parent_vertex_ = nullptr, 
            OptimalBranchVertex * child_vertex_ = nullptr);

        void procObs(
            //Process observations using the two observation vertices
            //The exact implementation is system / task dependent.
        );

        void setChainParams(
            //Parameters of this vertex supplied by the user
            //This includes:
            //prior for true / false intention
            //Markov chain parameters for gaze
            //Markov chain prameters for action
        );

        void computePosterior();

        void resetBeliefEstimation();

};



#endif