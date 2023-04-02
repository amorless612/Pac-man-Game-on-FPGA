##clk
set_property PACKAGE_PIN D4 [get_ports sys_clk]
set_property IOSTANDARD LVCMOS33 [get_ports sys_clk]
##RSTn
set_property PACKAGE_PIN T9 [get_ports sys_rst_n]
set_property IOSTANDARD LVCMOS33 [get_ports sys_rst_n]

##DEBUGGER
set_property PACKAGE_PIN H14 [get_ports SWDIO]
set_property IOSTANDARD LVCMOS33 [get_ports SWDIO]
set_property PACKAGE_PIN H12 [get_ports SWCLK]
set_property IOSTANDARD LVCMOS33 [get_ports SWCLK]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets SWCLK]

##keyboard
set_property IOSTANDARD LVCMOS33 [get_ports {col[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {col[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {col[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {col[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {row[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {row[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {row[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {row[0]}]

set_property PACKAGE_PIN T10 [get_ports {col[3]}]
set_property PACKAGE_PIN R11 [get_ports {col[2]}]
set_property PACKAGE_PIN T12 [get_ports {col[1]}]
set_property PACKAGE_PIN R12 [get_ports {col[0]}]
set_property PACKAGE_PIN R10 [get_ports {row[3]}]
set_property PACKAGE_PIN P10 [get_ports {row[2]}]
set_property PACKAGE_PIN M6 [get_ports {row[1]}]
set_property PACKAGE_PIN K3 [get_ports {row[0]}]


##lcd
set_property PACKAGE_PIN A3 [get_ports LCD_CS]
set_property PACKAGE_PIN D3 [get_ports LCD_RS]
set_property PACKAGE_PIN B4 [get_ports LCD_WR]
set_property PACKAGE_PIN A4 [get_ports LCD_RD]
set_property PACKAGE_PIN B5 [get_ports LCD_RST]
set_property PACKAGE_PIN C8 [get_ports LCD_BL_CTR]

set_property PACKAGE_PIN A5 [get_ports {LCD_DATA[0]}]
set_property PACKAGE_PIN B6 [get_ports {LCD_DATA[1]}]
set_property PACKAGE_PIN B7 [get_ports {LCD_DATA[2]}]
set_property PACKAGE_PIN A7 [get_ports {LCD_DATA[3]}]
set_property PACKAGE_PIN C4 [get_ports {LCD_DATA[4]}]
set_property PACKAGE_PIN E5 [get_ports {LCD_DATA[5]}]
set_property PACKAGE_PIN D5 [get_ports {LCD_DATA[6]}]
set_property PACKAGE_PIN D6 [get_ports {LCD_DATA[7]}]
set_property PACKAGE_PIN C6 [get_ports {LCD_DATA[8]}]
set_property PACKAGE_PIN E6 [get_ports {LCD_DATA[9]}]
set_property PACKAGE_PIN C7 [get_ports {LCD_DATA[10]}]
set_property PACKAGE_PIN D8 [get_ports {LCD_DATA[11]}]
set_property PACKAGE_PIN D9 [get_ports {LCD_DATA[12]}]
set_property PACKAGE_PIN C9 [get_ports {LCD_DATA[13]}]
set_property PACKAGE_PIN D10 [get_ports {LCD_DATA[14]}]
set_property PACKAGE_PIN A8 [get_ports {LCD_DATA[15]}]

set_property IOSTANDARD LVCMOS33 [get_ports LCD_CS]
set_property IOSTANDARD LVCMOS33 [get_ports LCD_RS]
set_property IOSTANDARD LVCMOS33 [get_ports LCD_WR]
set_property IOSTANDARD LVCMOS33 [get_ports LCD_RD]
set_property IOSTANDARD LVCMOS33 [get_ports LCD_RST]
set_property IOSTANDARD LVCMOS33 [get_ports LCD_BL_CTR]

set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[8]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[9]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[10]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[11]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[12]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[13]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[14]}]
set_property IOSTANDARD LVCMOS33 [get_ports {LCD_DATA[15]}]


set_property IOSTANDARD LVCMOS33 [get_ports beep]
set_property PACKAGE_PIN L2 [get_ports beep]

set_property IOSTANDARD LVCMOS33 [get_ports RXD]
set_property PACKAGE_PIN J15 [get_ports RXD]
set_property IOSTANDARD LVCMOS33 [get_ports TXD]
set_property PACKAGE_PIN G15 [get_ports TXD]

##VGA
set_property PACKAGE_PIN R13 [get_ports hsync]
set_property IOSTANDARD LVCMOS33 [get_ports hsync]

set_property PACKAGE_PIN T13 [get_ports vsync]
set_property IOSTANDARD LVCMOS33 [get_ports vsync]

set_property PACKAGE_PIN M15 [get_ports {rgb[11]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb[11]}]
set_property PACKAGE_PIN M16 [get_ports {rgb[10]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb[10]}]
set_property PACKAGE_PIN F4 [get_ports {rgb[9]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb[9]}]
set_property PACKAGE_PIN F5 [get_ports {rgb[8]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb[8]}]

set_property PACKAGE_PIN R15 [get_ports {rgb[7]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb[7]}]
set_property PACKAGE_PIN P16 [get_ports {rgb[6]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb[6]}]
set_property PACKAGE_PIN P15 [get_ports {rgb[5]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb[5]}]
set_property PACKAGE_PIN N16 [get_ports {rgb[4]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb[4]}]

set_property PACKAGE_PIN T14 [get_ports {rgb[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb[3]}]
set_property PACKAGE_PIN P14 [get_ports {rgb[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb[2]}]
set_property PACKAGE_PIN T15 [get_ports {rgb[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb[1]}]
set_property PACKAGE_PIN R16 [get_ports {rgb[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb[0]}]



