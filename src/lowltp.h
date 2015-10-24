#include <string>
#include <cstring>
#include <vector>
#include "ltp/segment_dll.h"
#include "ltp/postag_dll.h"
#include "ltp/ner_dll.h"
#include "../inc/lowltp.h"

using namespace std;

extern void* cws;
extern void* pos;
extern void* ner;

extern int lowltp_tocstr(char* dest, vector<string> src);
extern int lowltp_tostrs(vector<string>&dest, char* src);
