#ifndef BASE64_H
#define BASE64_H
#include <cstdlib>
#include <cstring>

extern char base46_map[];

char* base64_encode(char* plain);
char* base64_decode(char* cipher);

#endif // BASE64_H
