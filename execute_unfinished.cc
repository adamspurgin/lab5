#include "mipsim.hpp"

Stats stats;
Caches caches(0);

unsigned int signExtend16to32ui(short i) {
  return static_cast<unsigned int>(static_cast<int>(i));
}

	//this is a new comment work, dammit

void execute() {
  Data32 instr = imem[pc];
  GenericType rg(instr);
  RType rt(instr);
  IType ri(instr);
  JType rj(instr);
  unsigned int pctarget = pc + 4;
  unsigned int addr;
  stats.instrs++;
  pc = pctarget;
  switch(rg.op) {
  case OP_SPECIAL:
	switch(rg.func) {
    case SP_ADDU:
      rf.write(rt.rd, rf[rt.rs] + rf[rt.rt]);
      break;
    case SP_SLL:
      rf.write(rt.rd, rf[rt.rt] << rt.sa);
      break;
    case SP_AND:
	  rf.wr
    default:
      cout << "Unsupported instruction: ";
      instr.printI(instr);
      exit(1);
      break;
    }
    break;
  case OP_ANDI:   //not sure if works
	 rf.write(ri.rt, rf[ri.rs] & ri.imm);
	 break;
  case OP_ADDIU:
    rf.write(ri.rt, rf[ri.rs] + signExtend16to32ui(ri.imm));
    break;
  case OP_ADDI:
    rf.write(ri.rt, rf[ri.rs] + ri.imm);
    break;
  case OP_ORI:
	rf.write(ri.rt, rf[ri.rs] | ri.imm);
	break;
  case OP_SW:
    addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
    caches.access(addr);
    dmem.write(addr, rf[ri.rt]);
    break;
  case OP_SB:  //not sure if this works
	addr = rf[ri.rt] + signExtend16to32ui(ri.imm);
	caches.access(addr);
	dmem.write(addr, rf[ri.rt]);
	break;
  case OP_LBU:
	break;
  case OP_LW:
    addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
    caches.access(addr);
    rf.write(ri.rt, dmem[addr]);
    break;
  case OP_SW:   //not sure if works
 	addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
	caches.access(addr);
	rf.write(ri.rt, dmem[addr]);
	break;
  case: OP_LB:
    addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
    caches.access(addr);
    rf.write(ri.rt, dmem[addr]);
    break;
  case: OP_SLTI:
	int tempval = (ri.rs < ri.imm)?1:0;
	rf.write(ri.rt, tempval);
	break;
  case: SLTIU
	int tempval = (ri.rs < signExtend16to32ui(ri.im))?1:0;
	rf.write(ri.rt, tempval);
	break;
  case: OP_BNE:
	if(ri.rs != ri.rt)
		pc += ri.imm;
	break;
  case: BEQ
	if(ri.rs == ri.rt)
		pc += ri.imm*4;
	break;
  case: BLEZ
	if(ri.rs < 0)
		pc += ri.imm*4;
	break;
  case: LUI
	rf.write(ri.rt, ri.imm << 16);
	break;
  case: JAL
  case: J
	pc = rj.target;
	break;
  case: ADDU
  case: SLT
  case: JR
  case: SLL
  default:
    cout << "Unsupported instruction: ";
    instr.printI(instr);
    exit(1);
    break;
  }
}
