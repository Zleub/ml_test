class Net {
  constructor(netObject) {
      this.alpha = netObject.alpha
      this.input = netObject.input
      this.output = netObject.output

      // if (this.input.length != this.output.length)
      //   this.error(`input and output length varies`);

      if (netObject.inputNodes != netObject.inputNodesShape.length) {
        this.print(`detecting different input node number than shapes`)
        process.exit(1)
        this.print(`generating ${netObject.inputNodes - netObject.inputNodesShape.length} input nodes`)
        // TODO: input node generation
      }

      let id = 0

      this.inputNodes = netObject.inputNodesShape.map( f => ({
        id: (id += 1),
        type: 'input',
        f: x => [1, ...f(x)]
      }))

      this.layerNodes = netObject.layerNodesShape.map( f => ({
        id: (id += 1),
        type: 'layer',
        f: (x, w) => [1, f(x, w)],
        weights: new Array(netObject.inputLength + 1).fill(0).map(Math.random)
      }))

      this.outputNodes = netObject.outputNodesShape.map( f => ({
        id: (id += 1),
        type: 'output',
        f: (x, w) => f(x, w),
        weights: new Array(2).fill(0).map(Math.random)
      }))

      this.nodes = this.inputNodes.concat(this.layerNodes).concat(this.outputNodes)
      this.res = []
  }

  runInput(input) {
    input.forEach( (e, i) => {
      this.inputNodes.forEach( ({id, type, f}) => {
        this.res.push({
          id: `${i}.${id}`,
          type: type,
          res: f(e)
        })
      })
    })

    // this.print(this.res)
  }

  runLayer() {
    this.res.forEach( e => {
      this.layerNodes.forEach( ({id, type, f, weights}) => {
        this.res.push({
          id: `${e.id}.${id}`,
          type: type,
          res: f(e.res, weights)
        })
      })
    })
  }

  runOutput() {
    this.res.filter(e => e.type == 'layer').forEach(e => {
      this.outputNodes.forEach(({id, type, f, weights}) => {
        this.res.push({
          id: `${e.id}.${id}`,
          type: type,
          res: f(e.res, weights)
        })
      })
    })
  }

  runForward(input) {
    this.res = []

    this.runInput(input)
    this.runLayer()
    this.runOutput()
  }

  runBackward() {
    this.res.filter(e => e.type == 'output').forEach( ({id, res}) => {
      let path = id.split('.').map(Number)

      let output_error = res - this.output[path[0]]
      let outputId = path.pop()
      let outputNode = this.nodes.find( ({id}) => id == outputId )

      let layer_res = this.res.find(e => e.id == path.join('.'))
      let layerId = path.pop()
      let layerNode = this.nodes.find( ({id}) => id == layerId )
      let layer_error = layer_res.res[1] * (1 - layer_res.res[1]) * dot([outputNode.weights[1]], [output_error])

      let input_res = this.res.find(e => e.id == path.join('.'))
      let inputId = path.pop()
      let inputNode = this.nodes.find( ({id}) => id == inputId )

      let layer_pd = input_res.res.map(e => e * layer_error)
      let output_pd = layer_res.res.map(e => e * output_error)

      layerNode.weights = layerNode.weights.map((e, i) => e + (-this.alpha * layer_pd[i]))
      outputNode.weights = outputNode.weights.map((e, i) => e + (-this.alpha * output_pd[i]))
    })
  }

  run(iter) {
    var hrstart = process.hrtime()

    for (var i = 0; i < (iter || 1); i++) {
      this.runForward(this.input)
      this.runBackward()
    }

    var hrend = process.hrtime(hrstart)
    console.info('Execution time (hr): %ds %dms', hrend[0], hrend[1] / 1000000)
  }

  ask() {
    const readline = require('readline');
    const rl = readline.createInterface({
      input: process.stdin,
      output: process.stdout,
      prompt: 'net > '
    });

    function round_to_precision(x, precision) {
      let n = 1 / precision
      return Math.round((x + Number.EPSILON) * n) / n
    }

    rl.prompt();
    rl.on('line', (line) => {
        let ask = eval(line)
        this.runForward([ask])
        console.log(line + " -> " + this.res.filter(e => e.type == 'output').map(e =>
          // e.res
          // isNaN(e.res) ? e.res :
          round_to_precision(e.res, 0.01)
        )
        .join(' | ')
        // .reduce( (p,e) => p * e, 1)
      )

      rl.prompt();
    }).on('close', () => {
      process.exit(0);
    });
  }

  print(s) { console.log(`Net: `, s) }
  warn(s) { console.warn(`Net: `, s) }
  error(s) {
    console.error(`Net: `, s)
    process.exit(-1);
  }
}

module.exports = Net;
