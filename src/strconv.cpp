#include "lowltp.h"

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
