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
	cJSON_AddItemToObject(jRoot, "words", strs_to_jary(words));

	//Postag
	vector<string> postags;
	if (flag & JSONLTP_FLAG_POS) {
		postagger_postag(pos, words, postags);
		cJSON_AddItemToObject(jRoot, "postags", strs_to_jary(postags));
	}

	//NER
	vector<string> nes;
	if (flag & JSONLTP_FLAG_NER) {
		ner_recognize(ner, words, postags, nes);
		cJSON_AddItemToObject(jRoot, "nes", strs_to_jary(nes));
	}

	//Parse
	vector< pair< int, string > > parse;
	if (flag & JSONLTP_FLAG_DP) {
		vector<int> heads;
		vector<string> deprels;
		parser_parse(par, words, postags, heads, deprels);
		cJSON* jParses = cJSON_CreateArray();
		for (int i = 0; i < heads.size(); i++) {
			parse.push_back(make_pair(heads[i] - 1, deprels[i]));

			cJSON* jParse = cJSON_CreateObject();
			cJSON_AddNumberToObject(jParse, "heads", heads[i]);
			cJSON_AddStringToObject(jParse, "deprels", deprels[i].c_str());
			cJSON_AddItemToArray(jParses, jParse);
		}
		cJSON_AddItemToObject(jRoot, "parse", jParses);
	}

	//SRL
	if (flag & JSONLTP_FLAG_SRL) {
		vector< pair< int, vector< pair<string, pair< int, int > > > > > srl;
		DoSRL(words, postags, nes, parse, srl);
		cJSON* jSRL = cJSON_CreateArray();
		for (int i = 0; i < srl.size(); i++) {
			cJSON* jPredicate = cJSON_CreateObject();
			cJSON_AddNumberToObject(jPredicate, "i", srl[i].first);

			cJSON* jArgs = cJSON_CreateArray();
			for (int j = 0; j < srl[i].second.size(); ++j)
			{
				cJSON* jArg = cJSON_CreateObject();
				cJSON_AddStringToObject(jArg, "type", srl[i].second[j].first.c_str());
				cJSON_AddNumberToObject(jArg, "beg", srl[i].second[j].second.first);
				cJSON_AddNumberToObject(jArg, "end", srl[i].second[j].second.second);
				cJSON_AddItemToArray(jArgs, jArg);
			}
			cJSON_AddItemToObject(jPredicate, "srl", jArgs);

			cJSON_AddItemToArray(jSRL, jPredicate);
		}
		cJSON_AddItemToObject(jRoot, "srl", jSRL);
	}

	char* jRootStr = cJSON_Print(jRoot);
	cJSON_Delete(jRoot);
	int jRootStrLen = strlen(jRootStr);
	strcpy(result, jRootStr);
	free(jRootStr);
	return jRootStrLen;
}
