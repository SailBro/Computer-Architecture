#include<stdio.h>
#include "instruction.h"
#include "shell.h"

void nop(){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    return;
}






void j(uint32_t target){
    // NEXT_STATE.PC=(target<<2);// 以字节为地址单位
    // 高四位不变，低28位<-target
    NEXT_STATE.PC = ((CURRENT_STATE.PC+4) & 0xF0000000) | (target << 2);
}

void jal(uint32_t target){
    // 后面要返回跳转指令后的下一条，因而需要保存
    // 返回地址存到$ra寄存器（一般是最后一位——31）
    NEXT_STATE.REGS[31]=CURRENT_STATE.PC+4;
    j(target);
}

void jr(uint8_t rs){
    // 读取寄存器中的地址
    NEXT_STATE.PC=CURRENT_STATE.REGS[rs];
}

void jalr(uint8_t rs, uint8_t rd){
    // jal+jr
    NEXT_STATE.PC=CURRENT_STATE.REGS[rs];
    if(rd!=0)
        NEXT_STATE.REGS[rd]=CURRENT_STATE.PC+4;
    else
        NEXT_STATE.REGS[31]=CURRENT_STATE.PC+4;
}

void beq(uint8_t rs, uint8_t rt, int16_t imm){
    // 比较rs与rt寄存器中值的结果，相等则跳转
    if(CURRENT_STATE.REGS[rs]==CURRENT_STATE.REGS[rt])
        NEXT_STATE.PC=CURRENT_STATE.PC+4+(imm<<2);
    else
        NEXT_STATE.PC=CURRENT_STATE.PC+4;
}

void bne(uint8_t rs, uint8_t rt, int16_t imm){
    // 不等则跳转
    if(CURRENT_STATE.REGS[rs]!=CURRENT_STATE.REGS[rt])
        NEXT_STATE.PC=CURRENT_STATE.PC+4+(imm<<2);
    else
        NEXT_STATE.PC=CURRENT_STATE.PC+4;
}

void blez(uint8_t rs, int16_t imm){
    // <=0则跳转
    if((int32_t)CURRENT_STATE.REGS[rs]<=0)
        NEXT_STATE.PC=CURRENT_STATE.PC+4+(imm<<2);
    else
        NEXT_STATE.PC=CURRENT_STATE.PC+4;
}

void bgtz(uint8_t rs, int16_t imm){
    // >0则跳转
    if((int32_t)CURRENT_STATE.REGS[rs]>0)
        NEXT_STATE.PC=CURRENT_STATE.PC+4+(imm<<2);
    else
        NEXT_STATE.PC=CURRENT_STATE.PC+4;
}

void bltz(uint8_t rs, int16_t offset){
    // <0则跳转
    if((int32_t)CURRENT_STATE.REGS[rs]<0)
        NEXT_STATE.PC=CURRENT_STATE.PC+4+(offset<<2);
    else
        NEXT_STATE.PC=CURRENT_STATE.PC+4;
}

void bgez(uint8_t rs, int16_t offset){
    // >=0则跳转
    if((int32_t)CURRENT_STATE.REGS[rs]>=0)
        NEXT_STATE.PC=CURRENT_STATE.PC+4+(offset<<2);
    else
        NEXT_STATE.PC=CURRENT_STATE.PC+4;
}

void bltzal(uint8_t rs, int16_t offset){
    // <0跳转，返回地址保存到31寄存器
    if((int32_t)CURRENT_STATE.REGS[rs]<0){
        NEXT_STATE.PC=CURRENT_STATE.PC+4+(offset<<2);
        NEXT_STATE.REGS[31]=CURRENT_STATE.PC+4;
    }
    else
        NEXT_STATE.PC=CURRENT_STATE.PC+4;
}

void bgezal(uint8_t rs, int16_t offset){
    // >=0跳转，返回地址保存到31寄存器
    if((int32_t)CURRENT_STATE.REGS[rs]>=0){
        NEXT_STATE.PC=CURRENT_STATE.PC+4+(offset<<2);
        NEXT_STATE.REGS[31]=CURRENT_STATE.PC+4;
    }
    else
        NEXT_STATE.PC=CURRENT_STATE.PC+4;
}









void add(uint8_t rs, uint8_t rt, uint8_t rd){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rd<-rs+rt
    if(rd==0)
        return;
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]+CURRENT_STATE.REGS[rt];
}

void addu(uint8_t rs, uint8_t rt, uint8_t rd){
    // 和add基本一样
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rd<-rs+rt
    if(rd==0)
        return;
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]+CURRENT_STATE.REGS[rt];
}

void sub(uint8_t rs, uint8_t rt, uint8_t rd){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rd<-rs-rt
    if(rd==0)
        return;
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]-CURRENT_STATE.REGS[rt];
}

void subu(uint8_t rs, uint8_t rt, uint8_t rd){
    // 和sub基本一样
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rd<-rs-rt
    if(rd==0)
        return;
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]-CURRENT_STATE.REGS[rt];
}

void and(uint8_t rs, uint8_t rt, uint8_t rd){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rd<-rs&rt
    if(rd==0)
        return;
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]&CURRENT_STATE.REGS[rt];
}

void or(uint8_t rs, uint8_t rt, uint8_t rd){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rd<-rs|rt
    if(rd==0)
        return;
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]|CURRENT_STATE.REGS[rt];
}

void xor(uint8_t rs, uint8_t rt, uint8_t rd){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rd<-rs^rt
    if(rd==0)
        return;
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rs]^CURRENT_STATE.REGS[rt];
}

void nor(uint8_t rs, uint8_t rt, uint8_t rd){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rd<-~(rs|rt)
    if(rd==0)
        return;
    NEXT_STATE.REGS[rd]=~(CURRENT_STATE.REGS[rs]|CURRENT_STATE.REGS[rt]);
}

void slt(uint8_t rs, uint8_t rt, uint8_t rd){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rd==0)
        return;
    if((int32_t)CURRENT_STATE.REGS[rs]<CURRENT_STATE.REGS[rt])
        NEXT_STATE.REGS[rd]=1;
    else
        NEXT_STATE.REGS[rd]=0;
}

void sltu(uint8_t rs, uint8_t rt, uint8_t rd){
    // 和slt基本一样
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rd==0)
        return;
    if(CURRENT_STATE.REGS[rs]<CURRENT_STATE.REGS[rt])
        NEXT_STATE.REGS[rd]=1;
    else
        NEXT_STATE.REGS[rd]=0;
}

void mult(uint8_t rs, uint8_t rt){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // 相乘结果
    int64_t res=(int32_t)CURRENT_STATE.REGS[rs]*CURRENT_STATE.REGS[rt];
    // 低32位保存在low，高32位保存在high
    NEXT_STATE.LO=res;
    NEXT_STATE.HI=(int64_t)res>>32;
}

void multu(uint8_t rs, uint8_t rt){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // 相乘结果(无符号数)
    uint32_t res=CURRENT_STATE.REGS[rs]*CURRENT_STATE.REGS[rt];
    // 低32位保存在low，高32位保存在high
    NEXT_STATE.LO=res;
    NEXT_STATE.HI=(int64_t)res>>32;
}

void mfhi(uint8_t rd){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rd==0)
        return;
    // rd<-high
    NEXT_STATE.REGS[rd]=CURRENT_STATE.HI;
}

void mflo(uint8_t rd){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rd==0)
        return;
    // rd<-low
    NEXT_STATE.REGS[rd]=CURRENT_STATE.LO;
}

void mthi(uint8_t rs){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rs==0)
        return;
    // rs<-high
    NEXT_STATE.REGS[rs]=CURRENT_STATE.HI;
}

void mtlo(uint8_t rs){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rs==0)
        return;
    // rs<-low
    NEXT_STATE.REGS[rs]=CURRENT_STATE.LO;
}

void div(uint8_t rs, uint8_t rt){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rs/rt，low<-商，high<-余数
    NEXT_STATE.LO=(int32_t)CURRENT_STATE.REGS[rs]/CURRENT_STATE.REGS[rt];
    NEXT_STATE.HI=(int32_t)CURRENT_STATE.REGS[rs]%CURRENT_STATE.REGS[rt];
}

void divu(uint8_t rs, uint8_t rt){
    // 和div基本一样
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rs/rt，low<-商，high<-余数
    NEXT_STATE.LO=CURRENT_STATE.REGS[rs]/CURRENT_STATE.REGS[rt];
    NEXT_STATE.HI=CURRENT_STATE.REGS[rs]%CURRENT_STATE.REGS[rt];
}













void sll(uint8_t rt, uint8_t rd, uint8_t shamt){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rd==0)
        return;
    // rd ← rt << sa
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rt]<<shamt;

}

void srl(uint8_t rt, uint8_t rd, uint8_t shamt){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rd==0)
        return;
    // rd ← rt >> sa
    NEXT_STATE.REGS[rd]=CURRENT_STATE.REGS[rt]>>shamt;

}

void sra(uint8_t rt, uint8_t rd, uint8_t shamt){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rd==0)
        return;
    // rd ← rt >> sa，空余值拿r[31]填充（强制类型转换）
    NEXT_STATE.REGS[rd]=(int32_t)CURRENT_STATE.REGS[rt]>>shamt;
}

void sllv(uint8_t rs, uint8_t rt, uint8_t rd){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rd ← rt << rs[4：0]
    //限定左移位数在0-31之间
    uint8_t shamt = CURRENT_STATE.REGS[rs] & 0x1F;
	NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << shamt;
}

void srlv(uint8_t rs, uint8_t rt, uint8_t rd){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rd ← rt >> rs[4：0]
    //限定右移位数在0-31之间
    uint8_t shamt = CURRENT_STATE.REGS[rs] & 0x1F;
	NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shamt;
}

void srav(uint8_t rs, uint8_t rt, uint8_t rd){
    // 算数右移，空余值拿r[31]填充（强制类型转换）
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rd ← rt >> rs[4：0]
    //限定右移位数在0-31之间
    uint8_t shamt = CURRENT_STATE.REGS[rs] & 0x1F;
	NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> shamt;
}

void lw(uint8_t base, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rt==0)
        return;
    // 确定地址add=[base]+imm
    uint32_t address = (int32_t) CURRENT_STATE.REGS[base] + imm;
    // 从add处读取数
	NEXT_STATE.REGS[rt] = mem_read_32(address);
}

void sw(uint8_t base, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // 确定地址add=[base]+imm
    uint32_t address = (int32_t) CURRENT_STATE.REGS[base] + imm;
    // 向add处写数
	mem_write_32(address,NEXT_STATE.REGS[rt]);
}

void lb(uint8_t base, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rt==0)
        return;
    // 确定地址add=[base]+imm
    uint32_t address = (int32_t) CURRENT_STATE.REGS[base] + imm;
    // 读取一个字节，然后符号扩展至32位
    NEXT_STATE.REGS[rt] = (int32_t) mem_read_32(address) & 0xFF;
    // 符号拓展
    NEXT_STATE.REGS[rt] = NEXT_STATE.REGS[rt] > 0x7F? NEXT_STATE.REGS[rt] | 0xFFFFFF00: NEXT_STATE.REGS[rt];
}

void lh(uint8_t base, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rt==0)
        return;
    // 确定地址add=[base]+imm
    uint32_t address = (int32_t) CURRENT_STATE.REGS[base] + imm;
    // 读取一个半字，然后符号扩展至32位
    NEXT_STATE.REGS[rt] = (int32_t) mem_read_32(address) & 0xFFFF;
    // 符号拓展
    NEXT_STATE.REGS[rt] = NEXT_STATE.REGS[rt] > 0x7F? NEXT_STATE.REGS[rt] | 0xFFFFFF00: NEXT_STATE.REGS[rt];
}

void lbu(uint8_t base, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rt==0)
        return;
    // 确定地址add=[base]+imm
    uint32_t address = (int32_t) CURRENT_STATE.REGS[base] + imm;
    // 读取一个字节，然后无符号扩展至32位
    NEXT_STATE.REGS[rt]=mem_read_32(address) & 0x000000FF;
}

void lhu(uint8_t base, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rt==0)
        return;
    // 确定地址add=[base]+imm
    uint32_t address = (int32_t) CURRENT_STATE.REGS[base] + imm;
    // 读取一个半字，然后无符号扩展至32位
    NEXT_STATE.REGS[rt]=mem_read_32(address) & 0x0000FFFF;
}

void sb(uint8_t base, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // 确定地址add=[base]+imm
    uint32_t address = (int32_t) CURRENT_STATE.REGS[base] + imm;
    // 最低字节保存
    // add处低八位（最低字节）清零
    uint32_t value = mem_read_32(address) & ~0x000000FF;
    // 合并add的其他位和rt的低八位
    value |= (CURRENT_STATE.REGS[rt] & 0x000000FF);
	mem_write_32(address, value);
}

void sh(uint8_t base, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // 确定地址add=[base]+imm
    uint32_t address = (int32_t) CURRENT_STATE.REGS[base] + imm;
    // 最低半字（2个字节）保存
    uint32_t value = mem_read_32(address) & ~0x0000FFFF;
	value |= (CURRENT_STATE.REGS[rt] & 0x0000FFFF);
	mem_write_32(address, value);
}











void addi(uint8_t rs, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rt<-rs+imm
    if(rt==0)
        return;
    NEXT_STATE.REGS[rt]=(int32_t)CURRENT_STATE.REGS[rs]+imm;
}

void addiu(uint8_t rs, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rt<-rs+imm
    if(rt==0)
        return;
    NEXT_STATE.REGS[rt]=CURRENT_STATE.REGS[rs]+imm;
}

void slti(uint8_t rs, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rt==0)
        return;
    if(CURRENT_STATE.REGS[rs]<imm)
        NEXT_STATE.REGS[rt]=1;
    else
        NEXT_STATE.REGS[rt]=0;
}

void sltiu(uint8_t rs, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    if(rt==0)
        return;
    if(CURRENT_STATE.REGS[rs]<imm)
        NEXT_STATE.REGS[rt]=1;
    else
        NEXT_STATE.REGS[rt]=0;
}

void andi(uint8_t rs, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rt<-rs&imm
    if(rt==0)
        return;
    NEXT_STATE.REGS[rt]=CURRENT_STATE.REGS[rs]&((int32_t)imm& 0x0000FFFF);
}

void ori(uint8_t rs, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rt<-rs|mm，高位填充0
    if(rt==0)
        return;
    NEXT_STATE.REGS[rt]=CURRENT_STATE.REGS[rs]|((int32_t)imm& 0x0000FFFF);
}

void xori(uint8_t rs, uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rt<-rs^imm
    if(rt==0)
        return;
    NEXT_STATE.REGS[rt]=CURRENT_STATE.REGS[rs]^((int32_t)imm& 0x0000FFFF);
}

void lui(uint8_t rt, int16_t imm){
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // rt<-imm<<16
    if(rt==0)
        return;
    NEXT_STATE.REGS[rt]=imm<<16;
}










void syscall(){
    // printf("ERROR!");
    // return;
    
    NEXT_STATE.PC=CURRENT_STATE.PC+4;
    // 系统调用
    if(CURRENT_STATE.REGS[2] == 0x0A)
        RUN_BIT = 0;  // 退出程序
    return;
}