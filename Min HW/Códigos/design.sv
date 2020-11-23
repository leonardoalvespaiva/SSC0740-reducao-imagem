//Hardware
module redux(
  input [31:0] pix_in,
  output reg [7:0] pix_out);
  
  always @ (pix_in) begin
    pix_out <= (pix_in[7:0] + pix_in[15:8] + pix_in[23:16] + pix_in[31:24]) / 4;
  end
  
endmodule