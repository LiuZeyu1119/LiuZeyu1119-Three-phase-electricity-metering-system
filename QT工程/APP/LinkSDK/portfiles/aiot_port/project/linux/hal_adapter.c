#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/time.h>
#include "aiot_state_api.h"
#include "aiot_sysdep_api.h"
#include "os_net_interface.h"
#include "aiot_at_api.h"
#include "serial_port.h"

extern aiot_os_al_t  *os_api;
static int g_uart_fd = 0;
static pthread_t g_serial_port_thread;

extern aiot_os_al_t g_aiot_linux_api;
extern aiot_net_al_t g_aiot_net_at_api;

/*AT module*/
extern at_device_t ec200_at_cmd;
extern at_device_t ec200_at_cmd_ssl;
extern at_device_t l610_at_cmd;
extern at_device_t l610_at_cmd_ssl;
extern at_device_t air724_at_cmd;
extern at_device_t air724_at_cmd_ssl;
at_device_t *device = &l610_at_cmd;

/* 串口数据接口线程 */
static uint8_t g_serial_port_recv_thread_running = 0;

void *demo_serial_port_thread(void *args)
{
    int32_t res = STATE_SUCCESS;
    uint8_t buf[1024] = {0};
    while (g_serial_port_recv_thread_running) {
        res = aiot_serial_port_read(g_uart_fd, buf, sizeof(buf));
        if (res <= 0) {
            usleep(200);
            continue;
        }
        printf("[%d] <<<< %*s\r\n", res, res, buf);
        aiot_at_hal_recv_handle(buf, res);
        memset(buf, 0, res);
    }

    return NULL;
}
/* 串口发送回调函数 */
int32_t at_uart_send(uint8_t *p_data, uint16_t len, uint32_t timeout)
{
    int32_t res = aiot_serial_port_write(g_uart_fd, p_data, len);
    printf("[%d] >>>> %*s\r\n", len, len, p_data);
    if (res == 0) {
        return len;
    } else {
        return -1;
    }
}


/*
* 1.初始化hal传输层，包活发送和接收
* 2.初始化模组，包括模组型号及网络注册
*/
int32_t at_hal_init()
{
    /* 串口初始化, 波特率115200, TODO: 请填写实际的串口设备名称 */
    g_uart_fd = aiot_serial_port_open("/dev/ttyUSB5", 115200);
    if (g_uart_fd < 0) {
        printf("aiot_serial_port_open failed\r\n");
        return -1;
    }
    aiot_install_os_api(&g_aiot_linux_api);
    aiot_install_net_api(&g_aiot_net_at_api);

    /* 初始化AT组件 */
    int res = aiot_at_init();
    if (res < 0) {
        printf("aiot_at_init failed\r\n");
        return -1;
    }
    /* 注册串口发送回调函数 */
    aiot_at_setopt(AIOT_ATOPT_UART_TX_FUNC, at_uart_send);
    g_serial_port_recv_thread_running = 1;
    /* 启动串口数据接收独立线程 */
    res = pthread_create(&g_serial_port_thread, NULL, demo_serial_port_thread, NULL);
    if (res < 0) {
        printf("pthread_create demo_serial_port_thread failed: %d\n", res);
        return -1;
    }

    /*设置模组*/
    aiot_at_setopt(AIOT_ATOPT_DEVICE, device);
    /* 模组初始化 */
    res = aiot_at_bootstrap();
    if (res < 0) {
        printf("aiot_at_bootstrap failed\r\n");
        return -1;
    }

    return STATE_SUCCESS;
}
