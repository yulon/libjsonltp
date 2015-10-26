#include "lowltp.h"

int lowltp_parser(char* words, char* postags, char* hsads){
	vector<string> ws;
	lowltp_tostrs(ws, words);

	vector<string> pts;
	lowltp_tostrs(pts, postags);

	vector<int> hs;
	vector<string> ds;
	parser_parse(parser, ws, pts, hs, ds);

	return lowltp_tocstrex(hsads, hs, ds);
}
