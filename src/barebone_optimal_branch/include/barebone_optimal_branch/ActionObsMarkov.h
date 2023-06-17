#ifndef ACTION_OBS_MARKOV
#define ACTION_OBS_MARKOV

using namespace std;

class ActionObsMarkov
{
    public:
        inline static const double flat_prior = 1.0 / 2; 
        //Type of chain
        enum Type
        {
            CORRECT = 0,//Right intention - executing the task
            WRONG = 1//Wrong intention - not executing the task
        };
        //Discretization of observations
        enum Obs
        {
            NA = -1,//Not observed
            T_MANIP = 0,//Correct action
            F_MANIP = 1//Incorrect action
        };

    private:
        Type type;
        list<Obs> obsSeq;
        Obs frontPopped;
        Obs backLastTime;
        double transitionLikelihoodThis;
        double likelihoodAccumulated;
        /*
        *   Parameters to be specified by the user
        */
        //Usually we are only interested in past observations within a window
        const int windowSize;
        //Transition matrix of this particular chain
        const double TT,TF,FF,FT;
        

    public:
        ActionObsMarkov(const Type& type_in):
        {
            type = type_in;
            resetChain();
        }

        void setChainParams(
            //Parameters of this chain is to be supplied by the user.
        );
        

        void updateChain(const Obs& obs_this)
        {
            //To avoid instability issue we return ONE TRANSTION likelihood (potentially with front corrected)
            //If no observation is valid, the liklihood reduces to a flat prior
            transitionLikelihoodThis = flat_prior;
            
            if(obs_this != Obs::NA)
            {
                //(1) Pop front
                if(obsSeq.size() < windowSize)
                {
                    //Window not full. No pop
                    frontPopped = Obs::NA;
                }
                else
                {
                    //Pop the first element in the window
                    frontPopped = obsSeq.front();
                    obsSeq.pop_front();
                }

                //(2) Append the new observation to the list
                if(obsSeq.size() >= 1)
                {//Record the old back
                    backLastTime = obsSeq.back();
                }
                obsSeq.push_back(obs_this);

                //(3) Compute likelihood of the chain
                transitionLikelihoodThis = computeChainLikelihoodThisObs();
                likelihoodAccumulated = likelihoodAccumulated * transitionLikelihoodThis;
            }
            else
            {
                //No action observation
            }
        }
        
        double getLikelihoodAccumulated()const
        {
            return likelihoodAccumulated;
        };

        double getTransitionLikelihoodThis()const
        {
            return transitionLikelihoodThis;
        }

        void resetChain()
        {
            frontPopped = Obs::NA;
            backLastTime = Obs::NA;
            obsSeq.clear();
            likelihoodAccumulated = 1;
            transitionLikelihoodThis = flat_prior;
        }

    private:
        double computeChainLikelihoodThisObs()
        {//Likelihood with respect to this transition ALONE
            
            double transition_this;
            
            if( obsSeq.size() == 1)
            {//Assume flat prior over the three possible state
                transition_this = flat_prior;
            }
            else
            {
                //Transition likelihood of the new obs
                transition_this = computeTransitionLikelihood(backLastTime,obsSeq.back()); 

                //Account for the popped front, if any
                if(frontPopped != Obs::NA)
                {
                    //Again we dont have to re-compute the prior term assuming a float prior
                    transition_this = transition_this / computeTransitionLikelihood(frontPopped,obsSeq.front()); 
                }
            }
            
            return transition_this;
        }

        double computeTransitionLikelihood(const Obs& obs_last,const Obs& obs_this)const
        {
            if(obs_last == Obs::T_MANIP)
            {
                if(obs_this == Obs::T_MANIP)
                {//T -> T
                    return TT;
                }
                else
                {//T -> F
                    return TF;
                }
            }
            else if(obs_last == Obs::F_MANIP)
            {
                if(obs_this == Obs::F_MANIP)
                {//F -> F
                    return FF;
                }
                else
                {//F -> T
                    return FT;
                }
            }
        }

};




#endif