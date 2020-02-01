`timescale 1ns / 1ps
 
module tb_mySPI_AXIS();
    wire sclk;
    wire mosi;
    wire ss;
     
    reg s00_axis_aclk = 0;
    reg s00_axis_aresetn = 0;
    wire s00_axis_tready;
    reg [31:0]s00_axis_tdata=0;
    reg s00_axis_tstrb=0;
    reg s00_axis_tlast=0;
    reg s00_axis_tvalid=0; 
 
    mySPI_Tx_AXIS_v1_0_S00_AXIS # (
        .width(8),
        .clkdiv(2),
        .C_S_AXIS_TDATA_WIDTH(32)
    ) mySPI_Tx_AXIS_v1_0_S00_AXIS_inst (
        .sclk(sclk),
        .mosi(mosi),
        .ss(ss),
        .S_AXIS_ACLK(s00_axis_aclk),
        .S_AXIS_ARESETN(s00_axis_aresetn),
        .S_AXIS_TREADY(s00_axis_tready),
        .S_AXIS_TDATA(s00_axis_tdata),
        .S_AXIS_TSTRB(s00_axis_tstrb),
        .S_AXIS_TLAST(s00_axis_tlast),
        .S_AXIS_TVALID(s00_axis_tvalid)
    );
 
    always begin
        #1 s00_axis_aclk=~s00_axis_aclk;
    end  
 
    initial begin
        #20;
        @ (posedge s00_axis_aclk) s00_axis_tdata = 16'hAAAA;s00_axis_tvalid = 1;
        while (s00_axis_tready==0) begin
            @ (posedge s00_axis_aclk) ;
        end
        @ (posedge s00_axis_aclk) s00_axis_tdata = 16'h5555;s00_axis_tvalid = 1;
        while (s00_axis_tready==0) begin
            @ (posedge s00_axis_aclk) ;
        end
        @ (posedge s00_axis_aclk) s00_axis_tdata = 16'h0000;s00_axis_tvalid = 0;
    end
endmodule