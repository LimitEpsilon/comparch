;buildInfoPackage: chisel3, version: 3.2.4, scalaVersion: 2.12.10, sbtVersion: 1.3.2
circuit SimpleSystem : 
  module SimpleAdder : 
    input clock : Clock
    input reset : Reset
    output io : {flip inputx : UInt<32>, flip inputy : UInt<32>, output : UInt<32>}
    
    node _T = add(io.inputx, io.inputy) @[simple.scala 11:26]
    node _T_1 = tail(_T, 1) @[simple.scala 11:26]
    io.output <= _T_1 @[simple.scala 11:13]
    
  module SimpleAdder_1 : 
    input clock : Clock
    input reset : Reset
    output io : {flip inputx : UInt<32>, flip inputy : UInt<32>, output : UInt<32>}
    
    node _T = add(io.inputx, io.inputy) @[simple.scala 11:26]
    node _T_1 = tail(_T, 1) @[simple.scala 11:26]
    io.output <= _T_1 @[simple.scala 11:13]
    
  module SimpleSystem : 
    input clock : Clock
    input reset : UInt<1>
    output io : {success : UInt<1>}
    
    inst adder1 of SimpleAdder @[simple.scala 17:22]
    adder1.clock <= clock
    adder1.reset <= reset
    inst adder2 of SimpleAdder_1 @[simple.scala 18:22]
    adder2.clock <= clock
    adder2.reset <= reset
    reg reg1 : UInt<32>, clock with : (reset => (reset, UInt<32>("h00"))) @[simple.scala 19:21]
    reg reg2 : UInt<32>, clock with : (reset => (reset, UInt<32>("h01"))) @[simple.scala 20:21]
    adder1.io.inputx <= reg1 @[simple.scala 22:20]
    adder1.io.inputy <= reg2 @[simple.scala 23:20]
    reg1 <= adder1.io.output @[simple.scala 24:8]
    adder2.io.inputx <= adder1.io.output @[simple.scala 26:20]
    adder2.io.inputy <= UInt<32>("h03") @[simple.scala 27:20]
    node _T = eq(adder2.io.output, UInt<8>("h080")) @[simple.scala 28:26]
    when _T : @[simple.scala 28:37]
      io.success <= UInt<1>("h01") @[simple.scala 29:16]
      skip @[simple.scala 28:37]
    else : @[simple.scala 30:16]
      io.success <= UInt<1>("h00") @[simple.scala 31:16]
      skip @[simple.scala 30:16]
    node _T_1 = bits(reset, 0, 0) @[simple.scala 33:9]
    node _T_2 = eq(_T_1, UInt<1>("h00")) @[simple.scala 33:9]
    when _T_2 : @[simple.scala 33:9]
      printf(clock, UInt<1>(1), "reg1: %d, reg2: %d, success: %d\n", reg1, reg2, io.success) @[simple.scala 33:9]
      skip @[simple.scala 33:9]
    
