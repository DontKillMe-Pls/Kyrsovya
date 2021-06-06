#include <UnitTest++/UnitTest++.h>
#include "getAudit.h"

struct Four_args{

};
SUITE(test_of_using_args){
	TEST(Normal_work){
		getAudit test1;
		int imulate_argc = 9;
		char *imulate_argv[imulate_argc] ={"./release2","--FD","1.06","--FT","9:00","--SD","2.06","--ST","15:00"} ;
		CHECK_EQUAL(0,test1.get_results(imulate_argc, imulate_argv));
	}
	TEST(Not_allowed_args){
		getAudit test2;
		int imulate_argc = 1;
		char *imulate_argv[imulate_argc] ={"./release"} ;
		CHECK_THROW(test2.get_results(imulate_argc,imulate_argv), Not_allowed_input_parametrs);
	}

	TEST(Incorrect_data){
		getAudit test3;
		int imulate_argc = 9;
		char *imulate_argv[imulate_argc] ={"./release","--FD","32.06","--FT","14:00","--SD","2.06","--ST","15:00"} ;
		CHECK_THROW(test3.get_results(imulate_argc, imulate_argv), incorrect_data);
	}
	TEST(Incorrect_time){
		getAudit test4;
		int imulate_argc = 9;
		char *imulate_argv[imulate_argc] ={"./release2","--FD","1.06","--FT","43:00","--SD","2.06","--ST","15:00"} ;
		CHECK_THROW(test4.get_results(imulate_argc, imulate_argv), incorect_time); 
	}
	TEST(Incorrect_args){
		getAudit test5;
		int imulate_argc = 1;
		char *imulate_argv[imulate_argc] ={"--FM"} ;
		CHECK_THROW(test5.get_results(imulate_argc, imulate_argv), incorrect_args); 
	}
}

int main(int argc, char **argv)
{
	return UnitTest::RunAllTests();
}
