
uintptr_t decrypt_client_info()
{
        const uint64_t mb = globals::base;
        uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;

        r8 = mem.Read<uintptr_t>(globals::base + 0xC8FF4E8);
        if(!r8)
                return r8;
        rdx= ~globals::vaPeb;           //mov rdx, gs:[rax]
        rax = r8;               //mov rax, r8
        rax >>= 0x18;           //shr rax, 0x18
        r8 ^= rax;              //xor r8, rax
        rax = r8;               //mov rax, r8
        rax >>= 0x30;           //shr rax, 0x30
        rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
        r8 ^= rax;              //xor r8, rax
        rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
        rcx ^= mem.Read<uintptr_t>(globals::base + 0xB3420B9);          //xor rcx, [0x000000000501FD0E]
        rax = 0x233F5F4AE79533B1;               //mov rax, 0x233F5F4AE79533B1
        r8 *= rax;              //imul r8, rax
        rax = 0x4FF2ED27F19D575D;               //mov rax, 0x4FF2ED27F19D575D
        rcx = ~rcx;             //not rcx
        r8 -= rdx;              //sub r8, rdx
        r8 += rax;              //add r8, rax
        rax = globals::base;            //lea rax, [0xFFFFFFFFF9CDDC2D]
        r8 ^= rax;              //xor r8, rax
        r8 *= mem.Read<uintptr_t>(rcx + 0x19);          //imul r8, [rcx+0x19]
        return r8;
}
uintptr_t decrypt_client_base( uintptr_t client_info)
{
        const uint64_t mb = globals::base;
        uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;
        r8 = mem.Read<uintptr_t>(client_info + 0x1defc8);
        if(!r8)
                return r8;
        rbx = globals::vaPeb;           //mov rbx, gs:[rax]
        rax = rbx;              //mov rax, rbx
        rax <<= 0x23;           //shl rax, 0x23
        rax = _byteswap_uint64(rax);            //bswap rax
        rax &= 0xF;
        switch(rax) {
        case 0:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r10, [0x000000000852DC84]
                rax = globals::base;            //lea rax, [0xFFFFFFFFFD1EB9E3]
                r8 -= rax;              //sub r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x1E;           //shr rax, 0x1E
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x3C;           //shr rax, 0x3C
                r8 ^= rax;              //xor r8, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFD1EB7C4]
                r8 -= rax;              //sub r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x28;           //shr rax, 0x28
                r8 ^= rax;              //xor r8, rax
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                r8 *= mem.Read<uintptr_t>(rax + 0x9);           //imul r8, [rax+0x09]
                rax = 0x9CC8E0420ADA280D;               //mov rax, 0x9CC8E0420ADA280D
                r8 *= rax;              //imul r8, rax
                r8 += rbx;              //add r8, rbx
                rax = r8;               //mov rax, r8
                rax >>= 0x11;           //shr rax, 0x11
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x22;           //shr rax, 0x22
                r8 ^= rax;              //xor r8, rax
                return r8;
        }
        case 1:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r10, [0x000000000852D7EE]
                rax = r8;               //mov rax, r8
                rax >>= 0x9;            //shr rax, 0x09
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x12;           //shr rax, 0x12
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x24;           //shr rax, 0x24
                r8 ^= rax;              //xor r8, rax
                r8 ^= rbx;              //xor r8, rbx
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                r8 *= mem.Read<uintptr_t>(rcx + 0x9);           //imul r8, [rcx+0x09]
                rcx = globals::base;            //lea rcx, [0xFFFFFFFFFD1EB34B]
                rax = rbx;              //mov rax, rbx
                rax -= rcx;             //sub rax, rcx
                rax += 0xFFFFFFFF9F0CFAED;              //add rax, 0xFFFFFFFF9F0CFAED
                r8 += rax;              //add r8, rax
                rax = 0x40ED86BABDEA8F5B;               //mov rax, 0x40ED86BABDEA8F5B
                r8 *= rax;              //imul r8, rax
                rax = 0xA7798517B7F399EA;               //mov rax, 0xA7798517B7F399EA
                r8 ^= rax;              //xor r8, rax
                rcx = globals::base + 0x755F7BDD;               //lea rcx, [0x00000000727E329D]
                rax = rcx;              //mov rax, rcx
                rax = ~rax;             //not rax
                rax ^= rbx;             //xor rax, rbx
                r8 += rax;              //add r8, rax
                rax = 0x459093E765583ADB;               //mov rax, 0x459093E765583ADB
                r8 *= rax;              //imul r8, rax
                return r8;
        }
        case 2:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r10, [0x000000000852D399]
                r14 = globals::base + 0xAC81;           //lea r14, [0xFFFFFFFFFD1F5F1D]
                rax = 0xE03443781C6DB26D;               //mov rax, 0xE03443781C6DB26D
                r8 *= rax;              //imul r8, rax
                rax = 0x26676A6627BAC50C;               //mov rax, 0x26676A6627BAC50C
                r8 -= rax;              //sub r8, rax
                rax = 0x541ECC7788F37ADE;               //mov rax, 0x541ECC7788F37ADE
                r8 += rax;              //add r8, rax
                r8 += r14;              //add r8, r14
                rax = globals::base + 0x142;            //lea rax, [0xFFFFFFFFFD1EAFA0]
                rax = ~rax;             //not rax
                rcx = rbx;              //mov rcx, rbx
                rcx = ~rcx;             //not rcx
                rcx -= rbx;             //sub rcx, rbx
                rcx += rax;             //add rcx, rax
                r8 += rcx;              //add r8, rcx
                rax = r8;               //mov rax, r8
                rax >>= 0x15;           //shr rax, 0x15
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x2A;           //shr rax, 0x2A
                r8 ^= rax;              //xor r8, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFD1EADFF]
                r8 -= rax;              //sub r8, rax
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                r8 *= mem.Read<uintptr_t>(rax + 0x9);           //imul r8, [rax+0x09]
                return r8;
        }
        case 3:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r10, [0x000000000852CEC0]
                r8 ^= rbx;              //xor r8, rbx
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                r8 *= mem.Read<uintptr_t>(rcx + 0x9);           //imul r8, [rcx+0x09]
                rax = 0x6C5618A3BE4C414;                //mov rax, 0x6C5618A3BE4C414
                r8 -= rax;              //sub r8, rax
                rax = 0xE98709096AD185CC;               //mov rax, 0xE98709096AD185CC
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rcx = globals::base + 0x5ED318FB;               //lea rcx, [0x000000005BF1C5BC]
                rax >>= 0xB;            //shr rax, 0x0B
                rcx = ~rcx;             //not rcx
                r8 ^= rax;              //xor r8, rax
                rcx *= rbx;             //imul rcx, rbx
                rax = r8;               //mov rax, r8
                rax >>= 0x16;           //shr rax, 0x16
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x2C;           //shr rax, 0x2C
                rcx ^= rax;             //xor rcx, rax
                r8 ^= rcx;              //xor r8, rcx
                rax = 0x22A1571E2E749CB;                //mov rax, 0x22A1571E2E749CB
                r8 *= rax;              //imul r8, rax
                rcx = globals::base + 0xF26D;           //lea rcx, [0xFFFFFFFFFD1F9E26]
                rax = rbx;              //mov rax, rbx
                rax *= rcx;             //imul rax, rcx
                r8 += rax;              //add r8, rax
                return r8;
        }
        case 4:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r10, [0x000000000852CA42]
                rax = 0x54EE9012A77B3C0E;               //mov rax, 0x54EE9012A77B3C0E
                r8 ^= rax;              //xor r8, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFD1EA4DB]
                rax += 0x432D;          //add rax, 0x432D
                rax += rbx;             //add rax, rbx
                r8 += rax;              //add r8, rax
                rax = 0xBE6A84FFF3304C3D;               //mov rax, 0xBE6A84FFF3304C3D
                r8 *= rax;              //imul r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x12;           //shr rax, 0x12
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x24;           //shr rax, 0x24
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x7;            //shr rax, 0x07
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0xE;            //shr rax, 0x0E
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x1C;           //shr rax, 0x1C
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x38;           //shr rax, 0x38
                r8 ^= rax;              //xor r8, rax
                rcx = globals::base + 0x72D0A311;               //lea rcx, [0x000000006FEF4C1C]
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                r8 *= mem.Read<uintptr_t>(rax + 0x9);           //imul r8, [rax+0x09]
                rax = rbx;              //mov rax, rbx
                rax *= rcx;             //imul rax, rcx
                r8 -= rax;              //sub r8, rax
                rax = 0x598660DAA37ACC99;               //mov rax, 0x598660DAA37ACC99
                r8 ^= rax;              //xor r8, rax
                return r8;
        }
        case 5:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r10, [0x000000000852C593]
                rcx = 0xC088FB236BE68165;               //mov rcx, 0xC088FB236BE68165
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rax = mem.Read<uintptr_t>(rax + 0x9);           //mov rax, [rax+0x09]
                rax *= rcx;             //imul rax, rcx
                r8 *= rax;              //imul r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x5;            //shr rax, 0x05
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0xA;            //shr rax, 0x0A
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x14;           //shr rax, 0x14
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x28;           //shr rax, 0x28
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0xB;            //shr rax, 0x0B
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x16;           //shr rax, 0x16
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x2C;           //shr rax, 0x2C
                r8 ^= rax;              //xor r8, rax
                rax = 0xF87FD44152069748;               //mov rax, 0xF87FD44152069748
                r8 ^= rax;              //xor r8, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFD1EA170]
                rax += 0x1079;          //add rax, 0x1079
                rax += rbx;             //add rax, rbx
                r8 ^= rax;              //xor r8, rax
                rcx = globals::base;            //lea rcx, [0xFFFFFFFFFD1EA360]
                rax = rbx;              //mov rax, rbx
                rax = ~rax;             //not rax
                rax -= rcx;             //sub rax, rcx
                rax += 0xFFFFFFFF968271AB;              //add rax, 0xFFFFFFFF968271AB
                r8 += rax;              //add r8, rax
                return r8;
        }
        case 6:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r10, [0x000000000852C115]
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                r8 *= mem.Read<uintptr_t>(rax + 0x9);           //imul r8, [rax+0x09]
                rcx = globals::base + 0x1EE2;           //lea rcx, [0xFFFFFFFFFD1EBEDB]
                rax = rbx;              //mov rax, rbx
                rax ^= rcx;             //xor rax, rcx
                rcx = 0x30DABF93D6E4FB5;                //mov rcx, 0x30DABF93D6E4FB5
                r8 ^= rcx;              //xor r8, rcx
                r8 -= rax;              //sub r8, rax
                rax = 0xDB8B0AAFA542904;                //mov rax, 0xDB8B0AAFA542904
                r8 -= rbx;              //sub r8, rbx
                r8 -= rax;              //sub r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x22;           //shr rax, 0x22
                r8 ^= rax;              //xor r8, rax
                rax = 0xDF170407BBE28DB5;               //mov rax, 0xDF170407BBE28DB5
                r8 *= rax;              //imul r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x8;            //shr rax, 0x08
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x10;           //shr rax, 0x10
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x20;           //shr rax, 0x20
                r8 ^= rax;              //xor r8, rax
                return r8;
        }
        case 7:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);            //mov r9, [0x000000000852BCDA]
                r14 = globals::base + 0xC177;           //lea r14, [0xFFFFFFFFFD1F5D54]
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r9;              //xor rax, r9
                rax = ~rax;             //not rax
                r8 *= mem.Read<uintptr_t>(rax + 0x9);           //imul r8, [rax+0x09]
                rax = 0x378CE09B287B2D41;               //mov rax, 0x378CE09B287B2D41
                r8 ^= rax;              //xor r8, rax
                rax = 0x1C4A7DE2E2F8F68F;               //mov rax, 0x1C4A7DE2E2F8F68F
                r8 += rax;              //add r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x23;           //shr rax, 0x23
                rax ^= r8;              //xor rax, r8
                r8 = rbx + 0x1;                 //lea r8, [rbx+0x01]
                rax += rbx;             //add rax, rbx
                r8 *= r14;              //imul r8, r14
                r8 += rax;              //add r8, rax
                rax = 0xEBEA9B8B5714671D;               //mov rax, 0xEBEA9B8B5714671D
                r8 *= rax;              //imul r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0xE;            //shr rax, 0x0E
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x1C;           //shr rax, 0x1C
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x38;           //shr rax, 0x38
                r8 ^= rax;              //xor r8, rax
                return r8;
        }
        case 8:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r10, [0x000000000852B7A7]
                rax = globals::base;            //lea rax, [0xFFFFFFFFFD1E94B8]
                r8 ^= rax;              //xor r8, rax
                rax = 0x3169FBDB3B875224;               //mov rax, 0x3169FBDB3B875224
                r8 += rax;              //add r8, rax
                rcx = globals::base + 0x88B9;           //lea rcx, [0xFFFFFFFFFD1F1F3B]
                rax = rcx;              //mov rax, rcx
                rax = ~rax;             //not rax
                rax *= rbx;             //imul rax, rbx
                r8 ^= rax;              //xor r8, rax
                r8 ^= rbx;              //xor r8, rbx
                rax = globals::base + 0x553;            //lea rax, [0xFFFFFFFFFD1E985F]
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x13;           //shr rax, 0x13
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x26;           //shr rax, 0x26
                r8 ^= rax;              //xor r8, rax
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rax = 0x49665D7F2AFA3F6B;               //mov rax, 0x49665D7F2AFA3F6B
                r8 *= rax;              //imul r8, rax
                rcx ^= r10;             //xor rcx, r10
                rax = globals::base + 0x11D125F7;               //lea rax, [0x000000000EEFB9EC]
                rax = ~rax;             //not rax
                rcx = ~rcx;             //not rcx
                rax *= rbx;             //imul rax, rbx
                r8 += rax;              //add r8, rax
                r8 *= mem.Read<uintptr_t>(rcx + 0x9);           //imul r8, [rcx+0x09]
                return r8;
        }
        case 9:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);            //mov r9, [0x000000000852B361]
                r11 = globals::base + 0x7C81;           //lea r11, [0xFFFFFFFFFD1F0EE5]
                rax = rbx;              //mov rax, rbx
                rax *= r11;             //imul rax, r11
                r8 -= rax;              //sub r8, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFD1E8F8B]
                r8 -= rax;              //sub r8, rax
                rax = rbx;              //mov rax, rbx
                rax -= globals::base;           //sub rax, [rbp-0x80] -- didn't find trace -> use base
                rax += 0xFFFFFFFFFFFF4D38;              //add rax, 0xFFFFFFFFFFFF4D38
                r8 += rax;              //add r8, rax
                rax = 0xB294869EA09D48AA;               //mov rax, 0xB294869EA09D48AA
                r8 ^= rax;              //xor r8, rax
                rax = 0xDA6A9700AB4D27FD;               //mov rax, 0xDA6A9700AB4D27FD
                r8 *= rax;              //imul r8, rax
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r9;              //xor rax, r9
                rax = ~rax;             //not rax
                r8 *= mem.Read<uintptr_t>(rax + 0x9);           //imul r8, [rax+0x09]
                rax = 0x38632CDC13FD78A5;               //mov rax, 0x38632CDC13FD78A5
                r8 += rax;              //add r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x1D;           //shr rax, 0x1D
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x3A;           //shr rax, 0x3A
                r8 ^= rax;              //xor r8, rax
                return r8;
        }
        case 10:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r10, [0x000000000852AE48]
                r8 += rbx;              //add r8, rbx
                rax = 0x36164EFD786890C1;               //mov rax, 0x36164EFD786890C1
                r8 *= rax;              //imul r8, rax
                rax = 0x6F993F33D7A49418;               //mov rax, 0x6F993F33D7A49418
                r8 += rax;              //add r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x8;            //shr rax, 0x08
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x10;           //shr rax, 0x10
                r8 ^= rax;              //xor r8, rax
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rax = r8;               //mov rax, r8
                rcx ^= r10;             //xor rcx, r10
                rax >>= 0x20;           //shr rax, 0x20
                r8 ^= rax;              //xor r8, rax
                rcx = ~rcx;             //not rcx
                r8 *= mem.Read<uintptr_t>(rcx + 0x9);           //imul r8, [rcx+0x09]
                rax = 0xE88B55E25B8B057C;               //mov rax, 0xE88B55E25B8B057C
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x1A;           //shr rax, 0x1A
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x34;           //shr rax, 0x34
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x4;            //shr rax, 0x04
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x8;            //shr rax, 0x08
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x10;           //shr rax, 0x10
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x20;           //shr rax, 0x20
                r8 ^= rax;              //xor r8, rax
                return r8;
        }
        case 11:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r10, [0x000000000852AA1E]
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                r8 *= mem.Read<uintptr_t>(rax + 0x9);           //imul r8, [rax+0x09]
                rax = rbx;              //mov rax, rbx
                uintptr_t RSP_0xFFFFFFFFFFFFFFD8;
                RSP_0xFFFFFFFFFFFFFFD8 = globals::base + 0xA1FD;                //lea rax, [0xFFFFFFFFFD1F2B2A] : RBP+0xFFFFFFFFFFFFFFD8
                rax *= RSP_0xFFFFFFFFFFFFFFD8;          //imul rax, [rbp-0x28]
                r8 += rax;              //add r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x26;           //shr rax, 0x26
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0xA;            //shr rax, 0x0A
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x14;           //shr rax, 0x14
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x28;           //shr rax, 0x28
                r8 ^= rax;              //xor r8, rax
                rax = 0xC6A8E21F37CF3675;               //mov rax, 0xC6A8E21F37CF3675
                r8 *= rax;              //imul r8, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFD1E8423]
                rax += rbx;             //add rax, rbx
                r8 -= rax;              //sub r8, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFD1E854F]
                r8 ^= rax;              //xor r8, rax
                return r8;
        }
        case 12:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r10, [0x000000000852A4EC]
                rax = 0x5D2901AC55739352;               //mov rax, 0x5D2901AC55739352
                r8 -= rax;              //sub r8, rax
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                r8 *= mem.Read<uintptr_t>(rax + 0x9);           //imul r8, [rax+0x09]
                rax = globals::base;            //lea rax, [0xFFFFFFFFFD1E7F4E]
                r8 += rax;              //add r8, rax
                rax = 0x156D71AB28FBFAFF;               //mov rax, 0x156D71AB28FBFAFF
                r8 *= rax;              //imul r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x27;           //shr rax, 0x27
                r8 ^= rax;              //xor r8, rax
                r8 -= rbx;              //sub r8, rbx
                rax = r8;               //mov rax, r8
                rax >>= 0x17;           //shr rax, 0x17
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x2E;           //shr rax, 0x2E
                r8 ^= rax;              //xor r8, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFD1E7FCF]
                r8 ^= rax;              //xor r8, rax
                return r8;
        }
        case 13:
        {
                r11 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r11, [0x0000000008529FA3]
                rax = r8;               //mov rax, r8
                rax >>= 0x1F;           //shr rax, 0x1F
                r8 ^= rax;              //xor r8, rax
                rcx = r8;               //mov rcx, r8
                rax = globals::base;            //lea rax, [0xFFFFFFFFFD1E7AD0]
                rcx >>= 0x3E;           //shr rcx, 0x3E
                rcx ^= r8;              //xor rcx, r8
                rdx = 0;                //and rdx, 0xFFFFFFFFC0000000
                rdx = _rotl64(rdx, 0x10);               //rol rdx, 0x10
                r8 = rbx;               //mov r8, rbx
                r8 = ~r8;               //not r8
                rdx ^= r11;             //xor rdx, r11
                r8 += rcx;              //add r8, rcx
                rdx = ~rdx;             //not rdx
                r8 -= rax;              //sub r8, rax
                r8 -= 0x6929AFAC;               //sub r8, 0x6929AFAC
                r8 *= mem.Read<uintptr_t>(rdx + 0x9);           //imul r8, [rdx+0x09]
                rax = r8;               //mov rax, r8
                rax >>= 0x18;           //shr rax, 0x18
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x30;           //shr rax, 0x30
                r8 ^= rax;              //xor r8, rax
                rax = 0x69651B1AF033619B;               //mov rax, 0x69651B1AF033619B
                r8 += rbx;              //add r8, rbx
                r8 *= rax;              //imul r8, rax
                rax = 0x29BBD1B30DFD9417;               //mov rax, 0x29BBD1B30DFD9417
                r8 *= rax;              //imul r8, rax
                rax = 0xA7B8F15C4FABBB6C;               //mov rax, 0xA7B8F15C4FABBB6C
                r8 ^= rax;              //xor r8, rax
                return r8;
        }
        case 14:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);            //mov r9, [0x0000000008529B2D]
                r8 += rbx;              //add r8, rbx
                rax = globals::base + 0x8D0;            //lea rax, [0xFFFFFFFFFD1E8173]
                rax -= rbx;             //sub rax, rbx
                r8 += rax;              //add r8, rax
                rax = 0xBC0AAA7E98B1663A;               //mov rax, 0xBC0AAA7E98B1663A
                r8 ^= rax;              //xor r8, rax
                rax = 0x54D1F9305B205B45;               //mov rax, 0x54D1F9305B205B45
                r8 *= rax;              //imul r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0xA;            //shr rax, 0x0A
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x14;           //shr rax, 0x14
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x28;           //shr rax, 0x28
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x12;           //shr rax, 0x12
                r8 ^= rax;              //xor r8, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x24;           //shr rax, 0x24
                r8 ^= rax;              //xor r8, rax
                rax = 0xFFFFFFFFDE23E20A;               //mov rax, 0xFFFFFFFFDE23E20A
                rax -= rbx;             //sub rax, rbx
                rax -= globals::base;           //sub rax, [rbp-0x80] -- didn't find trace -> use base
                r8 += rax;              //add r8, rax
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r9;              //xor rax, r9
                rax = ~rax;             //not rax
                r8 *= mem.Read<uintptr_t>(rax + 0x9);           //imul r8, [rax+0x09]
                return r8;
        }
        case 15:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3420EA);           //mov r10, [0x00000000085296AB]
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rax = mem.Read<uintptr_t>(rax + 0x9);           //mov rax, [rax+0x09]
                uintptr_t RSP_0xFFFFFFFFFFFFFFC8;
                RSP_0xFFFFFFFFFFFFFFC8 = 0x3A27415DA31CA989;            //mov rax, 0x3A27415DA31CA989 : RBP+0xFFFFFFFFFFFFFFC8
                rax *= RSP_0xFFFFFFFFFFFFFFC8;          //imul rax, [rbp-0x38]
                r8 *= rax;              //imul r8, rax
                rax = 0x6F6A3BE0CADE4A54;               //mov rax, 0x6F6A3BE0CADE4A54
                r8 -= rax;              //sub r8, rax
                r8 -= rbx;              //sub r8, rbx
                rax = r8;               //mov rax, r8
                rax >>= 0x13;           //shr rax, 0x13
                rcx = rbx;              //mov rcx, rbx
                r8 ^= rax;              //xor r8, rax
                rcx = ~rcx;             //not rcx
                rax = globals::base + 0x76BB;           //lea rax, [0xFFFFFFFFFD1EEB25]
                rax = ~rax;             //not rax
                rcx *= rax;             //imul rcx, rax
                rax = r8;               //mov rax, r8
                rax >>= 0x26;           //shr rax, 0x26
                r8 ^= rax;              //xor r8, rax
                r8 += rcx;              //add r8, rcx
                rax = r8;               //mov rax, r8
                rax >>= 0x28;           //shr rax, 0x28
                r8 ^= rax;              //xor r8, rax
                rax = 0x3224CE0A9BEB6A6E;               //mov rax, 0x3224CE0A9BEB6A6E
                r8 -= rax;              //sub r8, rax
                return r8;
        }
        }
}
uintptr_t GetCmdTextArray()
{
        const uint64_t mb = globals::base;
        uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;
        rcx = mem.Read<uintptr_t>(globals::base + 0x111BF680);
        if(!rcx)
                return rcx;
        r11 = globals::vaPeb;           //mov r11, gs:[rdx]
        rdx = r11;              //mov rdx, r11
        //failed to translate: mov [rsp+0xE0], r12
        rdx = _rotl64(rdx, 0x22);               //rol rdx, 0x22
        rdx &= 0xF;
        switch(rdx) {
        case 0:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB342169);           //mov r10, [0x0000000004F511EB]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0F07B]
                r15 = globals::base + 0x5E33;           //lea r15, [0xFFFFFFFFF9C14EA2]
                rax = rcx;              //mov rax, rcx
                rax >>= 0x1B;           //shr rax, 0x1B
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x36;           //shr rax, 0x36
                rcx ^= rax;             //xor rcx, rax
                rax = 0xB5E3A5C14A756615;               //mov rax, 0xB5E3A5C14A756615
                rcx ^= rax;             //xor rcx, rax
                rcx *= mem.Read<uintptr_t>(r10 + 0x15);                 //imul rcx, [r10+0x15]
                rax = r11;              //mov rax, r11
                rax *= r15;             //imul rax, r15
                rcx += rax;             //add rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x17;           //shr rax, 0x17
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x2E;           //shr rax, 0x2E
                rcx ^= rax;             //xor rcx, rax
                rcx += rbx;             //add rcx, rbx
                rax = 0x451CDD50ED47051D;               //mov rax, 0x451CDD50ED47051D
                rcx *= rax;             //imul rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x27;           //shr rax, 0x27
                rcx ^= rax;             //xor rcx, rax
                return rcx;
        }
        case 1:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB342169);            //mov r9, [0x0000000004F50CF8]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0EB88]
                rcx ^= rbx;             //xor rcx, rbx
                rcx *= mem.Read<uintptr_t>(r9 + 0x15);          //imul rcx, [r9+0x15]
                rax = 0x3F5FF8759C0450AD;               //mov rax, 0x3F5FF8759C0450AD
                rcx *= rax;             //imul rcx, rax
                rax = 0x49224897BA23AD81;               //mov rax, 0x49224897BA23AD81
                rcx *= rax;             //imul rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x26;           //shr rax, 0x26
                rcx ^= rax;             //xor rcx, rax
                rax = 0x9308B88C835A243;                //mov rax, 0x9308B88C835A243
                rcx -= rax;             //sub rcx, rax
                return rcx;
        }
        case 2:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB342169);           //mov r10, [0x0000000004F508D0]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0E760]
                r12 = globals::base + 0xC499;           //lea r12, [0xFFFFFFFFF9C1ABE8]
                rcx ^= r11;             //xor rcx, r11
                rcx ^= r12;             //xor rcx, r12
                rcx += r11;             //add rcx, r11
                rax = 0xDD209D02F3077017;               //mov rax, 0xDD209D02F3077017
                rcx *= rax;             //imul rcx, rax
                rcx *= mem.Read<uintptr_t>(r10 + 0x15);                 //imul rcx, [r10+0x15]
                rax = rcx;              //mov rax, rcx
                rax >>= 0x12;           //shr rax, 0x12
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x24;           //shr rax, 0x24
                rcx ^= rax;             //xor rcx, rax
                rax = 0x7B3DE336F351C129;               //mov rax, 0x7B3DE336F351C129
                rcx -= rax;             //sub rcx, rax
                rcx ^= rbx;             //xor rcx, rbx
                return rcx;
        }
        case 3:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB342169);           //mov r10, [0x0000000004F50531]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0E3B6]
                rax = 0x292A737D3A8A003D;               //mov rax, 0x292A737D3A8A003D
                rcx *= rax;             //imul rcx, rax
                rcx ^= r11;             //xor rcx, r11
                rcx ^= r11;             //xor rcx, r11
                rcx -= rbx;             //sub rcx, rbx
                rax = rcx;              //mov rax, rcx
                rax >>= 0x19;           //shr rax, 0x19
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x32;           //shr rax, 0x32
                rcx ^= rax;             //xor rcx, rax
                rcx *= mem.Read<uintptr_t>(r10 + 0x15);                 //imul rcx, [r10+0x15]
                rdx = r11;              //mov rdx, r11
                rdx = ~rdx;             //not rdx
                rax = globals::base + 0x4F2A;           //lea rax, [0xFFFFFFFFF9C12F20]
                rcx += rax;             //add rcx, rax
                rcx += rdx;             //add rcx, rdx
                rax = 0x1D53DC9394D6C68A;               //mov rax, 0x1D53DC9394D6C68A
                rcx += rax;             //add rcx, rax
                return rcx;
        }
        case 4:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB342169);            //mov r9, [0x0000000004F500FB]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0DF8B]
                rdi = globals::base + 0x46C0CD17;               //lea rdi, [0x000000004081AC96]
                rax = rcx;              //mov rax, rcx
                rax >>= 0x10;           //shr rax, 0x10
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x20;           //shr rax, 0x20
                rcx ^= rax;             //xor rcx, rax
                rcx ^= r11;             //xor rcx, r11
                rcx ^= rdi;             //xor rcx, rdi
                rax = rcx;              //mov rax, rcx
                rax >>= 0x17;           //shr rax, 0x17
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x2E;           //shr rax, 0x2E
                rcx ^= rax;             //xor rcx, rax
                rax = 0x2A27FA74C256E0E7;               //mov rax, 0x2A27FA74C256E0E7
                rcx *= rax;             //imul rcx, rax
                rcx += rbx;             //add rcx, rbx
                rcx *= mem.Read<uintptr_t>(r9 + 0x15);          //imul rcx, [r9+0x15]
                rax = 0xE889A0595E16BFDB;               //mov rax, 0xE889A0595E16BFDB
                rcx *= rax;             //imul rcx, rax
                return rcx;
        }
        case 5:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB342169);            //mov r9, [0x0000000004F4FBE2]
                rdi = globals::base + 0x6CA3;           //lea rdi, [0xFFFFFFFFF9C14715]
                rax = 0x4694415E362AF97D;               //mov rax, 0x4694415E362AF97D
                rcx *= rax;             //imul rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0xE;            //shr rax, 0x0E
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x1C;           //shr rax, 0x1C
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x38;           //shr rax, 0x38
                rcx ^= rax;             //xor rcx, rax
                rax = 0x2A796B075D8038A1;               //mov rax, 0x2A796B075D8038A1
                rcx ^= rax;             //xor rcx, rax
                rcx += r11;             //add rcx, r11
                rax = 0x3212ABD7EB1A3183;               //mov rax, 0x3212ABD7EB1A3183
                rcx += rax;             //add rcx, rax
                rcx *= mem.Read<uintptr_t>(r9 + 0x15);          //imul rcx, [r9+0x15]
                rax = r11;              //mov rax, r11
                rax *= rdi;             //imul rax, rdi
                rcx -= rax;             //sub rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x18;           //shr rax, 0x18
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x30;           //shr rax, 0x30
                rcx ^= rax;             //xor rcx, rax
                return rcx;
        }
        case 6:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB342169);           //mov r10, [0x0000000004F4F713]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0D5A3]
                r12 = globals::base + 0x2407;           //lea r12, [0xFFFFFFFFF9C0F99E]
                r13 = globals::base + 0xD54B;           //lea r13, [0xFFFFFFFFF9C1AAD7]
                rax = rcx;              //mov rax, rcx
                rax >>= 0x8;            //shr rax, 0x08
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x10;           //shr rax, 0x10
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x20;           //shr rax, 0x20
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0xF;            //shr rax, 0x0F
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x1E;           //shr rax, 0x1E
                rcx ^= rax;             //xor rcx, rax
                rdx = rcx;              //mov rdx, rcx
                rdx >>= 0x3C;           //shr rdx, 0x3C
                rax = r12;              //mov rax, r12
                rax = ~rax;             //not rax
                rdx ^= rax;             //xor rdx, rax
                rdx ^= r11;             //xor rdx, r11
                rcx ^= rdx;             //xor rcx, rdx
                rax = rbx + 0x86d9;             //lea rax, [rbx+0x86D9]
                rax += r11;             //add rax, r11
                rcx ^= rax;             //xor rcx, rax
                rax = 0x394D31FBFC54D5C7;               //mov rax, 0x394D31FBFC54D5C7
                rcx *= rax;             //imul rcx, rax
                rax = r13;              //mov rax, r13
                rax = ~rax;             //not rax
                rax *= r11;             //imul rax, r11
                rcx ^= rax;             //xor rcx, rax
                rax = 0xF248AD144683687F;               //mov rax, 0xF248AD144683687F
                rcx *= rax;             //imul rcx, rax
                rcx *= mem.Read<uintptr_t>(r10 + 0x15);                 //imul rcx, [r10+0x15]
                return rcx;
        }
        case 7:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB342169);           //mov r10, [0x0000000004F4F25F]
                r15 = globals::base + 0xF2B7;           //lea r15, [0xFFFFFFFFF9C1C3A6]
                rdi = globals::base + 0x727BCC8E;               //lea rdi, [0x000000006C3C9D71]
                rcx += rdi;             //add rcx, rdi
                rdx = r11;              //mov rdx, r11
                rdx = ~rdx;             //not rdx
                rax = rdx;              //mov rax, rdx
                rax ^= r15;             //xor rax, r15
                rdx -= rax;             //sub rdx, rax
                rcx += rdx;             //add rcx, rdx
                rax = rcx;              //mov rax, rcx
                rax >>= 0x18;           //shr rax, 0x18
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x30;           //shr rax, 0x30
                rcx ^= rax;             //xor rcx, rax
                rax = 0x2B8B78BC1D92212A;               //mov rax, 0x2B8B78BC1D92212A
                rcx -= rax;             //sub rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x17;           //shr rax, 0x17
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x2E;           //shr rax, 0x2E
                rcx ^= rax;             //xor rcx, rax
                rax = 0x49781D9754795626;               //mov rax, 0x49781D9754795626
                rcx ^= rax;             //xor rcx, rax
                rax = 0xE1A998C5EA9145DD;               //mov rax, 0xE1A998C5EA9145DD
                rcx *= rax;             //imul rcx, rax
                rcx *= mem.Read<uintptr_t>(r10 + 0x15);                 //imul rcx, [r10+0x15]
                return rcx;
        }
        case 8:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB342169);            //mov r9, [0x0000000004F4EE40]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0CCD0]
                rcx ^= r11;             //xor rcx, r11
                rax = 0xD0FA4725C1F6A4DB;               //mov rax, 0xD0FA4725C1F6A4DB
                rcx *= rax;             //imul rcx, rax
                rcx += rbx;             //add rcx, rbx
                rcx *= mem.Read<uintptr_t>(r9 + 0x15);          //imul rcx, [r9+0x15]
                rax = 0x2280D092AFB637A3;               //mov rax, 0x2280D092AFB637A3
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x21;           //shr rax, 0x21
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x1D;           //shr rax, 0x1D
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x3A;           //shr rax, 0x3A
                rcx ^= rax;             //xor rcx, rax
                return rcx;
        }
        case 9:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB342169);           //mov r10, [0x0000000004F4EA10]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0C8A0]
                rdi = globals::base + 0xF805;           //lea rdi, [0xFFFFFFFFF9C1C094]
                rax = r11;              //mov rax, r11
                rax *= rdi;             //imul rax, rdi
                rcx -= rax;             //sub rcx, rax
                rcx += r11;             //add rcx, r11
                rax = globals::base + 0x34E2;           //lea rax, [0xFFFFFFFFF9C0FCF3]
                rcx += rax;             //add rcx, rax
                rax = 0xD670AE07CD87C44B;               //mov rax, 0xD670AE07CD87C44B
                rcx *= rax;             //imul rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x11;           //shr rax, 0x11
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x22;           //shr rax, 0x22
                rcx ^= rax;             //xor rcx, rax
                rax = mem.Read<uintptr_t>(r10 + 0x15);          //mov rax, [r10+0x15]
                rdx = 0x7DF246B4B47C04D;                //mov rdx, 0x7DF246B4B47C04D
                rax *= rdx;             //imul rax, rdx
                rcx *= rax;             //imul rcx, rax
                rax = r11;              //mov rax, r11
                rax -= rbx;             //sub rax, rbx
                rax -= 0x3EA4E863;              //sub rax, 0x3EA4E863
                rcx ^= rax;             //xor rcx, rax
                rax = 0x6EAEB149F1BB523E;               //mov rax, 0x6EAEB149F1BB523E
                rcx ^= rax;             //xor rcx, rax
                return rcx;
        }
        case 10:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB342169);           //mov r10, [0x0000000004F4E6C0]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0C550]
                rcx += r11;             //add rcx, r11
                rcx ^= rbx;             //xor rcx, rbx
                rcx -= rbx;             //sub rcx, rbx
                rax = 0xC2C77ADBEA06CC71;               //mov rax, 0xC2C77ADBEA06CC71
                rcx *= rax;             //imul rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x20;           //shr rax, 0x20
                rcx ^= rax;             //xor rcx, rax
                rax = 0x6ABDE99A4C942C1D;               //mov rax, 0x6ABDE99A4C942C1D
                rcx -= rax;             //sub rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0xB;            //shr rax, 0x0B
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x16;           //shr rax, 0x16
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x2C;           //shr rax, 0x2C
                rcx ^= rax;             //xor rcx, rax
                rcx *= mem.Read<uintptr_t>(r10 + 0x15);                 //imul rcx, [r10+0x15]
                return rcx;
        }
        case 11:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB342169);            //mov r9, [0x0000000004F4E2D4]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0C164]
                rax = rcx;              //mov rax, rcx
                rax >>= 0xA;            //shr rax, 0x0A
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x14;           //shr rax, 0x14
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x28;           //shr rax, 0x28
                rcx ^= rax;             //xor rcx, rax
                rcx -= r11;             //sub rcx, r11
                rax = rbx + 0x723d2a5a;                 //lea rax, [rbx+0x723D2A5A]
                rax += r11;             //add rax, r11
                rcx ^= rax;             //xor rcx, rax
                rax = 0x405646879A90A4B1;               //mov rax, 0x405646879A90A4B1
                rcx *= rax;             //imul rcx, rax
                rax = 0x7E1BE77430218FC2;               //mov rax, 0x7E1BE77430218FC2
                rcx += rax;             //add rcx, rax
                rax = 0xF28B8C5F9F41196A;               //mov rax, 0xF28B8C5F9F41196A
                rcx ^= rax;             //xor rcx, rax
                rcx *= mem.Read<uintptr_t>(r9 + 0x15);          //imul rcx, [r9+0x15]
                rax = rcx;              //mov rax, rcx
                rax >>= 0xF;            //shr rax, 0x0F
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x1E;           //shr rax, 0x1E
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x3C;           //shr rax, 0x3C
                rcx ^= rax;             //xor rcx, rax
                return rcx;
        }
        case 12:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB342169);           //mov r10, [0x0000000004F4DE1E]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0BCAE]
                r15 = globals::base + 0x339332F9;               //lea r15, [0x000000002D53EF96]
                rax = r11;              //mov rax, r11
                rax *= r15;             //imul rax, r15
                rcx -= rax;             //sub rcx, rax
                rax = 0x3038E6AB6FEAABA9;               //mov rax, 0x3038E6AB6FEAABA9
                rcx *= rax;             //imul rcx, rax
                rcx ^= r11;             //xor rcx, r11
                rcx += r11;             //add rcx, r11
                rcx *= mem.Read<uintptr_t>(r10 + 0x15);                 //imul rcx, [r10+0x15]
                rcx -= rbx;             //sub rcx, rbx
                rax = rcx;              //mov rax, rcx
                rax >>= 0x25;           //shr rax, 0x25
                rcx ^= rax;             //xor rcx, rax
                rcx += r11;             //add rcx, r11
                return rcx;
        }
        case 13:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB342169);           //mov r10, [0x0000000004F4DA7C]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0B90C]
                rax = globals::base + 0x45FE7DB0;               //lea rax, [0x000000003FBF3586]
                rax -= r11;             //sub rax, r11
                rcx ^= rax;             //xor rcx, rax
                rax = rbx + 0x44c85679;                 //lea rax, [rbx+0x44C85679]
                rax += r11;             //add rax, r11
                rcx += rax;             //add rcx, rax
                rcx *= mem.Read<uintptr_t>(r10 + 0x15);                 //imul rcx, [r10+0x15]
                rax = rcx;              //mov rax, rcx
                rax >>= 0x1B;           //shr rax, 0x1B
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x36;           //shr rax, 0x36
                rcx ^= rax;             //xor rcx, rax
                rax = 0xDC51C6CA5ECBE269;               //mov rax, 0xDC51C6CA5ECBE269
                rcx *= rax;             //imul rcx, rax
                rax = rbx * 0xFFFFFFFFFFFFFFFE;                 //imul rax, rbx, 0xFFFFFFFFFFFFFFFE
                rcx += rax;             //add rcx, rax
                rax = 0xA8C2E47322E167D3;               //mov rax, 0xA8C2E47322E167D3
                rcx -= r11;             //sub rcx, r11
                rcx -= 0x6842;          //sub rcx, 0x6842
                rcx ^= rax;             //xor rcx, rax
                return rcx;
        }
        case 14:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB342169);            //mov r9, [0x0000000004F4D676]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0B506]
                rcx ^= rbx;             //xor rcx, rbx
                rax = 0xC2092D064BD7621B;               //mov rax, 0xC2092D064BD7621B
                rcx *= rax;             //imul rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0xA;            //shr rax, 0x0A
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x14;           //shr rax, 0x14
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x28;           //shr rax, 0x28
                rcx ^= rax;             //xor rcx, rax
                rax = globals::base + 0xB084;           //lea rax, [0xFFFFFFFFF9C16233]
                rcx += r11;             //add rcx, r11
                rcx += rax;             //add rcx, rax
                rax = r11;              //mov rax, r11
                rax -= rbx;             //sub rax, rbx
                rax -= 0xB9AC;          //sub rax, 0xB9AC
                rcx ^= rax;             //xor rcx, rax
                rax = 0x9883AEFFA28B11D0;               //mov rax, 0x9883AEFFA28B11D0
                rcx ^= rax;             //xor rcx, rax
                rcx *= mem.Read<uintptr_t>(r9 + 0x15);          //imul rcx, [r9+0x15]
                rax = rcx;              //mov rax, rcx
                rax >>= 0x1D;           //shr rax, 0x1D
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x3A;           //shr rax, 0x3A
                rcx ^= rax;             //xor rcx, rax
                return rcx;
        }
        case 15:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB342169);            //mov r9, [0x0000000004F4D1AE]
                rbx = globals::base;            //lea rbx, [0xFFFFFFFFF9C0B03E]
                rcx ^= rbx;             //xor rcx, rbx
                rax = 0x62EE0D555FE38340;               //mov rax, 0x62EE0D555FE38340
                rcx -= rax;             //sub rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x24;           //shr rax, 0x24
                rcx ^= rax;             //xor rcx, rax
                rcx *= mem.Read<uintptr_t>(r9 + 0x15);          //imul rcx, [r9+0x15]
                rax = 0x8821DA37E07E4065;               //mov rax, 0x8821DA37E07E4065
                rcx *= rax;             //imul rcx, rax
                rcx += rbx;             //add rcx, rbx
                rax = rcx;              //mov rax, rcx
                rax >>= 0x14;           //shr rax, 0x14
                rcx ^= rax;             //xor rcx, rax
                rax = rcx;              //mov rax, rcx
                rax >>= 0x28;           //shr rax, 0x28
                rcx ^= rax;             //xor rcx, rax
                rax = 0x6535948A0956C067;               //mov rax, 0x6535948A0956C067
                rcx *= rax;             //imul rcx, rax
                return rcx;
        }
        }
}
uintptr_t decrypt_client_active()
{
        const uint64_t mb = globals::base;
        uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;
        rax = mem.Read<uintptr_t>(rdx + 0xb539450);
        if(!rax)
                return rax;
        rbx = globals::vaPeb;           //mov rbx, gs:[rcx]
        //failed to translate: mov [rsp+0x68], rdi
        rcx = rbx;              //mov rcx, rbx
        //failed to translate: mov [rsp+0x60], r12
        rcx = _rotr64(rcx, 0x1D);               //ror rcx, 0x1D
        //failed to translate: mov [rsp+0x58], r13
        rcx &= 0xF;
        switch(rcx) {
        case 0:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x0000000009308A66]
                r11 = globals::base;            //lea r11, [0xFFFFFFFFFDFC6951]
                rcx = 0x75A35BF5EC482D53;               //mov rcx, 0x75A35BF5EC482D53
                rax -= rcx;             //sub rax, rcx
                rcx = r11 + 0x39674f96;                 //lea rcx, [r11+0x39674F96]
                rcx += rbx;             //add rcx, rbx
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x7;            //shr rcx, 0x07
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0xE;            //shr rcx, 0x0E
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x1C;           //shr rcx, 0x1C
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x38;           //shr rcx, 0x38
                rax ^= rcx;             //xor rax, rcx
                rcx = 0x7ED1321242287D37;               //mov rcx, 0x7ED1321242287D37
                rax *= rcx;             //imul rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x2;            //shr rcx, 0x02
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x4;            //shr rcx, 0x04
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x8;            //shr rcx, 0x08
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x10;           //shr rcx, 0x10
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x20;           //shr rcx, 0x20
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x22;           //shr rcx, 0x22
                rax ^= rcx;             //xor rax, rcx
                rax += r11;             //add rax, r11
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                return rax;
        }
        case 1:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x000000000930855B]
                r11 = globals::base;            //lea r11, [0xFFFFFFFFFDFC6446]
                r12 = globals::base + 0x2B0E;           //lea r12, [0xFFFFFFFFFDFC8F3D]
                r13 = globals::base + 0x2982AAEB;               //lea r13, [0x00000000277F0F0E]
                rdx = rbx;              //mov rdx, rbx
                rdx = ~rdx;             //not rdx
                rdx ^= r12;             //xor rdx, r12
                rcx = r11;              //mov rcx, r11
                rcx -= rdx;             //sub rcx, rdx
                rax += rcx;             //add rax, rcx
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                rcx = rbx;              //mov rcx, rbx
                rcx ^= r13;             //xor rcx, r13
                rax -= rcx;             //sub rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x5;            //shr rcx, 0x05
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0xA;            //shr rcx, 0x0A
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x14;           //shr rcx, 0x14
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x28;           //shr rcx, 0x28
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x10;           //shr rcx, 0x10
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x20;           //shr rcx, 0x20
                rax ^= rcx;             //xor rax, rcx
                rcx = 0x395F229C1F64329;                //mov rcx, 0x395F229C1F64329
                rax *= rcx;             //imul rax, rcx
                rcx = 0x90CE9B89EFABB41;                //mov rcx, 0x90CE9B89EFABB41
                rax -= rcx;             //sub rax, rcx
                return rax;
        }
        case 2:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x0000000009307FE3]
                r14 = globals::base + 0x30F0A65E;               //lea r14, [0x000000002EED0520]
                r15 = globals::base + 0x8EAC;           //lea r15, [0xFFFFFFFFFDFCED63]
                rdx = rbx;              //mov rdx, rbx
                rdx = ~rdx;             //not rdx
                rax += r15;             //add rax, r15
                rcx = rbx;              //mov rcx, rbx
                rcx *= r14;             //imul rcx, r14
                rdx -= rcx;             //sub rdx, rcx
                rax += rdx;             //add rax, rdx
                rcx = 0xF7070315E5585D71;               //mov rcx, 0xF7070315E5585D71
                rax ^= rcx;             //xor rax, rcx
                rcx = 0x5C10EC95D52AE35C;               //mov rcx, 0x5C10EC95D52AE35C
                rax += rcx;             //add rax, rcx
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x9;            //shr rcx, 0x09
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x12;           //shr rcx, 0x12
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x24;           //shr rcx, 0x24
                rax ^= rcx;             //xor rax, rcx
                rcx = 0xEAF8DD4E7DAEE839;               //mov rcx, 0xEAF8DD4E7DAEE839
                rax *= rcx;             //imul rax, rcx
                rax -= rbx;             //sub rax, rbx
                return rax;
        }
        case 3:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB34210E);            //mov r9, [0x0000000009307B4F]
                r11 = globals::base;            //lea r11, [0xFFFFFFFFFDFC5A3A]
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x20;           //shr rcx, 0x20
                rax ^= rcx;             //xor rax, rcx
                rcx = 0x5EF0345657B7395;                //mov rcx, 0x5EF0345657B7395
                rax *= rcx;             //imul rax, rcx
                rcx = 0xACDBE6CC0EC7F1D6;               //mov rcx, 0xACDBE6CC0EC7F1D6
                rax ^= rcx;             //xor rax, rcx
                rax += rbx;             //add rax, rbx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x28;           //shr rcx, 0x28
                rax ^= rcx;             //xor rax, rcx
                rax ^= r11;             //xor rax, r11
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r9;              //xor rcx, r9
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                rax += r11;             //add rax, r11
                return rax;
        }
        case 4:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x00000000093076E3]
                r15 = globals::base + 0xA062;           //lea r15, [0xFFFFFFFFFDFCF624]
                r12 = globals::base + 0x29D008DE;               //lea r12, [0x0000000027CC5E95]
                rcx = 0x61F81B41A154355F;               //mov rcx, 0x61F81B41A154355F
                rax += rcx;             //add rax, rcx
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                rcx = 0x60C7116DFD4132B;                //mov rcx, 0x60C7116DFD4132B
                rax *= rcx;             //imul rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x3;            //shr rcx, 0x03
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x6;            //shr rcx, 0x06
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0xC;            //shr rcx, 0x0C
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x18;           //shr rcx, 0x18
                rax ^= rcx;             //xor rax, rcx
                rdx = rax;              //mov rdx, rax
                rdx >>= 0x30;           //shr rdx, 0x30
                rdx ^= rax;             //xor rdx, rax
                rax = rbx;              //mov rax, rbx
                rax *= r12;             //imul rax, r12
                rax += rdx;             //add rax, rdx
                rcx = rbx;              //mov rcx, rbx
                rcx *= r15;             //imul rcx, r15
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x6;            //shr rcx, 0x06
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0xC;            //shr rcx, 0x0C
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x18;           //shr rcx, 0x18
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x30;           //shr rcx, 0x30
                rax ^= rcx;             //xor rax, rcx
                rcx = 0x7383B429035656CC;               //mov rcx, 0x7383B429035656CC
                rax -= rcx;             //sub rax, rcx
                return rax;
        }
        case 5:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x00000000093071AD]
                r11 = globals::base;            //lea r11, [0xFFFFFFFFFDFC5098]
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x1C;           //shr rcx, 0x1C
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x38;           //shr rcx, 0x38
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0xD;            //shr rcx, 0x0D
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x1A;           //shr rcx, 0x1A
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x34;           //shr rcx, 0x34
                rax ^= rcx;             //xor rax, rcx
                rcx = 0xFA0DDD2C604B9D1F;               //mov rcx, 0xFA0DDD2C604B9D1F
                rax *= rcx;             //imul rax, rcx
                rcx = globals::base + 0x46B0;           //lea rcx, [0xFFFFFFFFFDFC955A]
                rax -= rcx;             //sub rax, rcx
                rax += rbx;             //add rax, rbx
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                rcx = 0x64F0F35E29D4C7B9;               //mov rcx, 0x64F0F35E29D4C7B9
                rax *= rcx;             //imul rax, rcx
                rax -= r11;             //sub rax, r11
                rax += 0xFFFFFFFFFFFF24CA;              //add rax, 0xFFFFFFFFFFFF24CA
                rax += rbx;             //add rax, rbx
                rcx = 0x249EDB181C0475B9;               //mov rcx, 0x249EDB181C0475B9
                rax ^= rcx;             //xor rax, rcx
                return rax;
        }
        case 6:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x0000000009306D81]
                r11 = globals::base;            //lea r11, [0xFFFFFFFFFDFC4C61]
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x10;           //shr rcx, 0x10
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x20;           //shr rcx, 0x20
                rax ^= rcx;             //xor rax, rcx
                rax += rbx;             //add rax, rbx
                rdx = 0;                //and rdx, 0xFFFFFFFFC0000000
                rdx = _rotl64(rdx, 0x10);               //rol rdx, 0x10
                rdx ^= r10;             //xor rdx, r10
                rcx = rbx;              //mov rcx, rbx
                rcx -= r11;             //sub rcx, r11
                r15 = 0xD29D6FF40A4A734D;               //mov r15, 0xD29D6FF40A4A734D
                rcx += r15;             //add rcx, r15
                rdx = ~rdx;             //not rdx
                rax += rcx;             //add rax, rcx
                rax *= mem.Read<uintptr_t>(rdx + 0xf);          //imul rax, [rdx+0x0F]
                rcx = rbx;              //mov rcx, rbx
                rcx -= r11;             //sub rcx, r11
                rcx -= 0x160C0564;              //sub rcx, 0x160C0564
                rax ^= rcx;             //xor rax, rcx
                rcx = rbx;              //mov rcx, rbx
                rcx = ~rcx;             //not rcx
                rcx -= r11;             //sub rcx, r11
                rcx -= 0x473E;          //sub rcx, 0x473E
                rax ^= rcx;             //xor rax, rcx
                rcx = 0xA4D2A49AD11FF335;               //mov rcx, 0xA4D2A49AD11FF335
                rax *= rcx;             //imul rax, rcx
                return rax;
        }
        case 7:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x00000000093068E3]
                r11 = globals::base;            //lea r11, [0xFFFFFFFFFDFC47CE]
                rcx = 0x8A9DA3385FC38B18;               //mov rcx, 0x8A9DA3385FC38B18
                rax ^= rcx;             //xor rax, rcx
                rax ^= rbx;             //xor rax, rbx
                rdx = 0;                //and rdx, 0xFFFFFFFFC0000000
                rdx = _rotl64(rdx, 0x10);               //rol rdx, 0x10
                rdx ^= r10;             //xor rdx, r10
                rdx = ~rdx;             //not rdx
                rax *= mem.Read<uintptr_t>(rdx + 0xf);          //imul rax, [rdx+0x0F]
                rdx = rbx;              //mov rdx, rbx
                rcx = globals::base + 0x49AEB26D;               //lea rcx, [0x0000000047AAF961]
                rdx = ~rdx;             //not rdx
                rcx = ~rcx;             //not rcx
                rdx *= rcx;             //imul rdx, rcx
                rax ^= rdx;             //xor rax, rdx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0xF;            //shr rcx, 0x0F
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x1E;           //shr rcx, 0x1E
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x3C;           //shr rcx, 0x3C
                rax ^= rcx;             //xor rax, rcx
                rcx = 0xF4D742FA3C9800A5;               //mov rcx, 0xF4D742FA3C9800A5
                rax *= rcx;             //imul rax, rcx
                rcx = 0x10F2E1DC08054DCE;               //mov rcx, 0x10F2E1DC08054DCE
                rax ^= r11;             //xor rax, r11
                rax -= rcx;             //sub rax, rcx
                return rax;
        }
        case 8:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x000000000930648D]
                r11 = globals::base;            //lea r11, [0xFFFFFFFFFDFC4378]
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x7;            //shr rcx, 0x07
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0xE;            //shr rcx, 0x0E
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x1C;           //shr rcx, 0x1C
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x38;           //shr rcx, 0x38
                rax ^= rcx;             //xor rax, rcx
                rcx = 0x95279C81D5942D9;                //mov rcx, 0x95279C81D5942D9
                rax *= rcx;             //imul rax, rcx
                rcx = 0x43F7B4F4DCCCEAA1;               //mov rcx, 0x43F7B4F4DCCCEAA1
                rax -= r11;             //sub rax, r11
                rax -= rcx;             //sub rax, rcx
                rax ^= rbx;             //xor rax, rbx
                rax ^= r11;             //xor rax, r11
                rcx = 0x41A42223B53D6ABF;               //mov rcx, 0x41A42223B53D6ABF
                rax *= rcx;             //imul rax, rcx
                return rax;
        }
        case 9:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB34210E);            //mov r9, [0x0000000009306079]
                r11 = globals::base;            //lea r11, [0xFFFFFFFFFDFC3F64]
                rax ^= r11;             //xor rax, r11
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r9;              //xor rcx, r9
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                rax += rbx;             //add rax, rbx
                rax ^= rbx;             //xor rax, rbx
                rax -= r11;             //sub rax, r11
                rcx = 0x4B6230D25E9BA161;               //mov rcx, 0x4B6230D25E9BA161
                rax *= rcx;             //imul rax, rcx
                rax += rbx;             //add rax, rbx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0xE;            //shr rcx, 0x0E
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x1C;           //shr rcx, 0x1C
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x38;           //shr rcx, 0x38
                rax ^= rcx;             //xor rax, rcx
                return rax;
        }
        case 10:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x0000000009305BCA]
                r11 = globals::base;            //lea r11, [0xFFFFFFFFFDFC3AAA]
                r15 = globals::base + 0x2BB81C0C;               //lea r15, [0x0000000029B4569F]
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                rcx = rbx;              //mov rcx, rbx
                rcx -= r11;             //sub rcx, r11
                rcx += 0xFFFFFFFFFFFFCAD7;              //add rcx, 0xFFFFFFFFFFFFCAD7
                rax += rcx;             //add rax, rcx
                rcx = rbx;              //mov rcx, rbx
                rcx = ~rcx;             //not rcx
                rcx += r15;             //add rcx, r15
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x12;           //shr rcx, 0x12
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x24;           //shr rcx, 0x24
                rax ^= rcx;             //xor rax, rcx
                rdx = rbx;              //mov rdx, rbx
                rcx = globals::base + 0xEF52;           //lea rcx, [0xFFFFFFFFFDFD2881]
                rdx = ~rdx;             //not rdx
                rax += rcx;             //add rax, rcx
                rax += rdx;             //add rax, rdx
                rcx = 0x6763BC8B6D17752D;               //mov rcx, 0x6763BC8B6D17752D
                rax *= rcx;             //imul rax, rcx
                rcx = 0x8BEF7389669EF866;               //mov rcx, 0x8BEF7389669EF866
                rax ^= rcx;             //xor rax, rcx
                return rax;
        }
        case 11:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x00000000093056B7]
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                rax ^= rbx;             //xor rax, rbx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x1F;           //shr rcx, 0x1F
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x3E;           //shr rcx, 0x3E
                rax ^= rcx;             //xor rax, rcx
                rdx = rbx;              //mov rdx, rbx
                rdx = ~rdx;             //not rdx
                rcx = globals::base + 0x923A;           //lea rcx, [0xFFFFFFFFFDFCC5BE]
                rcx = ~rcx;             //not rcx
                rdx += rcx;             //add rdx, rcx
                rax ^= rdx;             //xor rax, rdx
                rax += rbx;             //add rax, rbx
                rcx = 0x9FC5A5033F4BA222;               //mov rcx, 0x9FC5A5033F4BA222
                rax ^= rcx;             //xor rax, rcx
                rcx = 0xEE85007B158F0715;               //mov rcx, 0xEE85007B158F0715
                rax *= rcx;             //imul rax, rcx
                rcx = 0x237F4FB43D19B0AB;               //mov rcx, 0x237F4FB43D19B0AB
                rax ^= rcx;             //xor rax, rcx
                return rax;
        }
        case 12:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x00000000093051E7]
                r11 = globals::base + 0x12A67ACE;               //lea r11, [0x0000000010A2AB94]
                rcx = 0x1A8D56D056CAA6AD;               //mov rcx, 0x1A8D56D056CAA6AD
                rax *= rcx;             //imul rax, rcx
                rcx = r11;              //mov rcx, r11
                rcx = ~rcx;             //not rcx
                rcx -= rbx;             //sub rcx, rbx
                rax ^= rcx;             //xor rax, rcx
                rax ^= rbx;             //xor rax, rbx
                rcx = 0xCF3780F20368ADFF;               //mov rcx, 0xCF3780F20368ADFF
                rax *= rcx;             //imul rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x15;           //shr rcx, 0x15
                rax ^= rcx;             //xor rax, rcx
                rdx = 0;                //and rdx, 0xFFFFFFFFC0000000
                rdx = _rotl64(rdx, 0x10);               //rol rdx, 0x10
                rcx = rax;              //mov rcx, rax
                rdx ^= r10;             //xor rdx, r10
                rcx >>= 0x2A;           //shr rcx, 0x2A
                rax ^= rcx;             //xor rax, rcx
                rdx = ~rdx;             //not rdx
                rax *= mem.Read<uintptr_t>(rdx + 0xf);          //imul rax, [rdx+0x0F]
                rcx = 0x620FE8A3984FA9A2;               //mov rcx, 0x620FE8A3984FA9A2
                rax ^= rcx;             //xor rax, rcx
                rax += rbx;             //add rax, rbx
                return rax;
        }
        case 13:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB34210E);            //mov r9, [0x0000000009304E5B]
                r11 = globals::base;            //lea r11, [0xFFFFFFFFFDFC2D46]
                rax += r11;             //add rax, r11
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x10;           //shr rcx, 0x10
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x20;           //shr rcx, 0x20
                rax ^= rcx;             //xor rax, rcx
                rcx = 0x153249CC4096DEBB;               //mov rcx, 0x153249CC4096DEBB
                rax += rcx;             //add rax, rcx
                rax += rbx;             //add rax, rbx
                rax ^= r11;             //xor rax, r11
                rcx = 0x3FEF9376461CD77C;               //mov rcx, 0x3FEF9376461CD77C
                rax += rcx;             //add rax, rcx
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r9;              //xor rcx, r9
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                rcx = 0xCD5C890FC6052E0B;               //mov rcx, 0xCD5C890FC6052E0B
                rax *= rcx;             //imul rax, rcx
                return rax;
        }
        case 14:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x0000000009304960]
                r11 = globals::base;            //lea r11, [0xFFFFFFFFFDFC284B]
                r12 = globals::base + 0x2858;           //lea r12, [0xFFFFFFFFFDFC5081]
                r13 = globals::base + 0xB818;           //lea r13, [0xFFFFFFFFFDFCE034]
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                rax -= r11;             //sub rax, r11
                rcx = rax;              //mov rcx, rax
                rdx = rbx;              //mov rdx, rbx
                rdx *= r13;             //imul rdx, r13
                rcx >>= 0x28;           //shr rcx, 0x28
                rdx ^= rcx;             //xor rdx, rcx
                rax ^= rdx;             //xor rax, rdx
                rcx = 0x51E63BDB2878DA3D;               //mov rcx, 0x51E63BDB2878DA3D
                rax *= rcx;             //imul rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x17;           //shr rcx, 0x17
                rax ^= rcx;             //xor rax, rcx
                rcx = globals::base + 0x54FCAA3A;               //lea rcx, [0x0000000052F8CF6A]
                rdx = rax;              //mov rdx, rax
                rcx = ~rcx;             //not rcx
                rdx >>= 0x2E;           //shr rdx, 0x2E
                rcx ^= rbx;             //xor rcx, rbx
                rax ^= rdx;             //xor rax, rdx
                rax -= rcx;             //sub rax, rcx
                rcx = rbx;              //mov rcx, rbx
                rcx ^= r12;             //xor rcx, r12
                rax -= rcx;             //sub rax, rcx
                return rax;
        }
        case 15:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB34210E);           //mov r10, [0x0000000009304535]
                r11 = globals::base;            //lea r11, [0xFFFFFFFFFDFC2420]
                r12 = globals::base + 0x6D7996B9;               //lea r12, [0x000000006B75BAB7]
                rax += r11;             //add rax, r11
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x16;           //shr rcx, 0x16
                rax ^= rcx;             //xor rax, rcx
                rcx = rax;              //mov rcx, rax
                rcx >>= 0x2C;           //shr rcx, 0x2C
                rax ^= rcx;             //xor rax, rcx
                rcx = r12;              //mov rcx, r12
                rcx = ~rcx;             //not rcx
                rcx *= rbx;             //imul rcx, rbx
                rax += rcx;             //add rax, rcx
                rdx = 0xEEC920FB0911427A;               //mov rdx, 0xEEC920FB0911427A
                rax += rdx;             //add rax, rdx
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                rax *= mem.Read<uintptr_t>(rcx + 0xf);          //imul rax, [rcx+0x0F]
                rcx = globals::base + 0x9A06;           //lea rcx, [0xFFFFFFFFFDFCBA3D]
                rcx = ~rcx;             //not rcx
                rax += rcx;             //add rax, rcx
                rcx = 0xC2732136FBDEB5CD;               //mov rcx, 0xC2732136FBDEB5CD
                rax -= rbx;             //sub rax, rbx
                rax ^= rcx;             //xor rax, rcx
                rcx = 0x8A516BBDDE1E408F;               //mov rcx, 0x8A516BBDDE1E408F
                rax *= rcx;             //imul rax, rcx
                return rax;
        }
        }
}
uintptr_t decrypt_bone_base()
{
        uint64_t mb = globals::base;
        uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;

        rdx = mem.Read<uintptr_t>(globals::base + 0x114E0F48);
        if(!rdx)
                return rdx;

        r11 = globals::vaPeb;           //mov r11, gs:[rax]
        rax = r11;              //mov rax, r11
        rax >>= 0x13;           //shr rax, 0x13
        rax &= 0xF;

        switch(rax)
        {
        case 0:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x0000000007336A26]
                r12 = globals::base + 0x8C93;           //lea r12, [0xFFFFFFFFFBFFD4D5]
                rax = r12;              //mov rax, r12
                rax -= r11;             //sub rax, r11
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x15;           //shr rax, 0x15
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x2A;           //shr rax, 0x2A
                rdx ^= rax;             //xor rdx, rax
                rdx += r11;             //add rdx, r11
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                rax = globals::base;            //lea rax, [0xFFFFFFFFFBFF44BD]
                rdx ^= rax;             //xor rdx, rax
                rax = 0x860534C8C01FEA7B;               //mov rax, 0x860534C8C01FEA7B
                rdx *= rax;             //imul rdx, rax
                rax = 0xEE334BF3EC572D68;               //mov rax, 0xEE334BF3EC572D68
                rdx ^= rax;             //xor rdx, rax
                return rdx;
        }
        case 1:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x00000000073365E4]
                r12 = globals::base + 0xDF5D;           //lea r12, [0xFFFFFFFFFC002351]
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                rax = 0x8A4B98169395E686;               //mov rax, 0x8A4B98169395E686
                rdx ^= rax;             //xor rdx, rax
                rax = 0xC3957EB9F84EC5AF;               //mov rax, 0xC3957EB9F84EC5AF
                rdx *= rax;             //imul rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0xE;            //shr rax, 0x0E
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x1C;           //shr rax, 0x1C
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x38;           //shr rax, 0x38
                rdx ^= rax;             //xor rdx, rax
                rax = globals::base + 0x31CB;           //lea rax, [0xFFFFFFFFFBFF7192]
                rax -= r11;             //sub rax, r11
                rdx += rax;             //add rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0xD;            //shr rax, 0x0D
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x1A;           //shr rax, 0x1A
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x34;           //shr rax, 0x34
                rdx ^= rax;             //xor rdx, rax
                rax = r12;              //mov rax, r12
                rax = ~rax;             //not rax
                rax ^= r11;             //xor rax, r11
                rdx ^= rax;             //xor rdx, rax
                return rdx;
        }
        case 2:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x00000000073360D9]
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                rcx = globals::base + 0x47C2AE1B;               //lea rcx, [0x0000000043C1ECE5]
                rax = rcx;              //mov rax, rcx
                rax = ~rax;             //not rax
                rax ^= r11;             //xor rax, r11
                rax += r11;             //add rax, r11
                rdx += rax;             //add rdx, rax
                rax = 0x94073D91C803188D;               //mov rax, 0x94073D91C803188D
                rdx ^= rax;             //xor rdx, rax
                rax = 0x2EEA8A0831CE333B;               //mov rax, 0x2EEA8A0831CE333B
                rdx *= rax;             //imul rdx, rax
                rdx += r11;             //add rdx, r11
                rax = rdx;              //mov rax, rdx
                rax >>= 0x13;           //shr rax, 0x13
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x26;           //shr rax, 0x26
                rdx ^= rax;             //xor rdx, rax
                rax = 0xD4E2CCE5B7959CA0;               //mov rax, 0xD4E2CCE5B7959CA0
                rdx ^= rax;             //xor rdx, rax
                return rdx;
        }
        case 3:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);            //mov r9, [0x0000000007335D28]
                r12 = globals::base + 0x114B;           //lea r12, [0xFFFFFFFFFBFF4C83]
                rax = rdx;              //mov rax, rdx
                rax >>= 0x13;           //shr rax, 0x13
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x26;           //shr rax, 0x26
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x24;           //shr rax, 0x24
                rdx ^= rax;             //xor rdx, rax
                rax = 0x764F15DD269101D3;               //mov rax, 0x764F15DD269101D3
                rdx *= rax;             //imul rdx, rax
                rax = 0x34E81942B113C230;               //mov rax, 0x34E81942B113C230
                rdx -= rax;             //sub rdx, rax
                rax = 0x13805FC46F4FC36A;               //mov rax, 0x13805FC46F4FC36A
                rdx += rax;             //add rdx, rax
                rax = r11;              //mov rax, r11
                rax -= globals::base;           //sub rax, [rbp-0x50] -- didn't find trace -> use base
                rax += 0xFFFFFFFFFFFF85F3;              //add rax, 0xFFFFFFFFFFFF85F3
                rdx += rax;             //add rdx, rax
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r9;              //xor rax, r9
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                rax = r11;              //mov rax, r11
                rax ^= r12;             //xor rax, r12
                rdx ^= rax;             //xor rdx, rax
                return rdx;
        }
        case 4:
        {
                r9 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);            //mov r9, [0x00000000073357B1]
                rax = rdx;              //mov rax, rdx
                rax >>= 0x11;           //shr rax, 0x11
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x22;           //shr rax, 0x22
                rdx ^= rax;             //xor rdx, rax
                rax = 0x2CFB6FB2F3BAD3C;                //mov rax, 0x2CFB6FB2F3BAD3C
                rdx -= rax;             //sub rdx, rax
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r9;              //xor rax, r9
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                rax = 0xEED0F28134CE8447;               //mov rax, 0xEED0F28134CE8447
                rdx *= rax;             //imul rdx, rax
                rax = 0x52D4170A67BFFCB2;               //mov rax, 0x52D4170A67BFFCB2
                rdx ^= rax;             //xor rdx, rax
                rdx += r11;             //add rdx, r11
                rax = rdx;              //mov rax, rdx
                rax >>= 0x16;           //shr rax, 0x16
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x2C;           //shr rax, 0x2C
                rdx ^= rax;             //xor rdx, rax
                rdx ^= r11;             //xor rdx, r11
                return rdx;
        }
        case 5:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x000000000733520E]
                r12 = globals::base + 0x654BDD13;               //lea r12, [0x00000000614B0D2C]
                rax = r12;              //mov rax, r12
                rax = ~rax;             //not rax
                rax += 1;               //inc rax
                rax += r11;             //add rax, r11
                rdx += rax;             //add rdx, rax
                rax = 0x4A2AFA53025C5181;               //mov rax, 0x4A2AFA53025C5181
                rdx *= rax;             //imul rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x28;           //shr rax, 0x28
                rdx ^= rax;             //xor rdx, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFBFF2CF1]
                rcx = rax + 0xa045;             //lea rcx, [rax+0xA045]
                rax += 0x19B7DBCB;              //add rax, 0x19B7DBCB
                rax += r11;             //add rax, r11
                rcx += r11;             //add rcx, r11
                rcx ^= rax;             //xor rcx, rax
                rdx ^= rcx;             //xor rdx, rcx
                rax = 0x574A3A5B7408079B;               //mov rax, 0x574A3A5B7408079B
                rdx *= rax;             //imul rdx, rax
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                return rdx;
        }
        case 6:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x0000000007334E17]
                r12 = globals::base + 0x4951;           //lea r12, [0xFFFFFFFFFBFF7573]
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                rdx += r11;             //add rdx, r11
                rax = r11;              //mov rax, r11
                rax *= r12;             //imul rax, r12
                rdx += rax;             //add rdx, rax
                rcx = globals::base;            //lea rcx, [0xFFFFFFFFFBFF2A8B]
                rax = rcx + 0x1d37b933;                 //lea rax, [rcx+0x1D37B933]
                rax += r11;             //add rax, r11
                rdx += rax;             //add rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x9;            //shr rax, 0x09
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x12;           //shr rax, 0x12
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x24;           //shr rax, 0x24
                rdx ^= rax;             //xor rdx, rax
                rax = 0x6C2A29044A40E4C7;               //mov rax, 0x6C2A29044A40E4C7
                rdx *= rax;             //imul rdx, rax
                rdx ^= rcx;             //xor rdx, rcx
                rax = rdx;              //mov rax, rdx
                rax >>= 0x3;            //shr rax, 0x03
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x6;            //shr rax, 0x06
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0xC;            //shr rax, 0x0C
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x18;           //shr rax, 0x18
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x30;           //shr rax, 0x30
                rdx ^= rax;             //xor rdx, rax
                return rdx;
        }
        case 7:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x0000000007334A21]
                rax = globals::base;            //lea rax, [0xFFFFFFFFFBFF2701]
                rdx += rax;             //add rdx, rax
                rax = 0x5F80490A38DB3901;               //mov rax, 0x5F80490A38DB3901
                rdx ^= rax;             //xor rdx, rax
                rax = 0x4EC9DC6A5902297D;               //mov rax, 0x4EC9DC6A5902297D
                rdx -= rax;             //sub rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x25;           //shr rax, 0x25
                rdx ^= rax;             //xor rdx, rax
                rcx = globals::base + 0xCEFB;           //lea rcx, [0xFFFFFFFFFBFFF70D]
                rax = r11;              //mov rax, r11
                rax ^= rcx;             //xor rax, rcx
                rdx += rax;             //add rdx, rax
                rax = 0x92B34BC27C367071;               //mov rax, 0x92B34BC27C367071
                rdx *= rax;             //imul rdx, rax
                rdx -= r11;             //sub rdx, r11
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                return rdx;
        }
        case 8:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x00000000073345EB]
                rcx = globals::base + 0x5723;           //lea rcx, [0xFFFFFFFFFBFF7AB7]
                rax = 0xE62DA6375F493113;               //mov rax, 0xE62DA6375F493113
                rdx *= rax;             //imul rdx, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFBFF2166]
                rdx -= rax;             //sub rdx, rax
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                rdx -= r11;             //sub rdx, r11
                rax = rdx;              //mov rax, rdx
                rax >>= 0xF;            //shr rax, 0x0F
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x1E;           //shr rax, 0x1E
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x3C;           //shr rax, 0x3C
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x3;            //shr rax, 0x03
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x6;            //shr rax, 0x06
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0xC;            //shr rax, 0x0C
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x18;           //shr rax, 0x18
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x30;           //shr rax, 0x30
                rdx ^= rax;             //xor rdx, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFBFF1FD8]
                rax += 0xFAB2;          //add rax, 0xFAB2
                rax += r11;             //add rax, r11
                rdx ^= rax;             //xor rdx, rax
                rax = r11;              //mov rax, r11
                rax ^= rcx;             //xor rax, rcx
                rdx ^= rax;             //xor rdx, rax
                return rdx;
        }
        case 9:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x00000000073340A3]
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                rax = globals::base;            //lea rax, [0xFFFFFFFFFBFF1E0D]
                rcx = rax + 0x429d;             //lea rcx, [rax+0x429D]
                rax += 0xF1EC;          //add rax, 0xF1EC
                rax += r11;             //add rax, r11
                rcx += r11;             //add rcx, r11
                rdx += rcx;             //add rdx, rcx
                rdx ^= rax;             //xor rdx, rax
                rax = globals::base + 0x5304B0E6;               //lea rax, [0x000000004F03CEC9]
                rdx ^= r11;             //xor rdx, r11
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x22;           //shr rax, 0x22
                rdx ^= rax;             //xor rdx, rax
                rax = 0xEE899EDDAF56550;                //mov rax, 0xEE899EDDAF56550
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0xE;            //shr rax, 0x0E
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x1C;           //shr rax, 0x1C
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x38;           //shr rax, 0x38
                rdx ^= rax;             //xor rdx, rax
                rax = 0x39D515C223A57391;               //mov rax, 0x39D515C223A57391
                rdx *= rax;             //imul rdx, rax
                return rdx;
        }
        case 10:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x0000000007333C27]
                rcx = globals::base + 0x1A3D;           //lea rcx, [0xFFFFFFFFFBFF33F4]
                rax = rdx;              //mov rax, rdx
                rax >>= 0xF;            //shr rax, 0x0F
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x1E;           //shr rax, 0x1E
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x3C;           //shr rax, 0x3C
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x13;           //shr rax, 0x13
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x26;           //shr rax, 0x26
                rdx ^= rax;             //xor rdx, rax
                rax = r11;              //mov rax, r11
                rax = ~rax;             //not rax
                rax *= rcx;             //imul rax, rcx
                rdx ^= rax;             //xor rdx, rax
                rax = 0x8330B389343DA675;               //mov rax, 0x8330B389343DA675
                rdx *= rax;             //imul rdx, rax
                rax = 0x5A325A7184C15E55;               //mov rax, 0x5A325A7184C15E55
                rdx -= rax;             //sub rdx, rax
                rax = 0xE28957C95B7E497;                //mov rax, 0xE28957C95B7E497
                rdx += rax;             //add rdx, rax
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                rdx -= r11;             //sub rdx, r11
                return rdx;
        }
        case 11:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x000000000733375C]
                r15 = globals::base + 0x67B591A2;               //lea r15, [0x0000000063B4A70E]
                rax = rdx;              //mov rax, rdx
                rax >>= 0x22;           //shr rax, 0x22
                rdx ^= rax;             //xor rdx, rax
                rax = r15;              //mov rax, r15
                rax = ~rax;             //not rax
                rax ^= r11;             //xor rax, r11
                rax += r11;             //add rax, r11
                rdx -= rax;             //sub rdx, rax
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                rdx ^= r11;             //xor rdx, r11
                rax = 0x112AEF7CBA9BEDF1;               //mov rax, 0x112AEF7CBA9BEDF1
                rdx *= rax;             //imul rdx, rax
                rax = 0x792205E77EAA6797;               //mov rax, 0x792205E77EAA6797
                rdx ^= rax;             //xor rdx, rax
                return rdx;
        }
        case 12:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x00000000073333B3]
                r12 = globals::base + 0x70E4B3E1;               //lea r12, [0x000000006CE3C59F]
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                rax = 0x33BF00DD8A073650;               //mov rax, 0x33BF00DD8A073650
                rdx -= rax;             //sub rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0xA;            //shr rax, 0x0A
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x14;           //shr rax, 0x14
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x28;           //shr rax, 0x28
                rdx ^= rax;             //xor rdx, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFBFF0F70]
                rdx ^= rax;             //xor rdx, rax
                rax = r12;              //mov rax, r12
                rax = ~rax;             //not rax
                rdx += rax;             //add rdx, rax
                rax = 0x37300D9E69A77B2F;               //mov rax, 0x37300D9E69A77B2F
                rdx *= rax;             //imul rdx, rax
                rdx -= r11;             //sub rdx, r11
                return rdx;
        }
        case 13:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x0000000007332FF1]
                r15 = globals::base + 0x666C9DA0;               //lea r15, [0x00000000626BAB9C]
                rax = r11;              //mov rax, r11
                rax ^= r15;             //xor rax, r15
                rdx -= rax;             //sub rdx, rax
                rax = 0x124569EA4125D98;                //mov rax, 0x124569EA4125D98
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x5;            //shr rax, 0x05
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0xA;            //shr rax, 0x0A
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x14;           //shr rax, 0x14
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x28;           //shr rax, 0x28
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x1A;           //shr rax, 0x1A
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x34;           //shr rax, 0x34
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rdx ^= rax;             //xor rdx, rax
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                rdx *= mem.Read<uintptr_t>(rcx + 0x17);                 //imul rdx, [rcx+0x17]
                rdx ^= r11;             //xor rdx, r11
                rax = 0xD83F30F92C64DF4F;               //mov rax, 0xD83F30F92C64DF4F
                rdx ^= rax;             //xor rdx, rax
                rax = 0xB69AFD2628432A9D;               //mov rax, 0xB69AFD2628432A9D
                rdx *= rax;             //imul rdx, rax
                return rdx;
        }
        case 14:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x0000000007332BCE]
                r12 = globals::base + 0x5113;           //lea r12, [0xFFFFFFFFFBFF5AEC]
                rax = rdx;              //mov rax, rdx
                rax >>= 0x1B;           //shr rax, 0x1B
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x36;           //shr rax, 0x36
                rcx = 0;                //and rcx, 0xFFFFFFFFC0000000
                rdx ^= rax;             //xor rdx, rax
                rcx = _rotl64(rcx, 0x10);               //rol rcx, 0x10
                rcx ^= r10;             //xor rcx, r10
                rcx = ~rcx;             //not rcx
                rdx *= mem.Read<uintptr_t>(rcx + 0x17);                 //imul rdx, [rcx+0x17]
                rax = 0xDC4274449EFE767B;               //mov rax, 0xDC4274449EFE767B
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x6;            //shr rax, 0x06
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0xC;            //shr rax, 0x0C
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x18;           //shr rax, 0x18
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x30;           //shr rax, 0x30
                rdx ^= rax;             //xor rdx, rax
                rax = r11;              //mov rax, r11
                rax ^= r12;             //xor rax, r12
                rdx -= rax;             //sub rdx, rax
                rax = 0x4480AA60A21867F9;               //mov rax, 0x4480AA60A21867F9
                rdx *= rax;             //imul rdx, rax
                rax = globals::base;            //lea rax, [0xFFFFFFFFFBFF06B2]
                rax += 0xD03A;          //add rax, 0xD03A
                rax += r11;             //add rax, r11
                rdx += rax;             //add rdx, rax
                return rdx;
        }
        case 15:
        {
                r10 = mem.Read<uintptr_t>(globals::base + 0xB3421DD);           //mov r10, [0x0000000007332734]
                rcx = globals::base + 0x6744783A;               //lea rcx, [0x0000000063437CD5]
                rdx += r11;             //add rdx, r11
                rax = r11;              //mov rax, r11
                rax = ~rax;             //not rax
                uintptr_t RSP_0xFFFFFFFFFFFFFFB0;
                RSP_0xFFFFFFFFFFFFFFB0 = globals::base + 0x642A39AC;            //lea rax, [0x0000000060293EFC] : RBP+0xFFFFFFFFFFFFFFB0
                rax ^= RSP_0xFFFFFFFFFFFFFFB0;          //xor rax, [rbp-0x50]
                rdx -= rax;             //sub rdx, rax
                rdx ^= r11;             //xor rdx, r11
                rdx ^= rcx;             //xor rdx, rcx
                rax = 0;                //and rax, 0xFFFFFFFFC0000000
                rax = _rotl64(rax, 0x10);               //rol rax, 0x10
                rax ^= r10;             //xor rax, r10
                rax = ~rax;             //not rax
                rdx *= mem.Read<uintptr_t>(rax + 0x17);                 //imul rdx, [rax+0x17]
                rax = 0x54750E0E4638841A;               //mov rax, 0x54750E0E4638841A
                rdx += rax;             //add rdx, rax
                rax = 0x17257FE07A931EB4;               //mov rax, 0x17257FE07A931EB4
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x4;            //shr rax, 0x04
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x8;            //shr rax, 0x08
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x10;           //shr rax, 0x10
                rdx ^= rax;             //xor rdx, rax
                rax = rdx;              //mov rax, rdx
                rax >>= 0x20;           //shr rax, 0x20
                rdx ^= rax;             //xor rdx, rax
                rax = 0x7493CCED6314B08B;               //mov rax, 0x7493CCED6314B08B
                rdx *= rax;             //imul rdx, rax
                return rdx;
        }
        }
};

uint16_t get_bone_index (uint32_t bone_index)
{
        const uint64_t mb = globals::base;
        uint64_t rax = mb, rbx = mb, rcx = mb, rdx = mb, rdi = mb, rsi = mb, r8 = mb, r9 = mb, r10 = mb, r11 = mb, r12 = mb, r13 = mb, r14 = mb, r15 = mb;
        rbx = bone_index;
        rcx = rbx * 0x13C8;
        rax = 0xCB182C584BD5193;                //mov rax, 0xCB182C584BD5193
        r11 = globals::base;            //lea r11, [0xFFFFFFFFFD1DFC6E]
        rax = _umul128(rax, rcx, (uintptr_t*)&rdx);             //mul rcx
        rax = rcx;              //mov rax, rcx
        r10 = 0xD6FB75C08B670E5B;               //mov r10, 0xD6FB75C08B670E5B
        rax -= rdx;             //sub rax, rdx
        rax >>= 0x1;            //shr rax, 0x01
        rax += rdx;             //add rax, rdx
        rax >>= 0xC;            //shr rax, 0x0C
        rax = rax * 0x1E7D;             //imul rax, rax, 0x1E7D
        rcx -= rax;             //sub rcx, rax
        rax = 0x4078E2A8FCDA18EF;               //mov rax, 0x4078E2A8FCDA18EF
        r8 = rcx * 0x1E7D;              //imul r8, rcx, 0x1E7D
        rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
        rdx >>= 0xB;            //shr rdx, 0x0B
        rax = rdx * 0x1FC4;             //imul rax, rdx, 0x1FC4
        r8 -= rax;              //sub r8, rax
        rax = 0xF0F0F0F0F0F0F0F1;               //mov rax, 0xF0F0F0F0F0F0F0F1
        rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
        rax = 0x624DD2F1A9FBE77;                //mov rax, 0x624DD2F1A9FBE77
        rdx >>= 0x6;            //shr rdx, 0x06
        rcx = rdx * 0x44;               //imul rcx, rdx, 0x44
        rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
        rax = r8;               //mov rax, r8
        rax -= rdx;             //sub rax, rdx
        rax >>= 0x1;            //shr rax, 0x01
        rax += rdx;             //add rax, rdx
        rax >>= 0x6;            //shr rax, 0x06
        rcx += rax;             //add rcx, rax
        rax = rcx * 0xFA;               //imul rax, rcx, 0xFA
        rcx = r8 * 0xFC;                //imul rcx, r8, 0xFC
        rcx -= rax;             //sub rcx, rax
        rax = mem.Read<uint16_t>(rcx + r11 * 1 + 0xA7620F0);            //movzx eax, word ptr [rcx+r11*1+0xA7620F0]
        r8 = rax * 0x13C8;              //imul r8, rax, 0x13C8
        rax = r10;              //mov rax, r10
        rax = _umul128(rax, r8, (uintptr_t*)&rdx);              //mul r8
        rax = r10;              //mov rax, r10
        rdx >>= 0xD;            //shr rdx, 0x0D
        rcx = rdx * 0x261B;             //imul rcx, rdx, 0x261B
        r8 -= rcx;              //sub r8, rcx
        r9 = r8 * 0x2F75;               //imul r9, r8, 0x2F75
        rax = _umul128(rax, r9, (uintptr_t*)&rdx);              //mul r9
        rdx >>= 0xD;            //shr rdx, 0x0D
        rax = rdx * 0x261B;             //imul rax, rdx, 0x261B
        r9 -= rax;              //sub r9, rax
        rax = 0x8FB823EE08FB823F;               //mov rax, 0x8FB823EE08FB823F
        rax = _umul128(rax, r9, (uintptr_t*)&rdx);              //mul r9
        rax = 0x579D6EE340579D6F;               //mov rax, 0x579D6EE340579D6F
        rdx >>= 0x5;            //shr rdx, 0x05
        rcx = rdx * 0x39;               //imul rcx, rdx, 0x39
        rax = _umul128(rax, r9, (uintptr_t*)&rdx);              //mul r9
        rdx >>= 0x6;            //shr rdx, 0x06
        rcx += rdx;             //add rcx, rdx
        rax = rcx * 0x176;              //imul rax, rcx, 0x176
        rcx = r9 * 0x178;               //imul rcx, r9, 0x178
        rcx -= rax;             //sub rcx, rax
        r14 = mem.Read<uint16_t>(rcx + r11 * 1 + 0xA766360);            //movsx r14d, word ptr [rcx+r11*1+0xA766360]
        return r14;
}

uintptr_t retrieve_ref_def()
{
    return mem.Read<uintptr_t>(globals::base + offsets::ref_def_ptr);
}

        constexpr auto timestamp = 0x688B4C95;
        constexpr auto ref_def_ptr = 0xC908D60;
        constexpr auto name_array = 0xCA7C628;
        constexpr auto name_array_pos = 0x3038; // 0x4C70 for MW1(2019)
        constexpr auto name_array_size = 0xC8;
        constexpr auto loot_ptr = 0xE2C1D08;
        constexpr auto loot_pos = 0x170;
        constexpr auto camera_base = 0xC5A57A0;
        constexpr auto camera_pos = 0x204;
        constexpr auto local_index = 0xA8FA8;
        constexpr auto local_index_pos = 0x394;
        constexpr auto game_mode = 0xB544188;
        constexpr auto weapon_definitions = 0xC7D15C0;
        constexpr auto distribute = 0x9790328;
        uint32_t o_visible_bit = 0x447AC;
        uint32_t o_no_recoil = 0x57188;
        uint32_t Player_client_state_enum = 0x1C9CBC;
        constexpr auto scoreboard = 0x513C0;
        constexpr auto scoreboardsize = 0x78;


namespace bone {
        constexpr auto bone_base = 0x1570E8;
        constexpr auto size = 0x1B8;
        constexpr auto offset = 0xD8;
};

namespace player {
        constexpr auto size = 0x2560;
        constexpr auto valid = 0x22DC;
        constexpr auto pos = 0x248;
        constexpr auto team = 0x130B;
        constexpr auto stance = 0x15F4;
        constexpr auto weapon_index = 0xC6A;
        constexpr auto dead_1 = 0x15400;
        constexpr auto dead_2 = 0x214;
        constexpr auto dead_3 = 0x11C;
};
