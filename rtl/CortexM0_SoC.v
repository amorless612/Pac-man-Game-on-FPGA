module CortexM0_SoC
    (
    input  wire                        sys_clk,
    input  wire                        sys_rst_n,
    inout  wire                        SWDIO,  
    input  wire                        SWCLK,

    input  wire                  [3:0] col,
    output wire                  [3:0] row,
    //input  wire               [15:0]  key_pluse,

    output wire                        beep,  
    output wire                        LCD_CS,
    output wire                        LCD_RS,
    output wire                        LCD_WR,
    output wire                        LCD_RD,
    output wire                        LCD_RST,
    output wire                 [15:0] LCD_DATA,
    output wire                        LCD_BL_CTR,

    input  wire                        RXD,
    output wire                        TXD,

    output wire                        hsync,
    output wire                        vsync,
    output wire                 [11:0] rgb
);
//------------------------------------------------------------------------------
// PLL
//------------------------------------------------------------------------------
wire                                             RSTn;
wire                                             clk;
wire                                             vga_clk;
wire                                             locked;

assign RSTn             = (sys_rst_n & locked);
//------------- clk_gen_inst -------------
clk_wiz_0 clk_gen_inst
    (
    .resetn                            (sys_rst_n                              ),
    .clk_in1                           (sys_clk                                ),

    .clk_out1                          (clk                                    ),
    .clk_out2                          (vga_clk                                ),
    .locked                            (locked                                 )
);  
//------------------------------------------------------------------------------
// DEBUG IOBUF 
//------------------------------------------------------------------------------
wire                                              SWDO;
wire                                              SWDOEN;
wire                                              SWDI;

assign SWDI             = SWDIO;
assign SWDIO            = (SWDOEN) ?  SWDO : 1'bz;
//------------------------------------------------------------------------------
// Interrupt
//------------------------------------------------------------------------------
wire                                      [31:0] IRQ;
wire                                             key_interrupt;
wire                                             LCD_INI_FINISH;
wire                                             music_interrupt;
wire                                             RXIRQ;
/*Connect the IRQ with keyboard*/
assign IRQ              = {28'd0,RXIRQ,music_interrupt,LCD_INI_FINISH,key_interrupt};
/***************************/
wire                                             RXEV;
assign RXEV             = 1'b0;
//------------------------------------------------------------------------------
// AHB
//------------------------------------------------------------------------------
wire                                      [31:0] HADDR;
wire                                      [ 2:0] HBURST;
wire                                             HMASTLOCK;
wire                                      [ 3:0] HPROT;
wire                                      [ 2:0] HSIZE;
wire                                      [ 1:0] HTRANS;
wire                                      [31:0] HWDATA;
wire                                             HWRITE;
wire                                      [31:0] HRDATA;
wire                                             HRESP;
wire                                             HMASTER;
wire                                             HREADY;
//------------------------------------------------------------------------------
// RESET AND DEBUG
//------------------------------------------------------------------------------
wire                                             SYSRESETREQ;
reg                                              cpuresetn;

always @(posedge clk or negedge RSTn)begin
        if (~RSTn) cpuresetn <= 1'b0;
        else if (SYSRESETREQ) cpuresetn <= 1'b0;
        else cpuresetn <= 1'b1;
end

wire                                             CDBGPWRUPREQ;
reg                                              CDBGPWRUPACK;

always @(posedge clk or negedge RSTn)begin
        if (~RSTn) CDBGPWRUPACK <= 1'b0;
        else CDBGPWRUPACK <= CDBGPWRUPREQ;
end
//------------------------------------------------------------------------------
// Instantiate Cortex-M0 processor logic level
//------------------------------------------------------------------------------
cortexm0ds_logic u_logic 
    (

    // System inputs
    .FCLK           (clk),           //FREE running clock 
    .SCLK           (clk),           //system clock
    .HCLK           (clk),           //AHB clock
    .DCLK           (clk),           //Debug clock
    .PORESETn       (RSTn),          //Power on reset
    .HRESETn        (cpuresetn),     //AHB and System reset
    .DBGRESETn      (RSTn),          //Debug Reset
    .RSTBYPASS      (1'b0),          //Reset bypass
    .SE             (1'b0),          // dummy scan enable port for synthesis

    // Power management inputs
    .SLEEPHOLDREQn  (1'b1),          // Sleep extension request from PMU
    .WICENREQ       (1'b0),          // WIC enable request from PMU
    .CDBGPWRUPACK   (CDBGPWRUPACK),  // Debug Power Up ACK from PMU

    // Power management outputs
    .CDBGPWRUPREQ   (CDBGPWRUPREQ),
    .SYSRESETREQ    (SYSRESETREQ),

    // System bus
    .HADDR          (HADDR[31:0]),
    .HTRANS         (HTRANS[1:0]),
    .HSIZE          (HSIZE[2:0]),
    .HBURST         (HBURST[2:0]),
    .HPROT          (HPROT[3:0]),
    .HMASTER        (HMASTER),
    .HMASTLOCK      (HMASTLOCK),
    .HWRITE         (HWRITE),
    .HWDATA         (HWDATA[31:0]),
    .HRDATA         (HRDATA[31:0]),
    .HREADY         (HREADY),
    .HRESP          (HRESP),

    // Interrupts
    .IRQ            (IRQ),          //Interrupt
    .NMI            (1'b0),         //Watch dog interrupt
    .IRQLATENCY     (8'h0),
    .ECOREVNUM      (28'h0),

    // Systick
    .STCLKEN        (1'b0),
    .STCALIB        (26'h0),

    // Debug - JTAG or Serial wire
    // Inputs
    .nTRST          (1'b1),
    .SWDITMS        (SWDI),
    .SWCLKTCK       (SWCLK),
    .TDI            (1'b0),
    // Outputs
    .SWDO           (SWDO),
    .SWDOEN         (SWDOEN),

    .DBGRESTART     (1'b0),

    // Event communication
    .RXEV           (RXEV),         // Generate event when a DMA operation completed.
    .EDBGRQ         (1'b0)          // multi-core synchronous halt request
);

//------------------------------------------------------------------------------
// AHBlite Interconncet
//------------------------------------------------------------------------------

wire                                             HSEL_P0;
wire                                     [31:0]  HADDR_P0;
wire                                     [2:0]   HBURST_P0;
wire                                             HMASTLOCK_P0;
wire                                     [3:0]   HPROT_P0;
wire                                     [2:0]   HSIZE_P0;
wire                                     [1:0]   HTRANS_P0;
wire                                     [31:0]  HWDATA_P0;
wire                                             HWRITE_P0;
wire                                             HREADY_P0;
wire                                             HREADYOUT_P0;
wire                                     [31:0]  HRDATA_P0;
wire                                             HRESP_P0;

wire                                             HSEL_P1;
wire                                     [31:0]  HADDR_P1;
wire                                     [2:0]   HBURST_P1;
wire                                             HMASTLOCK_P1;
wire                                     [3:0]   HPROT_P1;
wire                                     [2:0]   HSIZE_P1;
wire                                     [1:0]   HTRANS_P1;
wire                                     [31:0]  HWDATA_P1;
wire                                             HWRITE_P1;
wire                                             HREADY_P1;
wire                                             HREADYOUT_P1;
wire                                     [31:0]  HRDATA_P1;
wire                                             HRESP_P1;

wire                                             HSEL_P2;
wire                                     [31:0]  HADDR_P2;
wire                                     [2:0]   HBURST_P2;
wire                                             HMASTLOCK_P2;
wire                                     [3:0]   HPROT_P2;
wire                                     [2:0]   HSIZE_P2;
wire                                     [1:0]   HTRANS_P2;
wire                                     [31:0]  HWDATA_P2;
wire                                             HWRITE_P2;
wire                                             HREADY_P2;
wire                                             HREADYOUT_P2;
wire                                     [31:0]  HRDATA_P2;
wire                                             HRESP_P2;

wire                                             HSEL_P3;
wire                                     [31:0]  HADDR_P3;
wire                                     [2:0]   HBURST_P3;
wire                                             HMASTLOCK_P3;
wire                                     [3:0]   HPROT_P3;
wire                                     [2:0]   HSIZE_P3;
wire                                     [1:0]   HTRANS_P3;
wire                                     [31:0]  HWDATA_P3;
wire                                             HWRITE_P3;
wire                                             HREADY_P3;
wire                                             HREADYOUT_P3;
wire                                     [31:0]  HRDATA_P3;
wire                                             HRESP_P3;

wire                                             HSEL_P4;
wire                                     [31:0]  HADDR_P4;
wire                                     [2:0]   HBURST_P4;
wire                                             HMASTLOCK_P4;
wire                                     [3:0]   HPROT_P4;
wire                                     [2:0]   HSIZE_P4;
wire                                     [1:0]   HTRANS_P4;
wire                                     [31:0]  HWDATA_P4;
wire                                             HWRITE_P4;
wire                                             HREADY_P4;
wire                                             HREADYOUT_P4;
wire                                     [31:0]  HRDATA_P4;
wire                                             HRESP_P4;

wire                                             HSEL_P5;
wire                                     [31:0]  HADDR_P5;
wire                                     [2:0]   HBURST_P5;
wire                                             HMASTLOCK_P5;
wire                                     [3:0]   HPROT_P5;
wire                                     [2:0]   HSIZE_P5;
wire                                     [1:0]   HTRANS_P5;
wire                                     [31:0]  HWDATA_P5;
wire                                             HWRITE_P5;
wire                                             HREADY_P5;
wire                                             HREADYOUT_P5;
wire                                     [31:0]  HRDATA_P5;
wire                                             HRESP_P5;

AHBlite_Interconnect Interconncet
    (
    .HCLK           (clk),
    .HRESETn        (cpuresetn),

    // CORE SIDE
    .HADDR          (HADDR),
    .HTRANS         (HTRANS),
    .HSIZE          (HSIZE),
    .HBURST         (HBURST),
    .HPROT          (HPROT),
    .HMASTLOCK      (HMASTLOCK),
    .HWRITE         (HWRITE),
    .HWDATA         (HWDATA),
    .HRDATA         (HRDATA),
    .HREADY         (HREADY),
    .HRESP          (HRESP),

    // P0
    .HSEL_P0        (HSEL_P0),
    .HADDR_P0       (HADDR_P0),
    .HBURST_P0      (HBURST_P0),
    .HMASTLOCK_P0   (HMASTLOCK_P0),
    .HPROT_P0       (HPROT_P0),
    .HSIZE_P0       (HSIZE_P0),
    .HTRANS_P0      (HTRANS_P0),
    .HWDATA_P0      (HWDATA_P0),
    .HWRITE_P0      (HWRITE_P0),
    .HREADY_P0      (HREADY_P0),
    .HREADYOUT_P0   (HREADYOUT_P0),
    .HRDATA_P0      (HRDATA_P0),
    .HRESP_P0       (HRESP_P0),

    // P1
    .HSEL_P1        (HSEL_P1),
    .HADDR_P1       (HADDR_P1),
    .HBURST_P1      (HBURST_P1),
    .HMASTLOCK_P1   (HMASTLOCK_P1),
    .HPROT_P1       (HPROT_P1),
    .HSIZE_P1       (HSIZE_P1),
    .HTRANS_P1      (HTRANS_P1),
    .HWDATA_P1      (HWDATA_P1),
    .HWRITE_P1      (HWRITE_P1),
    .HREADY_P1      (HREADY_P1),
    .HREADYOUT_P1   (HREADYOUT_P1),
    .HRDATA_P1      (HRDATA_P1),
    .HRESP_P1       (HRESP_P1),

    // P2
    .HSEL_P2        (HSEL_P2),
    .HADDR_P2       (HADDR_P2),
    .HBURST_P2      (HBURST_P2),
    .HMASTLOCK_P2   (HMASTLOCK_P2),
    .HPROT_P2       (HPROT_P2),
    .HSIZE_P2       (HSIZE_P2),
    .HTRANS_P2      (HTRANS_P2),
    .HWDATA_P2      (HWDATA_P2),
    .HWRITE_P2      (HWRITE_P2),
    .HREADY_P2      (HREADY_P2),
    .HREADYOUT_P2   (HREADYOUT_P2),
    .HRDATA_P2      (HRDATA_P2),
    .HRESP_P2       (HRESP_P2),

    // P3
    .HSEL_P3        (HSEL_P3),
    .HADDR_P3       (HADDR_P3),
    .HBURST_P3      (HBURST_P3),
    .HMASTLOCK_P3   (HMASTLOCK_P3),
    .HPROT_P3       (HPROT_P3),
    .HSIZE_P3       (HSIZE_P3),
    .HTRANS_P3      (HTRANS_P3),
    .HWDATA_P3      (HWDATA_P3),
    .HWRITE_P3      (HWRITE_P3),
    .HREADY_P3      (HREADY_P3),
    .HREADYOUT_P3   (HREADYOUT_P3),
    .HRDATA_P3      (HRDATA_P3),
    .HRESP_P3       (HRESP_P3),

    // P4
    .HSEL_P4        (HSEL_P4),
    .HADDR_P4       (HADDR_P4),
    .HBURST_P4      (HBURST_P4),
    .HMASTLOCK_P4   (HMASTLOCK_P4),
    .HPROT_P4       (HPROT_P4),
    .HSIZE_P4       (HSIZE_P4),
    .HTRANS_P4      (HTRANS_P4),
    .HWDATA_P4      (HWDATA_P4),
    .HWRITE_P4      (HWRITE_P4),
    .HREADY_P4      (HREADY_P4),
    .HREADYOUT_P4   (HREADYOUT_P4),
    .HRDATA_P4      (HRDATA_P4),
    .HRESP_P4       (HRESP_P4),

    // P5
    .HSEL_P5        (HSEL_P5),
    .HADDR_P5       (HADDR_P5),
    .HBURST_P5      (HBURST_P5),
    .HMASTLOCK_P5   (HMASTLOCK_P5),
    .HPROT_P5       (HPROT_P5),
    .HSIZE_P5       (HSIZE_P5),
    .HTRANS_P5      (HTRANS_P5),
    .HWDATA_P5      (HWDATA_P5),
    .HWRITE_P5      (HWRITE_P5),
    .HREADY_P5      (HREADY_P5),
    .HREADYOUT_P5   (HREADYOUT_P5),
    .HRDATA_P5      (HRDATA_P5),
    .HRESP_P5       (HRESP_P5)
);

//------------------------------------------------------------------------------
// AHB RAMCODE
//------------------------------------------------------------------------------

wire                                      [31:0] RAMCODE_RDATA;
wire                                      [31:0] RAMCODE_WDATA;
wire                                      [13:0] RAMCODE_ADDR;
wire                                      [3:0]  RAMCODE_WRITE;

AHBlite_Block_RAM RAMCODE_Interface
    (
    /* Connect to Interconnect Port 0 */
    .HCLK           (clk),
    .HRESETn        (cpuresetn),
    .HSEL           (HSEL_P0),
    .HADDR          (HADDR_P0),
    .HPROT          (HPROT_P0),
    .HSIZE          (HSIZE_P0),
    .HTRANS         (HTRANS_P0),
    .HWDATA         (HWDATA_P0),
    .HWRITE         (HWRITE_P0),
    .HRDATA         (HRDATA_P0),
    .HREADY         (HREADY_P0),
    .HREADYOUT      (HREADYOUT_P0),
    .HRESP          (HRESP_P0),
    .BRAM_ADDR      (RAMCODE_ADDR),
    .BRAM_RDATA     (RAMCODE_RDATA),
    .BRAM_WDATA     (RAMCODE_WDATA),
    .BRAM_WRITE     (RAMCODE_WRITE)
    /**********************************/
);

//------------------------------------------------------------------------------
// AHB RAMDATA
//------------------------------------------------------------------------------

wire                                      [31:0] RAMDATA_RDATA;
wire                                      [31:0] RAMDATA_WDATA;
wire                                      [13:0] RAMDATA_ADDR;
wire                                      [3:0]  RAMDATA_WRITE;

AHBlite_Block_RAM RAMDATA_Interface
    (
    /* Connect to Interconnect Port 1 */
    .HCLK           (clk),
    .HRESETn        (cpuresetn),
    .HSEL           (HSEL_P1),
    .HADDR          (HADDR_P1),
    .HPROT          (HPROT_P1),
    .HSIZE          (HSIZE_P1),
    .HTRANS         (HTRANS_P1),
    .HWDATA         (HWDATA_P1),
    .HWRITE         (HWRITE_P1),
    .HRDATA         (HRDATA_P1),
    .HREADY         (HREADY_P1),
    .HREADYOUT      (HREADYOUT_P1),
    .HRESP          (HRESP_P1),
    .BRAM_ADDR      (RAMDATA_ADDR),
    .BRAM_WDATA     (RAMDATA_WDATA),
    .BRAM_RDATA     (RAMDATA_RDATA),
    .BRAM_WRITE     (RAMDATA_WRITE)
    /**********************************/
);
//------------------------------------------------------------------------------
// RAM
//------------------------------------------------------------------------------
Block_RAM U_RAM_CODE
    (
    .clka           (clk),
    .addra          (RAMCODE_ADDR),
    .dina           (RAMCODE_WDATA),
    .douta          (RAMCODE_RDATA),
    .wea            (RAMCODE_WRITE)
);

Block_RAM U_RAM_DATA
    (
    .clka           (clk),
    .addra          (RAMDATA_ADDR),
    .dina           (RAMDATA_WDATA),
    .douta          (RAMDATA_RDATA),
    .wea            (RAMDATA_WRITE)
);

//------------------------------------------------------------------------------
// AHB Keyboard
//------------------------------------------------------------------------------

wire                                      [15:0] key_data;
wire                                             key_clear;

AHBlite_Keyboard Keyboard_Interface
    (
    /* Connect to Interconnect Port 2 */
    .HCLK                   (clk),
    .HRESETn                (cpuresetn),
    .HSEL                   (HSEL_P2),
    .HADDR                  (HADDR_P2),
    .HTRANS                 (HTRANS_P2),
    .HSIZE                  (HSIZE_P2),
    .HPROT                  (HPROT_P2),
    .HWRITE                 (HWRITE_P2),
    .HWDATA                 (HWDATA_P2),
    .HREADY                 (HREADY_P2),
    .HREADYOUT              (HREADYOUT_P2),
    .HRDATA                 (HRDATA_P2),
    .HRESP                  (HRESP_P2),
    .key_data               (key_data),
    .key_clear              (key_clear)
    /**********************************/ 
);
//------------------------------------------------------------------------------
// Keyboard
//------------------------------------------------------------------------------
Keyboard U_Keyboard
    (
    .clk                     (clk),
    .rstn                    (cpuresetn),
    .key_clear               (key_clear),
    .col                     (col),
    .row                     (row),
    //.key_pluse             (key_pluse),
    .key_interrupt           (key_interrupt),
    .key_data                (key_data)
);

//------------------------------------------------------------------------------
// AHB LCD
//------------------------------------------------------------------------------
wire                                             LCD_CS_run;
wire                                             LCD_RS_run;
wire                                             LCD_WR_run;
wire                                             LCD_RD_run;
wire                                             LCD_RST_run;
wire                                    [15:0]   LCD_DATA_run;
wire                                             LCD_BL_CTR_run;
wire                                             LCD_INI_en;
wire                                             LCD_MODE;

AHBlite_LCD LCD_Interface
    (
    /* Connect to Interconnect Port 3 */
    .HCLK           (clk),
    .HRESETn        (cpuresetn),
    .HSEL           (HSEL_P3),
    .HADDR          (HADDR_P3),
    .HTRANS         (HTRANS_P3),
    .HSIZE          (HSIZE_P3),
    .HPROT          (HPROT_P3),
    .HWRITE         (HWRITE_P3),
    .HWDATA         (HWDATA_P3),
    .HREADY         (HREADY_P3),
    .HREADYOUT      (HREADYOUT_P3),
    .HRDATA         (HRDATA_P3),
    .HRESP          (HRESP_P3),

    .LCD_CS         (LCD_CS_run),
    .LCD_RS         (LCD_RS_run),
    .LCD_WR         (LCD_WR_run),
    .LCD_RD         (LCD_RD_run),
    .LCD_RST        (LCD_RST_run),
    .LCD_DATA       (LCD_DATA_run),
    .LCD_BL_CTR     (LCD_BL_CTR_run),

    .LCD_INI_en     (LCD_INI_en),
    .LCD_MODE       (LCD_MODE)
    /**********************************/ 
);
//------------------------------------------------------------------------------
// LCD
//------------------------------------------------------------------------------

wire                                             LCD_CS_INI;
wire                                             LCD_RS_INI;
wire                                             LCD_WR_INI;
wire                                             LCD_RD_INI;
wire                                             LCD_RST_INI;
wire                                    [15:0]   LCD_DATA_INI;
wire                                             LCD_BL_CTR_INI;

LCD_INI U_LCD_INI
    (
    .clk             (clk),
    .rstn            (cpuresetn),
    .en              (LCD_INI_en),
    .Initial_finish  (LCD_INI_FINISH),
    .LCD_CS          (LCD_CS_INI),
    .LCD_RST         (LCD_RST_INI),
    .LCD_RS          (LCD_RS_INI),
    .LCD_WR          (LCD_WR_INI),
    .LCD_RD          (LCD_RD_INI),
    .LCD_DATA        (LCD_DATA_INI),
    .LCD_BL_CTR      (LCD_BL_CTR_INI)
);

assign LCD_CS           = ( LCD_MODE == 1'b1 ) ? LCD_CS_run     : LCD_CS_INI     ;
assign LCD_RST          = ( LCD_MODE == 1'b1 ) ? LCD_RST_run    : LCD_RST_INI    ;
assign LCD_RS           = ( LCD_MODE == 1'b1 ) ? LCD_RS_run     : LCD_RS_INI     ;
assign LCD_WR           = ( LCD_MODE == 1'b1 ) ? LCD_WR_run     : LCD_WR_INI     ;
assign LCD_RD           = ( LCD_MODE == 1'b1 ) ? LCD_RD_run     : LCD_RD_INI     ;
assign LCD_DATA         = ( LCD_MODE == 1'b1 ) ? LCD_DATA_run   : LCD_DATA_INI   ;
assign LCD_BL_CTR       = ( LCD_MODE == 1'b1 ) ? LCD_BL_CTR_run : LCD_BL_CTR_INI ;

//------------------------------------------------------------------------------
// AHB Buzzermusic
//------------------------------------------------------------------------------
wire                                       [1:0] music_select;
wire                                             music_start;
wire                                      [19:0] music_tune;

AHBlite_Buzzermusic Buzzermusic_Interface
    (
    .HCLK           (clk),
    .HRESETn        (cpuresetn),
    .HSEL           (HSEL_P4),
    .HADDR          (HADDR_P4),
    .HTRANS         (HTRANS_P4),
    .HSIZE          (HSIZE_P4),
    .HPROT          (HPROT_P4),
    .HWRITE         (HWRITE_P4),
    .HWDATA         (HWDATA_P4),
    .HREADY         (HREADY_P4),
    .HREADYOUT      (HREADYOUT_P4),
    .HRDATA         (HRDATA_P4),
    .HRESP          (HRESP_P4),
    .music_select   (music_select),
    .music_start    (music_start),
    .music_tune     (music_tune)
);
//------------------------------------------------------------------------------
//  Buzzermusic
//------------------------------------------------------------------------------
buzzermusic U_buzzermusic
    (
    .clk                     (clk),
    .rstn                    (cpuresetn),
    .music_select            (music_select),
    .music_start             (music_start),
    .music_interrupt         (music_interrupt),
    .music_tune              (music_tune),
    .beep                    (beep)
);



//------------------------------------------------------------------------------
// Synq AHB to APB Bridge
//------------------------------------------------------------------------------
//APB Port
wire                                      [15:0] PADDR;
wire                                             PENABLE;
wire                                             PWRITE;
wire                                      [31:0] PWDATA;
wire                                             PSEL;

wire                                      [31:0] PRDATA;
wire                                             PREADY;
wire                                             PSLVERR;

cmsdk_ahb_to_apb 
   #(
    .ADDRWIDTH      (16),
    .REGISTER_RDATA (0),
    .REGISTER_WDATA (0)
    ) 
    ahb_to_apb
    (
    //General Signals
    .HCLK           (clk),
    .HRESETn        (cpuresetn),
    .PCLKEN         (1'b1),

    //AHB Port
    .HSEL           (HSEL_P5),
    .HADDR          (HADDR_P5[15:0]),
    .HTRANS         (HTRANS_P5),
    .HSIZE          (HSIZE_P5),
    .HPROT          (HPROT_P5),
    .HWRITE         (HWRITE_P5),
    .HREADY         (HREADY_P5),
    .HWDATA         (HWDATA_P5),
    
    .HREADYOUT      (HREADYOUT_P5),
    .HRDATA         (HRDATA_P5),
    .HRESP          (HRESP_P5),

    //APB Port
    .PADDR          (PADDR),
    .PENABLE        (PENABLE),
    .PWRITE         (PWRITE),
    .PSTRB          (),
    .PPROT          (),
    .PWDATA         (PWDATA),
    .PSEL           (PSEL),

    .APBACTIVE      (),
    
    .PRDATA         (PRDATA),
    .PREADY         (PREADY),
    .PSLVERR        (PSLVERR)
);

//------------------------------------------------------------------------------
// APB Slave MUX
//------------------------------------------------------------------------------
//UART Port
wire                                             UART_PSEL;
wire                                             UART_PREADY;
wire                                      [31:0] UART_PRDATA;
wire                                             UART_PSLVERR;

wire                                             VGA_PSEL;
wire                                             VGA_PREADY;
wire                                      [31:0] VGA_PRDATA;
wire                                             VGA_PSLVERR;

cmsdk_apb_slave_mux 
   #(
    .PORT0_ENABLE   (1),
    .PORT1_ENABLE   (1),
    .PORT2_ENABLE   (0),
    .PORT3_ENABLE   (0),
    .PORT4_ENABLE   (0),
    .PORT5_ENABLE   (0),
    .PORT6_ENABLE   (0),
    .PORT7_ENABLE   (0),
    .PORT8_ENABLE   (0),
    .PORT9_ENABLE   (0),
    .PORT10_ENABLE  (0),
    .PORT11_ENABLE  (0),
    .PORT12_ENABLE  (0),
    .PORT13_ENABLE  (0),
    .PORT14_ENABLE  (0),
    .PORT15_ENABLE  (0)
    )
    cmsdk_apb_slave_mux
    (
    .DECODE4BIT     (PADDR[15:12]),
    .PSEL           (PSEL),

    //UART
    .PSEL0          (UART_PSEL),
    .PREADY0        (UART_PREADY),
    .PRDATA0        (UART_PRDATA),
    .PSLVERR0       (UART_PSLVERR),

    .PSEL1          (VGA_PSEL),
    .PREADY1        (VGA_PREADY),
    .PRDATA1        (VGA_PRDATA),
    .PSLVERR1       (VGA_PSLVERR),

    .PSEL2          (),
    .PREADY2        (1'b0),
    .PRDATA2        (32'b0),
    .PSLVERR2       (1'b0),

    .PSEL3          (),
    .PREADY3        (1'b0),
    .PRDATA3        (32'b0),
    .PSLVERR3       (1'b0),

    .PSEL4          (),
    .PREADY4        (1'b0),
    .PRDATA4        (32'b0),
    .PSLVERR4       (1'b0),

    .PSEL5          (),
    .PREADY5        (1'b0),
    .PRDATA5        (32'b0),
    .PSLVERR5       (1'b0),

    .PSEL6          (),
    .PREADY6        (1'b0),
    .PRDATA6        (32'b0),
    .PSLVERR6       (1'b0),

    .PSEL7          (),
    .PREADY7        (1'b0),
    .PRDATA7        (32'b0),
    .PSLVERR7       (1'b0),

    .PSEL8          (),
    .PREADY8        (1'b0),
    .PRDATA8        (32'b0),
    .PSLVERR8       (1'b0),

    .PSEL9          (),
    .PREADY9        (1'b0),
    .PRDATA9        (32'b0),
    .PSLVERR9       (1'b0),

    .PSEL10         (),
    .PREADY10       (1'b0),
    .PRDATA10       (32'b0),
    .PSLVERR10      (1'b0),

    .PSEL11         (),
    .PREADY11       (1'b0),
    .PRDATA11       (32'b0),
    .PSLVERR11      (1'b0),

    .PSEL12         (),
    .PREADY12       (1'b0),
    .PRDATA12       (32'b0),
    .PSLVERR12      (1'b0),

    .PSEL13         (),
    .PREADY13       (1'b0),
    .PRDATA13       (32'b0),
    .PSLVERR13      (1'b0),

    .PSEL14         (),
    .PREADY14       (1'b0),
    .PRDATA14       (32'b0),
    .PSLVERR14      (1'b0),

    .PSEL15         (),
    .PREADY15       (1'b0),
    .PRDATA15       (32'b0),
    .PSLVERR15      (1'b0),

    .PREADY         (PREADY),
    .PRDATA         (PRDATA),
    .PSLVERR        (PSLVERR)
);

//------------------------------------------------------------------------------
// APB_UART
//------------------------------------------------------------------------------

    cmsdk_apb_uart U_UART(
        .PCLK           (clk),
        .PCLKG          (clk),
        .PRESETn        (cpuresetn),
        .PSEL           (UART_PSEL),
        .PADDR          (PADDR[11:2]),
        .PENABLE        (PENABLE),
        .PWRITE         (PWRITE),
        .PWDATA         (PWDATA),
        .ECOREVNUM      (4'b0),
        .PRDATA         (UART_PRDATA),
        .PREADY         (UART_PREADY),
        .PSLVERR        (UART_PSLVERR),
        .RXD            (RXD),
        .TXD            (TXD),
        .TXEN           (),
        .BAUDTICK       (),
        .TXINT          (),
        .RXINT          (RXIRQ),
        .TXOVRINT       (),
        .RXOVRINT       (),
        .UARTINT        ()
    );

VGA_TOP
  # (
    .ADDR_WIDTH                        (12                                     ),
    .DATA_WIDTH                        (32                                     )
    )
    U_VGA_TOP
    (
    .pclk                              (clk                                    ),
    .preset_n                          (cpuresetn                              ),
    .psel                              (VGA_PSEL                               ),
    .penable                           (PENABLE                                ),
    .pwrite                            (PWRITE                                 ),
    .paddr                             (PADDR[11:0]                            ),
    .pwdata                            (PWDATA                                 ),
    .prdata                            (VGA_PRDATA                             ),
    .pready                            (VGA_PREADY                             ),
    .pslverr                           (VGA_PSLVERR                            ),

    .vga_clk                           (vga_clk                                ),
    .hsync                             (hsync                                  ),   
    .vsync                             (vsync                                  ),   
    .rgb                               (rgb                                    )    
    );
endmodule