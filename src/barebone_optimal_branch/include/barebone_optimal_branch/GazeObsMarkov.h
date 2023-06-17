#ifndef GAZE_OBS_MARKOV
#define GAZE_OBS_MARKOV

#include <std_msgs/String.h>

using namespace std;

class GazeMarkov
{
    public:
        inline static const double flat_prior = 1.0 / 3; 
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
            IRRELEVANT = 0,//IRRELEVANT

            //The following discretization is 
            //subject to task definition and the 
            //definitions are took from the paper
            ON_AVATAR = 1,//ON-AVATAR
            ON_REF = 2//ON-REFERENCE OBJECT
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
        int windowSize;
        //Transition matrix of this particular chain
        //Starting at ref
        double ref_persist;
        double ref_to_irr;
        double ref_to_avatar;
        //Starting at avatar
        double avatar_persist;
        double avatar_to_irr;        
        double avatar_to_ref;
        //Starting at irrelevant
        double irr_persist;  
        double irr_to_ref; 
        double irr_to_avatar; 

    public:
        GazeMarkov(const Type& type_in)
        {
            type = type_in;
            resetChain();
        }
        
        //[PSEUDO CODE]
        /*
        * Parameters of this chain 
        * is to be supplied by the user.
        */
        void setChainParams(PARAMS)
        {
            //Parameters to be specified could be seen in class definition
        }

        void updateChain(const Obs& obs_this)
        {//Update chain using the latest observation supplied by the user
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

                //(2) Append new observation to the list
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
                //No gaze observation
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
            
            if(obsSeq.size() == 1)
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
            if(obs_last == Obs::IRRELEVANT)
            {
                if(obs_this == Obs::IRRELEVANT)
                {//IRRELEVANT -> IRRELEVANT
                    return irr_persist;
                }
                else if(obs_this == Obs::ON_AVATAR)
                {//IRRELEVANT -> AVATAR
                    return irr_to_avatar;
                }
                else
                {//IRRELEVANT -> Ref
                    return irr_to_ref;
                }
            }
            else if(obs_last == Obs::ON_REF)
            {
                if(obs_this == Obs::ON_REF)
                {//Ref -> Ref
                    return ref_persist;
                }
                else if(obs_this == Obs::IRRELEVANT)
                {//Ref -> Irr
                    return ref_to_irr;
                }
                else
                {//Ref -> Ava
                    return ref_to_avatar;
                }
            }
            else if(obs_last == Obs::ON_AVATAR)
            {
                if(obs_this == Obs::ON_AVATAR)
                {//Ava -> Ava
                    return avatar_persist;
                }
                else if(obs_this == Obs::IRRELEVANT)
                {//Ava -> Irr
                    return avatar_to_irr;
                }
                else
                {//Ava -> Ref
                    return avatar_to_ref;
                }
            }
        }
};




#endif