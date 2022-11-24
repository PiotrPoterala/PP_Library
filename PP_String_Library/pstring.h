/**
 * @author  Piotr Poterała
 * @email   poterala.piotr@gmail.com
 * @website http://zappp.pl
 * @version v1.0
 * @ide     Keil uVision 5
 * @license GNU GPL v3
 *	
@verbatim
   ----------------------------------------------------------------------
    Copyright (C) Piotr Poterała, 2021
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.
     
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------
@endverbatim
 */

#ifndef PSTRING_H
#define PSTRING_H

#include <string>
#include <vector>
#include <map>

	#define  ZNAK_PLUS 		124
	#define  ZNAK_MINUS 	125
	#define  KROPKA 			126
	#define  SIGN_NULL 		255

using namespace std;

using StringList=vector<string>;

class PString: public string
{
public:
		PString();
		PString(const string &s);
    PString(const char* str);
    PString(string &str);

		enum SplitBehavior{SkipEmptyParts, KeepEmptyParts};

		PString mid(int position, int n);
		int toInt(int base=10);
		double toDouble();
		string findDataAfterAcronim(char acronim);
		double findValueAfterAcronim(char acronim, double defValue=0);
		map<char, double> findValuesAfterAcronims();
		PString& trimmed();
		PString& trimmedRight();
    vector<PString> split(char sep, SplitBehavior behavior = SkipEmptyParts);
		StringList splitWithClamps(char sep, char clamps);
		
		static string doubleToString(double doubleToStr, int unit);
};


using PStringList=vector<PString>;

#endif // PSTRING_H
