#ifdef __cplusplus
	#define JSONLTP_EXTERN extern "C"
#else
	#define JSONLTP_EXTERN extern
#endif

JSONLTP_EXTERN void jsonltp_init(char* dataDir);
JSONLTP_EXTERN void jsonltp_close();
JSONLTP_EXTERN int jsonltp(char* line, char* result, int flag);

#define JSONLTP_FLAG_POS = 0x000F;
#define JSONLTP_FLAG_NER = 0x00F0;
#define JSONLTP_FLAG_DP = 0x0F00;
#define JSONLTP_FLAG_SRL = 0xF000;
#define JSONLTP_FLAG_ALL = 0xFFFF;
