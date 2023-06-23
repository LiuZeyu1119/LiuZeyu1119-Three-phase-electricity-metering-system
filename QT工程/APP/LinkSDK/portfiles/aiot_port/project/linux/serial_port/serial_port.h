#ifndef _SERIAL_PORT_H_
#define _SERIAL_PORT_H_

#include <stdint.h>

/**
 * @brief 打开指定的串口设备, 配置为裸二进制传输模式, 配置读超时时间和波特率。
 *
 * @param device 要打开的串口设备
 * @param baud_rate 串口波特率
 * @return int32_t
 * @retval -1 执行失败
 * @retval >=0 串口设备fd
 */
int32_t aiot_serial_port_open(const char * device, uint32_t baud_rate);

/**
 * @brief 写数据到串口设备中
 *
 * @param fd 串口设备fd
 * @param buffer 指向外部数据缓冲区的指针
 * @param size 待写入数据的长度
 *
 * @return int32_t
 * @retval =0, 串口设备数据写入成功
 * @retval <0, 串口设备数据写入错误
 */
int32_t aiot_serial_port_write(int fd, uint8_t * buffer, uint32_t size);

/**
 * @brief 从指定fd的串口设备读取数据到外部大小为参数size的buffer中
 *
 * @param fd 串口设备fd
 * @param buffer 指向外部数据缓冲区的指针
 * @param size 外部数据缓冲区的大小
 *
 * @return int32_t
 * @retval >=0, 读取到的数据长度
 * @retval <0, 串口设备数据读取错误
 */
int32_t aiot_serial_port_read(int fd, uint8_t * buffer, uint32_t size);


#endif /* #ifndef _SERIAL_PORT_H_ */