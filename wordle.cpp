// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void permute(string in, int inIndex, string req, set<string>* validPermutations);
void permuteHelper(string in, int beginIndex, int endIndex, set<string>* validPermutations);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		set<string>* validStrings = new set<string>;
		set<string> insertions;

		string temp = in;

		int blanks = 0;
		for(size_t i = 0; i < in.size(); i++){
			if(in[i] == '-'){
				blanks++;
			}
		}
		blanks -= floating.size();
		if(blanks < 0){
			blanks = 0;
		}

		string blank(blanks, '-');

		permute(blank, 0, floating, &insertions);

		set<string>::iterator it;
		for(it = insertions.begin(); it != insertions.end(); it++){
			int j = 0;
			for(size_t i = 0; i < temp.size(); i++){
				if(temp[i] == '-'){
					temp[i] = (*it)[j];
					j++;
				}
			}
			if(dict.count(temp) != 0){
				validStrings->insert(temp);
			}
			temp = in;
		}

		return *validStrings;

}

// Define any helper functions here
void permute(string in, int inIndex, string req, set<string>* validPermutations){
	for(int i = 97; i <= 122; i++){
		if(in[inIndex] == '\0'){
			permuteHelper(req, 0, req.size()-1, validPermutations);
			return;
		}
		in[inIndex] = char(i);
		if(in[inIndex+1] != '\0'){
			permute(in, inIndex+1, req, validPermutations);
		}
		else{
			permuteHelper(in+req, 0, in.size()+req.size()-1, validPermutations);
		}
	}
}

void permuteHelper(string in, int beginIndex, int endIndex, set<string>* validPermutations){
	if(beginIndex == endIndex){
		validPermutations->insert(in);
	}
	else{
		for(int i = beginIndex; i <= endIndex; i++){
			swap(in[i], in[beginIndex]);
			permuteHelper(in, beginIndex+1, endIndex, validPermutations);
			swap(in[i], in[beginIndex]);
		}
	}
}
