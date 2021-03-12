# CODE_READABILITY_USING_AI

"demo" is the executable file with baseline code at same location and candidates code in "candidate" folder

1. Command to rank candidates on the basis of logic readability:

            ./demo results {setter.cpp} {2}

results -> to rank candidates <br />
setter.cpp -> the baseline code (it must be at same location)<br />
2 -> the number of candidates <br />
(each solution of candidates must be of form "candidates"+i+".cpp" in "candidate" folder)<br />

            ./demo (runs with default values)


2. Command to check nodes expanded:

            ./demo nodes {setter.cpp} {candidate1.cpp}

nodes -> to get number of nodes expanded <br />
setter.cpp -> the baseline code (it must be at same location) <br />
candidate1.cpp -> the candidate code for which number of nodes expanded is to check<br />
(candidate1.cpp must be in "candidate" folder)<br />
