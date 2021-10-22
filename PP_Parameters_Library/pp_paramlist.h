#ifndef PP_PARAM_LIST_H
#define PP_PARAM_LIST_H

#include "stm32xx.h"
#include <string>
#include <map>
#include "pp_param.h"
#include "pstring.h"

using namespace std;

class defOParamList
{

private:
    map<char, defOParam*> param;

public:
    defOParamList();
		defOParamList(const defOParamList& other);
    defOParamList(map<char, defOParam*> &copyParams);

		defOParamList* clone() const;

    map<char, defOParam*>* getParams(void);
    defOParam* getParam(char acronim);
    int getParamValue(char acronim);
		pair<char, defOParam*> getParamPair(char acronim);
		map<char, int> getParamsValues();
    bool setParamValue(char acronim, int val);
    vector<int>* getParamAllowedValues(char acronim);
    int getParamUpperLimit(char acronim);
    void copyListOfParams(map<char, defOParam*> &copyParams);
    void clearParams(void);
    void setParamsByValue(int value);
    void setParamsByDefaultValue();
    void setParamsValue(map<char, defOParam*> &copyParams);

    bool comparingParamsValue(map<char, defOParam*> &paramsToComp);
		bool comparingParamsValue(map<char, int> &paramToComp);

    void getParamsFromString(PString *data);
    void checksParamsValue();
};

#endif // COORDINATES_WEDM_H
