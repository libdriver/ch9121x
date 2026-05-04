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
 * @file      driver_ch9121x.c
 * @brief     driver ch9121x source file
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

#include "driver_ch9121x.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "WCH CH9121X"       /**< chip name */
#define MANUFACTURER_NAME         "WCH"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        3.2f                /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.4f                /**< chip max supply voltage */
#define MAX_CURRENT               76.2f               /**< chip max current */
#define TEMPERATURE_MIN           -40.0f              /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f               /**< chip max operating temperature */
#define DRIVER_VERSION            1000                /**< driver version */

/**
 * @brief chip basic command definition
 */
#define CH9121X_CMD_CHIP_VERSION                 0x01        /**< get chip version command */
#define CH9121X_CMD_RESET                        0x02        /**< reset chip command */
#define CH9121X_CMD_SAVE_TO_EEPROM               0x0D        /**< save to eeprom command */
#define CH9121X_CMD_RUN_AND_RESET                0x0E        /**< run the config and reset command */
#define CH9121X_CMD_EXIT                         0x5E        /**< exit command */
#define CH9121X_CMD_DHCP                         0x33        /**< dhcp command */
#define CH9121X_CMD_MAC                          0x81        /**< mac command */
#define CH9121X_CMD_SET_IP                       0x11        /**< set ip command */
#define CH9121X_CMD_SET_NETMASK                  0x12        /**< set netmask command */
#define CH9121X_CMD_SET_GATEWAY                  0x13        /**< set gateway command */
#define CH9121X_CMD_GET_IP                       0x61        /**< get ip command */
#define CH9121X_CMD_GET_NETMASK                  0x62        /**< get netmask command */
#define CH9121X_CMD_GET_GATEWAY                  0x63        /**< get gateway command */
#define CH9121X_CMD_DISCONNECT                   0x24        /**< set disconnect command */
#define CH9121X_CMD_SET_MAC_ADDR                 0x31        /**< set mac address command */
#define CH9121X_CMD_CLEAR_MAC_ADDR               0x51        /**< clear mac address command */
#define CH9121X_CMD_SET_ETH_CFG_ENABLE           0x52        /**< set eth cfg enable command */
#define CH9121X_CMD_GET_ETH_CFG_STATUS           0x53        /**< get eth cfg enable command */
#define CH9121X_CMD_SET_UART_CLOCK_MODE          0x54        /**< set uart clock mode command */
#define CH9121X_CMD_GET_UART_CLOCK_MODE          0x55        /**< get uart clock mode command */
#define CH9121X_CMD_GET_PHY_STATUS               0x69        /**< get phy status command */
#define CH9121X_CMD_GET_PORT1_2_LINKDOWN         0x74        /**< get port 1 and 2 linkdown command */
#define CH9121X_CMD_GET_DHCP_ENABLE              0x83        /**< get dhcp enable command */

/**
 * @brief chip port command definition
 */
#define CH9121X_CMD_PORT1_GET_STATUS             0x03        /**< check port1 status command */
#define CH9121X_CMD_PORT1_SET_MODE               0x10        /**< set port1 mode command */
#define CH9121X_CMD_PORT1_SET_PORT               0x14        /**< set port1 port command */
#define CH9121X_CMD_PORT1_SET_DST_IP             0x15        /**< set port1 dest ip command */
#define CH9121X_CMD_PORT1_SET_DST_PORT           0x16        /**< set port1 dest port command */
#define CH9121X_CMD_PORT1_SET_BAUD               0x21        /**< set port1 baud command */
#define CH9121X_CMD_PORT1_SET_CONFIG             0x22        /**< set port1 config command */
#define CH9121X_CMD_PORT1_SET_TIMEOUT            0x23        /**< set port1 timeout command */
#define CH9121X_CMD_PORT1_GET_MODE               0x60        /**< get port1 mode command */
#define CH9121X_CMD_PORT1_GET_PORT               0x64        /**< get port1 port command */
#define CH9121X_CMD_PORT1_GET_DST_IP             0x65        /**< get port1 dest ip command */
#define CH9121X_CMD_PORT1_GET_DST_PORT           0x66        /**< get port1 dest port command */
#define CH9121X_CMD_PORT1_GET_BAUD               0x71        /**< get port1 baud command */
#define CH9121X_CMD_PORT1_GET_CONFIG             0x72        /**< get port1 config command */
#define CH9121X_CMD_PORT1_GET_TIMEOUT            0x73        /**< get port1 timeout command */
#define CH9121X_CMD_PORT1_GET_RANDOM             0x67        /**< get port1 random command */
#define CH9121X_CMD_PORT1_GET_UART_PACK_LEN      0x75        /**< get port1 uart pack len command */
#define CH9121X_CMD_PORT1_GET_EMPTY              0x76        /**< get port1 empty command */
#define CH9121X_CMD_PORT2_GET_STATUS             0x04        /**< check port2 status command */
#define CH9121X_CMD_PORT2_SET_MODE               0x40        /**< set port2 mode command */
#define CH9121X_CMD_PORT2_SET_PORT               0x41        /**< set port2 port command */
#define CH9121X_CMD_PORT2_SET_DST_IP             0x42        /**< set port2 dest ip command */
#define CH9121X_CMD_PORT2_SET_DST_PORT           0x43        /**< set port2 dest port command */
#define CH9121X_CMD_PORT2_SET_BAUD               0x44        /**< set port2 baud command */
#define CH9121X_CMD_PORT2_SET_CONFIG             0x45        /**< set port2 config command */
#define CH9121X_CMD_PORT2_SET_TIMEOUT            0x46        /**< set port2 timeout command */
#define CH9121X_CMD_PORT2_GET_MODE               0x90        /**< get port2 mode command */
#define CH9121X_CMD_PORT2_GET_PORT               0x91        /**< get port2 port command */
#define CH9121X_CMD_PORT2_GET_DST_IP             0x92        /**< get port2 dest ip command */
#define CH9121X_CMD_PORT2_GET_DST_PORT           0x93        /**< get port2 dest port command */
#define CH9121X_CMD_PORT2_GET_BAUD               0x94        /**< get port2 baud command */
#define CH9121X_CMD_PORT2_GET_CONFIG             0x95        /**< get port2 config command */
#define CH9121X_CMD_PORT2_GET_TIMEOUT            0x96        /**< get port2 timeout command */
#define CH9121X_CMD_PORT2_GET_RANDOM             0x97        /**< get port2 random command */
#define CH9121X_CMD_PORT2_GET_UART_PACK_LEN      0x98        /**< get port2 uart pack len command */
#define CH9121X_CMD_PORT2_GET_EMPTY              0x99        /**< get port2 empty command */

/**
 * @brief chip port extern command definition
 */
#define CH9121X_CMD_PORT1_RANDOM_PORT            0x17        /**< set port1 random port command */
#define CH9121X_CMD_PORT1_LEN                    0x25        /**< set port1 package length command */
#define CH9121X_CMD_PORT1_FLUSH                  0x26        /**< set port1 flush command */
#define CH9121X_CMD_PORT1_DOMAIN                 0x34        /**< set port1 domain command */
#define CH9121X_CMD_PORT2_ENABLE                 0x39        /**< enable port2 command */
#define CH9121X_CMD_PORT2_RANDOM_PORT            0x47        /**< set port2 random port command */
#define CH9121X_CMD_PORT2_LEN                    0x48        /**< set port2 package length command */
#define CH9121X_CMD_PORT2_FLUSH                  0x49        /**< set port2 flush command */

/**
 * @brief chip port two bytes extern command definition
 */
#define CH9121X_CMD2_SET_TCP_RETRY_MODE          0xA104U     /**< set tcp retry mode command */
#define CH9121X_CMD2_FLOW_CONTROL_ENABLE         0xA107U     /**< flow control enable command */
#define CH9121X_CMD2_SET_ARP_RETRY               0xA108U     /**< set arp retry command */
#define CH9121X_CMD2_GET_TCP_RETRY_MODE          0xA204U     /**< get tcp retry mode command */
#define CH9121X_CMD2_GET_FLOW_CONTROL_ENABLE     0xA207U     /**< get flow control enable command */

/**
 * @brief     write and check
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] *param pointer to a param buffer
 * @param[in] len param length
 * @param[in] pre_delay delay in ms
 * @param[in] timeout timeout in ms
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 len is invalid
 *            - 3 error
 *            - 4 timeout
 * @note      none
 */
static uint8_t a_ch9121x_write_check(ch9121x_handle_t *handle,
                                     uint8_t *param, uint16_t len,
                                     uint16_t pre_delay, uint16_t timeout)
{
    uint16_t t;
    uint8_t res;
    
    if (len > 126)                                            /* check length */
    {
        handle->debug_print("ch9121x: len is invalid.\n");    /* len is invalid */
        
        return 2;                                             /* return error */
    }
    
    handle->buf[0] = 0x57;                                    /* set header 0 */
    handle->buf[1] = 0xAB;                                    /* set header 1 */
    memcpy(&handle->buf[2], param, len);                      /* copy param */
    res = handle->cfg_gpio_write(0);                          /* set low */
    if (res != 0)                                             /* check result */
    {
        return 1;                                             /* return error */
    }
    res = handle->uart_flush();                               /* uart flush */
    if (res != 0)                                             /* check result */
    {
        return 1;                                             /* return error */
    }
    if (handle->uart_write(handle->buf, 2 + len) != 0)        /* write command */
    {
        handle->debug_print("ch9121x: write failed.\n");      /* write failed */
        (void)handle->cfg_gpio_write(1);                      /* set high */
        
        return 1;                                             /* return error */
    }
    if (pre_delay != 0)                                       /* check pre_delay */
    {
        handle->delay_ms(pre_delay);                          /* delay pre_delay */
    }
    
    t = timeout / 10;                                         /* 10ms */
    while (t != 0)                                            /* check timeout */
    {
        if (handle->uart_read(&res, 1) == 1)                  /* read data */
        {
            if (res == 0xAA)                                  /* check 0xAA */
            {
                res = handle->cfg_gpio_write(1);              /* set high */
                if (res != 0)                                 /* check result */
                {
                    return 1;                                 /* return error */
                }
                
                return 0;                                     /* success return 0 */
            }
            else
            {
                handle->debug_print("ch9121x: error.\n");     /* error */
                (void)handle->cfg_gpio_write(1);              /* set high */
                
                return 3;                                     /* return error */
            }
        }
        handle->delay_ms(10);                                 /* delay 10ms */
        t--;                                                  /* timeout-- */
    }
    
    handle->debug_print("ch9121x: timeout.\n");               /* timeout */
    (void)handle->cfg_gpio_write(1);                          /* set high */
    
    return 4;                                                 /* return error */
}

/**
 * @brief      write and read
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  *param pointer to a param buffer
 * @param[in]  len param length
 * @param[out] *out pointer to an out buffer
 * @param[in]  out_len output length
 * @param[in]  pre_delay delay in ms
 * @param[in]  timeout timeout in ms
 * @return     status code
 *             - 0 success
 *             - 1 write failed
 *             - 2 len is invalid
 *             - 3 timeout
 * @note       none
 */
static uint8_t a_ch9121x_write_read(ch9121x_handle_t *handle,
                                    uint8_t *param, uint16_t len,
                                    uint8_t *out, uint16_t out_len,
                                    uint16_t pre_delay, uint16_t timeout)
{
    uint8_t res;
    uint16_t t;
    uint16_t point;
    
    if (len > 126)                                            /* check length */
    {
        handle->debug_print("ch9121x: len is invalid.\n");    /* len is invalid */
        
        return 2;                                             /* return error */
    }
    
    handle->buf[0] = 0x57;                                    /* set header 0 */
    handle->buf[1] = 0xAB;                                    /* set header 1 */
    memcpy(&handle->buf[2], param, len);                      /* copy param */
    res = handle->cfg_gpio_write(0);                          /* set low */
    if (res != 0)                                             /* check result */
    {
        return 1;                                             /* return error */
    }
    res = handle->uart_flush();                               /* uart flush */
    if (res != 0)                                             /* check result */
    {
        return 1;                                             /* return error */
    }
    if (handle->uart_write(handle->buf, 2 + len) != 0)        /* write command */
    {
        handle->debug_print("ch9121x: write failed.\n");      /* write failed */
        (void)handle->cfg_gpio_write(1);                      /* set high */
        
        return 1;                                             /* return error */
    }
    if (pre_delay != 0)                                       /* check pre_delay */
    {
        handle->delay_ms(pre_delay);                          /* delay pre_delay */
    }
    
    point = 0;                                                /* init 0 */
    t = timeout / 10;                                         /* 10ms */
    while (t != 0)                                            /* check timeout */
    {
        uint16_t l;
        
        l = handle->uart_read(&out[point], out_len - point);  /* read data */
        if (l != 0)
        {
            point += l;                                       /* point += l*/
            if (point >= out_len)                             /* check length */
            {
                res = handle->cfg_gpio_write(1);              /* set high */
                if (res != 0)                                 /* check result */
                {
                    return 1;                                 /* return error */
                }
                
                return 0;                                     /* success return 0 */
            }
        }
        handle->delay_ms(10);                                 /* delay 10ms */
        t--;                                                  /* timeout-- */
    }
    
    handle->debug_print("ch9121x: timeout.\n");               /* timeout */
    (void)handle->cfg_gpio_write(1);                          /* set high */
    
    return 3;                                                 /* return error */
}

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
uint8_t ch9121x_get_version(ch9121x_handle_t *handle, uint8_t *version)
{
    uint8_t cmd;
    
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    cmd = CH9121X_CMD_CHIP_VERSION;                                 /* set chip version */
    if (a_ch9121x_write_read(handle, &cmd, 1, version, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)    /* get version */
    {
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t ch9121x_reset(ch9121x_handle_t *handle)
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121X_CMD_RESET;                                          /* set reset */
    if (a_ch9121x_write_check(handle, &cmd, 1,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)     /* reset */
    {
        return 1;                                                     /* return error */
    }
    handle->delay_ms(1000);                                           /* delay 1000ms */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_save_to_eeprom(ch9121x_handle_t *handle)
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121X_CMD_SAVE_TO_EEPROM;                                 /* set save to eeprom */
    if (a_ch9121x_write_check(handle, &cmd, 1,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)     /* save to eeprom */
    {
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_config_and_reset(ch9121x_handle_t *handle)
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121X_CMD_RUN_AND_RESET;                                  /* set run config reset */
    if (a_ch9121x_write_check(handle, &cmd, 1,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)     /* run config reset */
    {
        return 1;                                                     /* return error */
    }
    handle->delay_ms(1000);                                           /* delay 1000ms */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_exit(ch9121x_handle_t *handle)
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121X_CMD_EXIT;                                           /* set exit */
    if (a_ch9121x_write_check(handle, &cmd, 1,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)     /* exit */
    {
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_set_dhcp(ch9121x_handle_t *handle, ch9121x_bool_t enable)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd[0] = CH9121X_CMD_DHCP;                                       /* set dhcp */
    cmd[1] = enable;                                                 /* set bool */
    if (a_ch9121x_write_check(handle, cmd, 2,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* dhcp */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_get_mac(ch9121x_handle_t *handle, uint8_t mac[6])
{
    uint8_t cmd;
    
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    cmd = CH9121X_CMD_MAC;                                          /* set mac */
    if (a_ch9121x_write_read(handle, &cmd, 1, mac, 6,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)    /* mac*/
    {
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t ch9121x_get_status(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_status_t *status)
{
    uint8_t cmd;
    uint8_t param;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121X_PORT1)                                        /* port1 */
    {
        cmd = CH9121X_CMD_PORT1_GET_STATUS;                           /* get port1 status */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121X_CMD_PORT2_GET_STATUS;                           /* get port2 status */
    }
    if (a_ch9121x_write_read(handle, &cmd, 1, &param, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get status */
    {
        return 1;                                                     /* return error */
    }
    *status = (ch9121x_status_t)(param);                              /* get the status */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_set_mode(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_mode_t mode)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121X_PORT1)                                       /* port1 */
    {
        cmd[0] = CH9121X_CMD_PORT1_SET_MODE;                         /* set port1 mode */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121X_CMD_PORT2_SET_MODE;                         /* set port2 mode */
    }
    cmd[1] = mode;                                                   /* set mode */
    if (a_ch9121x_write_check(handle, cmd, 2,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write mode */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_get_mode(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_mode_t *mode)
{
    uint8_t cmd;
    uint8_t param;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121X_PORT1)                                        /* port1 */
    {
        cmd = CH9121X_CMD_PORT1_GET_MODE;                             /* get port1 mode */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121X_CMD_PORT2_GET_MODE;                             /* get port2 mode */
    }
    if (a_ch9121x_write_read(handle, &cmd, 1, &param, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get mode */
    {
        return 1;                                                     /* return error */
    }
    *mode = (ch9121x_mode_t)(param);                                  /* get mode */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_set_ip(ch9121x_handle_t *handle, uint8_t ip[4])
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd[0] = CH9121X_CMD_SET_IP;                                     /* set ip */
    cmd[1] = ip[0];                                                  /* set ip[0] */
    cmd[2] = ip[1];                                                  /* set ip[1] */
    cmd[3] = ip[2];                                                  /* set ip[2] */
    cmd[4] = ip[3];                                                  /* set ip[3] */
    if (a_ch9121x_write_check(handle, cmd, 5,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write ip */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_get_ip(ch9121x_handle_t *handle, uint8_t ip[4])
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121X_CMD_GET_IP;                                         /* get ip */
    if (a_ch9121x_write_read(handle, &cmd, 1, ip, 4,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* read ip */
    {
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_set_subnet_mask(ch9121x_handle_t *handle, uint8_t mask[4])
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd[0] = CH9121X_CMD_SET_NETMASK ;                               /* set sub mask  */
    cmd[1] = mask[0];                                                /* set mask[0] */
    cmd[2] = mask[1];                                                /* set mask[1] */
    cmd[3] = mask[2];                                                /* set mask[2] */
    cmd[4] = mask[3];                                                /* set mask[3] */
    if (a_ch9121x_write_check(handle, cmd, 5,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write subnet mask */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_get_subnet_mask(ch9121x_handle_t *handle, uint8_t mask[4])
{
    uint8_t cmd;
    
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    cmd = CH9121X_CMD_GET_NETMASK ;                                 /* get mask */
    if (a_ch9121x_write_read(handle, &cmd, 1, mask, 4,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)    /* read subnet mask */
    {
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t ch9121x_set_gateway(ch9121x_handle_t *handle, uint8_t ip[4])
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd[0] = CH9121X_CMD_SET_GATEWAY ;                               /* set gateway  */
    cmd[1] = ip[0];                                                  /* set ip[0] */
    cmd[2] = ip[1];                                                  /* set ip[1] */
    cmd[3] = ip[2];                                                  /* set ip[2] */
    cmd[4] = ip[3];                                                  /* set ip[3] */
    if (a_ch9121x_write_check(handle, cmd, 5,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write ip */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_get_gateway(ch9121x_handle_t *handle, uint8_t ip[4])
{
    uint8_t cmd;
    
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    cmd = CH9121X_CMD_GET_GATEWAY;                                  /* get gateway */
    if (a_ch9121x_write_read(handle, &cmd, 1, ip, 4,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)    /* read gateway */
    {
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t ch9121x_set_source_port(ch9121x_handle_t *handle, ch9121x_port_t port, uint16_t num)
{
    uint8_t cmd[3];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121X_PORT1)                                       /* port1 */
    {
        cmd[0] = CH9121X_CMD_PORT1_SET_PORT;                         /* set port1 port */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121X_CMD_PORT2_SET_PORT;                         /* set port2 port */
    }
    cmd[1] = (num >> 0) & 0xFF;                                      /* set port msb */
    cmd[2] = (num >> 8) & 0xFF;                                      /* set port lsb */
    if (a_ch9121x_write_check(handle, cmd, 3,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write port */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_get_source_port(ch9121x_handle_t *handle, ch9121x_port_t port, uint16_t *num)
{
    uint8_t cmd;
    uint8_t buf[2];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121X_PORT1)                                        /* port1 */
    {
        cmd = CH9121X_CMD_PORT1_GET_PORT;                             /* get port1 port */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121X_CMD_PORT2_GET_PORT;                             /* get port2 port */
    }
    if (a_ch9121x_write_read(handle, &cmd, 1, buf, 2,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get port */
    {
        return 1;                                                     /* return error */
    }
    *num= (uint16_t)((uint16_t)buf[1] << 8 | buf[0]);                 /* get port */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_set_dest_ip(ch9121x_handle_t *handle, ch9121x_port_t port, uint8_t ip[4])
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121X_PORT1)                                       /* port1 */
    {
        cmd[0] = CH9121X_CMD_PORT1_SET_DST_IP;                       /* set port1 dest ip */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121X_CMD_PORT2_SET_DST_IP;                       /* set port2 dest ip */
    }
    cmd[1] = ip[0];                                                  /* set ip[0] */
    cmd[2] = ip[1];                                                  /* set ip[1] */
    cmd[3] = ip[2];                                                  /* set ip[0] */
    cmd[4] = ip[3];                                                  /* set ip[1] */
    if (a_ch9121x_write_check(handle, cmd, 5,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write dest ip */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_get_dest_ip(ch9121x_handle_t *handle, ch9121x_port_t port, uint8_t ip[4])
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121X_PORT1)                                        /* port1 */
    {
        cmd = CH9121X_CMD_PORT1_GET_DST_IP;                           /* get port1 dest ip */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121X_CMD_PORT2_GET_DST_IP;                           /* get port2 dest ip */
    }
    if (a_ch9121x_write_read(handle, &cmd, 1, ip, 4,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get dest ip */
    {
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_set_dest_port(ch9121x_handle_t *handle, ch9121x_port_t port, uint16_t num)
{
    uint8_t cmd[3];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121X_PORT1)                                       /* port1 */
    {
        cmd[0] = CH9121X_CMD_PORT1_SET_DST_PORT;                     /* set port1 dest port */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121X_CMD_PORT2_SET_DST_PORT;                     /* set port2 dest port */
    }
    cmd[1] = (num >> 0) & 0xFF;                                      /* set port msb */
    cmd[2] = (num >> 8) & 0xFF;                                      /* set port lsb */
    if (a_ch9121x_write_check(handle, cmd, 3,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write dest port */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_get_dest_port(ch9121x_handle_t *handle, ch9121x_port_t port, uint16_t *num)
{
    uint8_t cmd;
    uint8_t buf[2];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121X_PORT1)                                        /* port1 */
    {
        cmd = CH9121X_CMD_PORT1_GET_DST_PORT;                         /* get port1 dest port */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121X_CMD_PORT2_GET_DST_PORT;                         /* get port2 dest port */
    }
    if (a_ch9121x_write_read(handle, &cmd, 1, buf, 2,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get dest port */
    {
        return 1;                                                     /* return error */
    }
    *num= (uint16_t)((uint16_t)buf[1] << 8 | buf[0]);                 /* get port */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_set_uart_baud(ch9121x_handle_t *handle, ch9121x_port_t port, uint32_t baud)
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121X_PORT1)                                       /* port1 */
    {
        cmd[0] = CH9121X_CMD_PORT1_SET_BAUD;                         /* set port1 baud */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121X_CMD_PORT2_SET_BAUD;                         /* set port2 baud */
    }
    cmd[1] = (baud >> 0) & 0xFF;                                     /* set baud[0] */
    cmd[2] = (baud >> 8) & 0xFF;                                     /* set baud[8] */
    cmd[3] = (baud >> 16) & 0xFF;                                    /* set baud[16] */
    cmd[4] = (baud >> 24) & 0xFF;                                    /* set baud[24] */
    if (a_ch9121x_write_check(handle, cmd, 5,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write dest port */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_get_uart_baud(ch9121x_handle_t *handle, ch9121x_port_t port, uint32_t *baud)
{
    uint8_t cmd;
    uint8_t buf[4];
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->inited != 1)                                                 /* check handle initialization */
    {
        return 3;                                                            /* return error */
    }
    
    if (port == CH9121X_PORT1)                                               /* port1 */
    {
        cmd = CH9121X_CMD_PORT1_GET_BAUD;                                    /* get port1 baud */
    }
    else                                                                     /* port2 */
    {
        cmd = CH9121X_CMD_PORT2_GET_BAUD;                                    /* get port2 baud */
    }
    if (a_ch9121x_write_read(handle, &cmd, 1, buf, 4,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)             /* get dest port */
    {
        return 1;                                                            /* return error */
    }
    *baud = (uint32_t)(((uint32_t)buf[0] << 0) | ((uint32_t)buf[1] << 8) |
            ((uint32_t)buf[2] << 16) | ((uint32_t)buf[3] << 24));            /* get baud */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t ch9121x_set_uart_config(ch9121x_handle_t *handle, ch9121x_port_t port, uint8_t data_bit, ch9121x_parity_t parity, uint8_t stop_bit)
{
    uint8_t cmd[4];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121X_PORT1)                                       /* port1 */
    {
        cmd[0] = CH9121X_CMD_PORT1_SET_CONFIG;                       /* set port1 config */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121X_CMD_PORT2_SET_CONFIG;                       /* set port2 config */
    }
    cmd[1] = stop_bit;                                               /* set stop bit */
    cmd[2] = parity;                                                 /* set parity */
    cmd[3] = data_bit;                                               /* set data bit */
    if (a_ch9121x_write_check(handle, cmd, 4,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write dest port */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_get_uart_config(ch9121x_handle_t *handle, ch9121x_port_t port, uint8_t *data_bit, ch9121x_parity_t *parity, uint8_t *stop_bit)
{
    uint8_t cmd;
    uint8_t buf[3];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121X_PORT1)                                        /* port1 */
    {
        cmd = CH9121X_CMD_PORT1_GET_CONFIG;                           /* get port1 config */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121X_CMD_PORT2_GET_CONFIG;                           /* get port2 config */
    }
    if (a_ch9121x_write_read(handle, &cmd, 1, buf, 3,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get dest port */
    {
        return 1;                                                     /* return error */
    }
    *stop_bit = buf[0];                                               /* get stop bit */
    *parity = (ch9121x_parity_t)buf[1];                               /* get parity */
    *data_bit = buf[2];                                               /* get data bit */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_set_uart_timeout(ch9121x_handle_t *handle, ch9121x_port_t port, uint8_t timeout)
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121X_PORT1)                                       /* port1 */
    {
        cmd[0] = CH9121X_CMD_PORT1_SET_TIMEOUT;                      /* set port1 timeout */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121X_CMD_PORT2_SET_TIMEOUT;                      /* set port2 timeout */
    }
    cmd[1] = timeout;                                                /* set timeout */
    cmd[2] = 0x00;                                                   /* set 0x00 */
    cmd[3] = 0x00;                                                   /* set 0x00 */
    cmd[4] = 0x00;                                                   /* set 0x00 */
    if (a_ch9121x_write_check(handle, cmd, 5,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write uart timeout */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_get_uart_timeout(ch9121x_handle_t *handle, ch9121x_port_t port, uint8_t *timeout)
{
    uint8_t cmd;
    
    if (handle == NULL)                                           /* check handle */
    {
        return 2;                                                 /* return error */
    }
    if (handle->inited != 1)                                      /* check handle initialization */
    {
        return 3;                                                 /* return error */
    }
    
    if (port == CH9121X_PORT1)                                    /* port1 */
    {
        cmd = CH9121X_CMD_PORT1_GET_TIMEOUT;                      /* get port1 timeout */
    }
    else                                                          /* port2 */
    {
        cmd = CH9121X_CMD_PORT2_GET_TIMEOUT;                      /* get port2 timeout */
    }
    if (a_ch9121x_write_read(handle, &cmd, 1, timeout, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)  /* get uart timeout */
    {
        return 1;                                                 /* return error */
    }
    
    return 0;                                                     /* success return 0 */
}

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
uint8_t ch9121x_uart_timeout_convert_to_register(ch9121x_handle_t *handle, uint16_t ms, uint8_t *reg)
{
    if (handle == NULL)              /* check handle */
    {
        return 2;                    /* return error */
    }
    if (handle->inited != 1)         /* check handle initialization */
    {
        return 3;                    /* return error */
    }
    
    *reg = (uint8_t)(ms / 5);        /* convert real data to register data */
    
    return 0;                        /* success return 0 */
}

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
uint8_t ch9121x_uart_timeout_convert_to_data(ch9121x_handle_t *handle, uint8_t reg, uint16_t *ms)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    *ms = reg * 5;                  /* convert raw data to real data */
    
    return 0;                       /* success return 0 */
}

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
uint8_t ch9121x_set_source_port_random(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_bool_t enable)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121X_PORT1)                                       /* port1 */
    {
        cmd[0] = CH9121X_CMD_PORT1_RANDOM_PORT;                      /* set port1 random */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121X_CMD_PORT2_RANDOM_PORT ;                     /* set port2 random */
    }
    cmd[1] = enable;                                                 /* set bool */
    if (a_ch9121x_write_check(handle, cmd, 2,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write source port random */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_set_uart_buffer_length(ch9121x_handle_t *handle, ch9121x_port_t port, uint32_t len)
{
    uint8_t cmd[5];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121X_PORT1)                                       /* port1 */
    {
        cmd[0] = CH9121X_CMD_PORT1_LEN;                              /* set port1 uart buffer */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121X_CMD_PORT2_LEN ;                             /* set port2 uart buffer */
    }
    cmd[1] = (len >> 0) & 0xFF;                                      /* set len[0] */
    cmd[2] = (len >> 8) & 0xFF;                                      /* set len[8] */
    cmd[3] = (len >> 16) & 0xFF;                                     /* set len[16] */
    cmd[4] = (len >> 24) & 0xFF;                                     /* set len[24] */
    if (a_ch9121x_write_check(handle, cmd, 5,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write uart buffer */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_set_uart_flush(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_bool_t enable)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (port == CH9121X_PORT1)                                       /* port1 */
    {
        cmd[0] = CH9121X_CMD_PORT1_FLUSH;                            /* set port1 flush */
    }
    else                                                             /* port2 */
    {
        cmd[0] = CH9121X_CMD_PORT2_FLUSH ;                           /* set port2 flush */
    }
    cmd[1] = enable;                                                 /* set bool */
    if (a_ch9121x_write_check(handle, cmd, 2,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write flush */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_set_port2(ch9121x_handle_t *handle, ch9121x_bool_t enable)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd[0] = CH9121X_CMD_PORT2_ENABLE;                               /* enable port2 */
    cmd[1] = enable;                                                 /* set bool */
    if (a_ch9121x_write_check(handle, cmd, 2,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write enable */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_set_disconnect_with_no_rj45(ch9121x_handle_t *handle, ch9121x_bool_t enable)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    cmd[0] = CH9121X_CMD_DISCONNECT;                                 /* set disconnect */
    cmd[1] = enable;                                                 /* set bool */
    if (a_ch9121x_write_check(handle, cmd, 2,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)    /* write disconnect */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief     set chip domain
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] *domain pointer to a domain buffer
 * @return    status code
 *            - 0 success
 *            - 1 set domain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ch9121x_set_domain(ch9121x_handle_t *handle, char *domain)
{
    uint8_t cmd[29];
    
    if (handle == NULL)                                            /* check handle */
    {
        return 2;                                                  /* return error */
    }
    if (handle->inited != 1)                                       /* check handle initialization */
    {
        return 3;                                                  /* return error */
    }
    if (strlen(domain) > 28)                                       /* check domain */
    {
        handle->debug_print("ch9121x: domain > 28.\n");            /* domain > 28 */
        
        return 4;                                                  /* return error */
    }
    
    cmd[0] = CH9121X_CMD_PORT1_DOMAIN ;                            /* set domain */
    memcpy(&cmd[1], (uint8_t *)domain, strlen(domain));
    if (a_ch9121x_write_check(handle, cmd,
                             (uint16_t)(strlen(domain) + 1),
                              CH9121X_UART_PRE_DELAY, 1000) != 0)  /* write domain */
    {
        return 1;                                                  /* return error */
    }
    
    return 0;                                                      /* success return 0 */
}

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
uint8_t ch9121x_set_mac(ch9121x_handle_t *handle, uint8_t mac[6])
{
    uint8_t cmd[7];
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    cmd[0] = CH9121X_CMD_SET_MAC_ADDR;                                   /* set mac address */
    cmd[1] = mac[0];                                                     /* set mac 0 */
    cmd[2] = mac[1];                                                     /* set mac 1 */
    cmd[3] = mac[2];                                                     /* set mac 2 */
    cmd[4] = mac[3];                                                     /* set mac 3 */
    cmd[5] = mac[4];                                                     /* set mac 4 */
    cmd[6] = mac[5];                                                     /* set mac 5 */
    if (a_ch9121x_write_check(handle, cmd, 7,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)        /* write command */
    {
        return 1;                                                        /* return error */
    }
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t ch9121x_clear_mac(ch9121x_handle_t *handle)
{
    uint8_t cmd[1];
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    cmd[0] = CH9121X_CMD_CLEAR_MAC_ADDR;                                 /* clear mac address */
    if (a_ch9121x_write_check(handle, cmd, 1,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)        /* write command */
    {
        return 1;                                                        /* return error */
    }
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t ch9121x_set_eth_cfg(ch9121x_handle_t *handle, ch9121x_bool_t enable)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    cmd[0] = CH9121X_CMD_SET_ETH_CFG_ENABLE;                             /* set eth cfg enable */
    cmd[1] = (uint8_t)enable;                                            /* bool value */
    if (a_ch9121x_write_check(handle, cmd, 2,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)        /* write command */
    {
        return 1;                                                        /* return error */
    }
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t ch9121x_get_eth_cfg(ch9121x_handle_t *handle, ch9121x_bool_t *enable)
{
    uint8_t cmd;
    uint8_t buf[1];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121X_CMD_GET_ETH_CFG_STATUS;                             /* get eth cfg enable */
    if (a_ch9121x_write_read(handle, &cmd, 1, buf, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get data */
    {
        return 1;                                                     /* return error */
    }
    *enable = (ch9121x_bool_t)buf[0];                                 /* set bool value */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_set_uart_clock_mode(ch9121x_handle_t *handle, ch9121x_uart_clock_mode_t mode)
{
    uint8_t cmd[2];
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    cmd[0] = CH9121X_CMD_SET_UART_CLOCK_MODE;                            /* set uart clock mode */
    cmd[1] = (uint8_t)mode;                                              /* set mode */
    if (a_ch9121x_write_check(handle, cmd, 2,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)        /* write command */
    {
        return 1;                                                        /* return error */
    }
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t ch9121x_get_uart_clock_mode(ch9121x_handle_t *handle, ch9121x_uart_clock_mode_t *mode)
{
    uint8_t cmd;
    uint8_t buf[1];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121X_CMD_GET_UART_CLOCK_MODE;                            /* get uart clock mode */
    if (a_ch9121x_write_read(handle, &cmd, 1, buf, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get data */
    {
        return 1;                                                     /* return error */
    }
    *mode = (ch9121x_uart_clock_mode_t)buf[0];                        /* set mode */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_get_source_port_random(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_bool_t *enable)
{
    uint8_t cmd;
    uint8_t buf[1];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121X_PORT1)                                        /* port1 */
    {
        cmd = CH9121X_CMD_PORT1_GET_RANDOM;                           /* get port1 random */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121X_CMD_PORT2_GET_RANDOM;                           /* get port2 random */
    }
    if (a_ch9121x_write_read(handle, &cmd, 1, buf, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get data */
    {
        return 1;                                                     /* return error */
    }
    *enable = (ch9121x_bool_t)buf[0];                                 /* set bool value */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_get_phy_status(ch9121x_handle_t *handle, ch9121x_phy_status_t *status)
{
    uint8_t cmd;
    uint8_t buf[1];
    
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->inited != 1)                                                /* check handle initialization */
    {
        return 3;                                                           /* return error */
    }
    
    cmd = CH9121X_CMD_GET_PHY_STATUS;                                       /* get phy status */
    if (a_ch9121x_write_read(handle, &cmd, 1, buf, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)            /* get data */
    {
        return 1;                                                           /* return error */
    }
    if (buf[0] == (uint8_t)CH9121X_PHY_STATUS_DISCONNECTED)                 /* disconnected */
    {
        *status = CH9121X_PHY_STATUS_DISCONNECTED;                          /* set status */
    }
    else if (buf[0] == (uint8_t)CH9121X_PHY_STATUS_10M_FULL_DUPLEX)         /* 10 mbps full duplex */
    {
        *status = CH9121X_PHY_STATUS_10M_FULL_DUPLEX;                       /* set status */
    }
    else if (buf[0] == (uint8_t)CH9121X_PHY_STATUS_10M_HALF_DUPLEX)         /* 10 mbps half duplex */
    {
        *status = CH9121X_PHY_STATUS_10M_HALF_DUPLEX;                       /* set status */
    }
    else if (buf[0] == (uint8_t)CH9121X_PHY_STATUS_100M_FULL_DUPLEX)        /* 100 mbps full duplex */
    {
        *status = CH9121X_PHY_STATUS_100M_FULL_DUPLEX;                      /* set status */
    }
    else if (buf[0] == (uint8_t)CH9121X_PHY_STATUS_100M_HALF_DUPLEX)        /* 100 mbps half duplex */
    {
        *status = CH9121X_PHY_STATUS_100M_HALF_DUPLEX;                      /* set status */
    }
    else                                                                    /* unknown */
    {
        *status = CH9121X_PHY_STATUS_UNKNOWN;                               /* set status */
    }
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t ch9121x_get_disconnect_with_no_rj45(ch9121x_handle_t *handle, ch9121x_bool_t *enable)
{
    uint8_t cmd;
    uint8_t buf[1];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121X_CMD_GET_PORT1_2_LINKDOWN;                           /* get port 1 and 2 linkdown */
    if (a_ch9121x_write_read(handle, &cmd, 1, buf, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get data */
    {
        return 1;                                                     /* return error */
    }
    *enable = (ch9121x_bool_t)buf[0];                                 /* set bool value */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_get_uart_buffer_length(ch9121x_handle_t *handle, ch9121x_port_t port, uint32_t *len)
{
    uint8_t cmd;
    uint8_t buf[4];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121X_PORT1)                                        /* port1 */
    {
        cmd = CH9121X_CMD_PORT1_GET_UART_PACK_LEN;                    /* get port1 uart pack len */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121X_CMD_PORT2_GET_UART_PACK_LEN;                    /* get port2 uart pack len */
    }
    if (a_ch9121x_write_read(handle, &cmd, 1, buf, 4,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get data */
    {
        return 1;                                                     /* return error */
    }
    *len = (uint32_t)buf[3] << 24 | (uint32_t)buf[2] << 16 |
           (uint32_t)buf[1] << 8 | (uint32_t)buf[0] << 0;             /* set length */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_get_uart_flush(ch9121x_handle_t *handle, ch9121x_port_t port, ch9121x_bool_t *enable)
{
    uint8_t cmd;
    uint8_t buf[1];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (port == CH9121X_PORT1)                                        /* port1 */
    {
        cmd = CH9121X_CMD_PORT1_GET_EMPTY;                            /* get port1 empty */
    }
    else                                                              /* port2 */
    {
        cmd = CH9121X_CMD_PORT2_GET_EMPTY;                            /* get port2 empty */
    }
    if (a_ch9121x_write_read(handle, &cmd, 1, buf, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get data */
    {
        return 1;                                                     /* return error */
    }
    *enable = (ch9121x_bool_t)buf[0];                                 /* set bool value */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_get_dhcp(ch9121x_handle_t *handle, ch9121x_bool_t *enable)
{
    uint8_t cmd;
    uint8_t buf[1];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121X_CMD_GET_DHCP_ENABLE;                                /* get dhcp enable */
    if (a_ch9121x_write_read(handle, &cmd, 1, buf, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get data */
    {
        return 1;                                                     /* return error */
    }
    *enable = (ch9121x_bool_t)buf[0];                                 /* set bool value */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     set tcp retry mode
 * @param[in] *handle pointer to a ch9121x handle structure
 * @param[in] t time
 * @return    status code
 *            - 0 success
 *            - 1 set tcp retry mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 t > 7
 * @note      none
 */
uint8_t ch9121x_set_tcp_retry_mode(ch9121x_handle_t *handle, uint8_t t)
{
    uint8_t cmd[3];
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    if (t > 7)                                                           /* check t */
    {
        handle->debug_print("ch9121x: t > 7.\n");                        /* t > 7 */
        
        return 4;                                                        /* return error */
    }
    
    cmd[0] = (CH9121X_CMD2_SET_TCP_RETRY_MODE >> 8) & 0xFF;              /* set msb */
    cmd[1] = (CH9121X_CMD2_SET_TCP_RETRY_MODE >> 0) & 0xFF;              /* set lsb */
    cmd[2] = (uint8_t)t;                                                 /* set time */
    if (a_ch9121x_write_check(handle, cmd, 3,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)        /* write command */
    {
        return 1;                                                        /* return error */
    }
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t ch9121x_get_tcp_retry_mode(ch9121x_handle_t *handle, uint8_t *t)
{
    uint8_t cmd[2];
    uint8_t buf[1];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd[0] = (CH9121X_CMD2_GET_TCP_RETRY_MODE >> 8) & 0xFF;           /* set msb */
    cmd[1] = (CH9121X_CMD2_GET_TCP_RETRY_MODE >> 0) & 0xFF;           /* set lsb */
    if (a_ch9121x_write_read(handle, cmd, 2, buf, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get data */
    {
        return 1;                                                     /* return error */
    }
    *t = buf[0];                                                      /* set time */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_set_flow_control(ch9121x_handle_t *handle, ch9121x_bool_t enable)
{
    uint8_t cmd[3];
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    cmd[0] = (CH9121X_CMD2_FLOW_CONTROL_ENABLE >> 8) & 0xFF;             /* set msb */
    cmd[1] = (CH9121X_CMD2_FLOW_CONTROL_ENABLE >> 0) & 0xFF;             /* set lsb */
    cmd[2] = (uint8_t)enable;                                            /* set bool value */
    if (a_ch9121x_write_check(handle, cmd, 3,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)        /* write command */
    {
        return 1;                                                        /* return error */
    }
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t ch9121x_get_flow_control(ch9121x_handle_t *handle, ch9121x_bool_t *enable)
{
    uint8_t cmd[2];
    uint8_t buf[1];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd[0] = (CH9121X_CMD2_GET_FLOW_CONTROL_ENABLE >> 8) & 0xFF;      /* set msb */
    cmd[1] = (CH9121X_CMD2_GET_FLOW_CONTROL_ENABLE >> 0) & 0xFF;      /* set lsb */
    if (a_ch9121x_write_read(handle, cmd, 2, buf, 1,
                             CH9121X_UART_PRE_DELAY, 1000) != 0)      /* get data */
    {
        return 1;                                                     /* return error */
    }
    *enable = (ch9121x_bool_t)buf[0];                                 /* set bool value */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_set_arp_retry(ch9121x_handle_t *handle, uint8_t period, uint8_t times)
{
    uint8_t cmd[4];
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->inited != 1)                                             /* check handle initialization */
    {
        return 3;                                                        /* return error */
    }
    
    cmd[0] = (CH9121X_CMD2_SET_ARP_RETRY >> 8) & 0xFF;                   /* set msb */
    cmd[1] = (CH9121X_CMD2_SET_ARP_RETRY >> 0) & 0xFF;                   /* set lsb */
    cmd[2] = period;                                                     /* set period */
    cmd[3] = times;                                                      /* set times */
    if (a_ch9121x_write_check(handle, cmd, 4,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)        /* write command */
    {
        return 1;                                                        /* return error */
    }
    
    return 0;                                                            /* success return 0 */
}

/**
 * @brief      convert the tcp retry time to the register raw data
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  ms time in ms
 * @param[out] *reg pointer to a register raw buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_tcp_retry_time_convert_to_register(ch9121x_handle_t *handle, uint16_t ms, uint8_t *reg)
{
    if (handle == NULL)                /* check handle */
    {
        return 2;                      /* return error */
    }
    if (handle->inited != 1)           /* check handle initialization */
    {
        return 3;                      /* return error */
    }
    
    *reg = (uint8_t)(ms / 500);        /* convert real data to register data */
    
    return 0;                          /* success return 0 */
}

/**
 * @brief      convert the register raw data to the tcp retry time
 * @param[in]  *handle pointer to a ch9121x handle structure
 * @param[in]  reg register raw data
 * @param[out] *ms pointer to a ms buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ch9121x_tcp_retry_time_convert_to_data(ch9121x_handle_t *handle, uint8_t reg, uint16_t *ms)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    *ms = reg * 500;                /* convert raw data to real data */
    
    return 0;                       /* success return 0 */
}

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
uint8_t ch9121x_arp_retry_period_convert_to_register(ch9121x_handle_t *handle, uint16_t ms, uint8_t *reg)
{
    if (handle == NULL)                /* check handle */
    {
        return 2;                      /* return error */
    }
    if (handle->inited != 1)           /* check handle initialization */
    {
        return 3;                      /* return error */
    }
    
    *reg = (uint8_t)(ms / 100);        /* convert real data to register data */
    
    return 0;                          /* success return 0 */
}

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
uint8_t ch9121x_arp_retry_period_convert_to_data(ch9121x_handle_t *handle, uint8_t reg, uint16_t *ms)
{
    if (handle == NULL)             /* check handle */
    {
        return 2;                   /* return error */
    }
    if (handle->inited != 1)        /* check handle initialization */
    {
        return 3;                   /* return error */
    }
    
    *ms = reg * 100;                /* convert raw data to real data */
    
    return 0;                       /* success return 0 */
}

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
uint8_t ch9121x_init(ch9121x_handle_t *handle)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->debug_print == NULL)                                   /* check debug_print */
    {
        return 3;                                                      /* return error */
    }
    if (handle->uart_init == NULL)                                     /* check uart_init */
    {
        handle->debug_print("ch9121x: uart_init is null.\n");          /* uart_init is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->uart_deinit == NULL)                                   /* check uart_deinit */
    {
        handle->debug_print("ch9121x: uart_deinit is null.\n");        /* uart_deinit is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->uart_read == NULL)                                     /* check uart_read */
    {
        handle->debug_print("ch9121x: uart_read is null.\n");          /* uart_read is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->uart_write == NULL)                                    /* check uart_write */
    {
        handle->debug_print("ch9121x: uart_write is null.\n");         /* uart_write is null */
        
        return 3;                                                      /* return error */
    } 
    if (handle->uart_flush == NULL)                                    /* check uart_flush */
    {
        handle->debug_print("ch9121x: uart_flush is null.\n");         /* uart_flush is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->delay_ms == NULL)                                      /* check delay_ms */
    {
        handle->debug_print("ch9121x: delay_ms is null.\n");           /* delay_ms is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->reset_gpio_init == NULL)                               /* check reset_gpio_init */
    {
        handle->debug_print("ch9121x: reset_gpio_init is null.\n");    /* reset_gpio_init is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->reset_gpio_deinit == NULL)                             /* check reset_gpio_deinit */
    {
        handle->debug_print("ch9121x: reset_gpio_deinit is null.\n");  /* reset_gpio_deinit is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->reset_gpio_write == NULL)                              /* check reset_gpio_write */
    {
        handle->debug_print("ch9121x: reset_gpio_write is null.\n");   /* reset_gpio_write is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->cfg_gpio_init == NULL)                                 /* check cfg_gpio_init */
    {
        handle->debug_print("ch9121x: cfg_gpio_init is null.\n");      /* cfg_gpio_init is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->cfg_gpio_deinit == NULL)                               /* check cfg_gpio_deinit */
    {
        handle->debug_print("ch9121x: cfg_gpio_deinit is null.\n");    /* cfg_gpio_deinit is null */
        
        return 3;                                                      /* return error */
    }
    if (handle->cfg_gpio_write == NULL)                                /* check cfg_gpio_write */
    {
        handle->debug_print("ch9121x: cfg_gpio_write is null.\n");     /* cfg_gpio_write is null */
        
        return 3;                                                      /* return error */
    }
    
    if (handle->uart_init() != 0)                                      /* uart init */
    {
        handle->debug_print("ch9121x: uart init failed.\n");           /* uart init failed */
        
        return 1;                                                      /* return error */
    }
    if (handle->reset_gpio_init() != 0)                                /* reset gpio init */
    {
        handle->debug_print("ch9121x: reset gpio init failed.\n");     /* reset gpio init failed */
        (void)handle->uart_deinit();                                   /* uart deinit */
        
        return 4;                                                      /* return error */
    }
    if (handle->cfg_gpio_init() != 0)                                  /* cfg gpio init */
    {
        handle->debug_print("ch9121x: cfg gpio init failed.\n");       /* cfg gpio init failed */
        (void)handle->uart_deinit();                                   /* uart deinit */
        (void)handle->reset_gpio_deinit();                             /* reset gpio deinit */
        
        return 5;                                                      /* return error */
    }
    if (handle->reset_gpio_write(0) != 0)                              /* set low */
    {
        handle->debug_print("ch9121x: cfg gpio write failed.\n");      /* cfg gpio write failed */
        (void)handle->uart_deinit();                                   /* uart deinit */
        (void)handle->reset_gpio_deinit();                             /* reset gpio deinit */
        (void)handle->cfg_gpio_deinit();                               /* cfg gpio deinit */
        
        return 6;                                                      /* return error */
    }
    handle->delay_ms(10);                                              /* delay 10ms */
    if (handle->reset_gpio_write(1) != 0)                              /* set high */
    {
        handle->debug_print("ch9121x: cfg gpio write failed.\n");      /* cfg gpio write failed */
        (void)handle->uart_deinit();                                   /* uart deinit */
        (void)handle->reset_gpio_deinit();                             /* reset gpio deinit */
        (void)handle->cfg_gpio_deinit();                               /* cfg gpio deinit */
        
        return 6;                                                      /* return error */
    }
    handle->delay_ms(1000);                                            /* delay 1000ms */
    handle->inited = 1;                                                /* flag finish initialization */
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t ch9121x_deinit(ch9121x_handle_t *handle)
{
    uint8_t cmd;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    cmd = CH9121X_CMD_RESET;                                          /* set reset */
    if (a_ch9121x_write_check(handle, &cmd, 1,
                              CH9121X_UART_PRE_DELAY, 1000) != 0)     /* reset */
    {
        return 4;                                                     /* return error */
    }
    handle->delay_ms(10);                                             /* delay 10ms */
    if (handle->uart_deinit() != 0)                                   /* uart deinit */
    {
        handle->debug_print("ch9121x: uart deinit failed.\n");        /* uart deinit failed */
        
        return 1;                                                     /* return error */
    }
    if (handle->reset_gpio_deinit() != 0)                             /* reset gpio deinit */
    {
        handle->debug_print("ch9121x: reset gpio deinit failed.\n");  /* reset gpio deinit failed */
        
        return 5;                                                     /* return error */
    }
    if (handle->cfg_gpio_deinit() != 0)                               /* cfg gpio deinit */
    {
        handle->debug_print("ch9121x: cfg gpio deinit failed.\n");    /* cfg gpio deinit failed */
        
        return 6;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ch9121x_write(ch9121x_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (handle->cfg_gpio_write(1) != 0)                              /* cfg gpio write */
    {
        handle->debug_print("ch9121x: cfg gpio write failed.\n");    /* cfg gpio write failed */
        
        return 1;                                                    /* return error */
    }
    if (handle->uart_write(buf, len) != 0)                           /* uart write */
    {
        handle->debug_print("ch9121x:uart write failed.\n");         /* uart write failed */
        
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ch9121x_read(ch9121x_handle_t *handle, uint8_t *buf, uint16_t *len)
{
    uint16_t l;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (handle->cfg_gpio_write(1) != 0)                              /* cfg gpio write */
    {
        handle->debug_print("ch9121x: cfg gpio write failed.\n");    /* cfg gpio write failed */
        
        return 1;                                                    /* return error */
    }
    l = handle->uart_read(buf, *len);                                /* uart read */
    *len = l;                                                        /* set data */
    
    return 0;                                                        /* success return 0 */
}

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
                            uint16_t pre_delay, uint16_t timeout)
{
    if (handle == NULL)                                      /* check handle */
    {
        return 2;                                            /* return error */
    }
    if (handle->inited != 1)                                 /* check handle initialization */
    {
        return 3;                                            /* return error */
    }
    
    if (a_ch9121x_write_read(handle, param, len,
                            out, out_len,
                            pre_delay, timeout) != 0)        /* set command */
    {
        return 1;                                            /* return error */
    }
    
    return 0;                                                /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a ch9121x info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ch9121x_info(ch9121x_info_t *info)
{
    if (info == NULL)                                              /* check handle */
    {
        return 2;                                                  /* return error */
    }
    
    memset(info, 0, sizeof(ch9121x_info_t));                       /* initialize ch9121x info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                       /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);       /* copy manufacturer name */
    strncpy(info->interface, "UART", 8);                           /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;               /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;               /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                            /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                       /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                       /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                         /* set driver version */
    
    return 0;                                                      /* success return 0 */
}
