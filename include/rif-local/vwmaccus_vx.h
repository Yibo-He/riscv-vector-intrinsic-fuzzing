// vwmaccus.vx vd, vs2, rs1
VI_CHECK_DSS(false);
VI_VX_MUL_ADD_LOOP_WIDEN
({
  VI_WIDE_OP_AND_ASSIGN_MIX(vs2, rs1, vd_w, *, +, int, int, uint);
})