
/* QUICK HACK! */

#define MBCS
#define _MBCS

#include <windows.h>
#include <tchar.h>
#include "dirent.h"

struct internalDIR {
	const char *dirname;
	HANDLE hFind;
};

DIR *opendir(const char *dirname) {
	static struct internalDIR dir;
	dir.dirname = dirname;
	dir.hFind = INVALID_HANDLE_VALUE;
	return (DIR*)&dir;
}
struct dirent *readdir(DIR* _dir) {
	static struct dirent dirent;
	struct internalDIR *dir = (struct internalDIR*)_dir;
	WIN32_FIND_DATA ffd;
	if(dir->hFind == INVALID_HANDLE_VALUE) {
		char buf[256];
		sprintf(buf, "%s\\*.*", dir->dirname);
		dir->hFind = FindFirstFileA(buf, &ffd);
		if(dir->hFind == INVALID_HANDLE_VALUE) {
			return NULL;
		}
	} else {
		BOOL res;
		res = FindNextFile(dir->hFind, &ffd);
		if(!res) {
			return NULL;
		}
	}
	_tcscpy(dirent.d_name, ffd.cFileName);
	return &dirent;
}

void closedir(DIR* _dir) {
	struct internalDIR *dir = (struct internalDIR*)_dir;
	if(dir->hFind != INVALID_HANDLE_VALUE) {
		FindClose(dir->hFind);
	}
	// dir is static-variable. no need to free.
}
