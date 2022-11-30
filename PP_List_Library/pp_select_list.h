#ifndef _PP_SELECT_LIST_H
	#define _PP_SELECT_LIST_H



		#include <string>
		#include <vector>


		using namespace std;
	

		class PSelectList{
			protected:
				int id=-1;
				vector<string> textsList;
			
			public:
				PSelectList(){};
				PSelectList(vector<string> &texts):textsList(texts){};
				PSelectList(vector<string> &texts, int index):textsList(texts){
				
					if(id>=0 && id<textsList.size()){
						id=index;
					}
				
				};
			
				void addItem(string &text){
					textsList.push_back(text);	
				}
				
				void addItems(vector<string> &texts){
					textsList.insert(textsList.end(), texts.begin(), texts.end());
					
				}
					
				int currentIndex(){return id;};
				
				string currentText(){
					string str;
					if(id>=0 && id<textsList.size()){
						str=textsList.at(id);
					}
					return str;
				};		
				
				string itemText(int index){
					string str;
					if(index>=0 && index<textsList.size()){
						str=textsList.at(index);
					}
					return str;
				};	
			
				int count(){return textsList.size();}
					
				void setCurrentIndex(int index){
					if(index>=0 && index<textsList.size())id=index;
				}
				
				void insertItem(int index, string &text){
					if(index>=0 && index<=textsList.size()){
						textsList.insert(textsList.begin()+index, text);
						if(id>=index)id++;
						
					}
				}
				void removeItem(int index){
					if(index>=0 && index<textsList.size()){
						textsList.erase(textsList.begin()+index);
						if(id==index)id=-1;
						else if(id>index)id--;
						
					}
					
				}
				void clear(){
					textsList.clear();
					id=-1;
				}

		};
		
using PSelectListShrPtr=shared_ptr<PSelectList>;		
	

#endif

