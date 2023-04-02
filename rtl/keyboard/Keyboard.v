 module Keyboard(
    input                 clk,
    input                 rstn,
    input                 key_clear,
    input        [3 :0]   col,
    output       [3 :0]   row,
//    input     [15:0]      key_pluse,
    output                key_interrupt,
    output       [15:0]   key_data
);

wire  [15:0]  key;
keyboard_scan keyboard_scan(
     .clk(clk)
    ,.rstn(rstn)
    ,.col(col)
    ,.row(row)
    ,.key(key)
);

wire [15:0] key_pluse;
keyboard_filter keyboard_filter(
     .clk(clk)
    ,.rstn(rstn)
    ,.key_in(key)
    ,.key_pluse(key_pluse)
);

assign key_interrupt = |key_pluse ;

keyboard_reg keyboard_reg(
     .clk(clk)
    ,.rstn(rstn)
    ,.key_clear(key_clear)
    ,.key_pluse(key_pluse)
    ,.key_reg(key_data)
);

endmodule