#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include "stdlib.h"

using std::endl;

#define DEBUG 0
#define CONVERSAO_GRAUS_RADIANOS 57.324840764

#define Error(msg)std::cerr<<"[ERROR] "<<__FILE__<<" | "<<__func__<<":"<<__LINE__<<"\t\t"<<msg<< "\n";exit(1);
#define ASSERT(exp)if(!(exp)){std::cerr<<"[ERROR] "<<__FILE__<<" | "<<__func__<<":"<<__LINE__<<"\t\tAssertion Failed."<< "\n";exit(1);}
#define SDL_ASSERT(exp)if(!(exp)){std::cerr<<"[ERROR] "<<__FILE__<<" | "<<__func__<<":"<<__LINE__<<"\t\tAssertion Failed:" << SDL_GetError()<< "\n";exit(1);}

#define WHERE __FILE__<<" | "<<__func__<<":"<<__LINE__

#define CHECK_SDL_ERROR std::cerr<<"[ERROR] "<<__FILE__<<" | "<<__func__<<":"<<__LINE__<<"\t\t"<<SDL_GetError()<< "\n"

#define REPORT_I_WAS_HERE if(DEBUG){std::cout <<"[DEBUG] I was here!\t"<<__FILE__<<" | "<<__func__<<":"<<__LINE__<<"\n";}

#define TEMP_REPORT_I_WAS_HERE if(1){std::cout <<"[DEBUG] I was here!\t"<<__FILE__<<" | "<<__func__<<":"<<__LINE__<<"\n";}

//void Error(char const * errMsg);

#endif // ERROR_H
