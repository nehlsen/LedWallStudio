#ifndef LEDWALLSTUDIO_SIMULATOR_SUPPORT_ESP_LOG_H
#define LEDWALLSTUDIO_SIMULATOR_SUPPORT_ESP_LOG_H

void esp_fake_log(const char* tag, const char* format, ...);

#define ESP_LOGD

#define ESP_LOGI(tag, format, ...) esp_fake_log(tag, format, ##__VA_ARGS__)

#define ESP_LOGE

#endif //LEDWALLSTUDIO_SIMULATOR_SUPPORT_ESP_LOG_H
