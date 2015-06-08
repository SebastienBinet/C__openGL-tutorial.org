#!/bin/sh
bindir=$(pwd)
cd /Users/seb/GitHub/opengl-tutorial-org/tutorial04_colored_cube/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/seb/GitHub/opengl-tutorial-org/builds/MinSizeRel/tutorial04_colored_cube 
	else
		"/Users/seb/GitHub/opengl-tutorial-org/builds/MinSizeRel/tutorial04_colored_cube"  
	fi
else
	"/Users/seb/GitHub/opengl-tutorial-org/builds/MinSizeRel/tutorial04_colored_cube"  
fi
