# CODE_READABILITY_USING_AI

"demo" is the executable file with baseline code at same location and candidates code in "candidate" folder

****
Command to rank candidates on the basis of logic readability:

            ./demo results {setter.cpp} {2}

results -> to rank candidates \\
setter.cpp -> the baseline code (it must be at same location)\\
2 -> the number of candidates \\
(each solution of candidates must be of form "candidates"+i+".cpp" in "candidate" folder)\\

            ./demo (runs with default values)

*****
Command to check nodes expanded:

            ./demo nodes {setter.cpp} {candidate1.cpp}

nodes -> to get number of nodes expanded \\
setter.cpp -> the baseline code (it must be at same location) \\
candidate1.cpp -> the candidate code for which number of nodes expanded is to check\\
(candidate1.cpp must be in "candidate" folder)\\
