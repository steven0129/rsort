#!/bin/bash
perf record -o perf.data.rec.bubble_sort --call-graph dwarf ./a.out -a bubble_sort ettoday_origin.txt > bubble_sort.rec.log
perf record -o perf.data.rec.insertion_sort --call-graph dwarf ./a.out -a insertion_sort ettoday_origin.txt > insertion_sort.rec.log
perf record -o perf.data.rec.selection_sort --call-graph dwarf ./a.out -a selection_sort ettoday_origin.txt > selection_sort.rec.log
perf record -o perf.data.rec.merge_sort --call-graph dwarf ./a.out -a merge_sort ettoday_origin.txt > merge_sort.rec.log
perf record -o perf.data.rec.heap_sort --call-graph dwarf ./a.out -a heap_sort ettoday_origin.txt > heap_sort.rec.log
perf record -o perf.data.rec.quick_sort --call-graph dwarf ./a.out -a quick_sort ettoday_origin.txt > quick_sort.rec.log