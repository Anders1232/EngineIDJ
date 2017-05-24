#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include "stdlib.h"

#ifdef _WIN32
	#define END_LINE "\r\n"
#else
	#define END_LINE "\n"
#endif

using std::endl;

#define DEBUG 0
#define CONVERSAO_GRAUS_RADIANOS 57.324840764

#define Error(msg)std::cerr<<"[ERROR] "<<WHERE<<"\t\t"<<msg<<END_LINE;exit(1);
#define ASSERT(exp)if(!(exp)){std::cerr<<"[ERROR] "<<WHERE<<"\t\tAssertion Failed."<<END_LINE;exit(1);}
#define ASSERT2(exp,msg)if(!(exp)){std::cerr<<"[ERROR] "<<WHERE<<"\t\tAssertion Failed." <<msg<< "\n";exit(1);}
#define SDL_ASSERT(exp)if(!(exp)){std::cerr<<"[ERROR] "<<WHERE<<"\t\tAssertion Failed:" << SDL_GetError()<<END_LINE;exit(1);}

#define WHERE __FILE__<<" | "<<__func__<<":"<<__LINE__

#define CHECK_SDL_ERROR std::cerr<<"[ERROR] "<<WHERE<<"\t\t"<<SDL_GetError()<<END_LINE

#define REPORT_DEBUG(msg) if(DEBUG){std::cout<<"[DEBUG]"<<WHERE<<msg<<END_LINE;}
#define REPORT_DEBUG2(cond, msg) if(cond){std::cout<<"[DEBUG]"<<WHERE<<msg<<END_LINE;}

#define REPORT_I_WAS_HERE if(DEBUG){std::cout <<"[DEBUG] I was here!\t"<<WHERE<<END_LINE;}

#define TEMP_REPORT_I_WAS_HERE if(1){std::cout<<"[DEBUG] I was here!\t"<<WHERE<<END_LINE;}

//void Error(char const * errMsg);

#endif // ERROR_H
