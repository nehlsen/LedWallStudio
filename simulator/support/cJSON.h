#ifndef LEDWALLSTUDIO_CJSON_H
#define LEDWALLSTUDIO_CJSON_H

class cJSON
{
public:
    int valueint = 0;
    char *valuestring = nullptr;
};

cJSON* cJSON_AddObjectToObject(cJSON *object, const char *key);
void cJSON_AddNumberToObject(cJSON *object, const char *key, int value);
void cJSON_AddBoolToObject(cJSON *object, const char *key, bool value);
void cJSON_AddStringToObject(cJSON *object, const char *key, const char *value);
cJSON* cJSON_AddArrayToObject(cJSON *object, const char *key);

cJSON* cJSON_CreateString(const char *string);
void cJSON_Delete(cJSON *item);

bool cJSON_AddItemToArray(cJSON *array, cJSON *item);

cJSON* cJSON_GetObjectItem(cJSON *object, const char *key);

bool cJSON_IsBool(cJSON *object);
bool cJSON_IsTrue(cJSON *object);
bool cJSON_IsString(cJSON *object);
bool cJSON_IsNumber(cJSON *object);
bool cJSON_IsArray(cJSON *object);

#define cJSON_ArrayForEach(item,array) while (false)

#endif //LEDWALLSTUDIO_CJSON_H
