Create your design in this folder.
Task Objective:  
- change the mode of vbuddy to 'one-shot', from the default 'toggle'
- modify counter.sv so that pressing the switch on EC11 forces the counter to pre-set to Vbuddy’s parameter value  
What I did:
- vbdSetMode(1) change the mode to 1-shot
- if (top->en)  top->count = vbdValue();