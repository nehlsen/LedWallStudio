#ifndef LEDWALLSTUDIO_CJSON_H
#define LEDWALLSTUDIO_CJSON_H

class cJSON
{
public:
    int valueint = 0;
};

void cJSON_AddNumberToObject(cJSON *object, const char *key, int value);
void cJSON_AddBoolToObject(cJSON *object, const char *key, bool value);

cJSON* cJSON_GetObjectItem(cJSON *object, const char *key);

bool cJSON_IsBool(cJSON *object);
bool cJSON_IsTrue(cJSON *object);

#endif //LEDWALLSTUDIO_CJSON_H
