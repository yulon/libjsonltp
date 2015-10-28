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

cJSON* strs_to_jary(vector<string> &strs){
	cJSON* jAry = cJSON_CreateArray();
	for (int i = 0; i < strs.size(); i++) {
		cJSON_AddItemToArray(jAry, cJSON_CreateString(strs[i].c_str()));
	}
	return jAry;
}

int jsonltp(char* line, char* result, int flag){
	cJSON* jRoot = cJSON_CreateObject();

	//Segment
	vector<string> words;
	int len = segmentor_segment(cws, (const string)line, words);
	cJSON_AddItemToObject(jRoot, "ws", strs_to_jary(words));

	//Postag
	if (flag & JSONLTP_FLAG_POS) {
		vector<string> postags;
		postagger_postag(pos, words, postags);
		cJSON_AddItemToObject(jRoot, "pos", strs_to_jary(postags));

		//Named entity recognize
		if (flag & JSONLTP_FLAG_NER) {
			vector<string> nes;
			ner_recognize(ner, words, postags, nes);
			cJSON_AddItemToObject(jRoot, "nes", strs_to_jary(nes));
		}
	}

	char* jRootStr = cJSON_Print(jRoot);
	cJSON_Delete(jRoot);
	int jRootStrLen = strlen(jRootStr);
	strcpy(result, jRootStr);
	free(jRootStr);
	return jRootStrLen;
}
