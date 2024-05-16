#!/bin/bash
TRACE_DIR=/sys/kernel/debug/tracing
TARGET=matrix_ioctl

# clear file
echo 0 > $TRACE_DIR/tracing_on 
echo > $TRACE_DIR/set_graph_function 
echo > $TRACE_DIR/set_ftrace_filter 
echo nop > $TRACE_DIR/current_tracer 
echo > $TRACE_DIR/trace

# settings
echo function_graph > $TRACE_DIR/current_tracer 
echo 3 > $TRACE_DIR/max_graph_depth
echo $TARGET > $TRACE_DIR/set_graph_function

# execute
echo 1 > $TRACE_DIR/tracing_on
../users
echo 0 > $TRACE_DIR/tracing_on

# output file
cat $TRACE_DIR/trace > trace.txt
