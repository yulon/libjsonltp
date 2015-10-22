#include "lowltp.h"

int lowltp_segment(char* line, char* words){
	vector<string> ws;
	int len = segmentor_segment(cws, (const string)line, ws);
	return lowltp_tocstr(words, ws);
}
