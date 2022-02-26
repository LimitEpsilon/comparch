package dinocpu
import chisel3._
import chisel3.util._

class SimpleAdder extends Module{
  val io = IO (new Bundle{
    val inputx = Input(UInt(32.W))
    val inputy = Input(UInt(32.W))
    val output = Output(UInt(32.W))
  })
  io.output := io.inputx + io.inputy
}
class SimpleSystem extends Module{
  val io = IO (new Bundle{
    val success = Output(Bool())
  })
  val adder1 = Module(new SimpleAdder)
  val adder2 = Module(new SimpleAdder)
  val reg1 = RegInit(1.U(32.W))
  val reg2 = RegInit(0.U(32.W))

  adder1.io.inputx := reg1
  adder1.io.inputy := reg2
  reg1 := adder1.io.output

  adder2.io.inputx := adder1.io.output
  adder2.io.inputy := 3.U(32.W)
  reg2 := adder2.io.output

  when (adder2.io.output === 128.U) {
    io.success := true.B
  } .otherwise {
    io.success := false.B
  }
  printf(p"reg1: $reg1, reg2: $reg2, success: ${io.success}\n")
}
