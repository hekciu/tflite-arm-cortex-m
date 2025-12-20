
ENTRY(Reset_Handler);

SEARCH_DIR(tflite-micro/gen/cortex_m_generic_cortex-m4_release_cmsis_nn_gcc/lib)
INPUT(-ltensorflow-microlite)

SEARCH_DIR(tflite-micro/tensorflow/lite/micro/tools/make/downloads/gcc_embedded/arm-none-eabi/lib)
INPUT(-lstdc++)
INPUT(-lm)
INPUT(-lc)
INPUT(-lc_nano)
INPUT(-lg)
INPUT(-lgfortran)
INPUT(-lgloss-linux)
INPUT(-lg_nano)
INPUT(-lnosys)
INPUT(-lrdimon)
INPUT(-lrdimon_nano)
INPUT(-lrdimon-v2m)
INPUT(-lrdpmon)
INPUT(-lstdc++exp)
INPUT(-lstdc++_nano)
INPUT(-lsupc++)
INPUT(-lsupc++_nano)

SEARCH_DIR(tflite-micro/tensorflow/lite/micro/tools/make/downloads/gcc_embedded/lib/gcc/arm-none-eabi/14.3.1)
INPUT(-lgcc)


MEMORY {
  flash(rx)  : ORIGIN = 0x08000000, LENGTH = 0x100000
  sram(rwx) : ORIGIN = 0x20000000, LENGTH = 0x30000
}

_estack     = ORIGIN(sram) + LENGTH(sram);    /* stack points to end of SRAM */

SECTIONS {
    .text     : {
        . = ALIGN(4);
        KEEP(*(.vectors .vectors.*))
        *(.text)
        tensorflow-microlite:*(.text)
        stdc++:*(.text)
        m:*(.text)
        c:*(.text)
        c_nano:*(.text)
        g:*(.text)
        gfortran:*(.text)
        gloss-linux:*(.text)
        g_nano:*(.text)
        nosys:*(.text)
        rdimon:*(.text)
        rdimon_nano:*(.text)
        rdimon-v2m:*(.text)
        rdpmon:*(.text)
        stdc++exp:*(.text)
        stdc++_nano:*(.text)
        supc++:*(.text)
        supc++_nano:*(.text)
        gcc:*(.text)

        *(.text*)
        tensorflow-microlite:*(.text*)
        stdc++:*(.text*)
        m:*(.text*)
        c:*(.text*)
        c_nano:*(.text*)
        g:*(.text*)
        gfortran:*(.text*)
        gloss-linux:*(.text*)
        g_nano:*(.text*)
        nosys:*(.text*)
        rdimon:*(.text*)
        rdimon_nano:*(.text*)
        rdimon-v2m:*(.text*)
        rdpmon:*(.text*)
        stdc++exp:*(.text*)
        stdc++_nano:*(.text*)
        supc++:*(.text*)
        supc++_nano:*(.text*)
        gcc:*(.text*)
    }           > flash


    __exidx_start = .;
    .ARM.exidx :
    {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > flash
    __exidx_end = .;

    .rodata   : {
        *(.rodata)
        tensorflow-microlite:*(.rodata)
        stdc++:*(.rodata)
        m:*(.rodata)
        c:*(.rodata)
        c_nano:*(.rodata)
        g:*(.rodata)
        gfortran:*(.rodata)
        gloss-linux:*(.rodata)
        g_nano:*(.rodata)
        nosys:*(.rodata)
        rdimon:*(.rodata)
        rdimon_nano:*(.rodata)
        rdimon-v2m:*(.rodata)
        rdpmon:*(.rodata)
        stdc++exp:*(.rodata)
        stdc++_nano:*(.rodata)
        supc++:*(.rodata)
        supc++_nano:*(.rodata)
        gcc:*(.rodata)

        *(.rodata*)
        tensorflow-microlite:*(.rodata*)
        stdc++:*(.rodata*)
        m:*(.rodata*)
        c:*(.rodata*)
        c_nano:*(.rodata*)
        g:*(.rodata*)
        gfortran:*(.rodata*)
        gloss-linux:*(.rodata*)
        g_nano:*(.rodata*)
        nosys:*(.rodata*)
        rdimon:*(.rodata*)
        rdimon_nano:*(.rodata*)
        rdimon-v2m:*(.rodata*)
        rdpmon:*(.rodata*)
        stdc++exp:*(.rodata*)
        stdc++_nano:*(.rodata*)
        supc++:*(.rodata*)
        supc++_nano:*(.rodata*)
        gcc:*(.rodata*)
    }         > flash

    .data : {
        _sdata = .;   /* .data section start */
        *(.data)
        tensorflow-microlite:*(.data)
        stdc++:*(.data)
        m:*(.data)
        c:*(.data)
        c_nano:*(.data)
        g:*(.data)
        gfortran:*(.data)
        gloss-linux:*(.data)
        g_nano:*(.data)
        nosys:*(.data)
        rdimon:*(.data)
        rdimon_nano:*(.data)
        rdimon-v2m:*(.data)
        rdpmon:*(.data)
        stdc++exp:*(.data)
        stdc++_nano:*(.data)
        supc++:*(.data)
        supc++_nano:*(.data)
        gcc:*(.data)

        *(.data*)
        tensorflow-microlite:*(.data*)
        stdc++:*(.data*)
        m:*(.data*)
        c:*(.data*)
        c_nano:*(.data*)
        g:*(.data*)
        gfortran:*(.data*)
        gloss-linux:*(.data*)
        g_nano:*(.data*)
        nosys:*(.data*)
        rdimon:*(.data*)
        rdimon_nano:*(.data*)
        rdimon-v2m:*(.data*)
        rdpmon:*(.data*)
        stdc++exp:*(.data*)
        stdc++_nano:*(.data*)
        supc++:*(.data*)
        supc++_nano:*(.data*)
        gcc:*(.data*)
        _edata = .;  /* .data section end */
    } > sram AT > flash
    _sidata = LOADADDR(.data);

    .bss : {
    _sbss = .;              /* .bss section start */
        *(.bss)
        tensorflow-microlite:*(.bss)
        stdc++:*(.bss)
        m:*(.bss)
        c:*(.bss)
        c_nano:*(.bss)
        g:*(.bss)
        gfortran:*(.bss)
        gloss-linux:*(.bss)
        g_nano:*(.bss)
        nosys:*(.bss)
        rdimon:*(.bss)
        rdimon_nano:*(.bss)
        rdimon-v2m:*(.bss)
        rdpmon:*(.bss)
        stdc++exp:*(.bss)
        stdc++_nano:*(.bss)
        supc++:*(.bss)
        supc++_nano:*(.bss)
        gcc:*(.bss)

        *(.bss*)
        tensorflow-microlite:*(.bss*)
        stdc++:*(.bss*)
        m:*(.bss*)
        c:*(.bss*)
        c_nano:*(.bss*)
        g:*(.bss*)
        gfortran:*(.bss*)
        gloss-linux:*(.bss*)
        g_nano:*(.bss*)
        nosys:*(.bss*)
        rdimon:*(.bss*)
        rdimon_nano:*(.bss*)
        rdimon-v2m:*(.bss*)
        rdpmon:*(.bss*)
        stdc++exp:*(.bss*)
        stdc++_nano:*(.bss*)
        supc++:*(.bss*)
        supc++_nano:*(.bss*)
        gcc:*(.bss*)
    _ebss = .;              /* .bss section end */
    } > sram

    . = ALIGN(8);
    _end = .;     /* for cmsis_gcc.h  */
}

/*
INCLUDE cmsis/cmsis_core/CMSIS/DSP/Platforms/FVP/ARMCM4/LinkScripts/GCC/lnk.ld
*/
