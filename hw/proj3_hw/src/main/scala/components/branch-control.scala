// Control logic for whether branches are taken or not

package dinocpu

import chisel3._
import chisel3.util._

/**
 * Controls whether or not branches are taken.
 *
 * Input:  branch, true if we are looking at a branch
 * Input:  funct3, the middle three bits of the instruction (12-14). Specifies the
 *         type of branch
 * Input:  inputx, first value (e.g., reg1)
 * Input:  inputy, second value (e.g., reg2)
 * Output: taken, true if the branch is taken.
 */
class BranchControl extends Module {
  val io = IO(new Bundle {
    val branch = Input(Bool())
    val funct3 = Input(UInt(3.W))
    val inputx = Input(UInt(32.W))
    val inputy = Input(UInt(32.W))

    val taken  = Output(Bool())
  })
  io.taken := false.B
  switch(io.funct3) {
    is(0.U){ //beq
      io.taken := io.branch & (io.inputx === io.inputy)
    }
    is(1.U){ //bne
      io.taken := io.branch & (io.inputx =/= io.inputy)
    }
    is(4.U){ //blt
      io.taken := io.branch & (io.inputx.asSInt < io.inputy.asSInt)
    }
    is(5.U){ //bge
      io.taken := io.branch & (io.inputx.asSInt >= io.inputy.asSInt)
    }
    is(6.U){ //bltu
      io.taken := io.branch & (io.inputx < io.inputy)
    }
    is(7.U){ //bgeu
      io.taken := io.branch & (io.inputx >= io.inputy)
    }
  }

}
