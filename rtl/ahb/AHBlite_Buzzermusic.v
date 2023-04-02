module AHBlite_Buzzermusic(
    input  wire           HCLK,
    input  wire           HRESETn,
    input  wire           HSEL,
    input  wire   [31:0]  HADDR,
    input  wire    [1:0]  HTRANS,
    input  wire    [2:0]  HSIZE,
    input  wire    [3:0]  HPROT,
    input  wire           HWRITE,
    input  wire   [31:0]  HWDATA,
    input  wire           HREADY,
    output wire           HREADYOUT,
    output wire   [31:0]  HRDATA,
    output wire           HRESP,

    output reg     [1:0]  music_select,
    output reg            music_start,
    input         [19:0]  music_tune
);

assign HRESP = 1'b0;
assign HREADYOUT = 1'b1;

wire write_en;
assign write_en = HSEL & HTRANS[1] & HWRITE & HREADY;

reg wr_en_reg;

always@(posedge HCLK or negedge HRESETn) begin
  if(~HRESETn) wr_en_reg <= 1'b0;
  else if(write_en) wr_en_reg <= 1'b1;
  else wr_en_reg <= 1'b0;
end

always@(posedge HCLK or negedge HRESETn)begin
  if(~HRESETn)begin
    music_start<=1'd0;music_select<=2'd0;
  end else begin
  if(wr_en_reg)begin
    music_start<=HWDATA[4];music_select<=HWDATA[1:0];
  end
end
end

assign HRDATA = {12'd0,music_tune};

endmodule