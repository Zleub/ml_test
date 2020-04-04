let Net = require('./ml_net')

sigmoid = x => 1 / (1 + Math.exp(-x))
dot = (a, b) => {
  if (a.length != b.length) {
    console.error(`dot error, not same len, a is ${a.length} and b is ${b.length}`)
    console.error(`a: ${a}, b: ${b}`)
  } else
    return a.map( (e,i) => a[i] * b[i]).reduce( (p,e) => p + e, 0)
}

net = new Net({
  alpha: 0.1,

  // inputLength: 1,
  input: [
    // [0, 0, 0, 0],
    [0, 0, 0, 1],
    [0, 0, 1, 0],
    [0, 0, 1, 1],
    [0, 1, 0, 0],
    [0, 1, 0, 1],
    [0, 1, 1, 0],
    [0, 1, 1, 1],
    [1, 0, 0, 0],
    [1, 0, 0, 1],
  ],

  output: [
    // [0, 0, 1, 1, 0, 0, 0, 0],
    [0, 0, 1, 1, 0, 0, 0, 1],
    [0, 0, 1, 1, 0, 0, 1, 0],
    [0, 0, 1, 1, 0, 0, 1, 1],
    [0, 0, 1, 1, 0, 1, 0, 0],
    [0, 0, 1, 1, 0, 1, 0, 1],
    [0, 0, 1, 1, 0, 1, 1, 0],
    [0, 0, 1, 1, 0, 1, 1, 1],
    [0, 0, 1, 1, 1, 0, 0, 0],
    [0, 0, 1, 1, 1, 0, 0, 1],
 ],

  // inputNodes: 4,
  inputNodesShape: [
    // x => x,
    x => x[0],
    x => x[0],
    x => x[0],
    x => x[0],
    x => x[1],
    x => x[1],
    x => x[1],
    x => x[2],
    x => x[2],
    x => x[3],
    // x => x.reverse().map( (e, i) => 1 / ((e + 1) * (i + 1)) )
  ],

  layerNodesShape: [
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),

    // (input, weights) => sigmoid( dot(input, weights) ),
    // (input, weights) => sigmoid( dot(input, weights) ),
    // (input, weights) => sigmoid( dot(input, weights) ),
    // (input, weights) => sigmoid( dot(input, weights) ),
    // (input, weights) => sigmoid( dot(input, weights) ),
    // (input, weights) => sigmoid( dot(input, weights) ),
    // (input, weights) => sigmoid( dot(input, weights) ),
    // (input, weights) => sigmoid( dot(input, weights) ),
    // (input, weights) => sigmoid( dot(input, weights) ),
    // (input, weights) => sigmoid( dot(input, weights) ),
  ],

  outputNodesShape: [
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
    (input, weights) => sigmoid( dot(input, weights) ),
  ]

})

// console.dir(net, { depth: null })
net.run(10000)
net.ask()
// console.dir(net, { depth: null })
