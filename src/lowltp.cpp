#include <stdio.h>
#include "lowltp.h"

void* cws;
void* pos;
void* ner;

void lowltp_init(char* dataDir){
	cws = segmentor_create_segmentor((const char*)((string)dataDir + (string)"/cws.model").c_str());
	pos = postagger_create_postagger((const char*)((string)dataDir + (string)"/pos.model").c_str());
	ner = ner_create_recognizer((const char*)((string)dataDir + (string)"/ner.model").c_str());
}

void lowltp_close(){
	segmentor_release_segmentor(cws);
	postagger_release_postagger(pos);
	ner_release_recognizer(ner);
}
