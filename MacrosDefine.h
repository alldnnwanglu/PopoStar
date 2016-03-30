#ifndef HelloCpp_MacrosDefine_h
#define HelloCpp_MacrosDefine_h

#define SWX_PROPERTY(varType, varName, funName)\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

#endif