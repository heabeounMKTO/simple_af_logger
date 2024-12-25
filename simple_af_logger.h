// long ass names becaues i dont want to to conflict....

#ifndef SIMPLE_AF_LOGGER_H
#define SIMPLE_AF_LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <time.h>
#include <pthread.h>



typedef enum  {
  SAFL_LOG_LEVEL_INFO,
  SAFL_LOG_LEVEL_WARN,
  SAFL_LOG_LEVEL_ERROR
} SimpleAfLoggerLogLevel;

static SimpleAfLoggerLogLevel current_log_level = SAFL_LOG_LEVEL_INFO;
static int logging_enabled = 1; 
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

static inline void set_log_level(SimpleAfLoggerLogLevel level) {
    current_log_level = level;
}

static inline void set_logging_enabeled(int enabled) {
  logging_enabled = enabled;
}


static inline const char* get_timestamp() {
    static char buffer[20];
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    return buffer;
}


#define SAFL_LOG(level, format, ...) do { \
    if (logging_enabled && level >= current_log_level) { \
        pthread_mutex_lock(&log_mutex); \
        const char *level_str = ""; \
        switch (level) { \
            case SAFL_LOG_LEVEL_INFO: level_str = "INFO"; break; \
            case SAFL_LOG_LEVEL_WARN: level_str = "WARN"; break; \
            case SAFL_LOG_LEVEL_ERROR: level_str = "ERROR"; break; \
        } \
        fprintf(stderr, "[%s] [%s] " format "\n", get_timestamp(), level_str, ##__VA_ARGS__); \
        pthread_mutex_unlock(&log_mutex); \
    } \
} while (0)

#define SAFL_LOG_INFO(format, ...) SAFL_LOG(SAFL_LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define SAFL_LOG_WARN(format, ...) SAFL_LOG(SAFL_LOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define SAFL_LOG_ERROR(format, ...) SAFL_LOG(SAFL_LOG_LEVEL_ERROR, format, ##__VA_ARGS__)


#ifdef __cplusplus
}
#endif
#endif  
