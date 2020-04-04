class Net {
  constructor(netObject) {
      this.alpha = netObject.alpha
      this.input = netObject.input
      this.output = netObject.output

      // if (this.input.length != this.output.length)
      //   this.error(`input and output length varies`);

      // if (netObject.inputNodes != netObject.inputNodesShape.length) {
      //   this.print(`detecting different input node number than shapes`)
      //   process.exit(1)
      //   this.print(`generating ${netObject.inputNodes - netObject.inputNodesShape.length} input nodes`)
      //   // TODO: input node generation
      // }

      let id = 0

      this.inputNodes = netObject.inputNodesShape.map( f => ({
        id: (id += 1),
        type: 'input',
        f: f
      }))

      this.layerNodes = netObject.layerNodesShape.map( f => ({
        id: (id += 1),
        type: 'layer',
        f: f,
        weights: new Array(this.inputNodes.length + 1).fill(0).map(Math.random)
      }))

      this.outputNodes = netObject.outputNodesShape.map( f => ({
        id: (id += 1),
        type: 'output',
        f: f,
        weights: new Array(this.layerNodes.length + 1).fill(0).map(Math.random)
      }))

      this.nodes = this.inputNodes.concat(this.layerNodes).concat(this.outputNodes)
      this.res = []
  }

  runInput(input) {
    this.inputNodes.forEach( ({id, type, f}) => {
      this.res.push({
        id: `${id}`,
        type: type,
        res: f(input)
      })
    })

    // this.print(this.res)
  }

  runLayer() {
    // this.res.forEach( e => {
      this.layerNodes.forEach( ({id, type, f, weights}) => {
        this.res.push({
          id: `${id}`,
          type: type,
          res: f([1, ...this.res.filter(({type}) => type == 'input').map(e => e.res)], weights)
        })
      })
    // })
  }

  runOutput() {
    // this.res.filter(e => e.type == 'layer').forEach(e => {
      this.outputNodes.forEach(({id, type, f, weights}) => {
        this.res.push({
          id: `${id}`,
          type: type,
          res: f([1, ...this.res.filter(({type}) => type == 'layer').map(e => e.res)], weights)
        })
      })
    // })
  }

  runForward(input) {
    this.res = []

    this.runInput(input)
    this.runLayer()
    this.runOutput()
  }

  runBackward(y) {
    // console.log(y)
    // console.log(this.res.filter(e => e.type == 'output').map((e,i) => e.res - y[i]))
    // this.res.filter(e => e.type == 'output').forEach( e => console.log(e))
    // console.dir(this, {depth: null})

    this.res.filter(e => e.type == 'output').forEach( ({id, res}, i) => {
      let path = id.split('.').map(Number)
      let output_res = res

      // console.log(output_res, y[i])
      let output_error = output_res - y[i]
      let outputNode = this.nodes.find( e => e.id == id )
      // console.log(outputNode);
      let outputWeight = outputNode.weights.slice(1)

      this.res.filter(e => e.type == 'layer').forEach( ({id, res}, i) => {
        let layer_res = res
        let layerNode = this.nodes.find( e => e.id == id )
        let layer_error = outputWeight[i] * output_error// outputNode.weights.map(w => w * output_error).reduce( (p,e) => p + e, 0)

        // console.log("layer_error", layer_error)

        // layer_error.forEach(layer_error => {
          let layer_pd = this.res.filter(e => e.type == 'input').map(e => {
            // console.log(-this.alpha , layer_res , (1 - layer_res) , layer_error , e.res)
            return -this.alpha * layer_res * (1 - layer_res) * layer_error * e.res
          })
          // console.log(layer_pd.reduce( (p,e) => p + e, 0) / layer_pd.length < Math.EPSILON)

          let bias_weights = layerNode.weights.shift()
          layerNode.weights = [bias_weights, ...layerNode.weights.map((w, i) => w + layer_pd[i])]
        // })

      })
      let output_pd = this.res.filter(e => e.type == 'layer').map(e => {
        // console.log(output_error, e.res)
        return -this.alpha * output_res * (1 - output_res) * output_error * e.res
        // return e.res * output_error
      })
      let bias_weights = outputNode.weights.shift()
      outputNode.weights = [bias_weights, ...outputNode.weights.map((e, i) => e + output_pd[i])]

      // console.log(output_pd.reduce( (p,e) => p * e, 1) < Math.EPSILON)
      if (output_pd.reduce( (p,e) => p * e, 1) < 0.0001)
      {
        this.end = true
      }
    })
  }

  run(iter) {
    var hrstart = process.hrtime()
    this.end = false

    for (var i = 0; i < (iter || 1) && this.end != true; i++) {
      this.input.forEach( (e, i) => {
        this.runForward(e)
        this.runBackward( this.output[i] )
      })
      if (i % (iter / 10) == 0)
        process.stdout.write('.')
    }

    var hrend = process.hrtime(hrstart)
    console.info('Execution time (hr): %ds %dms', hrend[0], hrend[1] / 1000000)
    console.info('Iteration log: %d', i)
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

      this.runForward(ask)

      let res = this.res.filter(e => e.type == 'output').map(e =>
        round_to_precision(e.res, 0.01)
      )
      let _res = res.map(e => Math.round(e))

      let trained = this.input.find( e => JSON.stringify(e)==JSON.stringify(ask))
      let trainedI = this.input.indexOf( trained )
      let output = this.output[trainedI]

      let isok = trainedI != -1 ? _res.join('') == output.join('') : _res.join('') == ("0011" + ask.join(''))

      // console.log( '\t' + line + " -> " + res.join(' | ') )
      // console.log('\t\t\t\t' + res.map(e => String(e).padEnd(5)).join(' | ') )
      console.log('\t' + ask + " -> " + _res.join('') + `\t ${trained ? "true" : "false"} : ${isok}` )
      // console.log(`[ ${ask} -> ${ parseInt(_res.join(''), 2)} ]`)

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
