#include <string>
#include <cstring>
#include <vector>
#include "ltp/segment_dll.h"
#include "ltp/postag_dll.h"
#include "ltp/ner_dll.h"
#include "ltp/parser_dll.h"
#include "ltp/SRL_DLL.h"
#include "../inc/jsonltp.h"
#include "cJSON.h"

using namespace std;

void* cws;
void* pos;
void* ner;
void* par;

void jsonltp_init(char* dataDir){
	cws = segmentor_create_segmentor((const char*)((string)dataDir + (string)"/cws.model").c_str());
	pos = postagger_create_postagger((const char*)((string)dataDir + (string)"/pos.model").c_str());
	ner = ner_create_recognizer((const char*)((string)dataDir + (string)"/ner.model").c_str());
	par = parser_create_parser((const char*)((string)dataDir + (string)"/parser.model").c_str());
	SRL_LoadResource((string)dataDir + (string)"/srl/");
}

void jsonltp_close(){
	segmentor_release_segmentor(cws);
	postagger_release_postagger(pos);
	ner_release_recognizer(ner);
	parser_release_parser(par);
	SRL_ReleaseResource();
}

int jsonltp(char* line, char* result, int flag){
	
}