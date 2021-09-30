# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cstring>
# include <fstream>
# include <cmath>
# include <ctime>
# include <string>
# include <vector>
#include <sstream>

using namespace std;

# include "cnf_io.hpp"
# include "cnf_io_prb_evaluate.hpp" 



//****************************************************************************80

int main (int argc, char* argv[])

//****************************************************************************80
//
//  Purpose:
//
//    MAIN is the main program for CNF_IO_PRB.
//
//  Discussion:
//
//    CNF_IO_PRB tests the CNF_IO library.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    09 June 2008
//
//  Author:
//
//    John Burkardt
//
{
	int retval = -1;
	if (argc != 3)
	{
		cerr << "You should give an argument\n";
		return retval;
	}
	else
	{
		std::string cnf_file_name = argv[1];
		std::string solution_file_name = argv[2];
		retval = evaluate(cnf_file_name, solution_file_name);
	}
	return retval;
}

//****************************************************************************80

int evaluate(std::string cnf_file_name, std::string solution_file_name)

//****************************************************************************80
//
//  Purpose:
//
//    TEST00 calls CNF_WRITE to write elements file in a .dat for ADMD later on.
//
//  Licensing:
//
//    This code is writen by Stéphane Jacquet. 
//
//  Modified:
//
//    From 3rd October to 
//
//  Author:
//
//    Stéphane Jacquet
//
{
#define C_NUM 2
#define L_NUM 5
  int retval = 0;// the returned value: the sum of the weights of the satisfied clauses
  int c_num;
  bool satisfied;
  bool error;
  int *l_c_num;
  int l_num;
  int *l_val;
  int v_num;
  bool *v_valeur;
  int count=0;
  double value;
  int *weights;

  error = cnf_header_read ( cnf_file_name, &v_num, &c_num, &l_num );
  v_valeur=new bool[v_num];
  ifstream inputFile;
  inputFile.open(solution_file_name);
  if (inputFile.is_open())
  {    	  
        for(int j=0;j<v_num;j++)
	{       
		
		//cout << "count vaut "<< count<<endl;
		//cout << "variable = "<<count+1 <<endl;
		inputFile>>value;
		//getline (inputFile,line);
  		//stringstream(line) >> value;
		
		cout << "value = "<<value <<endl;
		if (value>0.5)
		{
			v_valeur[count]=true;
		}
		else {
			v_valeur[count]=false;
		}
		//cout << "bool_value = "<<v_valeur[count] <<endl;
		count++;
	}
  }
  inputFile.close(); 
  
  l_c_num = new int[c_num];
  l_val = new int[l_num];
  weights = new int[c_num];
  
  cnf_data_read_with_weights ( cnf_file_name, v_num, c_num, l_num, l_c_num, l_val, weights );

  //We can check now if the output satsfies the SAT problem
  //int clause_non_satisfied=-1;
  retval = wcnf_evaluate ( v_num, c_num, l_num, l_c_num, l_val, v_valeur, weights );
  //satisfied = true;
  cout << "La valeur de ce weighted MAXSAT est  "<<retval <<endl;
 
  if ( error )
  {
    cerr << "\n";
    cerr << "  The header information could not be read.\n";
    retval = -1;
  }
# undef C_NUM
# undef L_NUM

	// Cleanup
	delete [] l_c_num;
	delete [] l_val;
	delete[] v_valeur;
	delete[] weights;
	
	// Return
	return retval;
}
