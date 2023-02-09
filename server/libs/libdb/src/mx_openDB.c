#include "libdb.h"

void mx_openDB(const char* filename, sqlite3** ppDB) {
    int rc = sqlite3_open(filename, ppDB);
    
    if(rc){
      sqlite3_close(*ppDB);
      return;
    }
}