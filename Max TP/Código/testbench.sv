//testbench 
`define height 120
`define width 160

module read_TXT;

  reg [7:0] Mem [0:`height-1][0:`width-1];	//Memória
  integer i, j, count;
  integer file_out;
  reg [7:0] in[0:3][0:4];
  reg [7:0] out[0:4];
    
  redux_paralelo rp_1(.pix_in(in), .pix_out(out));
  
initial begin
  $readmemh("pix.txt", Mem);			//Carrega imagem
  file_out = $fopen("redux.txt", "w");
  count = 0;
end

initial begin
  #10;
  for (i=0; i<`height; i=i+2) begin
    for (j=0; j<`width; j=j+2)begin
      
      //Carrega pipelines
      in[0][count] <= Mem[i][j];      
      in[1][count] <= Mem[i][j + 1];
      in[2][count] <= Mem[i + 1][j];
      in[3][count] <= Mem[i + 1][j + 1];
      
      count = count + 1;
      
      //Quando enche, espera e salva resultad
      if (count == 5) begin 
        count = 0;
        #10
        $fwrite(file_out, "%X %X %X %X %x ", out[0], out[1], out[2], out[3], out[4]);
      end
      
	end	//end for j
    $fwrite(file_out, "\n");
  end	//end for i
  
  #10
  $fclose(file_out);
 end
endmodule