#include "bo6.h"
#include "globals.h"
#include "offsets.h"

uintptr_t retrieve_ref_def()
{
    return mem.Read<uintptr_t>(globals::base + offsets::ref_def_ptr);
}