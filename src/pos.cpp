#include "lowltp.h"

int lowltp_postag(char* words, char* tags){
	vector<string> ws;
	lowltp_tostrs(ws, words);

	vector<string> ts;
	postagger_postag(pos, ws, ts);

	return lowltp_tocstr(tags, ts);
}
