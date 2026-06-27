### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

UART Pin: TX/RX GPIO14/GPIO15.

GPIO Pin: RSTI/CFG GPIO27/GPIO17.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
# open another terminal
./ch9121x_server 

# use the CMake terminal
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ch9121x REQUIRED)
```

### 3. CH9121X

#### 3.1 Command Instruction

1. Show ch9121x chip and driver information.

   ```shell
   ch9121x (-i | --information)
   ```

2. Show ch9121x help.

   ```shell
   ch9121x (-h | --help)
   ```

3. Show ch9121x pin connections of the current board.

   ```shell
   ch9121x (-p | --port)
   ```

4. Run ch9121x register test.

   ```shell
   ch9121x (-t reg | --test=reg)
   ```

5. Run ch9121x net test.

   ```shell
   ch9121x (-t net | --test=net) [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>]
   ```

6. Run ch9121x net init function.

   ```shell
   ch9121x (-e net-init | --example=net-init)
   ```

7. Run ch9121x net deinit function.

   ```shell
   ch9121x (-e net-deinit | --example=net-deinit)
   ```

8. Run ch9121x config function, sip is the source ip, sport is the source port, mask is the subnet mask, gateway is the gateway, dip is the dest ip and dport is the dest port.

   ```shell
   ch9121x (-e net-cfg | --example=net-cfg) [--uport=<1 | 2>] [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>] [--sip=<sip>] [--sport=<sport>] [--mask=<mask>] [--gateway=<gateway>] [--dip=<dip>] [--dport=<dport>]
   ```

9. Run ch9121x net write function, str is the write data.

   ```shell
   ch9121x (-e net-write | --example=net-write) [--data=<str>]
   ```

10. Run ch9121x net read function.

    ```shell
    ch9121x (-e net-read | --example=net-read)
    ```
    
#### 3.2 How to run

```shell
# open one terminal and run the server
./ch9121x_server 
```
```shell
# open another terminal and sent the command
./ch9121x xxx xxx xxx ...
```

#### 3.3 Command Example

```shell
./ch9121x -i

ch9121x: chip is WCH CH9121X.
ch9121x: manufacturer is WCH.
ch9121x: interface is UART.
ch9121x: driver version is 1.0.
ch9121x: min supply voltage is 2.7V.
ch9121x: max supply voltage is 3.6V.
ch9121x: max current is 190.00mA.
ch9121x: max temperature is 85.0C.
ch9121x: min temperature is -40.0C.
```

```shell
./ch9121x -p

ch9121x: TX connected to GPIO15(BCM).
ch9121x: RX connected to GPIO14(BCM).
ch9121x: RSTI connected to GPIO27(BCM).
ch9121x: CFG connected to GPIO17(BCM).
```

```shell
./ch9121x -t reg

ch9121x: chip is WCH CH9121X.
ch9121x: manufacturer is WCH.
ch9121x: interface is UART.
ch9121x: driver version is 1.0.
ch9121x: min supply voltage is 3.2V.
ch9121x: max supply voltage is 3.4V.
ch9121x: max current is 76.20mA.
ch9121x: max temperature is 85.0C.
ch9121x: min temperature is -40.0C.
ch9121x: start register test.
ch9121x: ch9121x_get_version test.
ch9121x: version is 0x2A.
ch9121x: ch9121x_save_to_eeprom test.
ch9121x: check save to eeprom ok.
ch9121x: ch9121x_exit test.
ch9121x: check exit ok.
ch9121x: ch9121x_set_port2 test.
ch9121x: disable port2.
ch9121x: check port2 ok.
ch9121x: enable port2.
ch9121x: check port2 ok.
ch9121x: ch9121x_set_disconnect_with_no_rj45/ch9121x_get_disconnect_with_no_rj45 test.
ch9121x: disable disconnect with no rj45.
ch9121x: check disconnect with no rj45 ok.
ch9121x: enable disconnect with no rj45.
ch9121x: check disconnect with no rj45 ok.
ch9121x: ch9121x_set_domain test.
ch9121x: set domain www.ch9121x.com.
ch9121x: check domain ok.
ch9121x: ch9121x_set_dhcp/ch9121x_get_dhcp test.
ch9121x: disable dhcp.
ch9121x: check dhcp ok.
ch9121x: enable dhcp.
ch9121x: check dhcp ok.
ch9121x: ch9121x_set_mac/ch9121x_get_mac test.
ch9121x: set mac 0xAE 0x1C 0xEA 0x0B 0x23 0x04.
ch9121x: check mac[0] ok.
ch9121x: check mac[1] ok.
ch9121x: check mac[2] ok.
ch9121x: check mac[3] ok.
ch9121x: check mac[4] ok.
ch9121x: check mac[5] ok.
ch9121x: ch9121x_clear_mac test.
ch9121x: default mac is 0x3C 0xAB 0x72 0x52 0x81 0xDD.
ch9121x: ch9121x_set_ip/ch9121x_get_ip test.
ch9121x: set ip 119.193.33.150.
ch9121x: check ip ok.
ch9121x: ch9121x_set_subnet_mask/ch9121x_get_subnet_mask test.
ch9121x: set subnet mask 28.81.50.9.
ch9121x: check subnet mask ok.
ch9121x: ch9121x_set_gateway/ch9121x_get_gateway test.
ch9121x: set gateway 177.105.156.251.
ch9121x: check gateway ok.
ch9121x: ch9121x_get_status test.
ch9121x: get port1 status disconnect.
ch9121x: get port2 status disconnect.
ch9121x: ch9121x_set_mode/ch9121x_get_mode test.
ch9121x: set port1 tcp server mode.
ch9121x: check mode ok.
ch9121x: set port1 tcp client mode.
ch9121x: check mode ok.
ch9121x: set port1 udp server mode.
ch9121x: check mode ok.
ch9121x: set port1 udp client mode.
ch9121x: check mode ok.
ch9121x: set port2 tcp server mode.
ch9121x: check mode ok.
ch9121x: set port2 tcp client mode.
ch9121x: check mode ok.
ch9121x: set port2 udp server mode.
ch9121x: check mode ok.
ch9121x: set port2 udp client mode.
ch9121x: check mode ok.
ch9121x: ch9121x_set_source_port/ch9121x_get_source_port test.
ch9121x: set source port1 57361.
ch9121x: check source port ok.
ch9121x: set source port2 26258.
ch9121x: check source port ok.
ch9121x: ch9121x_set_dest_ip/ch9121x_get_dest_ip test.
ch9121x: set port1 dest ip 17.175.189.19.
ch9121x: check dest ip ok.
ch9121x: set port2 dest ip 106.167.111.67.
ch9121x: check dest ip ok.
ch9121x: ch9121x_set_dest_port/ch9121x_get_dest_port test.
ch9121x: set dest port1 60428.
ch9121x: check dest port ok.
ch9121x: set dest port2 24378.
ch9121x: check dest port ok.
ch9121x: ch9121x_set_uart_baud/ch9121x_get_uart_baud test.
ch9121x: set port1 uart baud 9600.
ch9121x: check uart baud ok.
ch9121x: set port2 uart baud 9600.
ch9121x: check uart baud ok.
ch9121x: ch9121x_set_uart_config/ch9121x_get_uart_config test.
ch9121x: set port1 data_bit 8, parity none, stop_bit 1.
ch9121x: check uart data bit ok.
ch9121x: check uart parity ok.
ch9121x: check uart stop bit ok.
ch9121x: set port2 data_bit 8, parity none, stop_bit 1.
ch9121x: check uart data bit ok.
ch9121x: check uart parity ok.
ch9121x: check uart stop bit ok.
ch9121x: ch9121x_set_uart_timeout/ch9121x_get_uart_timeout test.
ch9121x: set port1 uart timeout 128.
ch9121x: check uart timeout ok.
ch9121x: set port2 uart timeout 196.
ch9121x: check uart timeout ok.
ch9121x: ch9121x_set_source_port_random/ch9121x_get_source_port_random test.
ch9121x: enable port1 source port random.
ch9121x: check source port random ok.
ch9121x: disable port1 source port random.
ch9121x: check source port random ok.
ch9121x: enable port2 source port random.
ch9121x: check source port random ok.
ch9121x: disable port2 source port random.
ch9121x: check source port random ok.
ch9121x: ch9121x_set_uart_buffer_length/ch9121x_get_uart_buffer_length test.
ch9121x: set port1 uart buffer length 170.
ch9121x: check uart buffer length ok.
ch9121x: set port2 uart buffer length 146.
ch9121x: check uart buffer length ok.
ch9121x: ch9121x_set_uart_flush/ch9121x_get_uart_flush test.
ch9121x: enable port1 uart flush.
ch9121x: check uart flush ok.
ch9121x: disable port1 uart flush.
ch9121x: check uart flush ok.
ch9121x: enable port2 uart flush.
ch9121x: check uart flush ok.
ch9121x: disable port2 uart flush.
ch9121x: check uart flush ok.
ch9121x: ch9121x_set_eth_cfg/ch9121x_get_eth_cfg test.
ch9121x: enable eth cfg.
ch9121x: check eth cfg ok.
ch9121x: ch9121x_set_uart_clock_mode/ch9121x_get_uart_clock_mode test.
ch9121x: set uart clock mode default.
ch9121x: check uart clock mode ok.
ch9121x: set uart clock mode classical.
ch9121x: check uart clock mode ok.
ch9121x: ch9121x_set_tcp_retry_mode/ch9121x_get_tcp_retry_mode test.
ch9121x: set tcp retry 2.
ch9121x: check tcp retry ok.
ch9121x: ch9121x_set_arp_retry test.
ch9121x: check arp retry ok.
ch9121x: ch9121x_get_phy_status test.
ch9121x: phy status is 100Mbps full duplex.
ch9121x: ch9121x_uart_timeout_convert_to_register/ch9121x_uart_timeout_convert_to_data test.
ch9121x: uart timeout convert to register 30.
ch9121x: check uart timeout convert ok.
ch9121x: ch9121x_arp_retry_period_convert_to_register/ch9121x_arp_retry_period_convert_to_data test.
ch9121x: arp retry period convert to register 500.
ch9121x: check arp retry period convert ok.
ch9121x: finish register test.
```

```shell
./ch9121x -t net --mode=TCP_CLIENT

ch9121x: chip is WCH CH9121X.
ch9121x: manufacturer is WCH.
ch9121x: interface is UART.
ch9121x: driver version is 1.0.
ch9121x: min supply voltage is 2.7V.
ch9121x: max supply voltage is 3.6V.
ch9121x: max current is 190.00mA.
ch9121x: max temperature is 85.0C.
ch9121x: min temperature is -40.0C.
ch9121x: start net test.
ch9121x: tcp client dest port 2000, dest ip 192.168.1.10.
ch9121x: write LibDriver.
ch9121x: finish net test.
```

```shell
./ch9121x -t net --mode=TCP_SERVER

ch9121x: chip is WCH CH9121X.
ch9121x: manufacturer is WCH.
ch9121x: interface is UART.
ch9121x: driver version is 1.0.
ch9121x: min supply voltage is 2.7V.
ch9121x: max supply voltage is 3.6V.
ch9121x: max current is 190.00mA.
ch9121x: max temperature is 85.0C.
ch9121x: min temperature is -40.0C.
ch9121x: start net test.
ch9121x: tcp server src port 1000, src ip 192.168.1.230.
ch9121x: read L.
ch9121x: finish net test.
```

```shell
./ch9121x -t net --mode=UDP_CLIENT

ch9121x: chip is WCH CH9121X.
ch9121x: manufacturer is WCH.
ch9121x: interface is UART.
ch9121x: driver version is 1.0.
ch9121x: min supply voltage is 2.7V.
ch9121x: max supply voltage is 3.6V.
ch9121x: max current is 190.00mA.
ch9121x: max temperature is 85.0C.
ch9121x: min temperature is -40.0C.
ch9121x: start net test.
ch9121x: udp client dest port 2000, dest ip 192.168.1.10.
ch9121x: write LibDriver.
ch9121x: write LibDriver.
ch9121x: write LibDriver.
ch9121x: write LibDriver.
ch9121x: write LibDriver.
ch9121x: write LibDriver.
ch9121x: write LibDriver.
ch9121x: write LibDriver.
ch9121x: write LibDriver.
ch9121x: write LibDriver.
ch9121x: finish net test.
```

```shell
./ch9121x -t net --mode=UDP_SERVER

ch9121x: chip is WCH CH9121X.
ch9121x: manufacturer is WCH.
ch9121x: interface is UART.
ch9121x: driver version is 1.0.
ch9121x: min supply voltage is 2.7V.
ch9121x: max supply voltage is 3.6V.
ch9121x: max current is 190.00mA.
ch9121x: max temperature is 85.0C.
ch9121x: min temperature is -40.0C.
ch9121x: start net test.
ch9121x: udp server src port 1000, src ip 192.168.1.230.
ch9121x: read L.
ch9121x: finish net test.
```

```shell
./ch9121x -e net-init

ch9121x: net init.
```

```shell
./ch9121x -e net-deinit

ch9121x: net deinit.
```

```shell
./ch9121x -e net-cfg --uport=1 --mode=TCP_CLIENT --sip=192.168.1.230 --sport=1000 --mask=255.255.255.0 --gateway=192.168.1.1 --dip=192.168.1.10 --dport=2000

ch9121x: source ip 192.168.1.230.
ch9121x: source port 1000.
ch9121x: subnet mask 255.255.255.0.
ch9121x: gateway 192.168.1.1.
ch9121x: dest ip 192.168.1.10.
ch9121x: dest port 2000.
```

```shell
./ch9121x -e net-write --data=LibDriver

ch9121x: net write LibDriver.
```

```shell
./ch9121x -e net-read

ch9121x: net read LibDriver.
```

```shell
./ch9121x -h

Usage:
  ch9121x (-i | --information)
  ch9121x (-h | --help)
  ch9121x (-p | --port)
  ch9121x (-t reg | --test=reg)
  ch9121x (-t net | --test=net) [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>]
  ch9121x (-e net-init | --example=net-init)
  ch9121x (-e net-deinit | --example=net-deinit)
  ch9121x (-e net-cfg | --example=net-cfg) [--uport=<1 | 2>] [--mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER>]
          [--sip=<sip>] [--sport=<sport>] [--mask=<mask>] [--gateway=<gateway>] [--dip=<dip>] [--dport=<dport>]
  ch9121x (-e net-write | --example=net-write) [--data=<str>]
  ch9121x (-e net-read | --example=net-read)

Options:
  -e <net-init | net-deinit | net-cfg | net-write | net-read>, --example=<net-init | net-deinit | net-cfg | net-write | net-read>
                             Run the driver example.
      --data=<str>           Set write data.([default: LibDriver])
      --dip=<dip>            Set the dest ip.([default: 192.168.1.10])
      --dport=<dport>        Set dest port.([default: 1000])
      --gateway=<gateway>    Set the gateway.([default: 192.168.1.1])
  -h, --help                 Show the help.
  -i, --information          Show the chip information.
      --mask=<mask>          Set the subnet mask.([default: 255.255.255.0])
      --mode=<TCP_CLIENT | TCP_SERVER | UDP_CLIENT | UDP_SERVER
                             Set the chip mode.([default: TCP_CLIENT])
  -p, --port                 Display the pin connections of the current board.
      --sip=<sip>            Set the source ip.([default: 192.168.1.230])
      --sport=<sport>        Set source port.([default: 2000])
  -t <reg | net>, --test=<reg | net>
                             Run the driver test.
      --uport=<1 | 2>        Set the uart port.([default: 1])
```
