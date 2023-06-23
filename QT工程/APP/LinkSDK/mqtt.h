#ifndef MQTT_H
#define MQTT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "aiot_state_api.h"
#include "aiot_sysdep_api.h"
#include "aiot_mqtt_api.h"

#include "cJSON.h"
#include "sys/time.h"

typedef struct{
    //电压
    /*电压有效值*/
    float r_UaRms;
    float r_UbRms;
    float r_UcRms;
    /*电压夹角*/
    float uAB_angle;
    float uAC_angle;
    float uBC_angle;
    /*流压夹角*/
    float uiA_angle;
    float uiB_angle;
    float uiC_angle;
    //电流
    /*电流有效值*/
    float r_IaRms;
    float r_IbRms;
    float r_IcRms;
    float r_ItRms;
    /*零序电流*/
    float zero_i;

    //频率
    float Freq;

    //功率
    /*有功功率*/
    float pN_a;
    float pN_b;
    float pN_c;
    float pN_t;
    float utrm;//电压和有效值
    float itrm;//电压和有效值
    /*基波功率*/
    float linepN_a;
    float linepN_b;
    float linepN_c;
    float linepN_t;
    /*基波dianneng*/
    float lineEpN_a;
    float lineEpN_b;
    float lineEpN_c;
    float lineEpN_t;
    /*无功功率*/
    float qN_a;
    float qN_b;
    float qN_c;
    float qN_t;
    /*视在功率*/
    float sN_a;
    float sN_b;
    float sN_c;
    float sN_t;
    /*功率因数*/
    float pFN_a;
    float pFN_b;
    float pFN_c;
    float pFN_t;

    /*有功电能*/
    float epN_a;
    float epN_b;
    float epN_c;
    float epN_t;
    /*视在电能*/
    float esN_a;
    float esN_b;
    float esN_c;
    float esN_t;

    /*芯片温度*/
    float tpsd;


}sensor_data;





#endif // MQTT_H
