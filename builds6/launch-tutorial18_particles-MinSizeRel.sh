#!/bin/sh
bindir=$(pwd)
cd /Users/seb/GitHub/opengl-tutorial-org/tutorial18_billboards_and_particles/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/seb/GitHub/opengl-tutorial-org/builds6/MinSizeRel/tutorial18_particles 
	else
		"/Users/seb/GitHub/opengl-tutorial-org/builds6/MinSizeRel/tutorial18_particles"  
	fi
else
	"/Users/seb/GitHub/opengl-tutorial-org/builds6/MinSizeRel/tutorial18_particles"  
fi
