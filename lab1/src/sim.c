#include <stdio.h>
#include "shell.h"
#include "instruction.h"
#include "instruction.c"


void shifts(rt, rd, shamt, funct){
    // 调用相应的位移指令函数
    switch(funct) {
		case SLL:
			sll(rt, rd, shamt);
			return;
		case SRL:
			srl(rt, rd, shamt);
			return;
		case SRA:
			sra(rt, rd, shamt);
			return;
		case SLLV:
			sllv(rt, rd, shamt);
			return;
		case SRLV:
			srlv(rt, rd, shamt);
			return;
		case SRAV:
			srav(rt, rd, shamt);
			return;
	}
}

void arithmetic(rs, rt, rd, funct){
    switch(funct) {
		case ADD:
			add(rs, rt, rd);
			return;
		case ADDU:
			addu(rs, rt, rd);
			return;
		case SUB:
			sub(rs, rt, rd);
			return;
		case SUBU:
			subu(rs, rt, rd);
			return;
		case MULT:
			mult(rs, rt);
			return;
		case MULTU:
			multu(rs, rt);
			return;
		case DIV:
			div(rs, rt);
			return;
		case DIVU:
			divu(rs, rt);
			return;
	}
}

void logical(rs, rt, rd, funct){
    switch(funct) {
		case AND:
			and(rs, rt, rd);
			return;
		case OR:
			or(rs, rt, rd);
			return;
		case XOR:
			xor(rs, rt, rd);
			return;
		case NOR:
			nor(rs, rt, rd);
			return;
	}
}

void conditional(rs, rt, rd, funct){
    switch(funct) {
		case SLT:
			slt(rs, rt, rd);
			return;
		case SLTU:
			sltu(rs, rt, rd);
			return;
	}
}

void rtype_jump(rs, rd, funct){
    switch(funct) {
		case JR:
			jr(rs);
			return;
		case JALR:
			jalr(rs, rd);
			return;
	}
}

void rtype_lo_hi(rs, rd, funct){
    switch(funct) {
		case MFHI:
			mfhi(rd);
			return;
		case MFLO:
			mflo(rd);
			return;
		case MTHI:
			mthi(rs);
			return;
		case MTLO:
			mtlo(rs);
			return;
	}
}

void itype_branches(op, rs, rt, imm){
    switch(op) {
		case BEQ:
			beq(rs, rt, imm);
			return;
		case BNE:
			bne(rs, rt, imm);
			return;
		case BLEZ:
			blez(rs, imm);
			return;
		case BGTZ:
			bgtz(rs, imm);
			return;
	}
}

void itype_arithmetic(op, rs, rt, imm){
    switch(op) {
		case ADDI:
			addi(rs, rt, imm);
			return;
		case ADDIU:
			addiu(rs, rt, imm);
			return;
		case SLTI:
			slti(rs, rt, imm);
			return;
		case SLTIU:
			sltiu(rs, rt, imm);
			return;
		case ANDI:
			andi(rs, rt, imm);
			return;
		case ORI:
			ori(rs, rt, imm);
			return;
		case XORI:
			xori(rs, rt, imm);
			return;
		case LUI:
			lui(rt, imm);
			return;
	}
}

void mem_load_store(uint8_t op, uint8_t base, uint8_t rt, int16_t imm) {
    switch(op) {
		case LB:
			lb(base, rt, imm);
			return;
		case LH:
			lh(base, rt, imm);
			return;
		case LW:
			lw(base, rt, imm);
			return;
		case LBU:
			lbu(base, rt, imm);
			return;
		case LHU:
			lhu(base, rt, imm);
			return;
		case SB:
			sb(base, rt, imm);
			return;
		case SH:
			sh(base, rt, imm);
			return;
		case SW:
			sw(base, rt, imm);
			return;
	}
}



// MIPS指令的大体分类R/I/J（给定字段不同）

// R型指令：寄存器之间的操作
void rtype(uint8_t rs, uint8_t rt, uint8_t rd, uint8_t shamt, uint8_t funct) {
   
    // 根据funct字段的值进一步分类

    if(funct <= 7)
        // 位移指令
		shifts(rt, rd, shamt, funct);
	else if( (funct >= 24 && funct <= 27) || (funct >= 32 && funct <= 35) )
		// 算术指令
        arithmetic(rs, rt, rd, funct);
	else if(funct >= 36 && funct <= 39)
		// 逻辑指令
        logical(rs, rt, rd, funct);
	else if(funct == 42 || funct == 43)
		// 条件分支指令
        conditional(rs, rt, rd, funct);
	else if(funct == 8 || funct == 9)
		// 跳转指令
        rtype_jump(rs, rd, funct);
	else if(funct >= 16  && funct <= 19)
		// low与high寄存器相关
        rtype_lo_hi(rs, rd, funct);
	else if(funct == 12)
		syscall();
    else
        return ;
}

// I型指令
void itype(uint8_t op, uint8_t rs, uint8_t rt, int16_t imm){
    
    // 根据op字段的值分类

    if(op >= 4 && op <= 7)
        // 分支指令
		itype_branches(op, rs, rt, imm);
	else if(op >= 8 && op <= 15)
		// 算术指令
        itype_arithmetic(op, rs, rt, imm);
	else if(op >= 32 && op <= 43) 
		// 加载指令
        mem_load_store(op, rs, rt, imm);
    else
        return ;
}

// J型指令
void jtype(uint8_t op, uint32_t target){
    switch(op) {
		case J:
			j(target);
			return;
		case JAL:
			jal(target);
			return;
	}
}

// I型分支指令(特殊)
void itype_sbranches(uint8_t rs, uint8_t rt, int16_t imm){
    // 条件分支
    switch(rt) {
		case BLTZ:
			bltz(rs, imm);
			return;
		case BGEZ:
			bgez(rs, imm);
			return;
		case BLTZAL:
			bltzal(rs, imm);
			return;
		case BGEZAL:
			bgezal(rs, imm);
			return;
	}
}

void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */

    // 读取内存中的指令
    uint32_t instruction = 0x0;
	instruction = mem_read_32(CURRENT_STATE.PC);

    // 确定各字段值
	uint8_t op = 0;
	uint8_t rs = 0, rt = 0, rd = 0, shamt = 0, funct = 0;
	uint16_t imm = 0;
	uint32_t target = 0;
	op = ((instruction >> 26) & 0x3F);
	rs = ((instruction >> 21) & 0x1F);
	rt = ((instruction >> 16) & 0x1F);
	rd = ((instruction >> 11) & 0x1F);
	shamt = ((instruction >> 6) & 0x1F);
	funct = (instruction & 0x3F);
	imm = instruction;
	target = instruction & 0x03FFFFFF;

    // 区分指令类型，调用相应函数并传参
    if(instruction==0)
        nop();
    
    switch (op)
    {
    case 0:
        rtype(rs, rt, rd, shamt, funct);
        break;
    case 1:
        itype_sbranches(rs, rt, imm); 
        break;
    case 2:
        jtype(op, target);
        break;
    case 3:
        jtype(op, target);
        break;
    default:
        itype(op, rs, rt, imm);
        break;
    }
}
