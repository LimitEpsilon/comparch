// This file contains ALU control logic.

package dinocpu

import chisel3._
import chisel3.util._

/**
 * The ALU control unit
 *
 * Input:  add, if true, add no matter what the other bits are
 * Input:  immediate, if true, ignore funct7 when computing the operation
 * Input:  funct7, the most significant bits of the instruction
 * Input:  funct3, the middle three bits of the instruction (12-14)
 * Output: operation, What we want the ALU to do.
 *
 * For more information, see Section 4.4 and A.5 of Patterson and Hennessy.
 * This is loosely based on figure 4.12
 */
class ALUControl extends Module {
  val io = IO(new Bundle {
    val add       = Input(Bool())
    val immediate = Input(Bool())
    val funct7    = Input(UInt(7.W))
    val funct3    = Input(UInt(3.W))

    val operation = Output(UInt(4.W))
  })

  // Do not modify 
  io.operation := 15.U // invalid operation

  // Your code goes here
  when (io.add === true.B){
    io.operation := 2.U
  } .otherwise {
    //need to see funct7 and funct7 asserted
    when (io.immediate === false.B && io.funct7(5) === 1.U){
      switch (io.funct3){        
        is (0.U) {io.operation := 3.U}
        is (5.U) {io.operation := 8.U}
      }
    } .otherwise{
        switch (io.funct3){
          is (0.U) {io.operation := 2.U}
          is (1.U) {io.operation := 6.U}
          is (2.U) {io.operation := 4.U}
          is (3.U) {io.operation := 5.U}
          is (4.U) {io.operation := 9.U}
          is (5.U) {io.operation := 7.U}
          is (6.U) {io.operation := 1.U}
          is (7.U) {io.operation := 0.U}
        }
    }
  } 
}

