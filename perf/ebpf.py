#!/usr/bin/env python3
import subprocess
from bcc import BPF

code = """
#include <uapi/linux/ptrace.h>

BPF_HASH(start, u64);

int BPF_kprobe(struct pt_regs *ctx)
{
	u64 ts = bpf_ktime_get_ns();
	bpf_trace_printk("in %llu\\n",ts);
	return 0;
}

int BPF_kretprobe(struct pt_regs *ctx)
{
	u64 ts = bpf_ktime_get_ns();
	bpf_trace_printk("out %llu\\n",ts);
	return 0;
}
"""

b = BPF(text=code)
b.attach_kprobe(event="worker_thread", fn_name="BPF_kprobe")
b.attach_kretprobe(event="worker_thread", fn_name="BPF_kretprobe")

count = 0

with open("out.txt", "w") as f:
	while True:
			in_res = b.trace_fields()
			in_res = in_res[5].decode()

			out_res = b.trace_fields()
			out_res = out_res[5].decode()

			print(in_res, out_res)
			delta = float(out_res[4:]) - float(in_res[3:])
			f.write(str(count) + " " + str(delta))
			f.write("\n")
			count += 1