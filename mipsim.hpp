#ifndef _MIPSIM_H_
#define _MIPSIM_H_

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

#undef LITTLE_ENDIAN
#undef BIG_ENDIAN

#ifdef _WIN32
#define LITTLE_ENDIAN
#endif
#ifdef __i386__
#define LITTLE_ENDIAN
#endif
#ifdef __x86_64__
#define LITTLE_ENDIAN
#endif
#ifdef _BIG_ENDIAN
#define BIG_ENDIAN
#endif

#ifndef LITTLE_ENDIAN
#ifndef BIG_ENDIAN
int this_is_bad = EndiannessIsNotDefined_CheckMipsimDotHpp();
#endif
#endif

#ifdef LITTLE_ENDIAN
#ifdef BIG_ENDIAN
int this_is_also_bad = EndiannessIsDefinedTwice_CheckMipsimDotHpp();
#endif
#endif

using namespace std;

enum Type { R_TYPE, I_TYPE, J_TYPE, GENERIC_TYPE };

enum Op {
  OP_SPECIAL, OP_REGIMM, OP_J, OP_JAL, OP_BEQ, OP_BNE, OP_BLEZ, OP_BGTZ,
  OP_ADDI, OP_ADDIU, OP_SLTI, OP_SLTIU, OP_ANDI, OP_ORI, OP_XORI, OP_LUI,
  OP_COP0, OP_COP1, OP_COP2, OP_23, OP_BEQL, OP_BNEL, OP_BLEZL, OP_BGTZL,
  OP_DADDI, OP_DADDIU, OP_LDL, OP_LDR, OP_34, OP_35, OP_36, OP_37,
  OP_LB, OP_LH, OP_LWL, OP_LW, OP_LBU, OP_LHU, OP_LWR, OP_LWU,
  OP_SB, OP_SH, OP_SWL, OP_SW, OP_SBU, OP_SHU, OP_SWR, OP_SWU,
  OP_UNDEFINED
};

enum Special {
  SP_SLL, SP_01, SP_SRL, SP_SRA, SP_SLLV, SP_05, SP_SRLV, SP_SRAV,
  SP_JR, SP_JALR, SP_12, SP_13, SP_SYSCALL, SP_BREAK, SP_16, SP_SYNC,
  SP_MFHI, SP_MTHI, SP_MFLO, SP_MTLO, SP_DSLLV, SP_25, SP_DSRLV, SP_DSRAV,
  SP_MULT, SP_MULTU, SP_DIV, SP_DIVU, SP_DMULT, SP_DMULTU, SP_DDIV, SP_DDIVU,
  SP_ADD, SP_ADDU, SP_SUB, SP_SUBU, SP_AND, SP_OR, SP_XOR, SP_NOR, 
  SP_50, SP_51, SP_SLT, SP_SLTU,
  SP_UNDEFINED
};

extern vector<string> opmap;
string opToString(const Op op);
extern vector<string> spmap;
string specialToString(const Special sp);
void op_init();
unsigned int swizzle(unsigned int d);

struct RType {
#ifdef BIG_ENDIAN
  unsigned int op : 6;
  unsigned int rs : 5;
  unsigned int rt : 5;
  unsigned int rd : 5;
  unsigned int sa : 5;
  unsigned int func : 6;
#endif /* BIG_ENDIAN */
#ifdef LITTLE_ENDIAN
  unsigned int func : 6;
  unsigned int sa : 5;
  unsigned int rd : 5;
  unsigned int rt : 5;
  unsigned int rs : 5;
  unsigned int op : 6;
#endif /* LITTLE_ENDIAN */
};

struct IType {
#ifdef BIG_ENDIAN
  unsigned int op : 6;
  unsigned int rs : 5;
  unsigned int rt : 5;
  short imm : 16;
#endif /* BIG_ENDIAN */
#ifdef LITTLE_ENDIAN
  short imm : 16;
  unsigned int rt : 5;
  unsigned int rs : 5;
  unsigned int op : 6;
#endif /* LITTLE_ENDIAN */
};

struct JType {
#ifdef BIG_ENDIAN
  unsigned int op : 6;
  int target : 26;
#endif /* BIG_ENDIAN */
#ifdef LITTLE_ENDIAN
  int target : 26;
  unsigned int op : 6;
#endif /* LITTLE_ENDIAN */
};

struct GenericType {
#ifdef BIG_ENDIAN
  unsigned int op : 6;
  unsigned int chud : 20;
  unsigned int func : 6;
#endif /* BIG_ENDIAN */
#ifdef LITTLE_ENDIAN
  unsigned int func : 6;
  unsigned int chud : 20;
  unsigned int op : 6;
#endif /* LITTLE_ENDIAN */
};

class Data8 {
private:
  unsigned char d;
public:
  Data8() {}
  Data8(unsigned char _d) : d(_d) {}
  operator unsigned char() const { return d; }
};

class Data32 {
private:
  union {
    unsigned int _uint;
    int _int;
    unsigned char _ubyte4[4];
    RType _rtype;
    IType _itype;
    JType _jtype;
    GenericType _gtype;
  } d;
public:
  // Data32() {}
  Data32(const unsigned int & _d) { d._uint = _d; }
  Data32(const unsigned char & d0, 
         const unsigned char & d1, 
         const unsigned char & d2, 
         const unsigned char & d3) { 
    set_data_ubyte4(0, d0);
    set_data_ubyte4(1, d1);
    set_data_ubyte4(2, d2);
    set_data_ubyte4(3, d3);
  }
  // Data32 & operator=(const Data32 & _d) { set_data_uint(_d.data_uint()); }
  operator unsigned int() const { return data_uint(); }
  bool operator==(const Data32 & dd) const { return (data_uint() == dd.data_uint()); }
  bool operator!=(const Data32 & dd) const { return (data_uint() != dd.data_uint()); }
  inline void set_data_int(int arg) { 
#ifdef LITTLE_ENDIAN
    // d._int = swizzle(arg);
    d._int = arg; 
#endif
#ifdef BIG_ENDIAN
    d._int = arg; 
#endif
  }
  inline int data_int(void) const {
#ifdef LITTLE_ENDIAN
    // return swizzle(d._int);
    return d._int; 
#endif
#ifdef BIG_ENDIAN
    return d._int; 
#endif
  }
  inline void set_data_uint(unsigned int arg) {
#ifdef LITTLE_ENDIAN
    // d._uint = swizzle(arg);
    d._uint = arg;
#endif
#ifdef BIG_ENDIAN
    d._uint = arg;
#endif
  }
  inline unsigned int data_uint(void) const {
#ifdef LITTLE_ENDIAN
    // return swizzle(d._uint);
    return d._uint; 
#endif
#ifdef BIG_ENDIAN
    return d._uint; 
#endif
  }
  inline void set_data_ubyte4(int i, unsigned char arg) {
#ifdef LITTLE_ENDIAN
    d._ubyte4[3-i] = arg;
#endif
#ifdef BIG_ENDIAN
    d._ubyte4[i] = arg;
#endif
  }
  inline unsigned char data_ubyte4(int i) const {
#ifdef LITTLE_ENDIAN
    return d._ubyte4[3-i]; 
#endif
#ifdef BIG_ENDIAN
    return d._ubyte4[i]; 
#endif
  }
  operator RType() const { return d._rtype; }
  operator IType() const { return d._itype; }
  operator JType() const { return d._jtype; }
  operator GenericType() const { return d._gtype; }
  static Type classifyType(const Data32 d) {
    GenericType rg(d);
    switch(rg.op) {
    case OP_J:
    case OP_JAL:
      return J_TYPE;
      break;
    case OP_SPECIAL:
      return R_TYPE;
      break;
    default:
      return I_TYPE;
      break;
    }
    // return R_TYPE;
  }
  static void printI(const Data32 d) {
    RType rt(d); IType it(d); JType jt(d);
    switch (classifyType(d)) {
    case R_TYPE:
      cout << hex
           << "op: " << opmap[rt.op]
           << " rs: " << rt.rs
           << " rt: " << rt.rt
           << " rd: " << rt.rd
           << " sa: " << rt.sa
           << " func: " << spmap[rt.func]
           << endl;
      break;
    case I_TYPE:
      cout << hex
           << "op: " << opmap[it.op]
           << " rs: " << it.rs
           << " rt: " << it.rt
           << " imm: " << it.imm
           << endl;
      break;
    case J_TYPE:
      cout << hex
           << "op: " << opmap[jt.op]
           << " target: " << jt.target
           << endl;
      break;
    }
  }
  static void printD(const Data32 d) {
    cout << hex << d.data_uint() << endl;
  }
};

enum MemType { MEM_MEM, MEM_RF, MEM_INVALID };

enum DataType { INSTRUCTIONS, DATA };

template<class Stored, class Accessed>
class Memory {
private:
  vector<Stored> m;
  unsigned int base;
  unsigned int lowest, highest;
public:
  Memory() : m(0), base(0), lowest(0xffffffff), highest(0) {}
  Memory(unsigned int _base) : m(0), base(_base), lowest(0xffffffff),
                               highest(0) {}
  Memory(unsigned int size, Stored d) : m(size, d), base(0), 
                                        lowest(0xffffffff), highest(0) {}
  unsigned int size() const { return m.size(); }
  typename vector<Stored>::const_iterator begin() const { return m.begin(); }
  typename vector<Stored>::const_iterator end() const { return m.end(); }
  void write(const unsigned int addr, const Accessed data);
  const Accessed operator[](const unsigned int addr) const;
  // Accessed & operator[](const unsigned int addr);
  void dump(DataType dt) const;
  unsigned int getBase() const { return base; }
  bool inRange(unsigned int r) { return (r >= base) && (r < base + size()); } 
};

class Register {
private:
  Data32 d;
public:
  Register() : d(0) {}
  Register(Data32 _d) : d(_d) {}
  void write(unsigned int val) {
    d = Data32(val);
  }
  operator Data32() const { return d; }
  operator unsigned int() const { return d.data_uint(); }
  Register & operator=(unsigned int val) {
    write(val);
  }
};

class Cache {
private:
  unsigned int size;
  unsigned int blocksize;
  vector<unsigned int> entries;
  unsigned int hits;
  unsigned int misses;
public:
  Cache(unsigned int _size, unsigned int _blocksize) :
    size(_size), blocksize(_blocksize), entries(_size / _blocksize, 0),
    hits(0), misses(0) {}
  bool access(unsigned int address);
  void printStats() const {
    cout << dec << size << " byte cache (blocksize " << dec << blocksize
         << " bytes): " << hits << " hits, " << misses << " misses (hit rate: " 
         << (static_cast<float>(hits) * 100.0f /
             static_cast<float>(hits + misses)) << "%)" << endl;
  }
};

class Caches {
private:
  unsigned int size;
  vector<Cache> caches;
public:
  Caches(unsigned int _size) : size(_size) {
    int i;
    for (i = 4; i <= size; i *= 2) {
      caches.push_back(Cache(size, i));
    }
  }
  void access(unsigned int address) {
    if (size == 0) {
      return;
    }
    vector<Cache>::iterator vci;
    for (vci = caches.begin(); vci != caches.end(); ++vci) {
      vci->access(address);
    }
  }
  void printStats() const {
    if (size == 0) {
      return;
    }
    for_each(caches.begin(), caches.end(), mem_fun_ref(&Cache::printStats));
  }
};

class Stats {
public:
  unsigned int instrs;

  unsigned int numForwardBranchesTaken;
  unsigned int numForwardBranchesNotTaken;
  unsigned int numBackwardBranchesTaken;
  unsigned int numBackwardBranchesNotTaken;

  unsigned int hasUsefulBranchDelaySlot;
  unsigned int hasUselessBranchDelaySlot;

  unsigned int loadHasLoadUseHazard;
  unsigned int loadHasNoLoadUseHazard;

  void print();
};

class Options {
public:
  Options() : program(false), dump(false), instrs(false), writes(false),
              stats(false) {}
  bool program;
  bool dump;
  bool instrs;
  bool writes;
  bool stats;
};

extern Memory<Data8,Data32> imem;
extern Memory<Data8,Data32> dmem;
extern Memory<Data32,Data32> rf;
extern Register pc;
extern Stats stats;
extern Options opts;
extern Caches caches;

void parse(const char * file);
void execute();  
#endif /* _MIPSIM_H_ */
