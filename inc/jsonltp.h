#ifdef __cplusplus
	#define JSONLTP_EXTERN extern "C"
#else
	#define JSONLTP_EXTERN extern
#endif

JSONLTP_EXTERN void jsonltp_init(char* dataDir);
JSONLTP_EXTERN void jsonltp_close();
JSONLTP_EXTERN int jsonltp(char* line, char* result, int flag);
