#!/bin/sh
bindir=$(pwd)
cd /Users/seb/GitHub/opengl-tutorial-org/tutorial02_red_triangle/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/seb/GitHub/opengl-tutorial-org/builds4/MinSizeRel/tutorial02_red_triangle 
	else
		"/Users/seb/GitHub/opengl-tutorial-org/builds4/MinSizeRel/tutorial02_red_triangle"  
	fi
else
	"/Users/seb/GitHub/opengl-tutorial-org/builds4/MinSizeRel/tutorial02_red_triangle"  
fi
