#!/bin/sh
bindir=$(pwd)
cd /Users/seb/GitHub/opengl-tutorial-org/misc05_picking/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/seb/GitHub/opengl-tutorial-org/builds2/Release/misc05_picking_BulletPhysics 
	else
		"/Users/seb/GitHub/opengl-tutorial-org/builds2/Release/misc05_picking_BulletPhysics"  
	fi
else
	"/Users/seb/GitHub/opengl-tutorial-org/builds2/Release/misc05_picking_BulletPhysics"  
fi
