#let box(content) = {
  align(center, block(
    width: 85%,
    inset: 10pt,
    stroke: 1pt + rgb(0, 100, 200),
    fill: rgb(240, 248, 255),
    radius: 8pt,
  )[
    #set align(left)
    #content
  ])
}

#let secth(content) = [
  #set text(size: 1.1em)
  \
  *#content*
  \
]
