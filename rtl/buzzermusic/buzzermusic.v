module buzzermusic(
    input           clk,
    input           rstn,
    input           [1:0]    music_select,
    input           music_start,
    output          beep,
    output          music_interrupt,
    output  [19:0]  music_tune
);

wire en;
assign en=music_start;

wire addr_finish;
wire beat_finish;
wire addr_en;
wire addr_rstn;
wire tune_pwm_en;
wire tune_pwm_rstn;
wire beat_cnt_en;
wire beat_cnt_rstn;
bzmusic_ctrl bzmusic_ctrl(
    .clk             (clk)
    ,.en             (en)
    ,.rstn           (rstn)
    ,.addr_finish    (addr_finish)
    ,.beat_finish    (beat_finish)
    ,.sel            (music_select)
    ,.addr_en        (addr_en)
    ,.addr_rstn      (addr_rstn)
    ,.tune_pwm_en    (tune_pwm_en)
    ,.tune_pwm_rstn  (tune_pwm_rstn)
    ,.beat_cnt_en    (beat_cnt_en)
    ,.beat_cnt_rstn  (beat_cnt_rstn) 
);

wire [11:0] data;
addr_cnt addr_cnt(
     .clk          (clk)
    ,.en           (addr_en)
    ,.rst_n        (addr_rstn)
    ,.addr_finish  (addr_finish)
    ,.data         (data)
    ,.sel          (music_select)
);

wire [19:0] tune_pwm_parameter;
assign music_tune=tune_pwm_parameter;

tune_decoder tune_decoder(
     .tune                (data[11:4])
    ,.tune_pwm_parameter  (tune_pwm_parameter)
);

tune_pwm tune_pwm(     
     .clk            (clk)
    ,.en             (tune_pwm_en)
    ,.rst_n          (tune_pwm_rstn)
    ,.pwm_parameter  (tune_pwm_parameter)
    ,.clk_pwm        (beep)
);

wire [27:0]  beat_cnt_parameter;      
beat_decoder beat_decoder(
     .beat                (data[3:0])
    ,.beat_cnt_parameter  (beat_cnt_parameter)
);

beat_cnt beat_cnt(
     .clk                 (clk)
    ,.en                  (beat_cnt_en)
    ,.rst_n                (beat_cnt_rstn)
    ,.beat_cnt_parameter  (beat_cnt_parameter)
    ,.beat_finish         (beat_finish) 
    ,.music_interrupt     (music_interrupt)  
);

endmodule