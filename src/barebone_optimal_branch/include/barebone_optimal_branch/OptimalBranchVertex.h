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
        OptimalBranchVertex(const string& ti_name)
        void setupConnection(
            OptimalBranchVertex * parent_vertex_ = nullptr, 
            OptimalBranchVertex * child_vertex_ = nullptr);
        
        //[PSEUDO CODE]
        /*
        * Process observations using the two observation vertices'
        * respective procObs() method
        * The exact implementation is system / task dependent.
        */
        void procObs(NEW_ACTION_GAZE_OBS)
        {
            actionObsVtx_->procObs(NEW_ACTION_OBS);
            gazeObsVtx_->procObs(NEW_GAZE_OBS);
        }

        //[PSEUDO CODE]
        /*
        * Parameters supplied by the user
        * This includes:
        * prior for true / false intention
        * Markov chain parameters for gaze obs vtx 
        * Markov chain prameters for action obs vtx
        */
        void setParams(PARAMS)
        {
            //(1) Params for this vertex itself is indicated in the class definiton
            FALSE_STATE_PRIOR = 
            TRUE_STATE_PRIOR = 

            //(2) Params for each observation vertiex
            actionObsVtx_->setParams(ACTION_PARAMS);
            gazeObsVtx_->setParams(GAZE_PARAMS);
        };

        void computePosterior();

        void resetIntentionEstimation();

        double getTrueStatePosterior();
};



#endif