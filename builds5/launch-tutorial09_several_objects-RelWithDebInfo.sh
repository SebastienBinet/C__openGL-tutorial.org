#!/bin/sh
bindir=$(pwd)
cd /Users/seb/GitHub/opengl-tutorial-org/tutorial09_vbo_indexing/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/seb/GitHub/opengl-tutorial-org/builds5/RelWithDebInfo/tutorial09_several_objects 
	else
		"/Users/seb/GitHub/opengl-tutorial-org/builds5/RelWithDebInfo/tutorial09_several_objects"  
	fi
else
	"/Users/seb/GitHub/opengl-tutorial-org/builds5/RelWithDebInfo/tutorial09_several_objects"  
fi
