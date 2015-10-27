#include <string>
#include <cstring>
#include <vector>
#include "ltp/segment_dll.h"
#include "ltp/postag_dll.h"
#include "ltp/ner_dll.h"
#include "ltp/parser_dll.h"
#include "ltp/SRL_DLL.h"
#include "../inc/lowltp.h"

using namespace std;

extern void* cws;
extern void* pos;
extern void* ner;
extern void* parser;

extern int lowltp_tocstr(char* dest, vector<string> src);
extern int lowltp_tostrs(vector<string>&dest, char* src);
extern int lowltp_tocstrex(char* dest, vector<int> src1, vector<string> src2);
