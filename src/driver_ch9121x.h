/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_ch9121x.h
 * @brief     driver ch9121x header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2026-05-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2026/05/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_CH9121X_H
#define DRIVER_CH9121X_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ch9121x_driver ch9121x driver function
 * @brief    ch9121x driver modules
 * @{
 */

/**
 * @addtogroup ch9121x_base_driver
 * @{
 */

/**
 * @brief ch9121x uart pre delay definition
 */
#ifndef CH9121X_UART_PRE_DELAY
    #define CH9121X_UART_PRE_DELAY    50        /**< 50ms */
#endif

/**
 * @brief ch9121x port enumeration definition
 */
typedef enum
{
    CH9121X_PORT1 = 0x00,        /**< port1 */
    CH9121X_PORT2 = 0x01,        /**< port2 */
} ch9121x_port_t;

/**
 * @brief ch9121x bool enumeration definition
 */
typedef enum
{
    CH9121X_BOOL_FALSE = 0x00,        /**< false */
    CH9121X_BOOL_TRUE  = 0x01,        /**< true */
} ch9121x_bool_t;

/**
 * @brief ch9121x status enumeration definition
 */
typedef enum
{
    CH9121X_STATUS_DISCONNECT = 0x00,        /**< disconnect */
    CH9121X_STATUS_CONNECT    = 0x01,        /**< connect */
} ch9121x_status_t;

/**
 * @brief ch9121x uart clock mode enumeration definition
 */
typedef enum
{
    CH9121X_UART_CLOCK_MODE_DEFAULT   = 0x00,        /**< default mode */
    CH9121X_UART_CLOCK_MODE_CLASSICAL = 0x01,        /**< classical mode */
} ch9121x_uart_clock_mode_t;

/**
 * @brief ch9121x phy status enumeration definition
 */
typedef enum
{
    CH9121X_PHY_STATUS_UNKNOWN          = 0x00,        /**< unknown */
    CH9121X_PHY_STATUS_DISCONNECTED     = 0x01,        /**< disconnected */
    CH9121X_PHY_STATUS_10M_FULL_DUPLEX  = 0x02,        /**< 10 mbps full duplex */
    CH9121X_PHY_STATUS_10M_HALF_DUPLEX  = 0x04,        /**< 10 mbps half duplex */
    CH9121X_PHY_STATUS_100M_FULL_DUPLEX = 0x08,        /**< 100 mbps full duplex */
    CH9121X_PHY_STATUS_100M_HALF_DUPLEX = 0x10,        /**< 100 mbps half duplex */
} ch9121x_phy_status_t;

/**
 * @brief ch9121x mode enumeration definition
 */
typedef enum
{
    CH9121X_MODE_TCP_SERVER = 0x00,        /**< tcp server */
    CH9121X_MODE_TCP_CLIENT = 0x01,        /**< tcp client */
    CH9121X_MODE_UDP_SERVER = 0x02,        /**< udp server */
    CH9121X_MODE_UDP_CLIENT = 0x03,        /**< udp client */
} ch9121x_mode_t;

/**
 * @brief ch9121x parity enumeration definition
 */
typedef enum
{
    CH9121X_PARITY_EVEN  = 0x00,        /**< even parity */
    CH9121X_PARITY_ODD   = 0x01,        /**< odd parity */
    CH9121X_PARITY_MARK  = 0x02,        /**< mark */
    CH9121X_PARITY_SPACE = 0x03,        /**< space */
    CH9121X_PARITY_NONE  = 0x04,        /**< none */
} ch9121x_parity_t;

/**
 * @brief ch9121x handle structure definition
 */
typedef struct ch9121x_handle_s
{
    uint8_t (*uart_init)(void);                               /**< point to an uart_init function address */
    uint8_t (*uart_deinit)(void);                             /**< point to an uart_deinit function address */
    uint16_t (*uart_read)(uint8_t *buf, uint16_t len);        /**< point to an uart_read function address */
    uint8_t (*uart_flush)(void);                              /**< point to an uart_flush function address */
    uint8_t (*uart_write)(uint8_t *buf, uint16_t len);        /**< point to an uart_write function address */
    uint8_t (*reset_gpio_init)(void);                         /**< point to a reset_gpio_init function address */
    uint8_t (*reset_gpio_deinit)(void);                       /**< point to a reset_gpio_deinit function address */
    uint8_t (*reset_gpio_write)(uint8_t data);                /**< point to a reset_gpio_write function address */
    uint8_t (*cfg_gpio_init)(void);                           /**< point to a cfg_gpio_init function address */
    uint8_t (*cfg_gpio_deinit)(void);                         /**< point to a cfg_gpio_deinit function address */
    uint8_t (*cfg_gpio_write)(uint8_t data);                  /**< point to a cfg_gpio_write function address */
    void (*delay_ms)(uint32_t ms);                            /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);          /**< point to a debug_print function address */
    uint8_t inited;                                           /**< inited flag */
    uint8_t buf[128];                                         /**< inner buffer */
} ch9121x_handle_t;

/**
 * @brief ch9121x information structure definition
 */
typedef struct ch9121x_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ch9121x_info_t;

/**
 * @}
 */

/**
 * @defgroup ch9121x_link_driver ch9121x link driver function
 * @brief    ch9121x link driver modules
 * @ingroup  ch9121x_driver
 * @{
 */

/**
 * @brief     initialize ch9121x structure
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] STRUCTURE ch9121x_handle_t
 * @note      none
 */
#define DRIVER_CH9121X_LINK_INIT(HANDLE, STRUCTURE)          memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link uart_init function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to an uart_init function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_UART_INIT(HANDLE, FUC)           (HANDLE)->uart_init = FUC

/**
 * @brief     link uart_deinit function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to an uart_deinit function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_UART_DEINIT(HANDLE, FUC)         (HANDLE)->uart_deinit = FUC

/**
 * @brief     link uart_read function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to an uart_read function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_UART_READ(HANDLE, FUC)           (HANDLE)->uart_read = FUC

/**
 * @brief     link uart_write function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to an uart_write function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_UART_WRITE(HANDLE, FUC)          (HANDLE)->uart_write = FUC

/**
 * @brief     link uart_flush function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to an uart_flush function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_UART_FLUSH(HANDLE, FUC)          (HANDLE)->uart_flush = FUC

/**
 * @brief     link reset_gpio_init function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to a reset_gpio_init function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_RESET_GPIO_INIT(HANDLE, FUC)     (HANDLE)->reset_gpio_init = FUC

/**
 * @brief     link reset_gpio_deinit function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to a reset_gpio_deinit function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_RESET_GPIO_DEINIT(HANDLE, FUC)   (HANDLE)->reset_gpio_deinit = FUC

/**
 * @brief     link reset_gpio_write function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to a reset_gpio_write function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_RESET_GPIO_WRITE(HANDLE, FUC)    (HANDLE)->reset_gpio_write = FUC

/**
 * @brief     link cfg_gpio_init function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to a cfg_gpio_init function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_CFG_GPIO_INIT(HANDLE, FUC)       (HANDLE)->cfg_gpio_init = FUC

/**
 * @brief     link cfg_gpio_deinit function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to a cfg_gpio_deinit function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_CFG_GPIO_DEINIT(HANDLE, FUC)     (HANDLE)->cfg_gpio_deinit = FUC

/**
 * @brief     link cfg_gpio_write function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to a cfg_gpio_write function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_CFG_GPIO_WRITE(HANDLE, FUC)      (HANDLE)->cfg_gpio_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_DELAY_MS(HANDLE, FUC)            (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a ch9121x handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_CH9121X_LINK_DEBUG_PRINT(HANDLE, FUC)         (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup ch9121x_base_driver ch9121x base driver function
 * @brief    ch9121x base driver modules
 * @ingroup  ch9121x_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a ch9121x info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ch9121x_info(ch9121x_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a ch9121x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 uart initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 reset gpio init failed
 *            - 5 cfg gpio init failed
 *            - 6 reset failed
 * @note      none
 */
uint8_t ch9121x_init(ch9121x_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a ch9121x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 uart deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 reset failed
 *            - 5 reset gpio deinit failed
 *            - 6 cfg gpio deinit failed
 * @note      none
 */
uint8_t ch9121x_deinit(ch9121x_handle_t *handle);

/**
 * @brief         read data
 * @param[in]     *handle pointer to a ch9121x handle structure
 * @param[out]    *buf pointer to a data buffer
 * @param[in,out] *len pointer to a length buffer
 * @return        status code
 *                - 0 success
 *                - 1 read failed
 *                - 2 handle is NULL
 *                - 3 handle is not initialized
 * @note          none
 */
uint8_t ch9121x_read(ch9121x_handle_t *handle, uint8_t *buf, uint16_t *len);

/**
 * @brief     write data
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] *buf pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_write(ch9121x_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @brief      get version
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[out] *version pointer to a version buffer
 * @return     status code
 *             - 0 success
 *             - 1 get version failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_version(ch9121x_handle_t *handle, uint8_t *version);

/**
 * @brief     reset the chip
 * @param[in] *handle pointer to a ch9121x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_reset(ch9121x_handle_t *handle);

/**
 * @brief     save to eeprom
 * @param[in] *handle pointer to a ch9121x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 save to eeprom failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_save_to_eeprom(ch9121x_handle_t *handle);

/**
 * @brief     config and reset the chip
 * @param[in] *handle pointer to a ch9121x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 config and reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_config_and_reset(ch9121x_handle_t *handle);

/**
 * @brief     exit
 * @param[in] *handle pointer to a ch9121x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 exit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_exit(ch9121x_handle_t *handle);

/**
 * @brief     enable or disable dhcp
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set dhcp failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_dhcp(ch9121x_handle_t *handle, ch9121x_bool_t enable);

/**
 * @brief      get dhcp status
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dhcp failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_dhcp(ch9121x_handle_t *handle, ch9121x_bool_t *enable);

/**
 * @brief     set mac address
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] *mac pointer to a mac buffer
 * @return    status code
 *            - 0 success
 *            - 1 set mac failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_mac(ch9121x_handle_t *handle, uint8_t mac[6]);

/**
 * @brief      get chip mac
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[out] *mac pointer to a mac buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mac failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_mac(ch9121x_handle_t *handle, uint8_t mac[6]);

/**
 * @brief     clear mac address
 * @param[in] *handle pointer to a ch9121x handle structure
 * @return    status code
 *            - 0 success
 *            - 1 clear mac failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_clear_mac(ch9121x_handle_t *handle);

/**
 * @brief     set ip address
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] *ip pointer to an ip buffer
 * @return    status code
 *            - 0 success
 *            - 1 set ip failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_ip(ch9121x_handle_t *handle, uint8_t ip[4]);

/**
 * @brief      get ip address
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[out] *ip pointer to an ip buffer
 * @return     status code
 *             - 0 success
 *             - 1 get ip failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_ip(ch9121x_handle_t *handle, uint8_t ip[4]);

/**
 * @brief     set subnet mask
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] *mask pointer to a mask buffer
 * @return    status code
 *            - 0 success
 *            - 1 set subnet mask failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_subnet_mask(ch9121x_handle_t *handle, uint8_t mask[4]);

/**
 * @brief      get subnet mask
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[out] *mask pointer to a mask buffer
 * @return     status code
 *             - 0 success
 *             - 1 get subnet mask failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_subnet_mask(ch9121x_handle_t *handle, uint8_t mask[4]);

/**
 * @brief     set gateway
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] *ip pointer to an ip buffer
 * @return    status code
 *            - 0 success
 *            - 1 set gateway failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_gateway(ch9121x_handle_t *handle, uint8_t ip[4]);

/**
 * @brief      get gateway
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[out] *ip pointer to an ip buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gateway failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_gateway(ch9121x_handle_t *handle, uint8_t ip[4]);

/**
 * @brief      get status
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  port input port
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_status(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_status_t *status);

/**
 * @brief     set mode
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] port input port
 * @param[in] mode chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_mode(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_mode_t mode);

/**
 * @brief      get mode
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  port input port
 * @param[out] *mode pointer to a mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_mode(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_mode_t *mode);

/**
 * @brief     set source port
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] port input port
 * @param[in] num source port
 * @return    status code
 *            - 0 success
 *            - 1 set source port failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_source_port(ch9121x_handle_t *handle, ch9121x_port_t port, uint16_t num);

/**
 * @brief      get source port
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  port input port
 * @param[out] *num pointer to a source port buffer
 * @return     status code
 *             - 0 success
 *             - 1 get source port failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_source_port(ch9121x_handle_t *handle, ch9121x_port_t port, uint16_t *num);

/**
 * @brief     set dest ip
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] port input port
 * @param[in] *ip pointer to an ip buffer
 * @return    status code
 *            - 0 success
 *            - 1 set dest ip failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_dest_ip(ch9121x_handle_t *handle, ch9121x_port_t port, uint8_t ip[4]);

/**
 * @brief      get dest ip
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  port input port
 * @param[out] *ip pointer to an ip buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dest ip failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_dest_ip(ch9121x_handle_t *handle, ch9121x_port_t port, uint8_t ip[4]);

/**
 * @brief     set dest port
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] port input port
 * @param[in] num dest port
 * @return    status code
 *            - 0 success
 *            - 1 set dest port failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_dest_port(ch9121x_handle_t *handle, ch9121x_port_t port, uint16_t num);

/**
 * @brief      get dest port
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  port input port
 * @param[out] *num pointer to a dest port buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dest port failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_dest_port(ch9121x_handle_t *handle, ch9121x_port_t port, uint16_t *num);

/**
 * @brief     set uart baud
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] port input port
 * @param[in] baud chip baud
 * @return    status code
 *            - 0 success
 *            - 1 set uart baud failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_uart_baud(ch9121x_handle_t *handle, ch9121x_port_t port, uint32_t baud);

/**
 * @brief      get uart baud
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  port input port
 * @param[out] *baud pointer to a baud buffer
 * @return     status code
 *             - 0 success
 *             - 1 get uart baud failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_uart_baud(ch9121x_handle_t *handle, ch9121x_port_t port, uint32_t *baud);

/**
 * @brief     set uart config
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] port input port
 * @param[in] data_bit uart data bit
 * @param[in] parity uart parity
 * @param[in] stop_bit uart stop bit
 * @return    status code
 *            - 0 success
 *            - 1 set uart config failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_uart_config(ch9121x_handle_t *handle, ch9121x_port_t port, uint8_t data_bit, ch9121x_parity_t parity, uint8_t stop_bit);

/**
 * @brief      get uart config
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  port input port
 * @param[out] *data_bit pointer to an uart data bit buffer
 * @param[out] *parity pointer to an uart parity buffer
 * @param[out] *stop_bit pointer to an uart stop bit buffer
 * @return     status code
 *             - 0 success
 *             - 1 get uart config failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_uart_config(ch9121x_handle_t *handle, ch9121x_port_t port, uint8_t *data_bit, ch9121x_parity_t *parity, uint8_t *stop_bit);

/**
 * @brief     set uart timeout
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] port input port
 * @param[in] timeout uart timeout
 * @return    status code
 *            - 0 success
 *            - 1 set uart timeout failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_uart_timeout(ch9121x_handle_t *handle, ch9121x_port_t port, uint8_t timeout);

/**
 * @brief      get uart timeout
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  port input port
 * @param[out] *timeout pointer to an uart timeout buffer
 * @return     status code
 *             - 0 success
 *             - 1 get uart timeout failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_uart_timeout(ch9121x_handle_t *handle, ch9121x_port_t port, uint8_t *timeout);

/**
 * @brief      convert the uart timeout to the register raw data
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  ms timeout
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_uart_timeout_convert_to_register(ch9121x_handle_t *handle, uint16_t ms, uint8_t *reg);

/**
 * @brief      convert the register raw data to the offset
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  reg register raw data
 * @param[out] *ms pointer to a ms buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_uart_timeout_convert_to_data(ch9121x_handle_t *handle, uint8_t reg, uint16_t *ms);

/**
 * @brief     enable or disable random source port number
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] port input port
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set source port random failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_source_port_random(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_bool_t enable);

/**
 * @brief      get random source port number status
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  port input port
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get source port random failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_source_port_random(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_bool_t *enable);

/**
 * @brief     set uart buffer length
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] port input port
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 set uart buffer length failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_uart_buffer_length(ch9121x_handle_t *handle, ch9121x_port_t port, uint32_t len);

/**
 * @brief      get uart buffer length
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  port input port
 * @param[out] *len pointer to a buffer length buffer
 * @return     status code
 *             - 0 success
 *             - 1 get uart buffer length failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_uart_buffer_length(ch9121x_handle_t *handle, ch9121x_port_t port, uint32_t *len);

/**
 * @brief     enable or disable uart auto flush
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] port input port
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set uart flush failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_uart_flush(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_bool_t enable);

/**
 * @brief      get uart auto flush status
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  port input port
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get uart flush failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_uart_flush(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_bool_t *enable);

/**
 * @brief     enable or disable uart port2
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set port2 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_port2(ch9121x_handle_t *handle, ch9121x_bool_t enable);

/**
 * @brief     enable or disable disconnect with no rj45
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set disconnect with no rj45 failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_disconnect_with_no_rj45(ch9121x_handle_t *handle, ch9121x_bool_t enable);

/**
 * @brief      get disconnect with no rj45 status
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get disconnect with no rj45 failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_disconnect_with_no_rj45(ch9121x_handle_t *handle, ch9121x_bool_t *enable);

/**
 * @brief     set chip domain
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] enable bool value
 * @param[in] *domain pointer to a domain buffer
 * @return    status code
 *            - 0 success
 *            - 1 set domain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 domain > 33
 * @note      none
 */
uint8_t ch9121x_set_domain(ch9121x_handle_t *handle, ch9121x_bool_t enable, char *domain);

/**
 * @brief     set eth cfg
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set eth cfg failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_eth_cfg(ch9121x_handle_t *handle, ch9121x_bool_t enable);

/**
 * @brief      get eth cfg
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get eth cfg failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_eth_cfg(ch9121x_handle_t *handle, ch9121x_bool_t *enable);

/**
 * @brief     set uart clock mode
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] mode uart clock mode
 * @return    status code
 *            - 0 success
 *            - 1 set uart clock mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_uart_clock_mode(ch9121x_handle_t *handle, ch9121x_uart_clock_mode_t mode);

/**
 * @brief      get uart clock mode
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[out] *mode pointer to an uart clock mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get uart clock mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_uart_clock_mode(ch9121x_handle_t *handle, ch9121x_uart_clock_mode_t *mode);

/**
 * @brief      get phy status
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get phy status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_phy_status(ch9121x_handle_t *handle, ch9121x_phy_status_t *status);

/**
 * @brief     set tcp retry mode
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] t time
 * @return    status code
 *            - 0 success
 *            - 1 set tcp retry mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 t > 1
 * @note      0 is 0.5s
 *            1 is 0.5s, 1s, ..., 3s, 3.5 step
 */
uint8_t ch9121x_set_tcp_retry_mode(ch9121x_handle_t *handle, uint8_t t);

/**
 * @brief      get tcp retry mode
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[out] *t pointer to a time buffer
 * @return     status code
 *             - 0 success
 *             - 1 get tcp retry mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_tcp_retry_mode(ch9121x_handle_t *handle, uint8_t *t);

/**
 * @brief     enable or disable flow control
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set flow control failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_flow_control(ch9121x_handle_t *handle, ch9121x_bool_t enable);

/**
 * @brief      get flow control status
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get flow control failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_get_flow_control(ch9121x_handle_t *handle, ch9121x_bool_t *enable);

/**
 * @brief     set arp retry
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] period input period
 * @param[in] times input times
 * @return    status code
 *            - 0 success
 *            - 1 set arp retry failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_arp_retry(ch9121x_handle_t *handle, uint8_t period, uint8_t times);

/**
 * @brief      convert the arp retry period to the register raw data
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  ms time in ms
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_arp_retry_period_convert_to_register(ch9121x_handle_t *handle, uint16_t ms, uint8_t *reg);

/**
 * @brief      convert the register raw data to the arp retry period
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  reg register raw data
 * @param[out] *ms pointer to a ms buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_arp_retry_period_convert_to_data(ch9121x_handle_t *handle, uint8_t reg, uint16_t *ms);

/**
 * @}
 */

/**
 * @defgroup ch9121x_extend_driver ch9121x extend driver function
 * @brief    ch9121x extend driver modules
 * @ingroup  ch9121x_driver
 * @{
 */

/**
 * @brief      set command
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  *param pointer to a param buffer
 * @param[in]  len param length
 * @param[out] *out pointer to an out buffer
 * @param[in]  out_len output length
 * @param[in]  pre_delay delay in ms
 * @param[in]  timeout timeout in ms
 * @return     status code
 *             - 0 success
 *             - 1 set command failed
 *             - 2 handle is NULL
 *             - 3 linked functions is NULL
 * @note       none
 */
uint8_t ch9121x_set_command(ch9121x_handle_t *handle,
                            uint8_t *param, uint16_t len,
                            uint8_t *out, uint16_t out_len,
                            uint16_t pre_delay, uint16_t timeout);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
