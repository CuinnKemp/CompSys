// File name: And16Way.tst

load And16Way.hdl,
output-file And16Way.out,
compare-to And16Way.cmp,
output-list in%B2.16.2 out%B2.1.2;

set in %B0000000000000000,
eval,
output;

set in %B1111111111111111,
eval,
output;

set in %B0001000000000000,
eval,
output;

set in %B0000000000000001,
eval,
output;

set in %B0010011000100110,
eval,
output;