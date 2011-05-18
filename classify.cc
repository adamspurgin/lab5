#include "mipsim.hpp"

vector<string> opmap = vector<string>(OP_UNDEFINED + 1, 
                                      string("OP_UNDEFINED"));
vector<string> spmap = vector<string>(SP_UNDEFINED + 1, 
                                      string("SP_UNDEFINED"));
string opToString(const Op op) {
  return opmap[op];
}
string spToString(const Special sp) {
  return spmap[sp];
}

void op_init() {
  opmap[OP_SPECIAL] = "OP_SPECIAL";
  opmap[OP_REGIMM] = "OP_REGIMM";
  opmap[OP_J] = "OP_J";
  opmap[OP_JAL] = "OP_JAL";
  opmap[OP_BEQ] = "OP_BEQ";
  opmap[OP_BNE] = "OP_BNE";
  opmap[OP_BLEZ] = "OP_BLEZ";
  opmap[OP_BGTZ] = "OP_BGTZ";
  opmap[OP_ADDI] = "OP_ADDI";
  opmap[OP_ADDIU] = "OP_ADDIU";
  opmap[OP_SLTI] = "OP_SLTI";
  opmap[OP_SLTIU] = "OP_SLTIU";
  opmap[OP_ANDI] = "OP_ANDI";
  opmap[OP_ORI] = "OP_ORI";
  opmap[OP_XORI] = "OP_XORI";
  opmap[OP_LUI] = "OP_LUI";
  opmap[OP_LB] = "OP_LB";
  opmap[OP_LH] = "OP_LH";
  opmap[OP_LW] = "OP_LW";
  opmap[OP_LBU] = "OP_LBU";
  opmap[OP_LHU] = "OP_LHU";
  opmap[OP_SB] = "OP_SB";
  opmap[OP_SH] = "OP_SH";
  opmap[OP_SW] = "OP_SW";
  opmap[OP_SBU] = "OP_SBU";
  opmap[OP_SHU] = "OP_SHU";
  spmap[SP_SLL] = "SP_SLL";
  spmap[SP_SRL] = "SP_SRL";
  spmap[SP_SRA] = "SP_SRA";
  spmap[SP_SLLV] = "SP_SLLV";
  spmap[SP_SRLV] = "SP_SRLV";
  spmap[SP_SRAV] = "SP_SRAV";
  spmap[SP_JR] = "SP_JR";
  spmap[SP_JALR] = "SP_JALR";
  spmap[SP_MFHI] = "SP_MFHI";
  spmap[SP_MTHI] = "SP_MTHI";
  spmap[SP_MFLO] = "SP_MFLO";
  spmap[SP_MTLO] = "SP_MTLO";
  spmap[SP_MULT] = "SP_MULT";
  spmap[SP_MULTU] = "SP_MULTU";
  spmap[SP_DIV] = "SP_DIV";
  spmap[SP_DIVU] = "SP_DIVU";
  spmap[SP_ADD] = "SP_ADD";
  spmap[SP_ADDU] = "SP_ADDU";
  spmap[SP_SUB] = "SP_SUB";
  spmap[SP_SUBU] = "SP_SUBU";
  spmap[SP_AND] = "SP_AND";
  spmap[SP_OR] = "SP_OR";
  spmap[SP_XOR] = "SP_XOR";
  spmap[SP_NOR] = "SP_NOR";
  spmap[SP_SLT] = "SP_SLT";
  spmap[SP_SLTU] = "SP_SLTU";
}
