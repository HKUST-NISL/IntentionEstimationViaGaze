#ifndef GAZE_OBS_VERTEX
#define GAZE_OBS_VERTEX

#include <GazeObsMarkov.h>

using namespace std;

class GazeObsVertex
{
    private:
        string task_name;
        GazeMarkov gazeMarkovChainCorrect;//For true state 
        GazeMarkov gazeMarkovChainWrong;//For false state 

    public:
        GazeObsVertex(const string& task_name);

        //[PSEUDO CODE]
        /*
        * Parameters supplied by the user
        * for both chains
        */
        void setParams(PARAMS)
        {
            gazeMarkovChainCorrect.setChainParams(CORRECT_PARAMS);
            gazeMarkovChainWrong.setChainParams(WRONG_PARAMS);
        };

        //[PSEUDO CODE]
        /*
        * Process task-related actions and gaze behaviors and 
        * update the corresponding Markov chain via the updateChain method.
        * The exact implementation is system / task dependent
        * For the expected discretization of the observation variables, 
        * please refer to the paper & 
        * the Markov chain code provided (updateChain() method in particular)
        */
        void procObs(NEW_GAZE_OBS)
        {
            gazeMarkovChainCorrect.updateChain(NEW_DISCRETIZED_OBS);
            gazeMarkovChainWrong.updateChain(NEW_DISCRETIZED_OBS);
        };
        
        void resetMarkov();

        double getTrueStateObsLikelihood();

        double getFalseStateObsLikelihood();


};



#endif