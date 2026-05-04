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
 * @file      driver_ch9121x_register_test.c
 * @brief     driver ch9121x register test source file
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

#include "driver_ch9121x_register_test.h"
#include <stdlib.h>

static ch9121x_handle_t gs_handle;        /**< ch9121x handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t ch9121x_register_test(void)
{
    uint8_t res;
    uint8_t reg;
    uint8_t reg_check;
    uint8_t version;
    uint8_t timeout;
    uint8_t timeout_check;
    uint8_t mac[6];
    uint8_t mac_check[6];
    uint8_t ip[4];
    uint8_t ip_check[4];
    uint8_t mask[4];
    uint8_t mask_check[4];
    uint16_t num;
    uint16_t num_check;
    uint32_t baud;
    uint32_t baud_check;
    uint32_t len;
    uint32_t len_check;
    uint8_t data_bit;
    uint8_t stop_bit;
    uint16_t ms;
    uint16_t ms_check;
    ch9121x_parity_t parity;
    ch9121x_info_t info;
    ch9121x_status_t status;
    ch9121x_mode_t mode;
    ch9121x_bool_t enable;
    ch9121x_uart_clock_mode_t uart_clock_mode;
    ch9121x_phy_status_t phy_status;
    char domain[] = "www.ch9121x.com";

    /* link interface function */
    DRIVER_CH9121X_LINK_INIT(&gs_handle, ch9121x_handle_t);
    DRIVER_CH9121X_LINK_UART_INIT(&gs_handle, ch9121x_interface_uart_init);
    DRIVER_CH9121X_LINK_UART_DEINIT(&gs_handle, ch9121x_interface_uart_deinit);
    DRIVER_CH9121X_LINK_UART_READ(&gs_handle, ch9121x_interface_uart_read);
    DRIVER_CH9121X_LINK_UART_WRITE(&gs_handle, ch9121x_interface_uart_write);
    DRIVER_CH9121X_LINK_UART_FLUSH(&gs_handle, ch9121x_interface_uart_flush);
    DRIVER_CH9121X_LINK_RESET_GPIO_INIT(&gs_handle, ch9121x_interface_reset_gpio_init);
    DRIVER_CH9121X_LINK_RESET_GPIO_DEINIT(&gs_handle, ch9121x_interface_reset_gpio_deinit);
    DRIVER_CH9121X_LINK_RESET_GPIO_WRITE(&gs_handle, ch9121x_interface_reset_gpio_write);
    DRIVER_CH9121X_LINK_CFG_GPIO_INIT(&gs_handle, ch9121x_interface_cfg_gpio_init);
    DRIVER_CH9121X_LINK_CFG_GPIO_DEINIT(&gs_handle, ch9121x_interface_cfg_gpio_deinit);
    DRIVER_CH9121X_LINK_CFG_GPIO_WRITE(&gs_handle, ch9121x_interface_cfg_gpio_write);
    DRIVER_CH9121X_LINK_DELAY_MS(&gs_handle, ch9121x_interface_delay_ms);
    DRIVER_CH9121X_LINK_DEBUG_PRINT(&gs_handle, ch9121x_interface_debug_print);

    /* get ch9121x information */
    res = ch9121x_info(&info);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get info failed.\n");

        return 1;
    }
    else
    {
        /* print chip information */
        ch9121x_interface_debug_print("ch9121x: chip is %s.\n", info.chip_name);
        ch9121x_interface_debug_print("ch9121x: manufacturer is %s.\n", info.manufacturer_name);
        ch9121x_interface_debug_print("ch9121x: interface is %s.\n", info.interface);
        ch9121x_interface_debug_print("ch9121x: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ch9121x_interface_debug_print("ch9121x: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ch9121x_interface_debug_print("ch9121x: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ch9121x_interface_debug_print("ch9121x: max current is %0.2fmA.\n", info.max_current_ma);
        ch9121x_interface_debug_print("ch9121x: max temperature is %0.1fC.\n", info.temperature_max);
        ch9121x_interface_debug_print("ch9121x: min temperature is %0.1fC.\n", info.temperature_min);
    }

    /* start register test */
    ch9121x_interface_debug_print("ch9121x: start register test.\n");

    /* ch9121x init */
    res = ch9121x_init(&gs_handle);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: init failed.\n");

        return 1;
    }

    /* ch9121x_get_version test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_get_version test.\n");

    /* get version */
    res = ch9121x_get_version(&gs_handle, &version);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get version failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: version is 0x%02X.\n", version);

    /* ch9121x_save_to_eeprom test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_save_to_eeprom test.\n");

    /* save to eeprom */
    res = ch9121x_save_to_eeprom(&gs_handle);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: save to eeprom failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check save to eeprom %s.\n", res == 0 ? "ok" : "error");

    /* ch9121x_exit test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_exit test.\n");

    /* exit */
    res = ch9121x_exit(&gs_handle);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: exit failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check exit %s.\n", res == 0 ? "ok" : "error");

    /* ch9121x_set_port2 test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_port2 test.\n");

    /* disable port2 */
    res = ch9121x_set_port2(&gs_handle, CH9121X_BOOL_FALSE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set port2 failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* disable port2 */
    ch9121x_interface_debug_print("ch9121x: disable port2.\n");

    /* output */
    ch9121x_interface_debug_print("ch9121x: check port2 %s.\n", res == 0 ? "ok" : "error");

    /* enable port2 */
    res = ch9121x_set_port2(&gs_handle, CH9121X_BOOL_TRUE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set port2 failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* enable port2 */
    ch9121x_interface_debug_print("ch9121x: enable port2.\n");

    /* output */
    ch9121x_interface_debug_print("ch9121x: check port2 %s.\n", res == 0 ? "ok" : "error");

    /* ch9121x_set_disconnect_with_no_rj45/ch9121x_get_disconnect_with_no_rj45 test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_disconnect_with_no_rj45/ch9121x_get_disconnect_with_no_rj45 test.\n");

    /* disable */
    res = ch9121x_set_disconnect_with_no_rj45(&gs_handle, CH9121X_BOOL_FALSE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set disconnect with no rj45 failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: disable disconnect with no rj45.\n");
    res = ch9121x_get_disconnect_with_no_rj45(&gs_handle, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get disconnect with no rj45 failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check disconnect with no rj45 %s.\n", enable == CH9121X_BOOL_FALSE ? "ok" : "error");

    /* enable */
    res = ch9121x_set_disconnect_with_no_rj45(&gs_handle, CH9121X_BOOL_TRUE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set disconnect with no rj45 failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: enable disconnect with no rj45.\n");
    res = ch9121x_get_disconnect_with_no_rj45(&gs_handle, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get disconnect with no rj45 failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check disconnect with no rj45 %s.\n", enable == CH9121X_BOOL_TRUE ? "ok" : "error");

    /* ch9121x_set_domain test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_domain test.\n");

    /* set domain */
    res = ch9121x_set_domain(&gs_handle, domain);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set domain failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* set domain */
    ch9121x_interface_debug_print("ch9121x: set domain %s.\n", domain);

    /* output */
    ch9121x_interface_debug_print("ch9121x: check domain %s.\n", res == 0 ? "ok" : "error");

    /* ch9121x_set_dhcp/ch9121x_get_dhcp test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_dhcp/ch9121x_get_dhcp test.\n");

    /* disable dhcp */
    res = ch9121x_set_dhcp(&gs_handle, CH9121X_BOOL_FALSE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set dhcp failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: disable dhcp.\n");
    res = ch9121x_get_dhcp(&gs_handle, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get dhcp failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check dhcp %s.\n", enable == CH9121X_BOOL_FALSE ? "ok" : "error");

    /* enable dhcp */
    res = ch9121x_set_dhcp(&gs_handle, CH9121X_BOOL_TRUE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set dhcp failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: enable dhcp.\n");
    res = ch9121x_get_dhcp(&gs_handle, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get dhcp failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check dhcp %s.\n", enable == CH9121X_BOOL_TRUE ? "ok" : "error");

    /* ch9121x_set_mac/ch9121x_get_mac test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_mac/ch9121x_get_mac test.\n");
    
    mac[0] = rand() % 0xFF;
    mac[1] = rand() % 0xFF;
    mac[2] = rand() % 0xFF;
    mac[3] = rand() % 0xFF;
    mac[4] = rand() % 0xFF;
    mac[5] = rand() % 0xFF;
    res = ch9121x_set_mac(&gs_handle, mac);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set mac failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: set mac 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X.\n",
                                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    res = ch9121x_get_mac(&gs_handle, mac_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get mac failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check mac[0] %s.\n", mac[0] == mac_check[0] ? "ok" : "error");
    ch9121x_interface_debug_print("ch9121x: check mac[1] %s.\n", mac[1] == mac_check[1] ? "ok" : "error");
    ch9121x_interface_debug_print("ch9121x: check mac[2] %s.\n", mac[2] == mac_check[2] ? "ok" : "error");
    ch9121x_interface_debug_print("ch9121x: check mac[3] %s.\n", mac[3] == mac_check[3] ? "ok" : "error");
    ch9121x_interface_debug_print("ch9121x: check mac[4] %s.\n", mac[4] == mac_check[4] ? "ok" : "error");
    ch9121x_interface_debug_print("ch9121x: check mac[5] %s.\n", mac[5] == mac_check[5] ? "ok" : "error");
    
    /* ch9121x_clear_mac test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_clear_mac test.\n");

    /* clear mac */
    res = ch9121x_clear_mac(&gs_handle);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: clear mac failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* get mac */
    res = ch9121x_get_mac(&gs_handle, mac);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get mac failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: default mac is 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X.\n",
                                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    /* ch9121x_set_ip/ch9121x_get_ip test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_ip/ch9121x_get_ip test.\n");

    /* random ip */
    ip[0] = rand() % 0xFF;
    ip[1] = rand() % 0xFF;
    ip[2] = rand() % 0xFF;
    ip[3] = rand() % 0xFF;

    /* set ip */
    res = ch9121x_set_ip(&gs_handle, ip);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set ip failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set ip %d.%d.%d.%d.\n",
                                  ip[0], ip[1], ip[2], ip[3]);

    /* get ip */
    res = ch9121x_get_ip(&gs_handle, ip_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get ip failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check ip %s.\n", memcmp(ip, ip_check, 4) == 0 ? "ok" : "error");

    /* ch9121x_set_subnet_mask/ch9121x_get_subnet_mask test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_subnet_mask/ch9121x_get_subnet_mask test.\n");

    /* random mask */
    mask[0] = rand() % 0xFF;
    mask[1] = rand() % 0xFF;
    mask[2] = rand() % 0xFF;
    mask[3] = rand() % 0xFF;

    /* set subnet mask */
    res = ch9121x_set_subnet_mask(&gs_handle, mask);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set subnet mask failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set subnet mask %d.%d.%d.%d.\n",
                                  mask[0], mask[1], mask[2], mask[3]);

    /* get subnet mask */
    res = ch9121x_get_subnet_mask(&gs_handle, mask_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get subnet mask failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check subnet mask %s.\n", memcmp(mask, mask_check, 4) == 0 ? "ok" : "error");

    /* ch9121x_set_gateway/ch9121x_get_gateway test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_gateway/ch9121x_get_gateway test.\n");

    /* random ip */
    ip[0] = rand() % 0xFF;
    ip[1] = rand() % 0xFF;
    ip[2] = rand() % 0xFF;
    ip[3] = rand() % 0xFF;

    /* set gateway */
    res = ch9121x_set_gateway(&gs_handle, ip);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set gateway failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set gateway %d.%d.%d.%d.\n",
                                  ip[0], ip[1], ip[2], ip[3]);

    /* get gateway */
    res = ch9121x_get_gateway(&gs_handle, ip_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get gateway failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check gateway %s.\n", memcmp(ip, ip_check, 4) == 0 ? "ok" : "error");

    /* ch9121x_get_status test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_get_status test.\n");

    /* port1 */
    res = ch9121x_get_status(&gs_handle, CH9121X_PORT1, &status);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get status failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: get port1 status %s.\n", status == CH9121X_STATUS_CONNECT ? "connect" : "disconnect");

    /* port2 */
    res = ch9121x_get_status(&gs_handle, CH9121X_PORT2, &status);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get status failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: get port2 status %s.\n", status == CH9121X_STATUS_CONNECT ? "connect" : "disconnect");

    /* ch9121x_set_mode/ch9121x_get_mode test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_mode/ch9121x_get_mode test.\n");

    /* tcp server */
    res = ch9121x_set_mode(&gs_handle, CH9121X_PORT1, CH9121X_MODE_TCP_SERVER);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port1 tcp server mode.\n");

    res = ch9121x_get_mode(&gs_handle, CH9121X_PORT1, &mode);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check mode %s.\n", mode == CH9121X_MODE_TCP_SERVER ? "ok" : "error");

    /* tcp client */
    res = ch9121x_set_mode(&gs_handle, CH9121X_PORT1, CH9121X_MODE_TCP_CLIENT);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port1 tcp client mode.\n");

    res = ch9121x_get_mode(&gs_handle, CH9121X_PORT1, &mode);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check mode %s.\n", mode == CH9121X_MODE_TCP_CLIENT ? "ok" : "error");

    /* udp server */
    res = ch9121x_set_mode(&gs_handle, CH9121X_PORT1, CH9121X_MODE_UDP_SERVER);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port1 udp server mode.\n");

    res = ch9121x_get_mode(&gs_handle, CH9121X_PORT1, &mode);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check mode %s.\n", mode == CH9121X_MODE_UDP_SERVER ? "ok" : "error");

    /* udp client */
    res = ch9121x_set_mode(&gs_handle, CH9121X_PORT1, CH9121X_MODE_UDP_CLIENT);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port1 udp client mode.\n");

    res = ch9121x_get_mode(&gs_handle, CH9121X_PORT1, &mode);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check mode %s.\n", mode == CH9121X_MODE_UDP_CLIENT ? "ok" : "error");

    /* tcp server */
    res = ch9121x_set_mode(&gs_handle, CH9121X_PORT2, CH9121X_MODE_TCP_SERVER);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port2 tcp server mode.\n");

    res = ch9121x_get_mode(&gs_handle, CH9121X_PORT2, &mode);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check mode %s.\n", mode == CH9121X_MODE_TCP_SERVER ? "ok" : "error");

    /* tcp client */
    res = ch9121x_set_mode(&gs_handle, CH9121X_PORT2, CH9121X_MODE_TCP_CLIENT);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port2 tcp client mode.\n");

    res = ch9121x_get_mode(&gs_handle, CH9121X_PORT2, &mode);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check mode %s.\n", mode == CH9121X_MODE_TCP_CLIENT ? "ok" : "error");

    /* udp server */
    res = ch9121x_set_mode(&gs_handle, CH9121X_PORT2, CH9121X_MODE_UDP_SERVER);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port2 udp server mode.\n");

    res = ch9121x_get_mode(&gs_handle, CH9121X_PORT2, &mode);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check mode %s.\n", mode == CH9121X_MODE_UDP_SERVER ? "ok" : "error");

    /* udp client */
    res = ch9121x_set_mode(&gs_handle, CH9121X_PORT2, CH9121X_MODE_UDP_CLIENT);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port2 udp client mode.\n");

    res = ch9121x_get_mode(&gs_handle, CH9121X_PORT2, &mode);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check mode %s.\n", mode == CH9121X_MODE_UDP_CLIENT ? "ok" : "error");

    /* ch9121x_set_source_port/ch9121x_get_source_port test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_source_port/ch9121x_get_source_port test.\n");

    /* random */
    num = rand() % 0xFFFFU;

    /* port1 */
    res = ch9121x_set_source_port(&gs_handle, CH9121X_PORT1, num);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set source port failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set source port1 %d.\n", num);

    /* get source port */
    res = ch9121x_get_source_port(&gs_handle, CH9121X_PORT1, &num_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get source port failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check source port %s.\n", num_check == num ? "ok" : "error");

    /* random */
    num = rand() % 0xFFFFU;

    /* port2 */
    res = ch9121x_set_source_port(&gs_handle, CH9121X_PORT2, num);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set source port failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set source port2 %d.\n", num);

    /* get source port */
    res = ch9121x_get_source_port(&gs_handle, CH9121X_PORT2, &num_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get source port failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check source port %s.\n", num_check == num ? "ok" : "error");

    /* ch9121x_set_dest_ip/ch9121x_get_dest_ip test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_dest_ip/ch9121x_get_dest_ip test.\n");

    /* random ip */
    ip[0] = rand() % 0xFF;
    ip[1] = rand() % 0xFF;
    ip[2] = rand() % 0xFF;
    ip[3] = rand() % 0xFF;

    /* port1 */
    res = ch9121x_set_dest_ip(&gs_handle, CH9121X_PORT1, ip);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set dest ip failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port1 dest ip %d.%d.%d.%d.\n", ip[0], ip[1], ip[2], ip[3]);

    /* get dest ip */
    res = ch9121x_get_dest_ip(&gs_handle, CH9121X_PORT1, ip_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get dest ip failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check dest ip %s.\n", memcmp(ip, ip_check, 4) == 0 ? "ok" : "error");

    /* random ip */
    ip[0] = rand() % 0xFF;
    ip[1] = rand() % 0xFF;
    ip[2] = rand() % 0xFF;
    ip[3] = rand() % 0xFF;

    /* port2 */
    res = ch9121x_set_dest_ip(&gs_handle, CH9121X_PORT2, ip);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set dest ip failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port2 dest ip %d.%d.%d.%d.\n", ip[0], ip[1], ip[2], ip[3]);

    /* get dest ip */
    res = ch9121x_get_dest_ip(&gs_handle, CH9121X_PORT2, ip_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get dest ip failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check dest ip %s.\n", memcmp(ip, ip_check, 4) == 0 ? "ok" : "error");

    /* ch9121x_set_dest_port/ch9121x_get_dest_port test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_dest_port/ch9121x_get_dest_port test.\n");

    /* random */
    num = rand() % 0xFFFFU;

    /* port1 */
    res = ch9121x_set_dest_port(&gs_handle, CH9121X_PORT1, num);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set dest port failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set dest port1 %d.\n", num);

    /* get dest port */
    res = ch9121x_get_dest_port(&gs_handle, CH9121X_PORT1, &num_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get dest port failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check dest port %s.\n", num_check == num ? "ok" : "error");

    /* random */
    num = rand() % 0xFFFFU;

    /* port2 */
    res = ch9121x_set_dest_port(&gs_handle, CH9121X_PORT2, num);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set dest port failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set dest port2 %d.\n", num);

    /* get dest port */
    res = ch9121x_get_dest_port(&gs_handle, CH9121X_PORT2, &num_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get dest port failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check dest port %s.\n", num_check == num ? "ok" : "error");

    /* ch9121x_set_uart_baud/ch9121x_get_uart_baud test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_uart_baud/ch9121x_get_uart_baud test.\n");

    /* 9600 */
    baud = 9600;

    /* port1 */
    res = ch9121x_set_uart_baud(&gs_handle, CH9121X_PORT1, baud);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart baud failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port1 uart baud %d.\n", baud);

    /* get uart baud */
    res = ch9121x_get_uart_baud(&gs_handle, CH9121X_PORT1, &baud_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart baud failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart baud %s.\n", baud_check == baud ? "ok" : "error");

    /* 9600 */
    baud = 9600;

    /* port2 */
    res = ch9121x_set_uart_baud(&gs_handle, CH9121X_PORT2, baud);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart baud failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port2 uart baud %d.\n", baud);

    /* get uart baud */
    res = ch9121x_get_uart_baud(&gs_handle, CH9121X_PORT2, &baud_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart baud failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart baud %s.\n", baud_check == baud ? "ok" : "error");

    /* ch9121x_set_uart_config/ch9121x_get_uart_config test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_uart_config/ch9121x_get_uart_config test.\n");

    /* set uart config */
    res = ch9121x_set_uart_config(&gs_handle, CH9121X_PORT1, 8, CH9121X_PARITY_NONE, 1);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart config failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port1 data_bit 8, parity none, stop_bit 1.\n");

    /* get uart config */
    res = ch9121x_get_uart_config(&gs_handle, CH9121X_PORT1, &data_bit, &parity, &stop_bit);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart config failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart data bit %s.\n", data_bit == 8 ? "ok" : "error");
    ch9121x_interface_debug_print("ch9121x: check uart parity %s.\n", parity == CH9121X_PARITY_NONE ? "ok" : "error");
    ch9121x_interface_debug_print("ch9121x: check uart stop bit %s.\n", stop_bit == 1 ? "ok" : "error");

    /* set uart config */
    res = ch9121x_set_uart_config(&gs_handle, CH9121X_PORT2, 8, CH9121X_PARITY_NONE, 1);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart config failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port2 data_bit 8, parity none, stop_bit 1.\n");

    /* get uart config */
    res = ch9121x_get_uart_config(&gs_handle, CH9121X_PORT2, &data_bit, &parity, &stop_bit);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart config failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart data bit %s.\n", data_bit == 8 ? "ok" : "error");
    ch9121x_interface_debug_print("ch9121x: check uart parity %s.\n", parity == CH9121X_PARITY_NONE ? "ok" : "error");
    ch9121x_interface_debug_print("ch9121x: check uart stop bit %s.\n", stop_bit == 1 ? "ok" : "error");

    /* ch9121x_set_uart_timeout/ch9121x_get_uart_timeout test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_uart_timeout/ch9121x_get_uart_timeout test.\n");

    /* random timeout */
    timeout = rand() % 0xFF;

    /* set uart timeout */
    res = ch9121x_set_uart_timeout(&gs_handle, CH9121X_PORT1, timeout);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart timeout failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port1 uart timeout %d.\n", timeout);

    /* get uart timeout */
    res = ch9121x_get_uart_timeout(&gs_handle, CH9121X_PORT1, &timeout_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart timeout failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart timeout %s.\n", timeout_check == timeout ? "ok" : "error");

    /* random timeout */
    timeout = rand() % 0xFF;

    /* set uart timeout */
    res = ch9121x_set_uart_timeout(&gs_handle, CH9121X_PORT2, timeout);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart timeout failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: set port2 uart timeout %d.\n", timeout);

    /* get uart timeout */
    res = ch9121x_get_uart_timeout(&gs_handle, CH9121X_PORT2, &timeout_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart timeout failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart timeout %s.\n", timeout_check == timeout ? "ok" : "error");

    /* ch9121x_set_source_port_random/ch9121x_get_source_port_random test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_source_port_random/ch9121x_get_source_port_random test.\n");

    /* port1 */
    res = ch9121x_set_source_port_random(&gs_handle, CH9121X_PORT1, CH9121X_BOOL_TRUE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set source port random failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: enable port1 source port random.\n");
    res = ch9121x_get_source_port_random(&gs_handle, CH9121X_PORT1, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get source port random failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check source port random %s.\n", enable == CH9121X_BOOL_TRUE ? "ok" : "error");

    /* port1 */
    res = ch9121x_set_source_port_random(&gs_handle, CH9121X_PORT1, CH9121X_BOOL_FALSE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set source port random failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: disable port1 source port random.\n");
    res = ch9121x_get_source_port_random(&gs_handle, CH9121X_PORT1, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get source port random failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check source port random %s.\n", enable == CH9121X_BOOL_FALSE ? "ok" : "error");

    /* port2 */
    res = ch9121x_set_source_port_random(&gs_handle, CH9121X_PORT2, CH9121X_BOOL_TRUE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set source port random failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: enable port2 source port random.\n");
    res = ch9121x_get_source_port_random(&gs_handle, CH9121X_PORT2, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get source port random failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check source port random %s.\n", enable == CH9121X_BOOL_TRUE ? "ok" : "error");

    /* port2 */
    res = ch9121x_set_source_port_random(&gs_handle, CH9121X_PORT2, CH9121X_BOOL_FALSE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set source port random failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: disable port2 source port random.\n");
    res = ch9121x_get_source_port_random(&gs_handle, CH9121X_PORT2, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get source port random failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check source port random %s.\n", enable == CH9121X_BOOL_FALSE ? "ok" : "error");

    /* ch9121x_set_uart_buffer_length/ch9121x_get_uart_buffer_length test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_uart_buffer_length/ch9121x_get_uart_buffer_length test.\n");

    /* random len */
    len = 128 + rand() % 50;

    /* set_uart_buffer_length */
    res = ch9121x_set_uart_buffer_length(&gs_handle, CH9121X_PORT1, len);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart buffer length failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: set port1 uart buffer length %d.\n", len);
    res = ch9121x_get_uart_buffer_length(&gs_handle, CH9121X_PORT1, &len_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart buffer length failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart buffer length %s.\n", len == len_check ? "ok" : "error");

    /* random len */
    len = 128 + rand() % 50;

    /* set_uart_buffer_length */
    res = ch9121x_set_uart_buffer_length(&gs_handle, CH9121X_PORT2, len);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart buffer length failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: set port2 uart buffer length %d.\n", len);
    res = ch9121x_get_uart_buffer_length(&gs_handle, CH9121X_PORT2, &len_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart buffer length failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart buffer length %s.\n", len == len_check ? "ok" : "error");

    /* ch9121x_set_uart_flush/ch9121x_get_uart_flush test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_uart_flush/ch9121x_get_uart_flush test.\n");

    /* enable uart flush */
    res = ch9121x_set_uart_flush(&gs_handle, CH9121X_PORT1, CH9121X_BOOL_TRUE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart flush failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: enable port1 uart flush.\n");
    res = ch9121x_get_uart_flush(&gs_handle, CH9121X_PORT1, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart flush failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart flush %s.\n", enable == CH9121X_BOOL_TRUE ? "ok" : "error");

    /* disable uart flush */
    res = ch9121x_set_uart_flush(&gs_handle, CH9121X_PORT1, CH9121X_BOOL_FALSE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart flush failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: disable port1 uart flush.\n");
    res = ch9121x_get_uart_flush(&gs_handle, CH9121X_PORT1, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart flush failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart flush %s.\n", enable == CH9121X_BOOL_FALSE ? "ok" : "error");
    
    /* enable uart flush */
    res = ch9121x_set_uart_flush(&gs_handle, CH9121X_PORT2, CH9121X_BOOL_TRUE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart flush failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: enable port2 uart flush.\n");
    res = ch9121x_get_uart_flush(&gs_handle, CH9121X_PORT2, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart flush failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart flush %s.\n", enable == CH9121X_BOOL_TRUE ? "ok" : "error");

    /* disable uart flush */
    res = ch9121x_set_uart_flush(&gs_handle, CH9121X_PORT2, CH9121X_BOOL_FALSE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart flush failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: disable port2 uart flush.\n");
    res = ch9121x_get_uart_flush(&gs_handle, CH9121X_PORT2, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart flush failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart flush %s.\n", enable == CH9121X_BOOL_FALSE ? "ok" : "error");
    
    /* ch9121x_set_eth_cfg/ch9121x_get_eth_cfg test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_eth_cfg/ch9121x_get_eth_cfg test.\n");
    
    /* enable eth cfg */
    res = ch9121x_set_eth_cfg(&gs_handle, CH9121X_BOOL_TRUE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set eth cfg failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: enable eth cfg.\n");
    res = ch9121x_get_eth_cfg(&gs_handle, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get eth cfg failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check eth cfg %s.\n", enable == CH9121X_BOOL_TRUE ? "ok" : "error");
    
    /* ch9121x_set_uart_clock_mode/ch9121x_get_uart_clock_mode test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_uart_clock_mode/ch9121x_get_uart_clock_mode test.\n");
    
    /* set uart clock mode default */
    res = ch9121x_set_uart_clock_mode(&gs_handle, CH9121X_UART_CLOCK_MODE_DEFAULT);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart clock mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: set uart clock mode default.\n");
    res = ch9121x_get_uart_clock_mode(&gs_handle, &uart_clock_mode);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart clock mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart clock mode %s.\n", uart_clock_mode == CH9121X_UART_CLOCK_MODE_DEFAULT ? "ok" : "error");
    
    /* set uart clock mode classical */
    res = ch9121x_set_uart_clock_mode(&gs_handle, CH9121X_UART_CLOCK_MODE_CLASSICAL);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set uart clock mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: set uart clock mode classical.\n");
    res = ch9121x_get_uart_clock_mode(&gs_handle, &uart_clock_mode);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get uart clock mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart clock mode %s.\n", uart_clock_mode == CH9121X_UART_CLOCK_MODE_CLASSICAL ? "ok" : "error");
    
    /* ch9121x_set_tcp_retry_mode/ch9121x_get_tcp_retry_mode test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_tcp_retry_mode/ch9121x_get_tcp_retry_mode test.\n");
    
    reg = 2;
    res = ch9121x_set_tcp_retry_mode(&gs_handle, reg);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set tcp retry mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: set tcp retry %d.\n", reg);
    res = ch9121x_get_tcp_retry_mode(&gs_handle, &reg_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get tcp retry mode failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check tcp retry %s.\n", reg == reg_check ? "ok" : "error");
    
#ifndef CH9121X_DISABLE_FLOW_CONTROL_TEST
    /* ch9121x_set_flow_control/ch9121x_get_flow_control test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_flow_control/ch9121x_get_flow_control test.\n");
    
    /* enable flow control */
    res = ch9121x_set_flow_control(&gs_handle, CH9121X_BOOL_TRUE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set flow control failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: enable flow control.\n");
    res = ch9121x_get_flow_control(&gs_handle, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get flow control failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check flow control %s.\n", enable == CH9121X_BOOL_TRUE ? "ok" : "error");
    
    /* disable flow control */
    res = ch9121x_set_flow_control(&gs_handle, CH9121X_BOOL_FALSE);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set flow control failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    ch9121x_interface_debug_print("ch9121x: disable flow control.\n");
    res = ch9121x_get_flow_control(&gs_handle, &enable);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get flow control failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check flow control %s.\n", enable == CH9121X_BOOL_FALSE ? "ok" : "error");
#endif
    
    /* ch9121x_set_arp_retry test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_set_arp_retry test.\n");
    
    /* set arp retry */
    res = ch9121x_set_arp_retry(&gs_handle, 0, 0);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: set arp retry failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check arp retry %s.\n", res == 0 ? "ok" : "error");
    
    /* ch9121x_get_phy_status test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_get_phy_status test.\n");
    
    /* get phy status */
    res = ch9121x_get_phy_status(&gs_handle, &phy_status);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: get phy status failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    if (phy_status == CH9121X_PHY_STATUS_DISCONNECTED)
    {
        ch9121x_interface_debug_print("ch9121x: phy status is disconnected.\n");
    }
    else if (phy_status == CH9121X_PHY_STATUS_10M_FULL_DUPLEX)
    {
        ch9121x_interface_debug_print("ch9121x: phy status is 10Mbps full duplex.\n");
    }
    else if (phy_status == CH9121X_PHY_STATUS_10M_HALF_DUPLEX)
    {
        ch9121x_interface_debug_print("ch9121x: phy status is 10Mbps half duplex.\n");
    }
    else if (phy_status == CH9121X_PHY_STATUS_100M_FULL_DUPLEX)
    {
        ch9121x_interface_debug_print("ch9121x: phy status is 100Mbps full duplex.\n");
    }
    else if (phy_status == CH9121X_PHY_STATUS_100M_HALF_DUPLEX)
    {
        ch9121x_interface_debug_print("ch9121x: phy status is 100Mbps half duplex.\n");
    }
    else
    {
        ch9121x_interface_debug_print("ch9121x: phy status is unknown.\n");
    }
    
    /* ch9121x_uart_timeout_convert_to_register/ch9121x_uart_timeout_convert_to_data test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_uart_timeout_convert_to_register/ch9121x_uart_timeout_convert_to_data test.\n");

    /* random ms */
    ms = (rand() % 10) * 5;

    /* uart timeout convert to register */
    res = ch9121x_uart_timeout_convert_to_register(&gs_handle, ms, &reg);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: uart timeout convert to register failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: uart timeout convert to register %d.\n", ms);

    /* uart timeout convert to data */
    res = ch9121x_uart_timeout_convert_to_data(&gs_handle, reg, &ms_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: uart timeout convert to data failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }

    /* output */
    ch9121x_interface_debug_print("ch9121x: check uart timeout convert %s.\n", ms == ms_check ? "ok" : "error");
    
    /* ch9121x_tcp_retry_time_convert_to_register/ch9121x_tcp_retry_time_convert_to_data test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_tcp_retry_time_convert_to_register/ch9121x_tcp_retry_time_convert_to_data test.\n");
    
    ms = (rand() % 7) * 500;
    res = ch9121x_tcp_retry_time_convert_to_register(&gs_handle, ms, &reg);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: tcp retry time convert to register failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: tcp retry time convert to register %d.\n", ms);
    
    res = ch9121x_tcp_retry_time_convert_to_data(&gs_handle, reg, &ms_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: tcp retry time convert to data failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check tcp retry time convert %s.\n", ms == ms_check ? "ok" : "error");
    
    /* ch9121x_arp_retry_period_convert_to_register/ch9121x_arp_retry_period_convert_to_data test */
    ch9121x_interface_debug_print("ch9121x: ch9121x_arp_retry_period_convert_to_register/ch9121x_arp_retry_period_convert_to_data test.\n");
    
    ms = (rand() % 7) * 100;
    res = ch9121x_arp_retry_period_convert_to_register(&gs_handle, ms, &reg);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: arp retry period convert to register failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: arp retry period convert to register %d.\n", ms);
    
    res = ch9121x_arp_retry_period_convert_to_data(&gs_handle, reg, &ms_check);
    if (res != 0)
    {
        ch9121x_interface_debug_print("ch9121x: arp retry period convert to data failed.\n");
        (void)ch9121x_deinit(&gs_handle);

        return 1;
    }
    
    /* output */
    ch9121x_interface_debug_print("ch9121x: check arp retry period convert %s.\n", ms == ms_check ? "ok" : "error");
    
    /* finish register test */
    ch9121x_interface_debug_print("ch9121x: finish register test.\n");
    (void)ch9121x_deinit(&gs_handle);

    return 0;
}
