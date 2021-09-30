# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cstring>
# include <fstream>
# include <cmath>
# include <ctime>
# include <string>
#include <vector>

using namespace std;

# include "cnf_io.hpp"
# include "cnf_io_prb.hpp" 
# include "latin_center.cpp"


//****************************************************************************80

int main ( int argc, char* argv[])

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



  if(argc==1)
	cout<<"You should give an argument\n";
  else
  {//cout << argv[1]<<endl;
  string cnf_file_name=argv[1];
  /*
  cout<<"the file name is "<< cnf_file_name<< endl;
  //timestamp ( );
  cout << "\n \n";
  cout << "CNF_IO_PRB\n";
  cout << "  C++ version\n";
  cout << "  Test the CNF_IO library.\n";
  */
  test00 ( cnf_file_name);
 // test01 ( );
 // test02 ( );
  //test03 ( );
  //test04 ( );
  //test05 ( );
  //test06 ( );
  //test07 ( );
  
//
  }
  //timestamp ( );

  return 0;
}

//****************************************************************************80

void test00 ( string cnf_file_name )

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
# define C_NUM 2
# define L_NUM 5


//




  //cout<<"the file name is "<< cnf_file_name<< endl;
  int c_num;
  //string cnf_file_name = "cnf_io_v3_c2.cnf";
  //string cnf_file_name = "cnf_io_v16_c18.cnf";
  //string cnf_file_name = "cnf_io_v3_c3.cnf";
  //string cnf_file_name = "easy_unsatisfiable.cnf";
  //string cnf_file_name = "easy_unsatisfiable2.cnf";
  //string cnf_file_name = "uf20-015.cnf";
  //string cnf_file_name = "uf20-0124.cnf";//à noter que les numero 125, 710 n'ont pas abouti
  ofstream myfile1;
myfile1.open ("problem_name.txt");
myfile1 << cnf_file_name;
myfile1.close();

  bool error;
  int *l_c_num;
  int l_num;
  int *l_val;
  int v_num;
  int *weights;
  long long int resultat;
  double resultat_kappa;

//  cout << "\n";
//  cout << "TEST03\n";
//  cout << "  CNF_DATA_READ reads the data of a CNF file.\n";

//  cout << "\n";
//  cout << "  Read the header of \"" << cnf_file_name << "\".\n";
  
  error = cnf_header_read ( cnf_file_name, &v_num, &c_num, &l_num );
  
  if ( error )
  {
    cout << "\n";
    cout << "  The header information could not be read.\n";
    return;
  }
/*
  cout << "\n";
  cout << "  The number of variables       V_NUM  = " << v_num << "\n";
  cout << "  The number of clauses         C_NUM  = " << c_num << "\n";
  cout << "  The number of signed literals L_NUM  = " << l_num-c_num << "\n";
*/
ofstream myfile0;
myfile0.open ("simple.dat");
myfile0 << "# v_num \n";
  myfile0 << v_num << "\n";
myfile0 << "# c_num \n";
  myfile0 << c_num  << "\n";
myfile0 << "# l_num \n";
  myfile0 << l_num-c_num  << "\n";


  l_c_num = new int[c_num];
  l_val = new int[l_num-c_num];
  weights = new int[c_num];
  
/*  for(int i=0; i<l_num-c_num; i++)
{

cout << "  l_val[ " << i << "]= " <<l_val[i] << " \n";


}  
*/
  
//  cout << "avant \n";
cnf_data_read_with_weights ( cnf_file_name, v_num, c_num, l_num-c_num, l_c_num, l_val, weights );
//   cout << "apres \n";
   
/*   
for(int i=0; i<c_num; i++)
{

cout << "  Clause " << i << " has a weight of " << weights[i] << " \n";


}   
*/
myfile0 << "# l_c_num \n";
for(int i=0;i<c_num;i++)
{

 
  myfile0 << l_c_num[i] << " ";
 
//cout << l_c_num[i];
//cout << " ";
}

myfile0 << "\n# l_val \n";
for(int i=0;i<l_num-c_num;i++)
{

 
  myfile0 << l_val[i] << " ";
 
//cout << l_val[i];
//cout << " ";
}

myfile0 << "\n# weights \n";
for(int i=0;i<c_num;i++)
{

 
  myfile0 << weights[i] << " ";
 
//cout << l_val[i];
//cout << " ";
}

myfile0.close();

//Create starting points using a latin hypercube and putting them in a file.
  //int dim_num=v_num;
  int num_points=1000;
  int seed=10;
  //double lh[num_points*v_num];
  double *lh;
  lh=new double[num_points*v_num];
//cout << "test \n ";
  latin_center (v_num, num_points, &seed,lh);

ofstream myfile_lh;
myfile_lh.open ("lh.txt");

  for(int i=0;i<num_points;i++)
{
	for(int j=0;j<v_num;j++)
	{
         
	myfile_lh <<  lh[i+num_points*j]<< " ";

	}	
myfile_lh << endl;
}

myfile_lh.close();
 




  cout << "\n";
  //cout << "  Here is the data as read from the file:\n";
  
 // cnf_print ( v_num, c_num, l_num, l_c_num, l_val );


//cout << "\n";
long long int best_result=0;
double* point;
point=new double[v_num];
/*
for(int i=0;i<v_num;i++)
{

point[i]=0.5;

}
*/


for(int k=0; k<num_points;k++)
{
for(int i=0;i<v_num;i++)
{

point[i]=lh[k+num_points*i];

}

//Pour vérifier, affichons output
/*cout <<  "En ce moment, intput vaut ";
for(int i=0; i<v_num;i++)
{

cout <<  point[i] << " ";

}
cout << "\n";
*/
//double res=kappa(v_num, c_num, l_num, l_c_num, l_val, weights, point);
//cout <<  "La valeur initiale de kappa est "<< res<<"\n" ;
create_corner_point ( v_num, c_num, l_num, l_c_num, l_val, weights, point);

//Pour vérifier, affichons output
/*cout <<  "\n A la fin, output vaut ";
for(int i=0; i<v_num;i++)
{

cout <<  point[i] << " ";

}
cout << "\n";
*/
resultat=wcnf_evaluate_algo (v_num, c_num, l_num, l_c_num, l_val, weights, point);
//resultat_kappa=kappa(v_num, c_num, l_num, l_c_num, l_val, weights, point);
cout << "  La valeur de ce (weighted) (partial) MAXSAT problem vaut " << resultat << " \n";
if(resultat­­>best_result){best_result=resultat;}
//cout << "  La valeur de ce (weighted) (partial) MAXSAT problem vaut via kappa " << resultat_kappa << " \n";

}

cout << "  La meilleur resultat de ce  MAXSAT problem vaut " << best_result << " \n";
//resultat=wcnf_evaluate_algo (v_num, c_num, l_num, l_c_num, l_val, weights, point);
//cout << "  La valeur de ce (weighted) (partial) MAXSAT problem vaut " << resultat << " \n";
//bool negatif=negative_input(weights, c_num);
//cout << "  Le fait qu'il n'y ait un poids négatif est " << negatif << " \n";
// Write some stuff in a file.

  //ofstream myfile;
  //myfile.open ("example_pour_postdoc.txt");
  //myfile << "Writing this to a file.\n";
  //myfile.close();

//  Terminate.
//
  //cout << "\n";
  //cout << "CNF_IO_PRB\n";
  //cout << "  Normal end of execution.\n";
  //cout << "\n";


# undef C_NUM
# undef L_NUM

  delete [] l_c_num;
  delete [] l_val;
  delete [] weights;
  delete [] point;
  delete [] lh;
  return ;
}

/*
//****************************************************************************80

void test01 ( void )

//****************************************************************************80
//
//  Purpose:
//
//    TEST01 calls CNF_WRITE to write a small CNF example to a CNF file.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    06 June 2008
//
//  Author:
//
//    John Burkardt
//
{
# define C_NUM 2
# define L_NUM 5



  int c_num = C_NUM;
  int l_num = L_NUM;

  string cnf_file_name = "cnf_io_v3_c2.cnf";
  bool error;
  int l_c_num[C_NUM] = { 2, 3 };
  int l_val[L_NUM] = { 1, -3, 2, 3, -1 };
  int v_num = 3;

  cout << "\n";
  cout << "TEST01\n";
  cout << "  CNF_WRITE can write CNF data to a CNF file.\n";
  cout << "\n";
  cout << "  Here is the data:\n";

  cnf_print ( v_num, c_num, l_num, l_c_num, l_val );

  cout << "\n";
  cout << "  Now we call CNF_WRITE to store this information\n";
  cout << "  in the file \"" << cnf_file_name << "\".\n";

  error = cnf_write ( v_num, c_num, l_num, l_c_num, l_val, cnf_file_name );

  return;
# undef C_NUM
# undef L_NUM
}
//****************************************************************************80

void test02 ( void )

//****************************************************************************80
//
//  Purpose:
//
//    TEST02 calls CNF_HEADER_READ to read the header of a small CNF example file.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    07 June 2008
//
//  Author:
//
//    John Burkardt
//
{
  int c_num;
  string cnf_file_name = "cnf_io_v3_c2.cnf";
  bool error;
  int l_num;
  int v_num;

  cout << "\n";
  cout << "TEST02\n";
  cout << "  CNF_HEADER_READ reads the header of a CNF file.\n";

  cout << "\n";
  cout << "  Read the header of \"" << cnf_file_name << "\".\n";

  error = cnf_header_read ( cnf_file_name, &v_num, &c_num, &l_num );

  if ( error )
  {
    cout << "\n";
    cout << "  The header information could not be read.\n";
    return;
  }

  cout << "\n";
  cout << "  The number of variables       V_NUM  = " << v_num << "\n";
  cout << "  The number of clauses         C_NUM  = " << c_num << "\n";
  cout << "  The number of signed literals L_NUM  = " << l_num << "\n";

  return;
}
//****************************************************************************80

void test03 ( void )

//****************************************************************************80
//
//  Purpose:
//
//    TEST03 calls CNF_DATA_READ to read the data of a small CNF example file.
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
  int c_num;
  string cnf_file_name = "cnf_io_v3_c2.cnf";
  bool error;
  int *l_c_num;
  int l_num;
  int *l_val;
  int v_num;

  cout << "\n";
  cout << "TEST03\n";
  cout << "  CNF_DATA_READ reads the data of a CNF file.\n";

  cout << "\n";
  cout << "  Read the header of \"" << cnf_file_name << "\".\n";

  error = cnf_header_read ( cnf_file_name, &v_num, &c_num, &l_num );

  if ( error )
  {
    cout << "\n";
    cout << "  The header information could not be read.\n";
    return;
  }

  cout << "\n";
  cout << "  The number of variables       V_NUM  = " << v_num << "\n";
  cout << "  The number of clauses         C_NUM  = " << c_num << "\n";
  cout << "  The number of signed literals L_NUM  = " << l_num << "\n";

  l_c_num = new int[c_num];
  l_val = new int[l_num];

  cnf_data_read ( cnf_file_name, v_num, c_num, l_num, l_c_num, l_val );

  cout << "\n";
  cout << "  Here is the data as read from the file:\n";

  cnf_print ( v_num, c_num, l_num, l_c_num, l_val );

  delete [] l_c_num;
  delete [] l_val;

  return;
}
//****************************************************************************80

void test04 ( void )

//*****************************************************************************80
//
//  Purpose:
//
//    TEST04 calls CNF_WRITE to write a CNF example to a CNF file.
//
//  Discussion:
//
//    This formula is used as an example in the Quinn reference.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    06 June 2008
//
//  Author:
//
//    John Burkardt
//
{
# define C_NUM 18
# define L_NUM 36

  int c_num = C_NUM;
  int l_num = L_NUM;

  string cnf_file_name ="cnf_io_v16_c18.cnf";
  bool error;
  int l_c_num[C_NUM] = {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
    2, 2, 2, 2, 2, 2, 2, 2 };
  int l_val[L_NUM] = {
    1,    2, 
   -2,   -4, 
    3,    4, 
   -4,   -5, 
    5,   -6, 
    6,   -7, 
    6,    7, 
    7,  -16, 
    8,   -9, 
   -8,  -14, 
    9,   10, 
    9,  -10, 
  -10,  -11, 
   10,   12, 
   11,   12, 
   13,   14, 
   14,  -15, 
   15,   16 };
  int v_num = 16;

  cout << "\n";
  cout << "TEST04\n";
  cout << "  CNF_WRITE can write CNF data to a CNF file.\n";
  cout << "\n";
  cout << "  Here is the data to be written to the file:\n";

  cnf_print ( v_num, c_num, l_num, l_c_num, l_val );

  cout << "\n";
  cout << "  Now we call CNF_WRITE to store this information\n";
  cout << "  in the file \"" << cnf_file_name << "\".\n";

  error = cnf_write ( v_num, c_num, l_num, l_c_num, l_val, cnf_file_name );

  return;
# undef C_NUM
# undef L_NUM
}
//****************************************************************************80

void test05 ( void )

//****************************************************************************80
//
//  Purpose:
//
//    TEST05 calls CNF_HEADER_READ to read the header of a small CNF example file.
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
  int c_num;
  string cnf_file_name = "cnf_io_v16_c18.cnf";
  bool error;
  int l_num;
  int v_num;

  cout << "\n";
  cout << "TEST05\n";
  cout << "  CNF_HEADER_READ reads the header of a CNF file.\n";

  cout << "\n";
  cout << "  Read the header of \"" << cnf_file_name << "\".\n";

  error = cnf_header_read ( cnf_file_name, &v_num, &c_num, &l_num );

  if ( error )
  {
    cout << "\n";
    cout << "  The header information could not be read.\n";
  }
  else
  {
    cout << "\n";
    cout << "  The number of variables       V_NUM  = " << v_num << "\n";
    cout << "  The number of clauses         C_NUM  = " << c_num << "\n";
    cout << "  The number of signed literals L_NUM  = " << l_num << "\n";
  }

  return;
}
//****************************************************************************80

void test06 ( void )

//****************************************************************************80
//
//  Purpose:
//
//    TEST06 calls CNF_DATA_READ to read the data of a small CNF example file.
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
  int c_num;
  string cnf_file_name = "cnf_io_v16_c18.cnf";
  bool error;
  int *l_c_num;
  int l_num;
  int *l_val;
  int v_num;

  cout << "\n";
  cout << "TEST06\n";
  cout << "  CNF_DATA_READ reads the data of a CNF file.\n";

  cout << "\n";
  cout << "  Read the header of \"" << cnf_file_name << "\".\n";

  error = cnf_header_read ( cnf_file_name, &v_num, &c_num, &l_num );

  if ( error )
  {
    cout << "\n";
    cout << "  The header information could not be read.\n";
    return;
  }

  cout << "\n";
  cout << "  The number of variables       V_NUM  = " << v_num << "\n";
  cout << "  The number of clauses         C_NUM  = " << c_num << "\n";
  cout << "  The number of signed literals L_NUM  = " << l_num << "\n";

  l_c_num = new int[c_num];
  l_val = new int[l_num];

  cnf_data_read ( cnf_file_name, v_num, c_num, l_num, l_c_num, l_val );

  cout << "\n";
  cout << "  Here is the data as read from the file:\n";

  cnf_print ( v_num, c_num, l_num, l_c_num, l_val );

  delete [] l_c_num;
  delete [] l_val;

  return;
}
//****************************************************************************80

void test07 ( void )

//****************************************************************************80
//
//  Purpose:
//
//    TEST07 calls CNF_EVALUATE to evaluate a formula.
//
//  Discussion:
//
//    This formula is used as an example in the Quinn reference.
//    Here, we seek the logical inputs that make the formula true.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license. 
//
//  Modified:
//
//    06 June 2008
//
//  Author:
//
//    John Burkardt
//
{
# define C_NUM 18
# define L_NUM 36
# define V_NUM 16

  int c_num = C_NUM;
  int l_num = L_NUM;
  int v_num = V_NUM;

  bool f_val;
  int i;
  int ihi;
  int j;
  int l_c_num[C_NUM] = {
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
    2, 2, 2, 2, 2, 2, 2, 2 };
  int l_val[L_NUM] = {
    1,    2, 
   -2,   -4, 
    3,    4, 
   -4,   -5, 
    5,   -6, 
    6,   -7, 
    6,    7, 
    7,  -16, 
    8,   -9, 
   -8,  -14, 
    9,   10, 
    9,  -10, 
  -10,  -11, 
   10,   12, 
   11,   12, 
   13,   14, 
   14,  -15, 
   15,   16 };
  int solution_num;
  bool v_val[V_NUM];

  cout << "\n";
  cout << "TEST07\n";
  cout << "  Seek inputs to a circuit that produce a 1 (TRUE) output.\n";
  cout << "\n";
  cout << "  Here is the CNF data defining the formula:\n";

  cnf_print ( v_num, c_num, l_num, l_c_num, l_val );
//
//  Initialize the logical vector.
//
  for ( j = 0; j < v_num; j++ )
  {
    v_val[j] = false;
  }
//
//  Compute the number of binary vectors to check.
//
  ihi = i4_power ( 2, v_num );

  cout << "\n";
  cout << "  Number of input vectors to check is " << ihi << "\n";
  cout << "\n";
  cout << "   #       Index    ---------Input Values----------\n";
  cout << "\n";
//
//  Check every possible input vector.
//
  solution_num = 0;

  for ( i = 0; i < ihi; i++ )
  {
    f_val = cnf_evaluate ( v_num, c_num, l_num, l_c_num, l_val, v_val );

    if ( f_val )
    {
      solution_num = solution_num + 1;
      cout << "  " << setw(2) << solution_num
           << "  " << setw(10) << i;
      for ( j = 0; j < v_num; j++ )
      {
        cout << v_val[j];
      }
      cout << "\n";
    }
    lvec_next ( v_num, v_val );
  }
//
//  Report.
//
  cout << "\n";
  cout << "  Number of solutions found was " << solution_num << "\n";

  return;
# undef C_NUM
# undef L_NUM
# undef V_NUM
}


*/
