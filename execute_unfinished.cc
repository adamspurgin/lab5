#include "mipsim.hpp"

Stats stats;
Caches caches(0);

unsigned int signExtend16to32ui(short i) {
  return static_cast<unsigned int>(static_cast<int>(i));
}

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
    case SP_SLT:
	  rf.write(rt.rd, (rf[rt.rs]<rf[rt.rt])?1:0);
	  break;
	case SP_JR:
	  pc.write(rt.rs);
	  break;
    default:
      cout << "Unsupported instruction: ";
      instr.printI(instr);
      exit(1);
      break;
    }
    break;
  case OP_ADDIU:
    rf.write(ri.rt, rf[ri.rs] + signExtend16to32ui(ri.imm));
    break;
  case OP_ORI:
	rf.write(ri.rt, rf[ri.rs] | ri.imm);
	break;
  case OP_SLTI:
	rf.write(ri.rt, (ri.rs<ri.imm)?1:0);
	break;
  case OP_SLTIU:			//not sure about this one
	rf.write(ri.rt, (ri.rs<signExtend16to32ui(ri.imm))?1:0);
	break;
  case OP_SW:
    addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
    caches.access(addr);
    dmem.write(addr, rf[ri.rt]);
    break;
  case OP_SB:					//still not sure about this one
	addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
	caches.access(addr);
	dmem.write(addr, rf[ri.rt].data_ubyte4);
	break;
  case OP_LUI:
	addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
	caches.access(addr);
	rf.write(ri.rt, dmem[addr].data_uint());
  case OP_LW:
    addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
    caches.access(addr);
    rf.write(ri.rt, dmem[addr]);
    break;
  case OP_LB:					//still not sure about this one
	addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
	caches.access(addr);
	rf.write(ri.rt, signExtend16to32ui(dmem[addr].data_ubyte4));
  case OP_LBU:					//still not sure about this one
	addr = rf[ri.rs] + signExtend16to32ui(ri.imm);
	caches.access(addr);
	rf.write(ri.rt, dmem[addr].data_ubyte4);
	break;
  case OP_BNE:					//still not sure about this one
	if(rf[ri.rt] != rf[ri.rs])
		pc.write(pc.d + signExtend16to32ui(ri.imm));
	break;
  case OP_BEQ:					//still not sure about this one
	if(rf[ri.rt] != 0)
		pc.write(signExtend16to32ui(ri.imm));
	break;
  case OP_BLEZ: 				//still not sure about this one
	if(rf[ri.rt] <= 0)
		pc.write(signExtend16to32ui(ri.imm));
	break;
  case OP_J:
	pc.write(rj.target);
	break;
  case OP_JAL:
	rf.write(31, pc.d);
	pc.write(signExtend16to32ui(ri.imm));
	break;
  default:
    cout << "Unsupported instruction: ";
    instr.printI(instr);
    exit(1);
    break;
  }
}
