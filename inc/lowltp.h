#ifdef __cplusplus
	#define LOWLTP_EXTERN extern "C"
#else
	#define LOWLTP_EXTERN extern
#endif

LOWLTP_EXTERN void lowltp_init(char* dataDir);
LOWLTP_EXTERN void lowltp_close();
LOWLTP_EXTERN int lowltp_segment(char* line, char* words);
LOWLTP_EXTERN int lowltp_postag(char* words, char* tags);
LOWLTP_EXTERN int lowltp_recognize(char* words, char* postags, char* tags);
LOWLTP_EXTERN int lowltp_parser(char* words, char* postags, char* hsads);
