OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY
{
	ram   (wxa!ri) : ORIGIN = 0x80210000, LENGTH = 32M
}

SECTIONS
{
    .text : {
		PROVIDE(_text_start = .);
		*(.text .text.*)
		PROVIDE(_text_end = .);
	} >ram

	.rodata : {
		PROVIDE(_rodata_start = .);
		*(.rodata .rodata.*)
		PROVIDE(_rodata_end = .);
	} >ram

	.data : {
		/*
		 * . = ALIGN(4096) tells the linker to align the current memory
		 * location to 4096 bytes. This will insert padding bytes until
		 * current location becomes aligned on 4096-byte boundary.
		 * This is because our paging system's resolution is 4,096 bytes.
		 */
		. = ALIGN(4096);
		PROVIDE(_data_start = .);
		/*
		 * sdata and data are essentially the same thing. We do not need
		 * to distinguish sdata from data.
		 */
		*(.sdata .sdata.*)
		*(.data .data.*)
		PROVIDE(_data_end = .);
	} >ram

	.bss :{
		/*
		 * https://sourceware.org/binutils/docs/ld/Input-Section-Common.html
		 * In most cases, common symbols in input files will be placed
		 * in the ‘.bss’ section in the output file.
		 */
		PROVIDE(_bss_start = .);
		*(.sbss .sbss.*)
		*(.bss .bss.*)
		*(COMMON)
		PROVIDE(_bss_end = .);
	} >ram

	PROVIDE(_memory_start = ORIGIN(ram));
	PROVIDE(_memory_end = ORIGIN(ram) + LENGTH(ram));

	PROVIDE(_heap_start = _bss_end);
	PROVIDE(_heap_size = _memory_end - _heap_start);
}