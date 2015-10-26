#include "lowltp.h"
#include <sstream>

int lowltp_tocstr(char* dest, vector<string> src){
	int offset = 0;
	int i;
	for (i = 0; i < src.size() - 1; i++) {
		strcpy(dest + offset, src[i].c_str());
		offset += src[i].size();
		dest[offset] = ' ';
		offset++;
	}
	strcpy(dest + offset, src[i].c_str());
	return offset + src[i].size();
}

int lowltp_tocstrex(char* dest, vector<int> src1, vector<string> src2){
	int offset = 0;
	int i;
	for (i = 0; i < src1.size() - 1; i++) {
		stringstream ss;
		string s;
		ss << src1[i];
		ss >> s;
		strcpy(dest + offset, s.c_str());
		offset += s.size();
		dest[offset] = ' ';
		offset++;

		strcpy(dest + offset, src2[i].c_str());
		offset += src2[i].size();
		dest[offset] = ' ';
		offset++;
	}
	stringstream ss;
	string s;
	ss << src1[i];
	ss >> s;
	strcpy(dest + offset, s.c_str());
	offset += s.size();
	dest[offset] = ' ';
	offset++;

	strcpy(dest + offset, src2[i].c_str());
	return offset + src2[i].size();
}

int lowltp_tostrs(vector<string>& dest, char* src){
	string str = (string)src;
	int spos = 0;
	int i;
	for (i = 0; i < str.size(); i++) {
		if(str[i] == ' '){
			dest.push_back(str.substr(spos, i - spos));
			spos = i + 1;
		}
	}
	dest.push_back(str.substr(spos, i - spos));
	return 0;
}
