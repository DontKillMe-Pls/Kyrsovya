#include <iostream>
#include <string>
#include "getAudit.h"

using namespace std;
/**
 * @file 
 * @authors Shipovsky.I.P
 * @date 03.06.2021
 * @version 3.7.2
 * @brief All relise in main.cpp
 * @param argc
 * @param argv
 */



int main(int argc, char **argv)
{	
	getAudit res;
	try{
		res.get_results(argc,argv);
	}catch(Not_allowed_input_parametrs){
		cout << "Not allowed input parametrs\n please, use --help" << endl;
	}catch(log_file_not_found){
		cout << "log file not found" << endl;
	}catch(incorrect_data){
		cout << "incorrect input data" << endl;
	}catch(incorect_time){
		cout << "incorrect input time" << endl;
	}catch(incorrect_args){
		cout << "incorrect_args" << endl;
	}catch(std::invalid_argument){
		cout << "unsupported log format" << endl;
	}
}
