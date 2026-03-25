module contu(
    input wire clk,
    input wire reset,
    input wire up,
    input wire down,
    output wire [3:0] count
);

reg [3:0] count_reg = 0;

always @(posedge clk)
begin
    if (reset)
        count_reg <= 0;
    if (up)
        count_reg <= count_reg + 1;
    if (down)
        count_reg <= count_reg - 1;

end

assign count = count_reg;

endmodule