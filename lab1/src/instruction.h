// 定义指令和16进制操作码&功能码的对应关系
// 定义函数

#include<stdint.h>

void nop();

// 12个跳转指令：Jump and Branch Instructions
// 操作码：
#define J 0x2
#define JAL 0x3
#define JR 0x8
#define JALR 0x9
#define BEQ 0x4
#define BNE 0x5
#define BLEZ 0x6
#define BGTZ 0x7
#define BLTZ 0x0
#define BGEZ 0x1
#define BLTZAL 0x10
#define BGEZAL 0x11

void j(uint32_t target);
void jal(uint32_t target);
void jr(uint8_t rs);
void jalr(uint8_t rs, uint8_t rd);
void beq(uint8_t rs, uint8_t rt, int16_t imm);
void bne(uint8_t rs, uint8_t rt, int16_t imm);
void blez(uint8_t rs, int16_t imm);
void bgtz(uint8_t rs, int16_t imm);
void bltz(uint8_t rs, int16_t offset);
void bgez(uint8_t rs, int16_t offset);
void bltzal(uint8_t rs, int16_t offset);
void bgezal(uint8_t rs, int16_t offset);

// 18个算数和逻辑指令：Arithmetic and Logical Instructions
// 操作码0x0，功能码：
#define ADD 0x20
#define ADDU 0x21
#define SUB 0x22
#define SUBU 0x23
#define AND 0x24
#define OR 0x25
#define XOR 0x26
#define NOR 0x27
#define SLT 0x2A
#define SLTU 0x2B
#define MULT 0x18
#define MULTU 0x19
#define MFHI 0x10
#define MFLO 0x12
#define MTHI 0x11
#define MTLO 0x13
#define DIV 0x1A
#define DIVU 0x1B

void add(uint8_t rs, uint8_t rt, uint8_t rd);
void addu(uint8_t rs, uint8_t rt, uint8_t rd);
void sub(uint8_t rs, uint8_t rt, uint8_t rd);
void subu(uint8_t rs, uint8_t rt, uint8_t rd);
void and(uint8_t rs, uint8_t rt, uint8_t rd);
void or(uint8_t rs, uint8_t rt, uint8_t rd);
void xor(uint8_t rs, uint8_t rt, uint8_t rd);
void nor(uint8_t rs, uint8_t rt, uint8_t rd);
void slt(uint8_t rs, uint8_t rt, uint8_t rd);
void sltu(uint8_t rs, uint8_t rt, uint8_t rd);
void mult(uint8_t rs, uint8_t rt);
void multu(uint8_t rs, uint8_t rt);
void mfhi(uint8_t rd);
void mflo(uint8_t rd);
void mthi(uint8_t rs);
void mtlo(uint8_t rs);
void div(uint8_t rs, uint8_t rt);
void divu(uint8_t rs, uint8_t rt);

// 6个移位指令：Shift Instructions
// 操作码0x0，功能码：
#define SLL 0x0
#define SRL 0x2
#define SRA 0x3
#define SLLV 0x4
#define SRLV 0x6
#define SRAV 0x7

void sll(uint8_t rt, uint8_t rd, uint8_t shamt);
void srl(uint8_t rt, uint8_t rd, uint8_t shamt);
void sra(uint8_t rt, uint8_t rd, uint8_t shamt);
void sllv(uint8_t rs, uint8_t rt, uint8_t rd);
void srlv(uint8_t rs, uint8_t rt, uint8_t rd);
void srav(uint8_t rs, uint8_t rt, uint8_t rd);

// 8个加载和存储指令：Load and Store Instructions
// 操作码：
#define LW 0x23
#define SW 0x2B
#define LB 0x20
#define LH 0x21
#define LBU 0x24
#define LHU 0x25
#define SB 0x28
#define SH 0x29

void lw(uint8_t base, uint8_t rt, int16_t imm);
void sw(uint8_t base, uint8_t rt, int16_t imm);
void lb(uint8_t base, uint8_t rt, int16_t imm);
void lh(uint8_t base, uint8_t rt, int16_t imm);
void lbu(uint8_t base, uint8_t rt, int16_t imm);
void lhu(uint8_t base, uint8_t rt, int16_t imm);
void sb(uint8_t base, uint8_t rt, int16_t imm);
void sh(uint8_t base, uint8_t rt, int16_t imm);

// 8个立即数指令：Immediate Instructions
// 操作码：
#define ADDI 0x8
#define ADDIU 0x9
#define SLTI 0xA
#define SLTIU 0xB
#define ANDI 0xC
#define ORI 0xD
#define XORI 0xE
#define LUI 0xF

void addi(uint8_t rs, uint8_t rt, int16_t imm);
void addiu(uint8_t rs, uint8_t rt, int16_t imm);
void slti(uint8_t rs, uint8_t rt, int16_t imm);
void sltiu(uint8_t rs, uint8_t rt, int16_t imm);
void andi(uint8_t rs, uint8_t rt, int16_t imm);
void ori(uint8_t rs, uint8_t rt, int16_t imm);
void xori(uint8_t rs, uint8_t rt, int16_t imm);
void lui(uint8_t rt, int16_t imm);

// 1个系统调用指令：System Call Instruction
// 操作码：
#define SYSCALL 0xC

void syscall();
