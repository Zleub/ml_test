let r = []

for (var i = 0; i < 16; i++) {
  let _ = [
    // i >> 7 & 1,
    // i >> 6 & 1,
    // i >> 5 & 1,
    // i >> 4 & 1,
    i >> 3 & 1,
    i >> 2 & 1,
    i >> 1 & 1,
    i & 1
  ]
  // console.log(_.join(''), parseInt(_.join(''), 2))
  // console.log(_)
  r.push(_)
}

console.log(r)
