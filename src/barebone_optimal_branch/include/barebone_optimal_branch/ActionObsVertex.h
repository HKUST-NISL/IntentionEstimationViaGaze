#ifndef ACTION_OBS_VERTEX
#define ACTION_OBS_VERTEX

#include <ActionObsMarkov.h>

using namespace std;

class ActionObsVertex
{        
    private:
        string task_name;
        ActionObsMarkov actionMarkovChainCorrect;//For true state
        ActionObsMarkov actionMarkovChainWrong;//For false state


    public:    
        ActionObsVertex(const string& task_name);
        

        void setChainParams(
            //Parameters supplied by the user
            //for both chains
        );

        void procObs(
            //Process task-related actions and gaze behaviors and 
            //update the corresponding Markov chain via the updateChain method.
            //The exact implementation is system / task dependent
            //For the expected discretization of the observation variables, 
            //For the expected discretization of the observation variables, 
            //please refer to the paper & 
            //the Markov chain code provided (updateChain() method in particular)
        );

        void resetMarkov();

        double getTrueStateObsLikelihood()const;

        double getFalseStateObsLikelihood()const;
};



#endif