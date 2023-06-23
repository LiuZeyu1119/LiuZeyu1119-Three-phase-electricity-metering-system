QT += quick core qml network positioning widgets quickcontrols2 widgets multimedia virtualkeyboard charts sql

CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        LinkSDK/cJSON.c \
        LinkSDK/cJSON_Utils.c \
        LinkSDK/components/data-model/aiot_dm_api.c \
        #LinkSDK/components/ntp/aiot_ntp_api.c \
        LinkSDK/core/aiot_mqtt_api.c \
        LinkSDK/core/aiot_mqtt_props_api.c \
        LinkSDK/core/aiot_state_api.c \
        LinkSDK/core/sysdep/core_adapter.c \
        LinkSDK/core/sysdep/core_sysdep.c \
        LinkSDK/core/utils/core_auth.c \
        LinkSDK/core/utils/core_diag.c \
        LinkSDK/core/utils/core_global.c \
        LinkSDK/core/utils/core_log.c \
        LinkSDK/core/utils/core_sha256.c \
        LinkSDK/core/utils/core_string.c \
        LinkSDK/external/ali_ca_cert.c \
        LinkSDK/external/mbedtls/library/aes.c \
        LinkSDK/external/mbedtls/library/asn1parse.c \
        LinkSDK/external/mbedtls/library/base64.c \
        LinkSDK/external/mbedtls/library/bignum.c \
        LinkSDK/external/mbedtls/library/cipher.c \
        LinkSDK/external/mbedtls/library/cipher_wrap.c \
        LinkSDK/external/mbedtls/library/ctr_drbg.c \
        LinkSDK/external/mbedtls/library/debug.c \
        LinkSDK/external/mbedtls/library/entropy.c \
        LinkSDK/external/mbedtls/library/error.c \
        LinkSDK/external/mbedtls/library/md.c \
        LinkSDK/external/mbedtls/library/md_wrap.c \
        LinkSDK/external/mbedtls/library/oid.c \
        LinkSDK/external/mbedtls/library/pem.c \
        LinkSDK/external/mbedtls/library/pk.c \
        LinkSDK/external/mbedtls/library/pk_wrap.c \
        LinkSDK/external/mbedtls/library/pkparse.c \
        LinkSDK/external/mbedtls/library/platform.c \
        LinkSDK/external/mbedtls/library/platform_util.c \
        LinkSDK/external/mbedtls/library/rsa.c \
        LinkSDK/external/mbedtls/library/rsa_internal.c \
        LinkSDK/external/mbedtls/library/sha1.c \
        LinkSDK/external/mbedtls/library/sha256.c \
        LinkSDK/external/mbedtls/library/ssl_ciphersuites.c \
        LinkSDK/external/mbedtls/library/ssl_cli.c \
        LinkSDK/external/mbedtls/library/ssl_cookie.c \
        LinkSDK/external/mbedtls/library/ssl_tls.c \
        LinkSDK/external/mbedtls/library/x509.c \
        LinkSDK/external/mbedtls/library/x509_crt.c \
        LinkSDK/portfiles/aiot_port/project/linux/hal_adapter.c \
        LinkSDK/mqtt.c \
        LinkSDK/mqtt4g.c \
        LinkSDK/portfiles/aiot_port/project/linux/serial_port/serial_port.c\
        LinkSDK/portfiles/aiot_port/project/linux/os_posix_impl.c\
        #LinkSDK/portfiles/aiot_port/posix_port.c \
        LinkSDK/portfiles/aiot_port/at/aiot_at_api.c \
        LinkSDK/portfiles/aiot_port/at/module/fibcom_l610_ssl.c \
        LinkSDK/portfiles/aiot_port/at/module/fibcom_l610_tcp.c \
        LinkSDK/portfiles/aiot_port/at/net_at_impl.c \
        LinkSDK/portfiles/aiot_port/at_port.c \
        main.cpp \
        sensordata/sensordata.cpp \
        sqlite/sqlite.cpp \
        timeset/timeset.cpp \
        topbar.cpp \
        wireless/wireless.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    LinkSDK/cJSON.h \
    LinkSDK/cJSON_Utils.h \
    LinkSDK/components/data-model/aiot_dm_api.h \
    LinkSDK/components/data-model/dm_private.h \
    #LinkSDK/components/ntp/aiot_ntp_api.h \
    #LinkSDK/components/ntp/ntp_private.h \
    LinkSDK/core/aiot_mqtt_api.h \
    LinkSDK/core/aiot_mqtt_props_api.h \
    LinkSDK/core/aiot_state_api.h \
    LinkSDK/core/aiot_sysdep_api.h \
    LinkSDK/core/sysdep/core_adapter.h \
    LinkSDK/core/sysdep/core_stdinc.h \
    LinkSDK/core/sysdep/core_sysdep.h \
    LinkSDK/core/utils/core_auth.h \
    LinkSDK/core/utils/core_diag.h \
    LinkSDK/core/utils/core_global.h \
    LinkSDK/core/utils/core_list.h \
    LinkSDK/core/utils/core_log.h \
    LinkSDK/core/utils/core_mqtt.h \
    LinkSDK/core/utils/core_sha256.h \
    LinkSDK/core/utils/core_string.h \
    LinkSDK/external/mbedtls/include/mbedtls/aes.h \
    LinkSDK/external/mbedtls/include/mbedtls/asn1.h \
    LinkSDK/external/mbedtls/include/mbedtls/base64.h \
    LinkSDK/external/mbedtls/include/mbedtls/bignum.h \
    LinkSDK/external/mbedtls/include/mbedtls/bn_mul.h \
    LinkSDK/external/mbedtls/include/mbedtls/check_config.h \
    LinkSDK/external/mbedtls/include/mbedtls/cipher.h \
    LinkSDK/external/mbedtls/include/mbedtls/cipher_internal.h \
    LinkSDK/external/mbedtls/include/mbedtls/config.h \
    LinkSDK/external/mbedtls/include/mbedtls/ctr_drbg.h \
    LinkSDK/external/mbedtls/include/mbedtls/debug.h \
    LinkSDK/external/mbedtls/include/mbedtls/des.h \
    LinkSDK/external/mbedtls/include/mbedtls/ecp.h \
    LinkSDK/external/mbedtls/include/mbedtls/entropy.h \
    LinkSDK/external/mbedtls/include/mbedtls/entropy_poll.h \
    LinkSDK/external/mbedtls/include/mbedtls/error.h \
    LinkSDK/external/mbedtls/include/mbedtls/md.h \
    LinkSDK/external/mbedtls/include/mbedtls/md5.h \
    LinkSDK/external/mbedtls/include/mbedtls/md_internal.h \
    LinkSDK/external/mbedtls/include/mbedtls/net.h \
    LinkSDK/external/mbedtls/include/mbedtls/net_sockets.h \
    LinkSDK/external/mbedtls/include/mbedtls/oid.h \
    LinkSDK/external/mbedtls/include/mbedtls/pem.h \
    LinkSDK/external/mbedtls/include/mbedtls/pk.h \
    LinkSDK/external/mbedtls/include/mbedtls/pk_internal.h \
    LinkSDK/external/mbedtls/include/mbedtls/platform.h \
    LinkSDK/external/mbedtls/include/mbedtls/platform_util.h \
    LinkSDK/external/mbedtls/include/mbedtls/rsa.h \
    LinkSDK/external/mbedtls/include/mbedtls/rsa_internal.h \
    LinkSDK/external/mbedtls/include/mbedtls/sha1.h \
    LinkSDK/external/mbedtls/include/mbedtls/sha256.h \
    LinkSDK/external/mbedtls/include/mbedtls/ssl.h \
    LinkSDK/external/mbedtls/include/mbedtls/ssl_ciphersuites.h \
    LinkSDK/external/mbedtls/include/mbedtls/ssl_cookie.h \
    LinkSDK/external/mbedtls/include/mbedtls/ssl_internal.h \
    LinkSDK/external/mbedtls/include/mbedtls/threading.h \
    LinkSDK/external/mbedtls/include/mbedtls/timing.h \
    LinkSDK/external/mbedtls/include/mbedtls/x509.h \
    LinkSDK/external/mbedtls/include/mbedtls/x509_crl.h \
    LinkSDK/external/mbedtls/include/mbedtls/x509_crt.h \
    LinkSDK/mqtt.h \
    LinkSDK/mqtt4g.h \
    LinkSDK/portfiles/aiot_port/os_net_interface.h \
    LinkSDK/portfiles/aiot_port/at/aiot_at_api.h \
    LinkSDK/portfiles/aiot_port/project/linux/serial_port/serial_port.h \
    sensordata/sensordata.h \
    sqlite/sqlite.h \
    timeset/timeset.h \
    topbar.h \
    wireless/wireless.h
INCLUDEPATH += \
                   LinkSDK/ \
                   LinkSDK/core/ \
                   LinkSDK/core/sysdep/ \
                   LinkSDK/core/utils/ \
                   LinkSDK/external/mbedtls/include/mbedtls/ \
                   LinkSDK/external/mbedtls/include/ \
                   LinkSDK/external/mbedtls/library/ \
                   LinkSDK/components/data-model/ \
                   LinkSDK/components/ntp/ \
                   LinkSDK/portfiles/aiot_port \
                   LinkSDK/portfiles/aiot_port/at/\
                   LinkSDK/portfiles/aiot_port/project/linux/serial_port/
DISTFILES += \
    LinkSDK/ChangeLog.md \
    LinkSDK/LICENSE \
    LinkSDK/components/data-model/README.md \
    LinkSDK/components/ntp/README.md \
    LinkSDK/core/README.md \
    LinkSDK/external/README.md \
    #LinkSDK/portfiles/README.md
