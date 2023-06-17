(1) The markov chain definition is provided. Note that the user has to specify the parameters of each chain. Also currently the gaze markov chain has its states hardcoded to suit the need of the example task in the paper. Extending the state definition requires updaing the state transition code accoridngly.

(1.5*)Actually any standard Markov Chain library will do instead of using the provided ones.

(2) The optimal branch definition is provided. The user could use these definitions together with his / her own symbolic task definitions and planner to create an optimal branch. Note that the user will have to implement the discretization of raw observations into action / gaze observations that the Markov chain accepts, with respect to each task on the branch.

(3) The cuing controller definition is provided. The user could supply it with the posterior probabilities computed using the observations and make a decision of on what level should the cue be made.

(4) One possible tool for setting up the task definitions and perform planning in HTN to use with the optimal branch is HATP from LAAS, https://www.openrobots.org/wiki/HATP

(5) Pseudo code guidelines are provided to indicate how parameters / discretized observations could be supplied to the model.
