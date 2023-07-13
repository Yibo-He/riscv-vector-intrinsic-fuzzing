// COMMAND: random_gen -r Vloxei32V32VInt32VISIVU_TU -n 1 -l 7 --has-ta --has-ma -c Vloxei32V32VInt32VISIVU_TU.c --has-policy
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <riscv_vector.h>
typedef _Float16 float16_t;
typedef float float32_t;
typedef double float64_t;
#define isNaNF16UI( a ) (((~(a) & 0x7C00) == 0) && ((a) & 0x03FF))
#define isNaNF32UI( a ) (((~(a) & 0x7F800000) == 0) && ((a) & 0x007FFFFF))
#define isNaNF64UI( a ) (((~(a) & UINT64_C( 0x7FF0000000000000 )) == 0) && ((a) & UINT64_C( 0x000FFFFFFFFFFFFF )))
int32_t value_0[7];
int32_t value_1[7];
uint32_t value_2[7];
int32_t value_3[7];
void vinit_rif_operator_1() {
int32_t tmp[] = {-5545814,7892207,5457874,-1416993,2596108,-7225462,-5629682,};
for (int i=0; i<7;++i) {value_0[i] = tmp[i];
}
}
void vinit_rif_operator_3() {
uint32_t tmp[] = {3902764u,7500210u,4235251u,5592077u,5806864u,1786754u,3702157u,};
for (int i=0; i<7;++i) {value_2[i] = tmp[i];
}
}
void vinit_rif_operator_2() {
int32_t tmp[] = {2884331,8398813,1958398,1879014,2303187,-7353883,-734314,};
for (int i=0; i<7;++i) {value_1[i] = tmp[i];
}
}
void vloxei32_v_operator_0() {
int32_t *placeholder0 = value_0;
int32_t *placeholder1 = value_1;
uint32_t *placeholder2 = value_2;
int32_t *placeholder3 = value_3;
int placeholder4 = 7;

size_t placeholder5 = 0;
for (size_t vl; placeholder4 > 0; placeholder4 -= vl) {
vl = 2;
size_t tail_vl = 1;
vint32m1_t vec_value_0_0= vle32_v_i32m1(placeholder0, vl);
vuint32m1_t vec_value_2_0= vle32_v_u32m1(placeholder2, vl);
if (7 < 4294967295) {
vec_value_2_0 = vremu_vx_u32m1(vec_value_2_0, 7, vl);
}
vec_value_2_0 = vmul_vx_u32m1(vec_value_2_0, 4, vl);
vint32m1_t vec_value_3_0= vloxei32_v_i32m1_tu(vec_value_0_0, placeholder1, vec_value_2_0, tail_vl);
vse32_v_i32m1(placeholder3, vec_value_3_0, vl);
placeholder0 += vl;
placeholder2 += vl;
placeholder3 += vl;
}
}
int golden_vinit_rif_operator_1() {
return 1;
}
int golden_vinit_rif_operator_3() {
return 1;
}
int golden_vinit_rif_operator_2() {
return 1;
}
int golden_vloxei32_v_operator_0() {
int32_t tmp[] = {-7353883,7892207,-734314,-1416993,2884331,-7225462,2303187,};
for (int i=0; i<7;++i)
if(value_3[i] != tmp[i]) {
return 0;
}
return 1;
}
int main () {
vinit_rif_operator_1();
vinit_rif_operator_3();
vinit_rif_operator_2();
vloxei32_v_operator_0();
printf("operator_1 : %s\n", golden_vinit_rif_operator_1() ? "pass" : "fail");
printf("operator_3 : %s\n", golden_vinit_rif_operator_3() ? "pass" : "fail");
printf("operator_2 : %s\n", golden_vinit_rif_operator_2() ? "pass" : "fail");
printf("operator_0 : %s\n", golden_vloxei32_v_operator_0() ? "pass" : "fail");
int ret = 1; // 1 = success
ret &= golden_vinit_rif_operator_1();
ret &= golden_vinit_rif_operator_3();
ret &= golden_vinit_rif_operator_2();
ret &= golden_vloxei32_v_operator_0();
if (!ret) return 1;
return 0; }