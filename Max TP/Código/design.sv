//Hardware
module redux_paralelo(
  input [7:0] pix_in[0:3][0:4],
  output reg [7:0] pix_out[0:4]);
  
  genvar i;
  
  generate
    for (i=0; i<5; i=i+1) begin : redux1
      always @ (pix_in[0][i] or pix_in[1][i] or pix_in[2][i] or pix_in[3][i]) begin
        pix_out[i] <= (pix_in[0][i] + pix_in[1][i] + pix_in[2][i] + pix_in[3][i]) / 4;
      end //end always
    end	//end for i
  endgenerate

endmodule