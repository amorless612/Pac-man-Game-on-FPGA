module tune_decoder(
    input        [7 :0]  tune,
    output  reg  [19:0]  tune_pwm_parameter
);
localparam tune_pwm_parameter_pause = 20'h0    ;//休止符不发声
localparam tune_pwm_parameter_do    = 20'h2EA9B;//低音do 261.6hz 191131
localparam tune_pwm_parameter_ri    = 20'h29902;//低音ri 293.7hz 170242
localparam tune_pwm_parameter_mi    = 20'h25093;//低音mi 329.6hz 151699
localparam tune_pwm_parameter_fa    = 20'h22F50;//低音fa 349.2hz 143184
localparam tune_pwm_parameter_so    = 20'h1F23F;//低音so 392hz 127551
localparam tune_pwm_parameter_la    = 20'h1BBE4;//低音la 440hz 113636
localparam tune_pwm_parameter_xi    = 20'h18B73;//低音xi 493.9hz 101235
localparam tune_pwm_parameter_Do    = 20'h1753B;//中音do 523.3hz 95547
localparam tune_pwm_parameter_Ri    = 20'h14C8F;//中音ri 587.3hz 85135
localparam tune_pwm_parameter_Mi    = 20'h1283E;//中音mi 659.3hz 75838
localparam tune_pwm_parameter_Fa    = 20'h11B44;//中音fa 698.5hz 72516
localparam tune_pwm_parameter_So    = 20'hF920; //中音so 784hz 63776
localparam tune_pwm_parameter_upSo  = 20'hEB08; //中音升so 831hz 60168
localparam tune_pwm_parameter_La    = 20'hDDF2; //中音la 880hz 56818
localparam tune_pwm_parameter_Xi    = 20'hC5BA; //中音xi 987.8hz 50618
localparam tune_pwm_parameter_DO    = 20'hBAA2; //高音do 1046.5hz 47778
localparam tune_pwm_parameter_upDO  = 20'hb029; //高音升do 1108.73hz 45097
localparam tune_pwm_parameter_RI    = 20'hA644; //高音ri 1174.7hz 42564
localparam tune_pwm_parameter_upRI  = 20'h9cf0; //高音升ri 1244.5hz 40176
localparam tune_pwm_parameter_MI    = 20'h9422; //高音mi 1318.5hz 37922
localparam tune_pwm_parameter_FA    = 20'h8BD2; //高音fa 1396.9hz 35794
localparam tune_pwm_parameter_upFA  = 20'h83fa; //高音升fa 1479.9hz 33786
localparam tune_pwm_parameter_SO    = 20'h7C90; //高音so 1568hz 31888
localparam tune_pwm_parameter_upSO  = 20'h7593; //高音升so 1661.2hz 30099
localparam tune_pwm_parameter_LA    = 20'h6EF9; //高音la 1760hz  28409
localparam tune_pwm_parameter_XI    = 20'h62DE; //高音xi 1975.5hz 25310/50M
localparam tune_pwm_parameter_DOO   = 20'h5d4b; //更高音do 2093.5hz 23883
always @(tune) begin
    case (tune)
        8'h00: tune_pwm_parameter = tune_pwm_parameter_pause;
        8'h11: tune_pwm_parameter = tune_pwm_parameter_do;
        8'h12: tune_pwm_parameter = tune_pwm_parameter_ri;
        8'h13: tune_pwm_parameter = tune_pwm_parameter_mi;
        8'h14: tune_pwm_parameter = tune_pwm_parameter_fa;
        8'h15: tune_pwm_parameter = tune_pwm_parameter_so;
        8'h16: tune_pwm_parameter = tune_pwm_parameter_la;
        8'h17: tune_pwm_parameter = tune_pwm_parameter_xi;
        8'h21: tune_pwm_parameter = tune_pwm_parameter_Do;
        8'h22: tune_pwm_parameter = tune_pwm_parameter_Ri;
        8'h23: tune_pwm_parameter = tune_pwm_parameter_Mi;
        8'h24: tune_pwm_parameter = tune_pwm_parameter_Fa;
        8'h25: tune_pwm_parameter = tune_pwm_parameter_So;
        8'h65: tune_pwm_parameter = tune_pwm_parameter_upSo;
        8'h26: tune_pwm_parameter = tune_pwm_parameter_La;
        8'h27: tune_pwm_parameter = tune_pwm_parameter_Xi;       
        8'h31: tune_pwm_parameter = tune_pwm_parameter_DO;
        8'h51: tune_pwm_parameter = tune_pwm_parameter_upDO;
        8'h32: tune_pwm_parameter = tune_pwm_parameter_RI;
        8'h52: tune_pwm_parameter = tune_pwm_parameter_upRI;
        8'h33: tune_pwm_parameter = tune_pwm_parameter_MI;
        8'h34: tune_pwm_parameter = tune_pwm_parameter_FA;
        8'h54: tune_pwm_parameter = tune_pwm_parameter_upFA;
        8'h35: tune_pwm_parameter = tune_pwm_parameter_SO;
        8'h55: tune_pwm_parameter = tune_pwm_parameter_upSO;
        8'h36: tune_pwm_parameter = tune_pwm_parameter_LA;
        8'h37: tune_pwm_parameter = tune_pwm_parameter_XI;
        8'h41: tune_pwm_parameter = tune_pwm_parameter_DOO;
        default:tune_pwm_parameter = 20'd0; 
    endcase 
end

endmodule