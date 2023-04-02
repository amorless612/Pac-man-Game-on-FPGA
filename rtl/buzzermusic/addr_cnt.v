module addr_cnt(
    input clk,
    input en,
    input rst_n,
    input [1:0] sel,
    output reg addr_finish,
    output reg [11:0] data
);
reg [15:0] addr;
reg en_1;
reg en_2;
reg en_3;
reg en_4;
wire [11:0] data_1;
wire [11:0] data_2;
wire [11:0] data_3;
wire [11:0] data_4;

//第一首歌
BlockROM11 #(
     .ADDR_WIDTH(16)
    ,.DATA_WIDTH(12)
) BlockROM11 (
     .clk(clk)
    ,.en(en_1)
    ,.addr_i(addr)
    ,.data_o(data_1)
);
//第二首歌
BlockROM22 #(
     .ADDR_WIDTH(16)
    ,.DATA_WIDTH(12)
) BlockROM22 (
     .clk(clk)
    ,.en(en_2)
    ,.addr_i(addr)
    ,.data_o(data_2)
);
//第三首歌
BlockROM33 #(
    .ADDR_WIDTH(16)
    ,.DATA_WIDTH(12)
) BlockROM33(
    .clk(clk)
    ,.en(en_3)
    ,.addr_i(addr)
    ,.data_o(data_3)
);
//第四首歌
BlockROM44 #(
    .ADDR_WIDTH(16)
    ,.DATA_WIDTH(12)
) BlockROM44(
    .clk(clk)
    ,.en(en_4)
    ,.addr_i(addr)
    ,.data_o(data_4)
);
always@(*)begin
    case(sel)
    2'b00:begin
        en_1 = 1'd1;
        en_2 = 1'd0;
        en_3 = 1'd0;
        en_4 = 1'd0;
        data = data_1;
    end 
    2'b01:begin
        en_1 = 1'd0;
        en_2 = 1'd1;
        en_3 = 1'd0;
        en_4 = 1'd0;
        data = data_2;
    end 
    2'b10:begin
        en_1 = 1'd0;
        en_2 = 1'd0;
        en_3 = 1'd1;
        en_4 = 1'd0;
        data = data_3;
    end
    2'b11:begin
        en_1 = 1'd0;
        en_2 = 1'd0;
        en_3 = 1'd0;
        en_4 = 1'd1;
        data = data_4;
    end
    default:begin
        en_1 = 1'd0;
        en_2 = 1'd0;
        en_3 = 1'd0;
        en_4 = 1'd0;
        data = 12'b0;
    end
    endcase
end

always @(posedge clk) begin 
    if (~rst_n)begin
        addr<=16'd0;
        addr_finish<=1'd0;
    end
    else begin
        if (en) begin
            if (data == 12'h0) begin
                addr_finish<=1'b1;
                addr<=16'd0;
            end
            addr<=addr+1'b1;
        end
    end
    end
endmodule
