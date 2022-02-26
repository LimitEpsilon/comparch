// This file contains the forwarding unit

package dinocpu

import chisel3._

/**
 * The Forwarding unit
 *
 * Input:  rs1, the register number for which the data is used in the execute stage
 * Input:  rs2, the register number for which the data is used in the execute stage
 * Input:  exmemrd, the destination register for the instruction in the mem stage
 * Input:  exmemrw, true if the instruction in the memory stage needs to write the register file
 * Input:  memwbrd, the destination register for the instruction in the writeback stage
 * Input:  memwbrw, true if the instruction in the writeback stage needs to write the register file
 *
 * Output: forwardA, 0, don't forward. 1, forward from mem stage. 2, forward from wb stage.
 *                   This is used for the "readdata1" forwarding
 * Output: forwardB, 0, don't forward. 1, forward from mem stage. 2, forward from wb stage.
 *                   This is used for the "readdata2" forwarding
 *
 * For more information, see Section 4.7 of Patterson and Hennessy
 * This follows figure 4.53
 */

class ForwardingUnit extends Module {
  val io = IO(new Bundle {
    val rs1     = Input(UInt(5.W))
    val rs2     = Input(UInt(5.W))
    val exmemrd = Input(UInt(5.W))
    val exmemrw = Input(Bool())
    val memwbrd = Input(UInt(5.W))
    val memwbrw = Input(Bool())

    val forwardA = Output(UInt(2.W))
    val forwardB = Output(UInt(2.W))
  })

  val A = Wire(UInt())
  val B = Wire(UInt())
  // set forward A
  when (io.exmemrw && (io.exmemrd === io.rs1)) { // forward the closest instruction. if the insn was ld, stalled anyways
    A := 1.U
  } .elsewhen (io.memwbrw && (io.memwbrd === io.rs1)) {
    A := 2.U
  } .otherwise {
    A := 0.U
  }
  io.forwardA := A
  // set forward B
  when (io.exmemrw && (io.exmemrd === io.rs2)) {
    B := 1.U
  } .elsewhen (io.memwbrw && (io.memwbrd === io.rs2)) {
    B := 2.U
  } .otherwise {
    B := 0.U
  }
  io.forwardB := B
}
