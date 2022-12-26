#include "cJSON.h"

cJSON* cJSON_AddObjectToObject(cJSON *object, const char *key)
{
    return nullptr;
}

void cJSON_AddNumberToObject(cJSON *object, const char *key, int value)
{}

void cJSON_AddBoolToObject(cJSON *object, const char *key, bool value)
{}

void cJSON_AddStringToObject(cJSON *object, const char *key, const char *value)
{}

cJSON* cJSON_AddArrayToObject(cJSON *object, const char *key)
{
    return nullptr;
}

cJSON* cJSON_CreateString(const char *string)
{
    return nullptr;
}

void cJSON_Delete(cJSON *item)
{}

bool cJSON_AddItemToArray(cJSON *array, cJSON *item)
{
    return false;
}

cJSON* cJSON_GetObjectItem(cJSON *object, const char *key)
{
    return nullptr;
}

bool cJSON_IsBool(cJSON *object)
{
    return false;
}

bool cJSON_IsTrue(cJSON *object)
{
    return false;
}

bool cJSON_IsString(cJSON *object)
{
    return false;
}

bool cJSON_IsNumber(cJSON *object)
{
    return false;
}

bool cJSON_IsArray(cJSON *object)
{
    return false;
}
