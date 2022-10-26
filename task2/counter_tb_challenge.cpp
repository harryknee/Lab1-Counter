#include "Vcounter_challenge.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"
// notice the header has changed, since we renamed the target of verilator
// now for the testbench we also need to change the name so that we can make the file

int main(int argc, char **argv, char **env){
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vcounter_challenge* top = new  Vcounter_challenge; // since we changed the import file, this object name is also changed
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open("counter_challenge.vcd");

    // initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // init Vbuddy
    if (vbdOpen()!=1)  return(-1);
    vbdHeader("Lab 1: Counter t2c1");

    // run simulation for many clock cycles
    for (i=0; i<300; i++){
        // dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++){
            tfp->dump(2*i+clk);
            top->clk = !top->clk; // toggle clock up and down
            top->eval();
        }

        // Send count value to Vbuddy
        vbdHex(4, (int(top->count) >> 16) & 0xF);
        vbdHex(3, (int(top->count) >> 8) & 0xF);
        vbdHex(2, (int(top->count) >> 4) & 0xF);
        vbdHex(1, int(top->count) & 0xF);
        vbdCycle(i+1);

        top->rst = (i < 2) | (i == 15); // here || and && same as | and & as comparator returns a boolean value
        // top->en = (i > 4) & !((8 <= i) & (i < 11));
        top->en = vbdFlag();
        if (Verilated::gotFinish())  exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}