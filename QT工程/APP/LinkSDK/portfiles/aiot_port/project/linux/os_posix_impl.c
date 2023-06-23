
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include "os_net_interface.h"

/**
 * @brief 申请内存
 */
static void* __malloc(uint32_t size) {
    return malloc(size);
}
/**
 * @brief 释放内存
 */
void __free(void *ptr) {
    free(ptr);
}
/**
 * @brief 获取当前的时间戳，SDK用于差值计算
 */
uint64_t __time(void) {
    struct timeval time;

    memset(&time, 0, sizeof(struct timeval));
    gettimeofday(&time, NULL);

    return ((uint64_t)time.tv_sec * 1000 + (uint64_t)time.tv_usec / 1000);
}
/**
 * @brief 睡眠指定的毫秒数
 */
void __sleep(uint64_t time_ms) {
    usleep(time_ms * 1000);
}
/**
 * @brief 随机数生成方法
 */
void __rand(uint8_t *output, uint32_t output_len) {
    uint32_t idx = 0, bytes = 0, rand_num = 0;
    struct timeval time;

    memset(&time, 0, sizeof(struct timeval));
    gettimeofday(&time, NULL);

    srand((unsigned int)(time.tv_sec * 1000 + time.tv_usec / 1000) + rand());

    for (idx = 0; idx < output_len;) {
        if (output_len - idx < 4) {
            bytes = output_len - idx;
        } else {
            bytes = 4;
        }
        rand_num = rand();
        while (bytes-- > 0) {
            output[idx++] = (uint8_t)(rand_num >> bytes * 8);
        }
    }
}
/**
 * @brief 创建互斥锁
 */
void*  __mutex_init(void) {
    int res = 0;
    pthread_mutex_t *mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (NULL == mutex) {
        return NULL;
    }

    if (0 != (res = pthread_mutex_init(mutex, NULL))) {
        perror("create mutex failed\n");
        free(mutex);
        return NULL;
    }
    /* printf("init mutex: %p\n",mutex); */

    return (void *)mutex;
}
/**
 * @brief 申请互斥锁
 */
void __mutex_lock(void *mutex) {
    int res = 0;
    if (mutex != NULL) {
        if (0 != (res = pthread_mutex_lock((pthread_mutex_t *)mutex))) {
            printf("lock mutex failed: - '%s' (%d)\n", strerror(res), res);
        }
    }
}
/**
 * @brief 释放互斥锁
 */
void __mutex_unlock(void *mutex) {
    int res = 0;
    if (mutex != NULL) {
        if (0 != (res = pthread_mutex_unlock((pthread_mutex_t *)mutex))) {
            printf("unlock mutex failed - '%s' (%d)\n", strerror(res), res);
        }
    }
}
/**
 * @brief 销毁互斥锁
 */
void __mutex_deinit(void **mutex) {
    int err_num = 0;
    if (mutex != NULL) {
        /* printf("deinit mutex: %p\n",mutex); */
        if (0 != (err_num = pthread_mutex_destroy(*(pthread_mutex_t **)mutex))) {
            perror("destroy mutex failed\n");
        }
        free(*(pthread_mutex_t **)mutex);
        *mutex = NULL;
    }
}

aiot_os_al_t  g_aiot_linux_api = {
    .malloc = __malloc,
    .free = __free,
    .time = __time,
    .sleep = __sleep,
    .rand = __rand,
    .mutex_init = __mutex_init,
    .mutex_lock = __mutex_lock,
    .mutex_unlock = __mutex_unlock,
    .mutex_deinit = __mutex_deinit,
};

