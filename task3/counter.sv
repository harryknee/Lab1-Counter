module counter #(
    parameter WIDTH = 8
)(
    // interface signals
    input logic clk,
    input logic rst,
    input logic en,
    input logic storedVal,
    input logic lastEn,
    output logic [WIDTH-1:0] count
);

always_ff @ (posedge clk)
    if (rst) count <= {WIDTH{1'b0}};
    else    if (en)   count <= storedVal; 
            else count <= count + {{WIDTH-1{1'b0}}, 1'b1};
            // count <= count + {{WIDTH-1{1'b0}}, en}; // this code is for the second part of task 3
    ;
    
endmodule
