mult = (a, b) => {
  console.log(a, b)
  let row = (a, i) => a[i]
  let col = (a, i) => a.map( e => e[i])

  let res = []
  for (var i = 0; i < a.length; i++) {
    let tmp = []
    for (var j = 0; j < b.length; j++) {
      tmp.push( dot( a[i], b[i] ) )
    }
    res.push(tmp)
  }
  console.log(res)
  return res
}

input = [
  [ 1, 1 ]
]
output = [ 1 ]

inputNodes = [
  x => [1, ...x]
]


layerWeight = [ // as many as input + bias
  [-0.16595599, 0.44064899, -0.99977125]
]

layerNodes = [
  // x => [1, sigmoid( mult(inputNodes.map(e => e(x)), layerWeight) )]
  x => [1, sigmoid( dot(inputNodes.map(e => e(x))[0], layerWeight[0]) )]
]

outputWeight = [
  [-0.39533485, -0.70648822]
]

outputNode = [
  x => mult( layerNodes.map(e => e(x)), outputWeight )
]

alpha = 0.1
iter = 1

// for (var a = 0; a < iter; a++) {
//   for (var i = 0; i < input.length; i++) {
//     input_output = inputNodes[0](input[i])
//     // console.log(`input output ${input_output}`)
//     layer_output = layerNodes[0](input[i])
//     // console.log(`layer output ${layer_output}`)
//     out = outputNode[0](input[i])
//     // console.log(`running input[${i}] as ${input[i]} => ${out}`)
//
//     output_error = out - output[i]
//     // console.log(`output_error ${output_error}`)
    layer_error = layer_output[1] * (1 - layer_output[1]) * dot([outputWeight[0][1]], [output_error])
//     // console.log(`layer_error ${layer_error}`)
//     // console.log( mult(inputNodes.map(e => e(input[0])), layerWeight) )
//
//     hidden_pd = input_output.map(e => e * layer_error)
//     output_pd = layer_output.map(e => e * output_error)
//
//     // console.log(`hidden_pd ${hidden_pd}`)
//     // console.log(`output_pd ${output_pd}`)
//
//     layerWeight[0] = layerWeight[0].map((e, i) => e + (-alpha * hidden_pd[i]))
//     outputWeight[0] = outputWeight[0].map((e,i) => e + (-alpha * output_pd[i]))
//     // console.log(layerWeight[0])
//
//   }
// }

  //   console.log(out)
  //
  // console.log( outputNode[0]([0, 0]) )
// console.log( mult([[1, 2]], [[3, 4]] ) )
