module beat_decoder(
    input [3:0] beat,
    output reg [27:0] beat_cnt_parameter
);
localparam quanyinfu  =28'h2FAF080;         //全音�??40000000 h2625a00
localparam erfenyinfu =28'h17D7840;         //二分音符20000000 h1312d00
localparam sifenyinfu =28'hBEBC20;         //四分音符10000000 h989680
localparam bafenyinfu =28'h5F5E10;          //八分音符5000000 h4c4b40
localparam shiliufenyinfu =28'h2FAF08;      //十六分音�??2500000 h2625a0

always@(beat)begin
    case(beat)
    4'h5: beat_cnt_parameter = shiliufenyinfu;//十六分音�??
    4'h4: beat_cnt_parameter = bafenyinfu;//八分音符
    4'h3: beat_cnt_parameter = sifenyinfu;//四分音符
    4'h2: beat_cnt_parameter = erfenyinfu;//二分音符
    4'h1: beat_cnt_parameter = quanyinfu;//全音�??
    default:beat_cnt_parameter = 28'h0;
    endcase
end
endmodule
