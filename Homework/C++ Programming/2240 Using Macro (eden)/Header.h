// MegaShow
#ifndef HEADER_H_
#define HEADER_H_

#include <iostream>
#include <string>

#define MAX 100
#define MIN -100
#define max(a,b) (a>b?a:b)
#define square(a) ((a)*(a))
#define e(a,b) (a##e##b)
#define mstr(a) (str(a))
#define str(a) (#a)
#define WARN_IF(a) if(a)std::cout<<"Warning: "<<str(a)<<std::endl

#endif
