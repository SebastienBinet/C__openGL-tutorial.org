#!/bin/sh
bindir=$(pwd)
cd /Users/seb/GitHub/opengl-tutorial-org/tutorial11_2d_fonts/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/seb/GitHub/opengl-tutorial-org/builds3/RelWithDebInfo/tutorial11_2d_fonts 
	else
		"/Users/seb/GitHub/opengl-tutorial-org/builds3/RelWithDebInfo/tutorial11_2d_fonts"  
	fi
else
	"/Users/seb/GitHub/opengl-tutorial-org/builds3/RelWithDebInfo/tutorial11_2d_fonts"  
fi
