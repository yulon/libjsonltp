#include "lowltp.h"

int lowltp_recognize(char* words, char* postags, char* nes){
	vector<string> ws;
	lowltp_tostrs(ws, words);

	vector<string> pts;
	lowltp_tostrs(pts, postags);

	vector<string> ts;
	ner_recognize(ner, ws, pts, ts);

	return lowltp_tocstr(nes, ts);
}
