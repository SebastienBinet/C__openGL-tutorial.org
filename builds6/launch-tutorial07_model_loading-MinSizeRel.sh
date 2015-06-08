#!/bin/sh
bindir=$(pwd)
cd /Users/seb/GitHub/opengl-tutorial-org/tutorial07_model_loading/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/seb/GitHub/opengl-tutorial-org/builds6/MinSizeRel/tutorial07_model_loading 
	else
		"/Users/seb/GitHub/opengl-tutorial-org/builds6/MinSizeRel/tutorial07_model_loading"  
	fi
else
	"/Users/seb/GitHub/opengl-tutorial-org/builds6/MinSizeRel/tutorial07_model_loading"  
fi
