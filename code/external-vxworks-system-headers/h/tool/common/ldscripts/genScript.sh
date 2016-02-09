#!/bin/sh

# genScript.sh
#
# a shell script to generate linker scripts.
#
# TODO:
# 1. convenience labels like etext, edata, end, and wrs_kernel_*_{start,end}
#    are primarily used by ROM kernels and can most likely be omitted from RAM
#    kernels. But they're harmless and it makes script sharing easier.
# 2. "classic" convenience labels (etext/edata/end) should be phased out in
#    favor of the newer ones. Further, DAT has requested that we make the new
#    names conform to wrsInitialCapitals style.
# 3. Due to the template generation strategy employed here, the final output
#    may look a little awkwardly formatted and certainly is not as clean and
#    simple as the early versions of the Diab scripts. Suggestions welcome.
#    I actually think this might not be such a bad application for (gasp!) Tcl,
#    so a future Tcl rewrite (which also helps windows users) is possible.
# 4. Currently GNU aligns everything to 16. This is probably overkill on many
#    chips, and especially once everyone is ELF, the internal section alignment
#    should take care of things -- except for convenience labels which need to
#    guarantee 4 byte alignment for use with copyLongs and fillLongs.
# 5. General convergence...

mod_history()
{
cat <<'EOF'
/*
modification history
--------------------
02k,16sep14,mcm  Fix for NOTYPE symbols (TCGNU-76)
02j,22apr13,g_x  Adding *(.gnu.linkonce.s.*) for gnu. (WIND00414091)
02i,02apr13,g_x  Add *(text.romentry) in the text segment for MIPS
                 (WIND00408686)
02h,12mar13,gvm  Fix for WIND00376986. Close alignment gap 
                 between _wrs_kernel_tls_vars_start and .tls_vars
02g,05jan12,my_  Place .copy.text and inflate.text into the .data
                 section for ARMARCH4
02f,06may10,slk  updates for large memory model support
02e,12jan11,pgh  Place .copy.text and inflate.text into the .data section
02d,09jul10,mcm  Adding .wrs_build_vars for GNU as well.
02c,10mar10,gvm  updates for icc
02b,16feb10,mcm  Update to allow the 'AT' directive introduced for .boot and
                 .reset to be present for gnu only.
02a,15feb10,mcm  Updates for GCC 4.3.3
01z,24jul09,pee  adding wrs_build_vars section.
01y,13nov08,mcm  Fix for WIND00143294 - gnu.linkonce.b sections not handled
                 correctly. Also added .bss.* and .sbss.*
01x,06may08,mcm  Changes for GNU Dwarf EH
01w,16oct07,sn   WIND00107939:fixed LMAs of .sdata etc. for Diab
01v,11jul07,pes  Update and rename generation of .kseg0data segment. (Renamed
                 to .kseg0bss.) Add .rodata.cst16 segment.
01u,07jul07,mcm  Fixing position of .tls* sections and adding support for tls
                 for GCC.
01t,08jun07,r_s  add support for Small Data Area segments.
01s,09nov06,gvm  Support for .tls_data, .tls_vars, and associated absolute
                 symbols in the Diab linker script
01r,25aug05,dlk  Support .text.init, .text.fast, .data.init, .data.fast.
01r,29jul05,slk  SPR 104264: fix MIPS romResident images
01q,06may05,rlg  changes for MIPS specific devices
01p,03jul04,f_b  Improved support for data alignment
01o,12dec03,sn   added more .rodata.str1.* handlers
01n,04dec03,sn   Diab: .rodata.* is not handled correctly by Diab linker; instead
		 use specific names
01m,28oct03,sn   Diab: collapse .rodata.cst* sections into .rodata
01l,29may02,tpw  Diab: pad out sections, needed for MIPS byteswap. SPR 78076
01k,24apr02,sn   GNU: SPR 75835 - added support for relocatable script link.OUT
01j,19apr02,tpw  Diab: provide _etext for ColdFire. SPR 75122
01i,06feb02,sn   Both: place .got2 to handle tramp.o (_x_gnu_tramp.o).
01h,25jan02,tpw  GNU: give debug sections explicit 0 addresses.
01g,14jan02,tpw  Diab: place .eh_frame data, in case of insistent GNU objects.
01f,14dec01,tpw  Diab: provide both underscore options of wrs_kernel* here too.
01e,05dec01,tpw  Both: Add .boot and .reset section support, for PPC 4xx series
                 and Book E.
01d,05dec01,tpw  Diab: Add .frame_info section to text region.
01c,03dec01,jab  Diab: replaced LOAD() with AT()
01b,14nov01,tpw  ALL: Correct some more bootrom/kernel issues.
01b,06nov01,tpw  GNU: Add /DISCARD/ directive to discard uninteresting sections
01a,01nov01,tpw  gnu script written
01a,29oct01,jab  diab script written
*/

EOF
}

filename="$1"
TOOL="$2"
shift 2
style="$*"

align=16
am1=`expr $align - 1`

bind=""
[ "$TOOL" = icc ] && TOOL=gnu
[ "$TOOL" = diab ] && bind=BIND
[ "$TOOL" = gnu ] && dot_boot_text="
  .boot $bind(wrs_kernel_text_start + wrs_kernel_rom_size - 0x800) : AT(wrs_kernel_text_start + wrs_kernel_rom_size - 0x800)
  {
  *(.boot)
  }
  .reset $bind(wrs_kernel_text_start + wrs_kernel_rom_size - 4) : AT(wrs_kernel_text_start + wrs_kernel_rom_size - 4)
  {
  *(.reset)
  }
"
[ "$TOOL" = diab ] && dot_boot_text="
  .boot $bind(wrs_kernel_text_start + wrs_kernel_rom_size - 0x800) :
  {
  *(.boot)
  }
  .reset $bind(wrs_kernel_text_start + wrs_kernel_rom_size - 4) :
  {
  *(.reset)
  }
"

bind=""
if [ "$TOOL" = diab ]; then
bind=BIND
kseg0bss_text="
  /* if LMM_ENABLED == 0 then this GROUP is legacy mode.
   * legacy mode requires the .kseg0bss section be located at
   * (wrs_kernel_bss_end & 0xbfffffff).  the other sections in this
   * group are not defined for legacy mode so they will not be included
   * in the image
   *
   * if LMM_ENABLED != 0 then the GROUP should be
   * located at the address specified by _VX_START_EXCPT_BASE.
   */

  _VX_START_EXCPT_ADRS = LMM_ENABLED==0?wrs_kernel_bss_end & 0xbfffffff  :_VX_START_EXCPT_BASE;

  GROUP $bind(_VX_START_EXCPT_ADRS) :{
    wrs_unmapped_text_start = .;
    .vectors.text (TEXT) : {
      *(.vectors.text)
    }
    .unmapped.text (TEXT) : {
      *(.unmapped.text)
    }
    wrs_unmapped_text_end = .;
    . = ((. + 31) & ~31);
    wrs_unmapped_data_start = .;
    .unmapped.data (DATA) : {
      wrs_unmapped_data_start = .;
      *(.unmapped.data)
    }
    wrs_unmapped_data_end = .;
    . = ((. + 15) & ~15);
    wrs_unmapped_bss_start = .;
    .kseg0bss (BSS) : {
      *(.kseg0bss)
    }
    wrs_unmapped_bss_end = .;
    . = ((. + 15) & ~15);
  }
"
kseg0bss_data="
  _VX_START_EXCPT_ADRS = wrs_kernel_bss_end & 0xbfffffff;
  GROUP $bind(_VX_START_EXCPT_ADRS) :
  {
    wrs_unmapped_text_start = .;
    .vectors.text (TEXT) : {
      *(.vectors.text)
    }
    .unmapped.text (TEXT) : {
      *(.unmapped.text)
    }
    wrs_unmapped_text_end = .;
    . = ((. + 31) & ~31);
    wrs_unmapped_data_start = .;
    .unmapped.data (DATA) : {
      wrs_unmapped_data_start = .;
      *(.unmapped.data)
    }
    wrs_unmapped_data_end = .;
    . = ((. + 15) & ~15);
    wrs_unmapped_bss_start = .;
    .kseg0bss (BSS) : {
      *(.kseg0bss)
    }
    wrs_unmapped_bss_end = .;
    . = ((. + 15) & ~15);
  }
"
wrs_kernel_text_start="wrs_kernel_text_start = .; _wrs_kernel_text_start = .;
      *(.text)"
fi

bind=""
if [ "$TOOL" = gnu ]; then
bind=BIND
kseg0bss_text="
  /* if LMM_ENABLED == 0 then this GROUP is legacy mode.
   * legacy mode requires the .kseg0bss section be located at
   * (wrs_kernel_bss_end & 0xbfffffff).  the other sections in this
   * group are not defined for legacy mode so they will not be included
   * in the image
   *
   * if LMM_ENABLED != 1 then the GROUP should be
   * located at the address specified by _VX_START_EXCPT_BASE.  this
   * is a large memory model configuration
   */

  _VX_START_EXCPT_ADRS = LMM_ENABLED==0?wrs_kernel_bss_end & 0xbfffffff :_VX_START_EXCPT_BASE;

  /* unmapped data and text sections */
  .vectors.text _VX_START_EXCPT_ADRS :
  {
      wrs_unmapped_text_start = .;
      *(.vectors.text)
      *(.unmapped.text)
      wrs_unmapped_text_end = .;
      . = ALIGN(32);
  }

  .unmapped.data     :
  {
      wrs_unmapped_data_start = .;
      *(.unmapped.data)
      wrs_unmapped_data_end = .;
      . = ALIGN(32);
  }

  .kseg0bss      :
  {
      wrs_unmapped_bss_start = .;
      *(.kseg0bss)
      . = ALIGN(32);
      wrs_unmapped_bss_end = .;
  }
"
kseg0bss_data="
  _VX_START_EXCPT_ADRS = wrs_kernel_bss_end & 0xbfffffff;

  /* unmapped data and text sections */
  .vectors.text _VX_START_EXCPT_ADRS :
  {
      wrs_unmapped_text_start = .;
      *(.vectors.text)
      *(.unmapped.text)
      wrs_unmapped_text_end = .;
      . = ALIGN(32);
  }

  .unmapped.data     :
  {
      wrs_unmapped_data_start = .;
      *(.unmapped.data)
      wrs_unmapped_data_end = .;
      . = ALIGN(32);
  }

  .kseg0bss      :
  {
      wrs_unmapped_bss_start = .;
      *(.kseg0bss)
      . = ALIGN(32);
      wrs_unmapped_bss_end = .;
  }
"
wrs_kernel_text_start="wrs_kernel_text_start = ABSOLUTE(.); _wrs_kernel_text_start = ABSOLUTE(.);
  _VX_START_TEXT = .;
    *(.text)"
fi

diab_data_group_text="  }
  GROUP BIND(_VX_START_DATA) : {"

diab_data_group_aligned="  }
  GROUP BIND((etext + _VX_DATA_ALIGN - 1) & -_VX_DATA_ALIGN) : {"

gnu_data_group_aligned="  . = ALIGN(_VX_DATA_ALIGN);"

named_debug_sections="
  /* Stabs debugging sections.  */
  .stab 0 : { *(.stab) }
  .stabstr 0 : { *(.stabstr) }
  .stab.excl 0 : { *(.stab.excl) }
  .stab.exclstr 0 : { *(.stab.exclstr) }
  .stab.index 0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment 0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }"

rom_at=""
dot_boot=""
kseg0bss=""
gnu_data_group=""
diab_data_group=""

zero=""
if [ "$TOOL" = diab ]; then
wrs_kernel_text_fast="wrs_kernel_text_fast = .; _wrs_kernel_text_fast = .;"
wrs_kernel_text_init="wrs_kernel_text_init = .; _wrs_kernel_text_init = .;"
wrs_kernel_text_end="wrs_kernel_text_end = .; _wrs_kernel_text_end = .;"
else
wrs_kernel_text_fast="wrs_kernel_text_fast = ABSOLUTE(.); _wrs_kernel_text_fast = ABSOLUTE(.);"
wrs_kernel_text_init="wrs_kernel_text_init = ABSOLUTE(.); _wrs_kernel_text_init = ABSOLUTE(.);"
wrs_kernel_text_end="wrs_kernel_text_end = ABSOLUTE(.); _wrs_kernel_text_end = ABSOLUTE(.);"
fi
etext="etext = .; _etext = .;"
wrs_kernel_copy_text=""
wrs_kernel_data_start="wrs_kernel_data_start = .; _wrs_kernel_data_start = .;"
wrs_kernel_data_fast="wrs_kernel_data_fast = .; _wrs_kernel_data_fast = .;"
wrs_kernel_data_init="wrs_kernel_data_init = .; _wrs_kernel_data_init = .;"
wrs_kernel_data_end="wrs_kernel_data_end = .; _wrs_kernel_data_end = .;"
edata="edata = .; _edata = .;"
wrs_kernel_bss_start="wrs_kernel_bss_start = .; _wrs_kernel_bss_start = .;"
wrs_kernel_bss_end="wrs_kernel_bss_end = .; _wrs_kernel_bss_end = .;"
wrs_kernel_tls_data_start="wrs_kernel_tls_data_start = .; _wrs_kernel_tls_data_start = .;"
wrs_kernel_tls_data_size="wrs_kernel_tls_data_size = . - wrs_kernel_tls_data_start; _wrs_kernel_tls_data_size = . - _wrs_kernel_tls_data_start;"
if [ "$TOOL" = diab ]; then
wrs_kernel_tls_data_align="wrs_kernel_tls_data_align = ALIGNOF(.tls_data); _wrs_kernel_tls_data_align = ALIGNOF(.tls_data);"
wrs_kernel_tls_vars_align=". = ((. + 7) & ~7);"
else
wrs_kernel_tls_data_align="wrs_kernel_tls_data_align = 16; _wrs_kernel_tls_data_align = 16;"
wrs_kernel_tls_vars_align=". = ALIGN(8);"
fi
wrs_kernel_tls_vars_start="wrs_kernel_tls_vars_start = .; _wrs_kernel_tls_vars_start = .;"
if [ "$TOOL" = diab ]; then
wrs_kernel_tls_vars_size="wrs_kernel_tls_vars_size = RAWSIZEOF(.tls_vars); _wrs_kernel_tls_vars_size = RAWSIZEOF(.tls_vars);"
else
wrs_kernel_tls_vars_size="wrs_kernel_tls_vars_size = SIZEOF(.tls_vars); _wrs_kernel_tls_vars_size = SIZEOF(.tls_vars);"
fi
end="end = .; _end = .;"

gp_mips_diab="_gp = ((. + $am1) & ~$am1) + 0x7ff0;"
gp_mips_gnu="_gp = ALIGN(16) + 0x7ff0;		/* set gp for MIPS startup code */"

wrs_gnu_stub_warn="*(.text.*) *(.stub) *(.gnu.warning) *(.gnu.linkonce.t*)";
sec_align_diab=". = ((. + 3) & ~3);"
sec_align_gnu=". = ALIGN($align);"
end_align_diab="$sec_align_diab"
end_align_gnu="$sec_align_gnu"
kseg0bss_align_diab=". = ((. + 255) & ~255);"
kseg0bss_align_gnu=". = ALIGN(256);"
mips_lmm_enabled=""
dot_text_begin=".text      :
  {"
wrs_text_wired=""
mips_end="
    /* add sizeof .kseg0bss to end and _end if it follows .bss section */
    endAdd = LMM_ENABLED == 0 ? SIZEOF(.kseg0bss) : 0x0;
    end = . + endAdd; _end = . + endAdd;"


is_rom=false
is_mips=false
is_armarch4=false

rom_section_at()
{
    if $is_rom && [ "$TOOL" = diab ]; then
	echo " AT(etext + ADDR($1) - ADDR(.data))"
    fi
}

for arg
do
    case "$arg" in
	AOUT)		named_debug_sections=""				;;
	ROM)		diab_data_group="$diab_data_group_text"		;
			if [ "$kseg0bss" != "" ]; then
			    kseg0bss="$kseg0bss_data"
			fi
			is_rom=true					;
			rom_at=" AT(etext)"				;;
	RAM)		gnu_data_group="$gnu_data_group_aligned"	;
			diab_data_group="$diab_data_group_aligned"	;;
	DOTBOOT)	dot_boot="$dot_boot_text"			;;
	ARMARCH4)       is_armarch4=true                                ;;
	MIPS)		kseg0bss="$kseg0bss_text"			;
			wrs_kernel_text_start="wrs_kernel_text_start = .; _wrs_kernel_text_start = .;" ;
			end_align_gnu="$kseg0bss_align_gnu"		;
			end_align_diab="$kseg0bss_align_diab"		;
			sdabase_mips_diab="_SDA_BASE_ = _gp;"		;
			dot_text_begin=""				;
			wrs_text_wired="*(.text.romentry)
      *(.text.wired)
      *(.text)"			;
			is_mips=true                                    ;
			end="$mips_end"					;;
	OUT)            zero="0"
			dot_text_begin=".text     0 :
  {"
			wrs_kernel_text_start="_VX_START_TEXT = .;
    *(.text)"
			wrs_kernel_text_fast=""
			wrs_kernel_text_init=""
			wrs_kernel_text_end=""
			etext=""
			wrs_kernel_data_start=""
			wrs_kernel_data_fast=""
			wrs_kernel_data_init=""
			wrs_kernel_data_end=""
			edata=""
			wrs_kernel_bss_start=""
			wrs_kernel_bss_end=""
			end=""
			gp_mips_gnu=""
			gp_mips_diab=""
			sec_align_gnu=""
			sec_align_diab=""
			end_align_gnu=""
			end_align_diab=""
			wrs_kernel_tls_vars_size=""
			wrs_kernel_tls_vars_start=""
			wrs_kernel_tls_data_align=""
			wrs_kernel_tls_data_size=""
			wrs_kernel_tls_data_start=""
			;;
	*)		echo "$0: '$arg' unknown." 1>&2	;	exit 1	;;
    esac
done
if [ "$is_rom" = true ] && [ "$is_armarch4" = true ]; then
	wrs_kernel_copy_text="wrs_kernel_copy_text_start = .;
      *(.copy.text)
      wrs_kernel_copy_text_end = .;
      *(.inflate.text)"                         
fi
if [ "$is_rom" = true ] && [ "$is_mips" = true ]; then
	mips_lmm_enabled="LMM_ENABLED = 0;"		;
	wrs_kernel_copy_text="wrs_kernel_copy_text_start = .;
      *(.copy.text)
      wrs_kernel_copy_text_end = .;
      *(.inflate.text)"                         
	wrs_gnu_stub_warn="*(.text.*) *(.stub) *(.gnu.warning) *(.gnu.linkonce.t*)";
	if [ "$TOOL" = gnu ]; then
		wrs_text_wired=".text     :
  {
    wrs_kernel_text_start = ABSOLUTE(.); _wrs_kernel_text_start = ABSOLUTE(.);
    _VX_START_TEXT = .;
    *(.text.romentry)
    *(.text)
    *(.text.wired)"		;
		wrs_kernel_text_start="" ;
	else
		wrs_text_wired="*(.text.romentry)
      *(.text)
      *(.text.wired)"
		wrs_kernel_text_start="wrs_kernel_text_start = ABSOLUTE(.); _wrs_kernel_text_start = ABSOLUTE(.);" ;
	fi
fi
if [ "$is_rom" = false ] && [ "$is_mips" = true ] && [ "$TOOL" = gnu ]; then
	wrs_text_wired="wrs_kernel_text_wired_size = 0;
  .text     :
  {
    wrs_kernel_text_wired_start = .;
    *(.text.romentry)
    *(.text.wired)
    wrs_kernel_text_wired_end = .;
    wrs_kernel_text_wired_size = SIZEOF(.text);
  }"			;
	wrs_kernel_text_start=".text      :
  {
    _VX_START_TEXT = wrs_kernel_text_wired_size == 0 ? . : wrs_kernel_text_wired_start;
    wrs_kernel_text_start = _VX_START_TEXT;
    _wrs_kernel_text_start = _VX_START_TEXT;
    *(.text)" ;
	wrs_gnu_stub_warn="*(.stub) *(.gnu.warning) *(.gnu.linkonce.t*)";
fi
cat <<EOF
/* $filename - $TOOL linker command file for VxWorks: $style */

/* Copyright 2001-2014 Wind River Systems, Inc. */

/* This file was automatically generated using tool/common/ldscripts. */

EOF

mod_history

if [ "$TOOL" = diab ]; then
cat <<EOF
SECTIONS {
  $mips_lmm_enabled
  GROUP BIND(_VX_START_TEXT) : {
    .text (TEXT) : {
      $wrs_kernel_text_start
      $wrs_text_wired
      $wrs_kernel_text_fast
      *(.text.fast)
      $wrs_kernel_text_init
      *(.text.init)
      *(.rdata) *(.rodata) *(.rodata.cst16) *(.rodata.cst8) *(.rodata.cst4) *(.rodata.str1.1) *(.rodata.str1.2) *(.rodata.str1.4) *(.rodata.str1.8) *(.rodata.str1.16) *(.rodata.str1.32) *(.rodata.str1.64) *(.rodata.str1.128) *(.rodata.str1.256)
      *(.init) *(.fini)
      *(.frame_info)
      $sec_align_diab
    }
    .wrs_build_vars (CONST) : {
      *(.wrs_build_vars)
      $sec_align_diab
    }
    .sdata2 (TEXT) : {
      *(.sdata2)
      $sec_align_diab
    }
    $sec_align_diab
    $etext
    $wrs_kernel_text_end
$diab_data_group
    .data (DATA)$rom_at : {
      $wrs_kernel_copy_text
      $wrs_kernel_data_start
      *(.data)
      $wrs_kernel_data_fast
      *(.data.fast)
      $wrs_kernel_data_init
      *(.data.init)
      *(.eh_frame)	/* Some GNU objects insist on having .eh_frame data. */
      *(.ctors)
      *(.dtors)
      *(.got2)
      $sec_align_diab
    }
    $wrs_kernel_tls_data_start
    .tls_data (DATA)`rom_section_at .tls_data` : {
      *(.tls_data)
    }
    $wrs_kernel_tls_data_size
    $wrs_kernel_tls_data_align
    $wrs_kernel_tls_vars_align
    $wrs_kernel_tls_vars_start
    .tls_vars (DATA)`rom_section_at .tls_vars` : {
      *(.tls_vars)
    }
    $wrs_kernel_tls_vars_size
    $sec_align_diab
    /* set gp for MIPS startup code */
    $gp_mips_diab
    $sdabase_mips_diab
    .sdata (DATA)`rom_section_at .sdata`  : {
      *(.sdata)
      $sec_align_diab
    }
    $sec_align_diab
    $edata
    $wrs_kernel_data_end
    .sbss (BSS)`rom_section_at .sbss` : {
      $wrs_kernel_bss_start
      *(.sbss)
      $sec_align_diab
    }
    .bss (BSS)`rom_section_at .bss` : {
      *(.bss)
      $sec_align_diab
    }
    $end_align_diab
    $end
    $wrs_kernel_bss_end
  }
$kseg0bss$dot_boot}
EOF
else
# presume $TOOL = gnu
cat <<EOF
ENTRY(_start)
SECTIONS
{
    $mips_lmm_enabled
    $dot_text_begin
    $wrs_text_wired
    $wrs_kernel_text_start
    $wrs_kernel_text_fast
    *(.text.fast)
    $wrs_kernel_text_init
    *(.text.init)
    $wrs_gnu_stub_warn
    KEEP(*(.init)) KEEP(*(.fini))
    *(.glue_7t) *(.glue_7) *(.rdata)			/* for ARM */
    *(.mips16.fn.*) *(.mips16.call.*) *(.reginfo)	/* for MIPS */
    *(.rodata) *(.rodata.*) *(.gnu.linkonce.r*) *(.rodata1)
    $sec_align_gnu
    . = ALIGN (8);
    *(.eh_frame_hdr)
    . = ALIGN (8);
    __EH_FRAME_BEGIN__ = .;
    KEEP (*(.eh_frame))
    LONG (0)
    . = ALIGN (8);
    *(.gcc_except_table .gcc_except_table.*)
  }
  .wrs_build_vars $zero : {
    *(.wrs_build_vars)
    $sec_align_gnu
  }
  .sdata2     $zero : {
    _SDA2_BASE_ = . + 0x7ff0 ;
    *(.sdata2) *(.sbss2)				/* for PPC */
    $sec_align_gnu
  }
  $sec_align_gnu
  $wrs_kernel_text_end
  $etext
$gnu_data_group
  .data   $zero :$rom_at
  {
    $wrs_kernel_copy_text
    $wrs_kernel_data_start
    _VX_START_DATA = .;
    *(.data)
    $wrs_kernel_data_fast
    *(.data.fast)
    $wrs_kernel_data_init
    *(.data.init)
    *(.data.*) *(.gnu.linkonce.d*) SORT(CONSTRUCTORS) *(.data1)
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    /* got*, dynamic, sdata*, lit[48], and sbss should follow _gp */
    *(.got.plt) *(.got) *(.dynamic)
    *(.got2)
    *(.lit8) *(.lit4)
    $sec_align_gnu
  }
  $wrs_kernel_tls_data_start
  .tls_data    $zero : {
    *(.tls_data)
  }
  $wrs_kernel_tls_data_size
  $wrs_kernel_tls_data_align
  $wrs_kernel_tls_vars_align
  $wrs_kernel_tls_vars_start
  .tls_vars    $zero : {
    *(.tls_vars)
  }
  $wrs_kernel_tls_vars_size
  $sec_align_gnu
  $gp_mips_gnu
  .sdata    $zero :
  {
    _SDA_BASE_ = . + 0x7ff0 ;
    *(.sdata) *(.sdata.*) *(.gnu.linkonce.s.*)
    $sec_align_gnu
  }
  $sec_align_gnu
  $edata
  $wrs_kernel_data_end
  .sbss     $zero :
  {
    $wrs_kernel_bss_start
    *(.sbss) *(.sbss.*) *(.scommon) 
    $sec_align_gnu
  }
  .bss     $zero  :
  {
    *(.dynbss) *(.bss) *(.bss.*) *(COMMON) *(.gnu.linkonce.b*)
    $sec_align_gnu
  }
  $end_align_gnu
  $end
  $wrs_kernel_bss_end
$kseg0bss$dot_boot
  /DISCARD/ :
  {
  *(.note)				/* seen on Pentium ELF */
  *(.comment)				/* seen on PPC & SH ELF */
  *(.pdr)				/* seen on MIPS ELF */
  }$named_debug_sections
}
EOF
fi
