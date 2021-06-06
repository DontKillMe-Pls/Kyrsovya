#include <iostream>
#include <string>
#include <fstream>
#include <getopt.h>
#include "getAudit.h"
using namespace std;

int getAudit::get_results(int argc, char**argv){
	if(argc == 1){
		throw Not_allowed_input_parametrs();
	}
	string Month;
//! give date 
	string FD,FT,SD,ST;
	static struct option long_options[] =
	{
		{"FD",		required_argument,	0,	'a'},	/* FD - first date */
		{"FT",		required_argument,	0,	'b'},	/* FT - first time */
		{"SD",		required_argument,	0,	'c'},	/* FD - second date */
		{"ST",		required_argument,	0,	'd'},	/* FD - second time */
		{"help",					0,	0,	'h'},	/* get help */
		{0, 0, 0, 0} 
	};
	int option_index = 0;
	int c = 0;
	while((c = getopt_long (argc, argv, "a:b:c:d:",long_options, &option_index)) != -1) {
		switch(c){
				case 'h':
					cout << string("Using format :") + argv[0]+ string(" --FD first date --FT first time --SD second date --ST second time") << endl;
					cout << "date format: number(1-31).month(1-12)" << endl;
					cout << "time format: hours(0-23):minutes(0-59)" << endl;
					return 1;
				case 'a':
					FD = argv[2];
					break;
				case 'b':
					FT = argv[4];
					break;
				case 'c':
					SD = argv[6];
					break;
				case 'd':
					ST = argv[8];
					break;
				case '?':
					throw incorrect_args();
					break;
		}
	}
	//! need it for cast from int to log's strings month
	string number_month_in_nameMonth[12] = {
		"Jan",
		"Feb",
		"Mar",
		"Apr",
		"May",
		"Jun",
		"Jul",
		"Aug",
		"Sep",
		"Oct",
		"Nov",
		"Dec"
	};
	//! making first date for logs
	string first_date,second_date,first_month,second_month, first_time_hours, first_time_minuts, second_time_hours, second_time_minuts;
	int i =0;
	while(FD[i]!='.'){
		first_date += FD[i];
		i++;
	}
	while(FD[i]!='\0'){
		i++;
		first_month += FD[i];
	}

	//!making second date for logs
	int j =0;
	while(SD[j]!='.'){
		second_date += SD[j];
		j++;
	}
	while(SD[j]!='\0'){
		j++;
		second_month += SD[j];
	}
	
	//!making time for logs
	int k = 0;
	while(FT[k]!=':'){
		first_time_hours += FT[k];
		k++;
	}
	while(FT[k]!='\0'){
		k++;
		first_time_minuts += FT[k];
	}
	k = 0;
	while(ST[k]!=':'){
		second_time_hours += ST[k];
		k++;
	}
	while(ST[k]!='\0'){
		k++;
		second_time_minuts += ST[k];
	}
	
	//! open log-file, output needed strings
	
	ifstream log_file;
	log_file.open("tip_log.log");
	string buff, month_in_buff, for_month_in_int = "123", for_date_in_int = "00", for_time_minuts_in_int = "00", for_time_hours_in_int = "00"; // 4-5
	int input_month_in_int, input_date_in_int;
	while(log_file){
		getline(log_file,buff);
	//! read first 3 sumb out of every strings of log, it's month and cast him in int for output
		for(int i = 0;i<3;i++){
			for_month_in_int[i] = buff[i];
		}
		
		if (log_file.fail()) 
			break;
		for(int i = 0;i<2;i++){
			for_date_in_int[i] = buff[i+4]; //!4 offset mk date in logs starts from 4 characters, counting from 0 
			if(buff[4]==(int)((char)(' '))){
				for_date_in_int[0] = '0';
			}
		}
		for(int i = 0; i < 2; i++){
			for_time_hours_in_int[i] = buff[i+7];  //!7 offset mk clock in logs starts from 7 character, counting from 0 
		}
		for(int i = 0; i < 2; i++){
			for_time_minuts_in_int[i] = buff[i+10];  //! 10 mk offset minutes in logs start from 10 characters, counting from 0 
		}
		input_date_in_int = stoi(for_date_in_int);
	
//! checking the incorrectly entered month, day and time (more than 12 months, more than 23:59, the number of months is more than 31) 
		if((stoi(first_month) > 12) or (stoi(second_month) > 12)){
			throw incorrect_data();
		}
		if(((stoi(first_date) > 31 ) or ((stoi(second_date)) > 31))){
			throw incorrect_data();
		}
		if(((stoi(first_time_hours) > 23 ) or ((stoi(second_time_hours)) > 23))){
			throw incorect_time();
		}
		if(((stoi(first_time_minuts) > 59 ) or ((stoi(second_time_minuts)) > 59))){
			throw incorect_time();
		}
		for(int i = 1; i<12;i++){
			if(for_month_in_int==number_month_in_nameMonth[i-1])
				input_month_in_int = i;
		}
			//! if the check is on the same day of one month
	if(FD == SD){
		if( stoi(first_month) == stoi(second_month) /* Introduced Same month */ 			and \
			(input_month_in_int) == stoi(first_month) /*month in the log is equal to entered */	and \
			stoi(first_date) == stoi(second_date) /* The dates entered are equal */ 			and \
			(input_date_in_int) == stoi(first_date) /*the date from the logs is equal to the entered one */	and \
			stoi(second_time_hours) >= stoi(for_time_hours_in_int) and stoi(first_time_hours) <= stoi(for_time_hours_in_int) and \
			stoi(second_time_minuts) >= stoi(for_time_minuts_in_int) and stoi(first_time_minuts) <= stoi(for_time_minuts_in_int) and \
			(10000>buff.find("sd"))){
				cout << buff << endl;
			}
		}else{
			if((input_month_in_int>stoi(first_month) and input_month_in_int<stoi(second_month)) and ((10000>buff.find("sd")) or (10000>buff.find("sd")) ))
			{	
				cout << buff << endl;
			}else if((((input_month_in_int==stoi(first_month)) and (input_date_in_int>=stoi(first_date)) and (10000>buff.find("sd")))) and \
				(((stoi(first_time_hours)<=stoi(for_time_hours_in_int)) and (stoi(first_time_minuts)<=stoi(for_time_minuts_in_int))))){
					cout << buff << endl;
			}else if((((input_month_in_int==stoi(second_month)) and (input_date_in_int<=stoi(second_date))and (10000>buff.find("sd")))) and \
				((stoi(second_time_hours)>=stoi(for_time_hours_in_int)) and (stoi(second_time_minuts)>=stoi(for_time_minuts_in_int)))){
					cout << buff << endl;
			}
		}
	}
//! close file
	log_file.close();
	return 0;
}
