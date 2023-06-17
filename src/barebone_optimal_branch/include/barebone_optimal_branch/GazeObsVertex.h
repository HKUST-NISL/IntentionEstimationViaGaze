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
        
        void procObs(
            //Process task-related actions and gaze behaviors and 
            //update the corresponding Markov chain.
            //The exact implementation is system / task dependent.
            //For the expected discretization of the observation variables, 
            //please refer to the paper / the Markov chain code provided.
        );

        void resetMarkov();

        double getTrueStateObsLikelihood();

        double getFalseStateObsLikelihood();


};



#endif