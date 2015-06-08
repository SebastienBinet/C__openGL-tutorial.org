#!/bin/sh
bindir=$(pwd)
cd /Users/seb/GitHub/opengl-tutorial-org/misc05_picking/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/seb/GitHub/opengl-tutorial-org/builds/Debug/misc05_picking_custom 
	else
		"/Users/seb/GitHub/opengl-tutorial-org/builds/Debug/misc05_picking_custom"  
	fi
else
	"/Users/seb/GitHub/opengl-tutorial-org/builds/Debug/misc05_picking_custom"  
fi
