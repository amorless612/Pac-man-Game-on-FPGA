module beat_cnt(
    input clk,
    input en,
    input rst_n,
    input [27:0] beat_cnt_parameter,
    output reg beat_finish,
    output music_interrupt
);
reg [27:0] cnt;
always @(posedge clk ) begin
    if(!rst_n)begin
        cnt<=28'd0;
        beat_finish<=1'd0;
    end   
    else begin
        if(en)begin
            if(cnt == beat_cnt_parameter)begin
                beat_finish <= 1'd1;
                cnt <= 1'd0;
            end
            cnt <= cnt + 1'd1;
        end
    end
end
assign music_interrupt=beat_finish;
endmodule
