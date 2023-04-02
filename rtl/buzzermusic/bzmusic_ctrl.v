module bzmusic_ctrl(
    input clk,
    input en,
    input rstn,
    input addr_finish ,
    input beat_finish,
    input [1:0] sel,
    output reg addr_en,      
    output reg addr_rstn,    
    output reg tune_pwm_en , 
    output reg tune_pwm_rstn,
    output reg beat_cnt_en  ,    
    output reg beat_cnt_rstn     
);

wire rstn_music_switch;
//assign rstn_music_switch=rstn;
reg [1:0] sel_temp;
//判断sel是否变化，变化则输出复位信号
always@(posedge clk or negedge rstn)begin
    if(~rstn)begin
        sel_temp <=2'd0;
    end
    else begin
        sel_temp <= sel;
    end
end
assign rstn_music_switch=(sel_temp != sel)?1'd0:1'd1;
/*always@(*)begin
    if(sel_temp != sel)begin
        rstn_music_switch=1'd0 ;
    end
    else begin 
        rstn_music_switch=1'd1 ;
    end
end*/
//状�?�机
reg [1:0] c_s;
reg [1:0] n_s;
parameter s0=2'b00;
parameter s1=2'b01;
parameter s2=2'b10;
always @(posedge clk or negedge rstn)begin
    if (~rstn )begin
        c_s <= s0;
    end
       else begin
            if (~rstn_music_switch)begin
                c_s <= s0;
            end
            else begin
                c_s <= n_s;
            end
       end
end

always @(*)begin
    case(c_s)
    s0:begin
            if (en)
            n_s=s1;
            else 
            n_s=s0;
        end
    s1:begin
            if(addr_finish)
            n_s=s0;
            else 
            n_s=s2;
        end
    s2:begin
            if (beat_finish)
            n_s=s1;
            else
            n_s=s2;
        end
    default:n_s=s0;
    endcase
end

always@(*)begin
    case(c_s)
    s0: begin 
    addr_en       = 1'd0;
    addr_rstn     = 1'd0;
    tune_pwm_en   = 1'd0;
    tune_pwm_rstn = 1'd0;
    beat_cnt_en   = 1'd0;
    beat_cnt_rstn = 1'd0;
    end
    s1:begin
    addr_en       = 1'd1;
    addr_rstn     = 1'd1;
    tune_pwm_en   = 1'd0;
    tune_pwm_rstn = 1'd0;
    beat_cnt_en   = 1'd0;
    beat_cnt_rstn = 1'd0;
    end 
    s2:begin
    addr_en       = 1'd0;
    addr_rstn     = 1'd1;
    tune_pwm_en   = 1'd1;
    tune_pwm_rstn = 1'd1;
    beat_cnt_en   = 1'd1;
    beat_cnt_rstn = 1'd1;  
    end
    default:begin
    addr_en       = 1'd0;
    addr_rstn     = 1'd0;
    tune_pwm_en   = 1'd0;
    tune_pwm_rstn = 1'd0;
    beat_cnt_en   = 1'd0;
    beat_cnt_rstn = 1'd0;
    end
    endcase 
end
endmodule