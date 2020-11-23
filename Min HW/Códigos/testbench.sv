//testbench
`define height 120
`define width 160

module read_TXT;

  reg [7:0] Mem [0:`height-1][0:`width-1];	//Memória
  integer i, j;
  integer file_out;
  reg [31:0] in;
  reg [7:0] out;
    
  redux r1(in, out);
  
initial begin
  $readmemh("pix.txt", Mem);			//Carrega imagem
  file_out = $fopen("redux.txt", "w");
end

initial begin
  #10;
  for (i=0; i<`height; i=i+2) begin
    for (j=0; j<`width; j=j+2)begin
      //Carrega entradas
      in[7:0] <= Mem[i][j];      
      in[15:8] <= Mem[i][j + 1];
      in[23:16] <= Mem[i + 1][j];
      in[31:24] <= Mem[i + 1][j + 1];
      
      //Salva saída
      #10
      $fwrite(file_out, "%X ", out);
      
	end	//end for j
    $fwrite(file_out, "\n");
  end	//end for i
  #10
  $fclose(file_out);
 end
endmodule