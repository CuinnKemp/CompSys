// File name: Decode.tst

load Decode.hdl,
output-file Decode.out,
compare-to Decode.cmp,
output-list in%B1.16.1 type%B3.1.3 a%B3.1.3 c1%B3.1.3 c2%B3.1.3 c3%B3.1.3 c4%B3.1.3 c5%B3.1.3 c6%B3.1.3 d1%B3.1.3 d2%B3.1.3 d3%B3.1.3 j1%B3.1.3 j2%B3.1.3 j3%B3.1.3;

set in %B0000000000000000,
eval,
output;

set in %B0111111111111111,
eval,
output;

set in %B1000000000000000,
eval,
output;

set in %B1111111111111111,
eval,
output;

set in %B1110101010101010,
eval,
output;

set in %B1111010101010101,
eval,
output;