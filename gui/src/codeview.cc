/*
 *  mcy-gui -- Mutation Cover with Yosys GUI
 *
 *  Copyright (C) 2019  Miodrag Milanovic <miodrag@symbioticeda.com>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include "codeview.h"
#include "ScintillaEdit.h"
#include "SciLexer.h"
#include <QFontDatabase>

CodeView::CodeView(QString filename, QWidget *parent) : filename(filename), ScintillaEdit(parent)
{
}

CodeView::~CodeView() {}

static const char *verilog_instre1 = "always and assign attribute begin buf bufif0 bufif1 case casex casez cmos deassign default defparam disable edge else end endattribute endcase endfunction endmodule endprimitive endspecify endtable endtask event for force forever fork function highz0 highz1 if ifnone initial inout input integer join medium module large localparam macromodule nand negedge nmos nor not notif0 notif1 or output parameter pmos posedge primitive pull0 pull1 pulldown pullup rcmos real realtime reg release repeat rnmos rpmos rtran rtranif0 rtranif1 scalared signed small specify specparam strength strong0 strong1 supply0 supply1 table task time tran tranif0 tranif1 tri tri0 tri1 triand trior trireg unsigned vectored wait wand weak0 weak1 while wire wor xnor xor alias always_comb always_ff always_latch assert assume automatic before bind bins binsof break constraint context continue cover cross design dist do expect export extends extern final first_match foreach forkjoin iff ignore_bins illegal_bins import incdir include inside instance intersect join_any join_none liblist library matches modport new noshowcancelled null packed priority protected pulsestyle_onevent pulsestyle_ondetect pure rand randc randcase randsequence ref return showcancelled solve tagged this throughout timeprecision timeunit unique unique0 use wait_order wildcard with within class clocking config generate covergroup interface package program property sequence endclass endclocking endconfig endgenerate endgroup endinterface endpackage endprogram endproperty endsequence bit byte cell chandle const coverpoint enum genvar int local logic longint shortint shortreal static string struct super type typedef union var virtual void";
static const char *verilog_instre2 = "SYNTHESIS $assertkill $assertoff $asserton $bits $bitstoreal $bitstoshortreal $cast $comment $countdrivers $countones $dimensions $display $dist_chi_square $dist_erlang $dist_exponential $dist_normal $dist_poisson $dist_t $dist_uniform $dumpall $dumpfile $dumpflush $dumplimit $dumpoff $dumpon $dumpvars $error $exit $fatal $fclose $fdisplay $fell $feof $ferror $fflush $fgetc $fgets $finish $fmonitor $fopen $fread $fscanf $fseek $fstrobe $ftell $fullskew $fwrite $get_coverage $getpattern $high $history $hold $increment $incsave $info $input $isunbounded $isunknown $itor $key $left $list $load_coverage_db $log $low $monitor $monitoroff $monitoron $nochange $nokey $nolog $onehot $onehot0 $past $period $printtimescale $q_add $q_exam $q_full $q_initialize $q_remove $random $readmemb $readmemh $realtime $realtobits $recovery $recrem $removal $reset $reset_count $reset_value $restart $rewind $right $root $rose $rtoi $sampled $save $scale $scope $set_coverage_db_name $setup $setuphold $sformat $shortrealtobits $showscopes $showvariables $showvars $signed $size $skew $sreadmemb $sreadmemh $sscanf $stable $stime $stop $strobe $swrite $time $timeformat $timescale $timeskew $typename $typeof $uandom $ungetc $unit $unpacked_dimensions $unsigned $upscope $urandom_range $value$plusargs $var $vcdclose $version $warning $width $write";

static const char *MonospaceFont()
{
	static char fontNameDefault[200] = "";
	if (!fontNameDefault[0]) {
        const QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
		strcpy(fontNameDefault, font.family().toUtf8());
	}
	return fontNameDefault;
}
void CodeView::loadContent(const char *content)
{
    styleSetFont(STYLE_DEFAULT, MonospaceFont());    
    setScrollWidth(200);
    setScrollWidthTracking(1);
    setUndoCollection(false);
    setMarginWidthN(0, 40); // Line number
    setLexer(SCLEX_VERILOG);            
    setKeyWords(0, verilog_instre1);
    setKeyWords(1, verilog_instre2);
    styleSetFore(SCE_V_DEFAULT,         0x000000);
    styleSetFore(SCE_V_COMMENT,         0x008000);
    styleSetFore(SCE_V_COMMENTLINE,     0x008000);
    styleSetFore(SCE_V_COMMENTLINEBANG, 0x008080);
    styleSetFore(SCE_V_NUMBER,          0xFF8000);
    styleSetFore(SCE_V_WORD,            0x8000FF);
    styleSetFore(SCE_V_STRING,          0x808080);
    styleSetFore(SCE_V_WORD2,           0x8000FF);
    styleSetFore(SCE_V_WORD3,           0x8000FF);
    styleSetFore(SCE_V_PREPROCESSOR,    0x804000);
    styleSetFore(SCE_V_OPERATOR,        0x000080);
    styleSetFore(SCE_V_IDENTIFIER,      0x000000);
    styleSetFore(SCE_V_STRINGEOL,       0x808080);
    styleSetFore(SCE_V_USER,            0x000000);
    styleSetFore(SCE_V_COMMENT_WORD,    0x008000);
    styleSetFore(SCE_V_INPUT,           0x000000);
    styleSetFore(SCE_V_OUTPUT,          0x000000);
    styleSetFore(SCE_V_INOUT,           0x000000);
    styleSetFore(SCE_V_PORT_CONNECT,    0x000000);
    
    setText(content);
    setSavePoint();
    gotoPos(0);
    setReadOnly(true);
}