#ifndef __GETTER_SETTER_H__
#define __GETTER_SETTER_H__

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

#endif // __GETTER_SETTER_H__
