#include "CppUTest/CommandLineTestRunner.h"

int main(int ac, char** av)
{
	
//	SystemCoreClock=180000000; 
	
  const char * av_override[] = { "exe", "-v" }; //turn on verbose mode

  return CommandLineTestRunner::RunAllTests(2, av_override);
//	return CommandLineTestRunner::RunAllTests(ac, av);
	
	
//	int ac_override = 2;
//const char * av_override[] = { "exe", "-v" }; //turn on verbose mode
//return RUN_ALL_TESTS(ac_override, av_override);
//	
}

