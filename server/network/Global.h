#pragma once

//#ifndef _WIN32_WINNT
//	#define _WIN32_WINNT 0x0501
//#endif

//#ifndef _CRT_SECURE_NO_WARNINGS
//	#define _CRT_SECURE_NO_WARNINGS 1
//#endif
//
//#ifndef _SCL_SECURE_NO_WARNINGS
//	#define _SCL_SECURE_NO_WARNINGS 1
//#endif

#include <stdio.h>
#include <tchar.h>
#include <stdint.h>

//typedef char int8;
//typedef short int16;
//typedef int int32;
//typedef long long int64;
//typedef unsigned char uint8;
//typedef unsigned short uint16;
//typedef unsigned int uint32;
//typedef unsigned long long uint64;

template <typename T>
inline void SAFE_DELETE(T& p) { if (p != NULL) { delete p; p = NULL; } }

template <typename T>
inline void SAFE_DELETE_ARRAY(T& p) { if (p != NULL) { delete[] p; p = NULL; } }

#define GETTER(varType, parameter, memberVar) \
varType Get##parameter() \
{ \
    return memberVar; \
}

#define SETTER(varType, parameter, memberVar) \
void Set##parameter(varType parameter) \
{ \
    memberVar = parameter; \
}

#define GETTER_SETTER(varType, parameter, memberVar) \
varType Get##parameter() \
{ \
    return memberVar; \
} \
void Set##parameter(varType parameter) \
{ \
    memberVar = parameter; \
}
