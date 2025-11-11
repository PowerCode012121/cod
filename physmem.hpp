#include "includes.h"
#include <iostream>
#include <unordered_map>
#include <Psapi.h>


class physmem
{
private:
	uintptr_t EP_DIRECTORYTABLE = 0x028;
	uintptr_t EP_UNIQUEPROCESSID = 0;
	uintptr_t EP_ACTIVEPROCESSLINK = 0;
	uintptr_t EP_VIRTUALSIZE = 0;
	uintptr_t EP_SECTIONBASE = 0;
	uintptr_t EP_IMAGEFILENAME = 0;
	uintptr_t EP_VADROOT = 0;
	uintptr_t EP_PEB = 0;

	int64_t mapped_pages;
	std::unordered_map<uint64_t, uint64_t> pdpt_page_table;

public:
	std::wstring local_process_name;
	uintptr_t attached_dtb;
	EPROCESS_DATA attached_process;

	byte cached_dtb_data[0x1000];

public:
	physmem() = default;
	physmem(uint64_t gb_to_map, HANDLE winio, HANDLE intel);

public:
	uintptr_t get_local_virt_from_phys(uintptr_t phys);
	bool read_physical_memory(uintptr_t phys, byte* buf, size_t size);
	bool write_physical_memory(uintptr_t phys, byte* buf, size_t size);

	uintptr_t convert_virtual_to_physical(uintptr_t virtual_address);

	bool read_virtual_memory(uintptr_t virt, byte* buf, size_t size);
	bool write_virtual_memory(uintptr_t virt, byte* buf, size_t size);

	template<typename T>
	inline T read_virtual_memory(uintptr_t virt)
	{
		T buf;
		if (!read_virtual_memory(virt, (byte*) &buf, sizeof(buf)))
			return T {};
		return buf;
	}

	template<typename T>
	inline T read_virtual_memory_chain(uintptr_t virt, const std::vector<std::uintptr_t>& chain)
	{
		auto current = virt;
		for (size_t i = 0; i < chain.size() - 1; i++) {
			current = this->read_virtual_memory<std::uintptr_t>(current + chain[i]);
		}
		return this->read_virtual_memory<T>(current + chain[chain.size() - 1]);
	}

	template<typename T>
	inline bool write_virtual_memory(uintptr_t virt, T val)
	{
		if (!write_virtual_memory(virt, (byte*) &val, sizeof(val)))
			return false;
		return true;
	}

	uint64_t find_self_referencing_pml4e();

	// warning: this method automatically attaches to the found dtb (if one is found)
	uintptr_t bruteforce_dtb_from_base(uintptr_t base);

	// caches and attaches to the new dtb
	bool cache_dtb(uintptr_t dtb);

	uintptr_t get_system_dirbase();

	void get_eprocess_offsets();
	bool leak_kpointers(std::vector<uintptr_t>& pointers);
	uintptr_t leak_kprocess();

	EPROCESS_DATA attach(std::wstring proc_name);
	EPROCESS_DATA attach(DWORD pid);

	uintptr_t get_module_base(std::wstring module_name);
};

namespace physmem_setup
{
	// DO NOT USE
	static HANDLE iqvw64e_device_handle;
	// DO NOT USE
	static HANDLE winio_device_handle;

	physmem setup(bool* status, int pages_to_map);
}