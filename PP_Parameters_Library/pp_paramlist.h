#ifndef PP_PARAM_LIST_H
#define PP_PARAM_LIST_H

#include "stm32xx.h"
#include <string>
#include <map>
#include "pp_param_general.h"
#include "pstring.h"

using namespace std;

class defOParamList
{

private:
    map<char, defOParamGeneral*> param;


public:
    defOParamList();
		defOParamList(const defOParamList& other);
    defOParamList(map<char, defOParamGeneral*> &copyParams);

		defOParamList* clone() const;

		defOParamGeneral* getParam(char acronim);
    map<char, defOParamGeneral*>* getParams(void);

    int getParamValue(char acronim);
		int getParamUpperLimit(char acronim);
		int getParamUnit(char acronim);
		int getParamPrecision(char acronim);

		pair<char, defOParamGeneral*> getParamPair(char acronim);
		map<char, int> getParamsValues();
		string getStringWithParams();

		int checkRange(char acronim, int val);

		void insert(pair<char, defOParamGeneral*>);
    void copyListOfParams(map<char, defOParamGeneral*> &copyParams);

    void clearParams(void);
		bool setParamValue(char acronim, int val);
    void setParamsByValue(int value);
    void setParamsByDefaultValue();
    void setParamsValue(map<char, defOParamGeneral*> &copyParams);

    bool comparingParamsValue(map<char, defOParamGeneral*> &paramsToComp);
		bool comparingParamsValue(map<char, int> &paramToComp);

    void setParamsBasedString(PString *data);
    void checksParamsValue();
};

#endif 
