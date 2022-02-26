circuit SimpleSystem :
  module SimpleAdder :
    input clock : Clock
    input reset : UInt<1>
    input io_inputx : UInt<32>
    input io_inputy : UInt<32>
    output io_output : UInt<32>
  
    node _T = add(io_inputx, io_inputy) @[simple.scala 11:26]
    node _T_1 = tail(_T, 1) @[simple.scala 11:26]
    io_output <= _T_1 @[simple.scala 11:13]

  module SimpleSystem :
    input clock : Clock
    input reset : UInt<1>
    output io_success : UInt<1>
  
    inst adder1 of SimpleAdder @[simple.scala 17:22]
    inst adder2 of SimpleAdder @[simple.scala 18:22]
    reg reg1 : UInt<32>, clock with :
      reset => (UInt<1>("h0"), reg1) @[simple.scala 19:21]
    reg reg2 : UInt<32>, clock with :
      reset => (UInt<1>("h0"), reg2) @[simple.scala 20:21]
    node _T = eq(adder2.io_output, UInt<8>("h80")) @[simple.scala 28:26]
    node _GEN_0 = mux(_T, UInt<1>("h1"), UInt<1>("h0")) @[simple.scala 28:37]
    node _T_1 = bits(reset, 0, 0) @[simple.scala 33:9]
    node _T_2 = eq(_T_1, UInt<1>("h0")) @[simple.scala 33:9]
    io_success <= _GEN_0 @[simple.scala 29:16 simple.scala 31:16]
    adder1.clock <= clock
    adder1.reset <= reset
    adder1.io_inputx <= reg1 @[simple.scala 22:20]
    adder1.io_inputy <= reg2 @[simple.scala 23:20]
    adder2.clock <= clock
    adder2.reset <= reset
    adder2.io_inputx <= adder1.io_output @[simple.scala 26:20]
    adder2.io_inputy <= UInt<32>("h3") @[simple.scala 27:20]
    reg1 <= mux(reset, UInt<32>("h0"), adder1.io_output) @[simple.scala 24:8]
    reg2 <= mux(reset, UInt<32>("h1"), reg2)
    printf(clock, and(and(UInt<1>("h1"), _T_2), UInt<1>("h1")), "reg1: %d, reg2: %d, success: %d\n", reg1, reg2, io_success) @[simple.scala 33:9]
