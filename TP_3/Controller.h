int controller_loadFromText(char* path , LinkedList* pArrayListPassenger);
int controller_loadFromLastId(char* pathNew);
int controller_refreshLastId(char* path,int* pLastId);
int controller_accessFileByName(char* path);
int controller_createLastIdTxt(char* path);
int controller_createLastIdTxt2(char* pathNew,char* pathCsv);
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger);
int controller_addPassenger(LinkedList* pArrayListPassenger);
int controller_editPassenger(LinkedList* pArrayListPassenger);
int controller_removePassenger(LinkedList* pArrayListPassenger);
int controller_ListPassenger(LinkedList* pArrayListPassenger);
int controller_sortPassenger(LinkedList* pArrayListPassenger);
int controller_saveAsText(char* path , LinkedList* pArrayListPassenger);
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger);


