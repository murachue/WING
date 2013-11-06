
/* QUICK HACK! */

typedef void* DIR;
struct dirent {
	// XXX: only for readdata.c!
	char d_name[256];
};

DIR *opendir(const char *dirname);
struct dirent *readdir(DIR* dir);
void closedir(DIR* dir);
