# Reformulation-of-weighted-MAXSAT-or-MINSAT-into-an-polynomial-optimization-problem-

This project is about a reformulation of the problems weighted (partial) MAXSAT and weighted (partial) MINSAT into a polynomial optimization problem. The work has been submitted to JSAT and the decision is still pending. 

The transformation of kappa using  partial derivatives as explained in the article can be used by using the execution of ''kappa'' using a .wcnf file as an argument from the folder WCNFToSolver. 

Another possibility is to use an external solver. Using the rest of the code, one can use the solver ADMB. The file simple.tpl should be used to transform into the ADMB experiments.

''run'' is a bash script doing the transformation from a .wcnf file into the solver, uses the solver, and interprets the final results. The .wcnf file should be put in the variable ''FILENAME'' in  ''run'' bash script.

The rest contains some codes about cnf files by John Burkardt which has been adapted by Stéphane Jacquet for wcnf files and for the purpose of this work.

